/******************************************************************
 *       File Name: main.c
 *     Description: 
 *          Author: He Xiwen
 *           Email: hexiwen2000@163.com 
 *    Created Time: 2015-11-17 15:19:05
 *   Modified Time: 
 *          License: 
 *****************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#ifdef _OPENMP
#include <omp.h>
#else
#include "my_single_omp.h"
#endif

#include "my_seq_ops.h"
#include "my_string.h"
#include "my_data.h"
#include "do_one_file.h"


int main(int argc, const char *argv[])
{
  int i;
  // 文件与文件夹访问的变量
  DIR *dir;
  struct dirent *fi;
  struct stat st;
  const char *input_f_d;
  const char *output_f;
  const char *tmp_dir = "./sort-tmp/";
  const char *rm_tmp_dir = "rm -rf ./sort-tmp";
  int ilen, olen;
  char *ifpath;
  char *ofpath; // no use;
  char *line;
  int file_cnt;
  int thread_cnt;
  // 缓存
  MyString ms;
  MyStringArr *msa_arr = NULL;
  MyStringArr *merge_msa_arr = NULL;
  // 时间间隔
  time_t time_start, time_end;
  clock_t clock_start, clock_end;
  clock_t c_start, c_end;
  clock_t clock_single_merge;
  int res;

  time_start = time(NULL);
  clock_start = clock();
  clock_single_read = 0;
  clock_single_write = 0;
  clock_parallel = 0;
  walltime_parallel = 0;
  clock_single_merge = 0;
  my_seq_ops_init();

  // 参数处理
#ifdef _OPENMP
  // usage: exe input_f_d output_f thread_cnt
  if (argc != 4)
#else
  // usage: exe input_f_d output_f
  if (argc != 3)
#endif
  {
    if(argc != 1) fprintf(stderr, "Wrong arguments!\n");
#ifdef _OPENMP
    printf("Usage: %s input_f_d output_f thread_cnt\n", argv[0]);
#else
    printf("Usage: %s input_f_d output_f\n", argv[0]);
#endif
    printf( "\tNote: all input files will be merged to output_f.\n" );
    if( argc==1 ) exit(EXIT_SUCCESS);
    else exit( EXIT_FAILURE );
  }
#ifdef DEBUG_TEST
  printf("argc: %d\n", argc);
  printf("argv: ");
  for (i = 0; i < argc; ++i) printf("%s ", argv[i]);
  printf("\n");
#endif

#ifdef _OPENMP
  thread_cnt = atoi( argv[3] );
  omp_set_num_threads( thread_cnt );
#pragma omp parallel for
  for( i=0; i<10; ++i ){
    if( 0==i ) printf( "multi-thread_cnt: %d\n", omp_get_num_threads() );
  }
#else
  thread_cnt = omp_get_num_threads();
  printf( "single-thread_cnt: %d\n", thread_cnt );
#endif

  conMyString( &ms );
  //conMyStringArr( &msa );
  msa_arr = (MyStringArr *) malloc( sizeof(MyStringArr) * thread_cnt );
  for( i=0; i<thread_cnt; ++i ) {
    conMyStringArr( msa_arr + i );
  }
  merge_msa_arr = (MyStringArr *) malloc( sizeof(MyStringArr) * thread_cnt );
  for( i=0; i<thread_cnt; ++i ) {
    conMyStringArr( merge_msa_arr + i );
  }

  // clear tmp_dir
  if( stat( tmp_dir, &st ) < 0 ) {
    // not exist;
    printf( "make sort temp dir.\n" );
    res = mkdir( tmp_dir, S_IRWXU );
    if( res != 0 ) perror( "mkdir tmp_dir" );
  } else {
    printf( "remove sort temp dir and then recreate it.\n" );
    //res = remove( tmp_dir ); // tmp_dir must be empty;
    //if( res != 0 ) perror( "remove tmp_dir" );
    system( rm_tmp_dir );
    res = mkdir( tmp_dir, S_IRWXU );
    if( res != 0 ) perror( "mkdir tmp_dir" );
  }

  input_f_d = argv[1];
  output_f = argv[2];

  line = (char *) malloc(sizeof(char) * (MY_LINE_MAX + 1));
  line[MY_LINE_MAX] = 0;

  ilen = strlen(input_f_d);
  ilen += MY_FILENAME_MAX + 1;
  ifpath = (char *) malloc(sizeof(char) * ilen);
  ifpath[0] = 0;

  olen = strlen(tmp_dir);
  olen += MY_FILENAME_MAX + 1;
  ofpath = (char *) malloc(sizeof(char) * olen);
  ofpath[0] = 0;

  // memory sort;
  file_cnt = 0;
  if (stat(input_f_d, &st) < 0) {
    // not exist;
    perror("Cannot access input_file_or_dir");
    exit(EXIT_FAILURE);
  }
  if (S_ISDIR(st.st_mode)) {
    // input_f_d: input_d
    printf("process dir.\n");

    if ((dir = opendir(input_f_d)) == NULL) {
      perror("Cannot open input_f_d");
      exit(EXIT_FAILURE);
    }

    while ((fi = readdir(dir)) != NULL) {
      snprintf(ifpath, ilen, "%s/%s", input_f_d,
         fi->d_name);
      if (fi->d_name[0] == '.') {
        // ignore: hidden file, or pwd, or parent dir of pwd;
        continue;
      }
      if (stat(ifpath, &st) < 0) {
        // not exist
        continue;
      }
      if (S_ISDIR(st.st_mode)) {
        // ignore: child dir
        continue;
      }
#ifdef DEBUG_TEST
      //printf( "ifpath: %s\n", ifpath );
#endif
      if (S_ISREG(st.st_mode)) {
        // 单文件处理
        snprintf( ofpath, olen, "%s/%s", tmp_dir, fi->d_name );
        file_cnt = do_one_file( ifpath, tmp_dir, line, msa_arr, merge_msa_arr, thread_cnt, &ms, file_cnt );
      }

    }
    closedir(dir);

  } else if (S_ISREG(st.st_mode)) {
    // 单文件处理
    // input_f_d: input_f
    printf("process file.\n");

    snprintf( ifpath, ilen, "%s", input_f_d );
    snprintf( ofpath, olen, "%s", tmp_dir );
    file_cnt = do_one_file( ifpath, tmp_dir, line, msa_arr, merge_msa_arr, thread_cnt, &ms, file_cnt );
  }

  //desMyStringArr( &msa );
  for( i=0; i<thread_cnt; ++i ) desMyStringArr( msa_arr+i );
  free( msa_arr );
  for( i=0; i<thread_cnt; ++i ) desMyStringArr( merge_msa_arr+i );
  free( merge_msa_arr );

  // 多路归并
  // merge sort;
  c_start = clock();
  do_merge_sort( tmp_dir, output_f, line, &ms );
  c_end = clock();
  clock_single_merge += c_end - c_start;

  free(ifpath);
  free(ofpath);
  free(line);
  desMyString( &ms );
  my_seq_ops_end();

  time_end = time(NULL);
  clock_end = clock();
  printf( "time: %ld\n", time_end-time_start );
  printf( "clock: %lf\n", (clock_end-clock_start)/(1.0*CLOCKS_PER_SEC) );
  printf( "clock_single_read: %lf\n", (clock_single_read)/(1.0*CLOCKS_PER_SEC) );
  printf( "clock_single_write: %lf\n", (clock_single_write)/(1.0*CLOCKS_PER_SEC) );
  printf( "clock: parallel part:  total of threads:%lf  wall time:%lf\n", (clock_parallel)/(1.0*CLOCKS_PER_SEC), walltime_parallel );
  printf( "clock_single_merge: %lf\n", (clock_single_merge)/(1.0*CLOCKS_PER_SEC) );
printf("sort finish\n");
  return 0;
}

