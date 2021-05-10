/******************************************************************
 *       File Name: do_one_file.c
 *     Description: 
 *          Author: He Xiwen
 *           Email: hexiwen2000@163.com 
 *    Created Time: 2015-11-23 17:27:24
 *   Modified Time: 
 *          License: 
 *****************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#ifdef _OPENMP
#include <omp.h>
#else
#include "my_single_omp.h"
#endif

#include "my_seq_ops.h"
#include "my_string.h"
#include "my_data.h"
#include "sort.h"
#include "do_one_file.h"


clock_t clock_single_read;
clock_t clock_single_write;
clock_t clock_parallel;
double walltime_parallel;


static size_t single_read_msa_arr( FILE *ifp, char *line, MyStringArr *msa_arr, int arr_size, MyString *ms, int *lineno );
static size_t merge_write_msa_arr( const char *ofpath, MyStringArr *msa_arr, int arr_size );
static size_t single_read_block( FILE *ifp, size_t read_block_size, int linecnt_max, char *line, MyStringArr *msa, MyString *ms, int *lineno );
//static size_t single_write_block( FILE *ofp, MyStringArr *msa );
static void sort_one_msa( MyStringArr *msa, MyStringArr *merge_msa );
static void for_parallel( MyStringArr *msa, MyStringArr *merge_msa );
static size_t read_one_line_to_msa( FILE *ifp, char *line, MyStringArr *msa, MyString *ms, int *line_no );
static size_t read_one_line( FILE *ifp, char *line, MyString *ms, int *line_no );

// 读入输入文件ifpath，每次读取一定大小的ifpath中的数据，排序后输出到文件夹output_d里的临时文件中，临时文件有file_cnt标识，file_cnt在每写入一个文件后自增，line、msa_arr、ms是缓存，thread_cnt是线程数，也是msa_arr数组的大小。
// ifpath: input file path;
// output_d: output dir;
// ms:  my string( one line in file is one string );
// msa: ms array;
// msa_arr: msa array;
// thread_cnt: num of threads;
// memory sort;
int do_one_file( const char *ifpath, const char *output_d, char *line, MyStringArr *msa_arr, MyStringArr *merge_msa_arr, int thread_cnt, MyString *ms, int file_cnt )
{
  int i;
  FILE *ifp; // 输入文件
  int olen;
  char *ofpath; // 输出文件路径
  size_t one_readed_size;
  size_t readed_size; // 读入数据大小
  size_t writed_size; // 写入数据大小
  int lineno; // 当前行号
  int lineno_old;
  clock_t t_start, t_end; // 时间统计
  struct timespec ts_b, ts_e;

#ifdef DEBUG_TEST
  printf( "now to file: %s\n", ifpath );
#endif

  // 输入输出文件
  ifp = fopen(ifpath, "r");
  if (ifp == NULL) {
    perror("Cannot open input file");
    exit(EXIT_FAILURE);
  }
  olen = strlen( output_d );
  olen += MY_FILENAME_MAX + 2;
  ofpath = (char *) malloc( sizeof(char) * olen );
  if( ofpath == NULL ) {
    perror("malloc(): failure");
    fclose( ifp );
    return file_cnt;
  }
  readed_size = 0;
  lineno = 0;
  writed_size = 0;

  while( !feof( ifp ) ){
    lineno_old = lineno;
    t_start = clock(); 
    // 从输入文件ifp中读取n行到thread_cnt个缓存msa_arr[thread_cnt]中。line、ms是缓存。lineno是当前行号。thread_cnt为线程数。msa_arr是thread_cnt个msa，一个msa是很多行的数组。这样，每个线程操作一个 行的集合。
    one_readed_size = single_read_msa_arr( ifp, line, msa_arr, thread_cnt, ms, &lineno );
    t_end = clock();
    clock_single_read += t_end - t_start;
    // 累加读取的大小。
    readed_size += one_readed_size;
#ifdef DEBUG_TEST
    printf( "one msa_arr:  size:%ld  line:%d\n", one_readed_size, lineno-lineno_old );
#endif
    t_start = clock(); 
    clock_gettime( CLOCK_MONOTONIC, &ts_b );
#ifdef _OPENMP
#pragma omp parallel for
#endif
    for( i=0; i<thread_cnt; ++i ){
#ifdef DEBUG_TEST
      //if( 0==i ) printf( "thread_cnt: %d\n", omp_get_num_threads() );
#endif
       // 每个线程处理一个 数据行的集合。
       for_parallel( msa_arr + i, merge_msa_arr + i );
       // 每个 数据行的集合 msa 都是排序好的了。
    }
    // 时间统计
    t_end = clock();
    clock_gettime( CLOCK_MONOTONIC, &ts_e );
    clock_parallel += t_end - t_start;
    walltime_parallel += (ts_e.tv_sec - ts_b.tv_sec) + (ts_e.tv_nsec - ts_b.tv_nsec)/(1000000000.0);
    //printf( "parallel part time: %ld\n", t_end-t_start );
    // 输出文件路径，临时文件夹下的临时文件。
    sprintf( ofpath, "%s/tmp-%04d", output_d, file_cnt );
    t_start = clock(); 
    // 单线程多路归并。输出文件路径 ofpath，msa_arr 是 thread_cnt 个已排好序的 数据行的集合 msa。将多个msa进行多路归并，输出到临时文件ofpath中。
    writed_size += merge_write_msa_arr( ofpath, msa_arr, thread_cnt );
    t_end = clock();
    clock_single_write += t_end - t_start;
    // 临时文件号自增。
    ++ file_cnt;
  }

  free( ofpath );
  fclose(ifp);
  return file_cnt;
}


// 单线程读
static size_t single_read_msa_arr( FILE *ifp, char *line, MyStringArr *msa_arr, int arr_size, MyString *ms, int *lineno )
{
  size_t readed_size;
  int i;
  int one_block_size;
  int one_line_max;

  // 读的大小主要由FILE_CHUNK_SIZE决定。
  one_block_size = FILE_CHUNK_SIZE / arr_size;
  one_line_max = LINE_CNT_MAX;
  readed_size = 0;
  for( i=0; i<arr_size; ++i ) {
    readed_size += single_read_block( ifp, one_block_size, one_line_max, line, msa_arr+i, ms, lineno );
  }
  return readed_size;
}


// 内存数据多路归并，输出到文件。
static size_t merge_write_msa_arr( const char *ofpath, MyStringArr *msa_arr, int arr_size )
{
  int i;
  size_t writed_size;
  FILE *ofp;
  char *buf;
  int *w_cnt;
  int min_ms;

  ofp = fopen(ofpath, "w");
  if (ofp == NULL) {
    perror("Cannot open output file");
    exit(EXIT_FAILURE);
  }
  w_cnt = (int *) malloc( sizeof(int) * arr_size );
  if( w_cnt == NULL ) {
    perror( "malloc: failure" );
    exit( EXIT_FAILURE );
  }
  for( i=0; i<arr_size; ++i ) w_cnt[i] = 0;

  writed_size = 0;
  while( 1 ) {
    // init min_ms;
    for( i=0; i<arr_size; ++i ) {
      if( w_cnt[i] < msa_arr[i].size ) break;
    }
    if( i < arr_size ) min_ms = i;
    else break;
    ++ i;
    for( ; i<arr_size; ++i ) {
      if( w_cnt[i] >= msa_arr[i].size ) continue;
      // cmp
      if( cmpMyString( &(msa_arr[i].arr[ w_cnt[i] ]), &(msa_arr[min_ms].arr[ w_cnt[min_ms] ]) ) < 0 ) min_ms = i;
    }
    buf =  msa_arr[min_ms].arr[ w_cnt[min_ms] ].data;
    ++ w_cnt[min_ms];
    fprintf( ofp, "%s\n", buf );
    writed_size += strlen( buf ) + 1;
  }

  fclose( ofp );
  free( w_cnt );
  return writed_size;
}


static size_t single_read_block( FILE *ifp, size_t read_block_size, int linecnt_max, char *line, MyStringArr *msa, MyString *ms, int *lineno ){
  size_t readed_size;
  int linecnt;
  int ret = 0;

  readed_size = 0;
  linecnt = 0;
  clearMyStringArr( msa );
  clearMyString( ms );

  while (1) {
    if( feof( ifp ) ) break;
    if( readed_size > read_block_size ) break;
    if( linecnt > linecnt_max ) break;
    ret = read_one_line_to_msa( ifp, line, msa, ms, lineno );
    if( ret < 0 ) break; // eof;
    readed_size += ret;
    ++linecnt;
  }
  return readed_size;
}

/*
static size_t single_write_block( FILE *ofp, MyStringArr *msa ){
  int i;
  char *buf;
  size_t writed_size = 0;
  for( i=0; i<msa->size; ++i ){
    buf = (msa->arr[i]).data;
    fprintf( ofp, "%s\n", buf );
    writed_size += strlen( buf ) + 1;
  }
  return writed_size;
}
*/

static void sort_one_msa( MyStringArr *msa, MyStringArr *merge_msa ){
  //printf("sort: qsort\n");
  //sortMyStringArr( msa );
  //printf("sort: merge sort\n");
  mergeSortMyStringArr( msa, merge_msa );
}


// 单个线程只处理一个msa。
static void for_parallel( MyStringArr *msa, MyStringArr *merge_msa ){
  sort_one_msa( msa, merge_msa );
}


static size_t read_one_line_to_msa( FILE *ifp, char *line, MyStringArr *msa, MyString *ms, int *line_no )
{
  size_t ret = 0;
  int line_no_old = *line_no;

  if( feof( ifp ) ) return -1; // eof;
  ret = read_one_line( ifp, line, ms, line_no );
  if( line_no_old == *line_no ) return -1; // eof;
  pushMyStringArr( msa, ms );
  clearMyString( ms );
  return ret;
}


static size_t read_one_line( FILE *ifp, char *line, MyString *ms, int *line_no ) // ret: line len; ret!=0 <=> ms->data[0]!=0;
{
  char *s_res;
  const int line_size = MY_LINE_MAX + 1;
  int lline;
  size_t ret;

  clearMyString( ms );
  ret = 0;
  while( 1 )
  {
    s_res = fgets( line, line_size, ifp );
    if( s_res == NULL )
    {
      if( ms->data[0] != 0 )
      {
        // line in ms; // no eol for last line in file;
        printf( "no EOL for the last line in file!" );
        ++ (*line_no);
      }
      break; // eof;
    }
    lline = strlen( line );
    ret += lline;
    if( line[lline-1] == '\n' )
    {
      // eol;
      ++ (*line_no);
      //if( (*line_no) % 10000 == 0 ) printf( "reading: line_no:%d\n", *line_no );
      appendnMyString( ms, line, lline-1 );
      break;
    }
    else
    {
      appendnMyString( ms, line, lline );
    }
  }
  return ret;
}


// 单线程，多路归并，输入是所有的前述的临时文件，归并这些文件的行到单个输出文件。
// single-thread multi-way merge sort;
void do_merge_sort( const char *input_d, const char *output_f, char *line, MyString *ms ){
  MyStringArr msa_out_buf;
  MyStringArr msa_merge_buf;

  conMyStringArr( &msa_out_buf );
  conMyStringArr( &msa_merge_buf );

  merge_sort( input_d, output_f, line, &msa_out_buf, &msa_merge_buf, ms );

  desMyStringArr( &msa_out_buf );
  desMyStringArr( &msa_merge_buf );
}


