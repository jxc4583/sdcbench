/*********************************************************************
 *       File Name: my_string.c
 *     Description: to implement functions in my_string.h
 *          Author: He Xiwen
 *           Email: hexiwen2000@163.com 
 *    Created Time: 2015-09-23 16:59:43
 *   Modified Time: 2015-09-23 17:00:16
 ********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#include "my_string.h"


static int expandMyStringArr( MyStringArr *s1 );
static int cmpMyStringForQsort( const void *p1, const void *p2 );


int conMyString( MyString *ms )
{
  ms->capacity = 4;
  ms->data = (char *)malloc( ms->capacity*sizeof(char) );
  if( ms->data == NULL ) return -1;
  ms->data[0] = 0;
  return 0;
}


int desMyString( MyString *ms )
{
  if( ms->data != NULL ) free( ms->data );
  ms->data = NULL;
  ms->capacity = 0;
  return 0;
}


int cpyMyString( MyString *ms1, MyString *ms2 ) // *ms1 = *ms2;
{
  //int i;
  int len;
  
  len = strlen( ms2->data );
  if( ms1->capacity <= len+1 )
  { // reallocate the space.
    ms1->capacity = len+2;
    if( ms1->data != NULL ) free( ms1->data );
    ms1->data = NULL;
    ms1->data = (char *)malloc( ms1->capacity*sizeof(char) );
    if( ms1->data == NULL ) return -1; 
  }
  else
  {
    // nothing
  }
  strncpy( ms1->data, ms2->data, ms1->capacity );
  return 0;
}


int cpyStrMyString( MyString *ms1, const char *str ) // *ms1 = str;
{
  //int i;
  int len;
  
  len = strlen( str );
  if( ms1->capacity <= len+1 )
  { // reallocate the space.
    ms1->capacity = len+2;
    if( ms1->data != NULL ) free( ms1->data );
    ms1->data = NULL;
    ms1->data = (char *)malloc( ms1->capacity*sizeof(char) );
    if( ms1->data == NULL ) return -1; 
  }
  else
  {
    // nothing
  }
  strncpy( ms1->data, str, ms1->capacity );
  return 0;
}


int cpynStrMyString( MyString *ms1, const char *str, int len ) // *ms1 = str;
{
  int i;
  //int len;
  
  //len = strlen( str );
  if( ms1->capacity <= len+1 )
  { // reallocate the space.
    ms1->capacity = len+2;
    if( ms1->data != NULL ) free( ms1->data );
    ms1->data = NULL;
    ms1->data = (char *)malloc( ms1->capacity*sizeof(char) );
    if( ms1->data == NULL ) return -1; 
  }
  else
  {
    // nothing
  }
  //strncpy( ms1->data, str, ms1->capacity );
  for( i=0; i<len; ++i )
  {
    if( str[i] == 0 ) break;
    ms1->data[i] = str[i];
  }
  ms1->data[i] = 0;
  return 0;
}


int clearMyString( MyString *ms )
{
  ms->data[0] = 0;
  return 0;
}


int cmpMyString( const MyString *ms1, const MyString *ms2 ) // compare;
{
  return strncmp( ms1->data, ms2->data, ( ms1->capacity < ms2->capacity ? ms2->capacity : ms1->capacity ) );
}


int appendMyString( MyString *ms, const char *str ) // *ms += str;
{
  //int i;
  int len_s;
  int len;
  char *old_str;

  len_s = strlen( ms->data );
  len = strlen( str );
  if( ms->capacity <= (len_s+len+1) )
  { // reallocate the space.
    ms->capacity = len_s+len+2;
    //if( ms->data != NULL ) free( ms->data );
    old_str = ms->data;
    ms->data = NULL;
    ms->data = (char *)malloc( ms->capacity*sizeof(char) );
    if( ms->data == NULL )
    {
      if( old_str != NULL ) free( old_str );
      return -1;
    }
    if( old_str != NULL )
    {
      strncpy( ms->data, old_str, ms->capacity );
      free( old_str );
    }
    strncpy( ms->data + len_s, str, ms->capacity - len_s );
  }
  else
  {
    strncpy( ms->data + len_s, str, ms->capacity - len_s );
  }
  return 0;
}


int appendnMyString( MyString *ms, const char *str, int len ) // *ms += str;
{
  //int i;
  int len_s;
  char *old_str;

  len_s = strlen( ms->data );
  if( ms->capacity <= (len_s+len+1) )
  { // reallocate the space.
    ms->capacity = len_s+len+2;
    //if( ms->data != NULL ) free( ms->data );
    old_str = ms->data;
    ms->data = NULL;
    ms->data = (char *)malloc( ms->capacity*sizeof(char) );
    if( ms->data == NULL )
    {
      if( old_str != NULL ) free( old_str );
      return -1;
    }
    if( old_str != NULL )
    {
      strncpy( ms->data, old_str, ms->capacity );
      free( old_str );
    }
    strncpy( ms->data + len_s, str, len );
    ms->data[len_s+len] = 0;
  }
  else
  {
    strncpy( ms->data + len_s, str, len );
    ms->data[len_s+len] = 0;
  }
  return 0;
}


//uint32_t findMyString( MyString *ms, char c ) // first one found;
//{
//  uint32_t i;
//  for( i=0; i<ms->capacity; ++i )
//  {
//    if( ms->data[i] == 0 ) break;
//    if( ms->data[i] == c ) return i;
//    //if( cmpMyString( s1->arr+i, ms ) == 0 ) return i;
//  }
//  return ms->capacity;
//}


int recapacityMyString( MyString *ms, uint32_t cap ){
  char *tmp;

  if( cap<=ms->capacity || cap<4 ) return -1;
  // recapacity; // maybe realloc() is better;
  tmp = (char *) malloc( cap * sizeof(char) );
  if( tmp == NULL ) return -1;
  strncpy( tmp, ms->data, cap );
  ms->capacity = cap;
  if( ms->data != NULL ) free( ms->data );
  ms->data = NULL;
  ms->data = tmp;
  return 0;
}


int conMyStringArr( MyStringArr *msa )
{
  uint32_t i;
  msa->size = 0; // msa: empty; need to conMyString();
  msa->capacity = 4;
  msa->arr = (MyString *)malloc( msa->capacity*sizeof(MyString) );
  if( msa->arr == NULL ) return -1;
  for( i=0; i<msa->capacity; ++i )
  {
    conMyString( msa->arr+i );
  }
  return 0;
}


int desMyStringArr( MyStringArr *msa )
{
  uint32_t i;
  //MyString *ms;
  if( msa->arr != NULL )
  {
    for( i=0; i<msa->capacity; ++i )
    {
      desMyString( msa->arr+i );
    }
    free( msa->arr );
  }
  msa->arr = NULL;
  msa->size = msa->capacity = 0;
  return 0;
}


int cpyMyStringArr( MyStringArr *s1, MyStringArr *s2 )
{
  int res;
  uint32_t i;
  if( s1->capacity <= s2->size+1 )
  { // reallocate the space.
    res = recapacityMyStringArr( s1, s2->size+2 );
    if( res < 0 ) return res;
    //desMyStringArr( s1 );
    s1->size = s2->size;
    //s1->capacity = s2->size+2;
    //s1->arr = (MyString *)malloc( s1->capacity*sizeof(MyString) );
    //if( s1->arr == NULL ) return -1; 
  }
  else
  {
    s1->size = s2->size;
  }
  for( i=0; i<s1->size; ++i )
  {
    //s1->arr[i] = s2->arr[i];
    cpyMyString( s1->arr+i, s2->arr+i );
  }
  return 0;
}


int clearMyStringArr( MyStringArr *msa )
{
  msa->size = 0;
  // not reallocate the space;
  //msa->capacity = 4;
  //if( msa->arr != NULL ) free( msa->arr );
  //msa->arr = (MyString*)malloc( sizeof(MyString)*4 );
  //if( msa->arr == NULL ) return -1;
  return 0;
}


MyString* getMyStringArr( MyStringArr *s1, uint32_t loc )
{
  if( loc >= s1->size ) return NULL;
  return &(s1->arr[loc]);
}


int pushMyStringArr( MyStringArr *s1, MyString *ms )
{
  expandMyStringArr( s1 );
  //return ( s1->arr[s1->size ++] = ms );
  return ( cpyMyString( s1->arr+( s1->size ++ ), ms ) );
}


int insertFirstMyStringArr( MyStringArr *s1, MyString *ms )
{
  uint32_t i;
  expandMyStringArr( s1 );
  if( s1->size > 0 )
  {
    for( i=s1->size; i>0; --i )
    {
      //s1->arr[i+1] = s1->arr[i];
      cpyMyString( s1->arr+i, s1->arr+(i-1) ); // actually it can be implement more efficient, just move pointer of MyString::data.
      // efficient way: (s1->arr+(i+1))->data=(s1->arr+i)->data; (s1->arr+(i+1))->capacity=(s1->arr+i)->capacity;
    }
    ++ s1->size;
  }
  //return ( s1->arr[0]=ms );
  return ( cpyMyString( s1->arr+0, ms ) );
}


int popMyStringArr( MyStringArr *s1 )
{
  if( s1->size <= 0 )return 0;
  -- s1->size;
  return 0;
  //return ( s1->arr[-- s1->size] );
}


int deleteFirstMyStringArr( MyStringArr *s1 )
{
  //MyString *ms;
  uint32_t i;
  if( s1->size <= 0 ) return 0;
  //ms = s1->arr+0;
  for( i=1; i<s1->size; ++i )
  {
    //s1->arr[i-1] = s1->arr[i];
    cpyMyString( s1->arr+(i-1), s1->arr+i ); // efficient way: just like what in insertFirstMyStringArr().
  }
  -- s1->size;
  //return ms;
  return 0;
}


static int expandMyStringArr( MyStringArr *s1 )
{
  uint32_t i;
  MyString *tmp;
  uint32_t size;
  uint32_t cap;

  if( s1->size <= s1->capacity-2 ) return 0;
  // need to expand. capacity=capacity*2;
  tmp = (MyString *)malloc( s1->capacity*2*sizeof(MyString) );
  if( tmp==NULL ) return -1;
  for( i=0; i<(s1->capacity*2); ++i )
  {
    conMyString( tmp+i );
  }
  for( i=0; i<s1->size; ++i )
  {
      //tmp[i] = s1->arr[i];
      cpyMyString( tmp+i, s1->arr+i );
  }
  size = s1->size;
  cap = s1->capacity;
  desMyStringArr( s1 );
  //free( s1->arr );
  s1->arr = tmp;
  s1->capacity = cap * 2;
  s1->size = size;
  return 0;
}


int recapacityMyStringArr( MyStringArr *s1, uint32_t cap )
{
  uint32_t i;
  MyString *tmp;
  uint32_t size;

  if( cap<s1->size || cap<4 ) return -1;
  // recapacity; // maybe realloc() is better;
  tmp = (MyString *)malloc( cap*sizeof(MyString) ); 
  if( tmp==NULL ) return -1;
  for( i=0; i<cap; ++i )
  {
    conMyString( tmp+i );
  }
  for( i=0; i<s1->size; ++i )
  {
      //tmp[i] = s1->arr[i];
      cpyMyString( tmp+i, s1->arr+i );
  }
  size = s1->size;
  //free( s1->arr );
  desMyStringArr( s1 );
  s1->arr = tmp;
  s1->capacity = cap;
  s1->size = size;
  return 0;
}


uint32_t findMyStringArr( MyStringArr *s1, MyString *ms ) // first one found;
{
  uint32_t i;
  for( i=0; i<s1->size; ++i )
  {
    //if( s1->arr[i] == ms ) return i;
    if( cmpMyString( s1->arr+i, ms ) == 0 ) return i;
  }
  return s1->size;
}


static int cmpMyStringForQsort( const void *p1, const void *p2 )
{
  return cmpMyString( (MyString *)p1, (MyString *)p2 );
}


int sortMyStringArr( MyStringArr *msa ) // sort; ascending order;
{
  // sort; stdlib.h::qsort();
  qsort( msa->arr, msa->size, sizeof( MyString ), cmpMyStringForQsort );
  return 0;
}


static void mergeMsa( MyStringArr *s_msa, MyStringArr *m_msa, int t, int m, int n )
{
  int i, j, k, p;
  i = t; j = m+1; k = t;
  while( i<=m && j<=n )
  {
    if( cmpMyString( s_msa->arr+i, s_msa->arr+j ) <= 0 )
    {
      cpyMyString( m_msa->arr+k, s_msa->arr+i );
      ++k, ++i;
    }
    else
    {
      cpyMyString( m_msa->arr+k, s_msa->arr+j );
      ++k, ++j;
    }
  }
  if( i > m )
    for( p=k; p<=n; ++p )
      cpyMyString( m_msa->arr+p, s_msa->arr+(j+p-k) );
  else
    for( p=k; p<=n; ++p )
      cpyMyString( m_msa->arr+p, s_msa->arr+(i+p-k) );
}


static void mergePassMsa( MyStringArr *s_msa, MyStringArr *m_msa, int n, int length )
{
  int i, j;
  for( j=0; j<=n-2*length; j+=2*length )
    mergeMsa( s_msa, m_msa, j, j+length-1, j+2*length-1 );
  if( j+length < n )
    mergeMsa( s_msa, m_msa, j, j+length-1, n-1 );
  else
    for( i=j; i<n; ++i )
      //m_msa[i] = s_msa[i];
      cpyMyString( m_msa->arr+i, s_msa->arr+i );
}


int mergeSortMyStringArr( MyStringArr *msa, MyStringArr *merge_msa ) // sort; ascending order;
{
  // sort; merge sort;
  int n = msa->size;
  int j;
  if( merge_msa->capacity < msa->size )
  {
    recapacityMyStringArr( merge_msa, msa->size );
  }
  merge_msa->size = msa->size;
  for( j=1; j<n; j*=2 )
  {
    mergePassMsa( msa, merge_msa, n, j );
    j *= 2;
    mergePassMsa( merge_msa, msa, n, j );
  }
  return 0;
}


#ifdef DEBUG_TEST
int displayMyString( MyString *ms )
{
  if( ms == NULL ) return -1;
  printf( "MyString: capacity:%d data:%s\n", ms->capacity, ms->data );
  return 0;
}


int displayMyStringArr( MyStringArr *s1 )
{
  uint32_t i;
  if( s1==NULL ) return -1;
  printf( "MyStringArr->display(): \n" );
  printf( "size: %d, capacity: %d. \n", s1->size, s1->capacity );
  if( s1->size>0 ) // s1!=0
  {
      // must int i, not unsigned i; // for( i=s1->size-1; i>=0; --i ) //printf( "%8x ", s1->arr[i] );
      for( i=0; i<s1->size; ++i )
      {
        printf( "  " );
        displayMyString( s1->arr+i );
      }
  }
  //else printf( "" );
  printf( "Display end. \n" );
  return 0;
}
#endif


int displayToFileMyString( FILE *ofp, MyString *ms )
{
  if( ms == NULL ) return -1;
  fprintf( ofp, "MyString: capacity:%d data:%s\n", ms->capacity, ms->data );
  return 0;
}


int displayToFileMyStringArr( FILE *ofp, MyStringArr *s1 )
{
  uint32_t i;
  if( s1==NULL ) return -1;
  fprintf( ofp, "MyStringArr->display(): \n" );
  fprintf( ofp, "size: %d, capacity: %d. \n", s1->size, s1->capacity );
  if( s1->size>0 ) // s1!=0
  {
      // must int i, not unsigned i; // for( i=s1->size-1; i>=0; --i ) //printf( "%8x ", s1->arr[i] );
      for( i=0; i<s1->size; ++i )
      {
        fprintf( ofp, "  " );
        displayToFileMyString( ofp, s1->arr+i );
      }
  }
  //else printf( "" );
  fprintf( ofp, "Display end. \n" );
  return 0;
}


int findChar( const char *str, char c ) // first one found
{
  int i;
  i = 0;
  while( 1 )
  {
    if( str[i] == c ) return i;
    if( str[i] == 0 ) break;
    ++ i;
  }
  return -1;
}


inline int is_blank( char c ) // ' ', '\n', '\r', '\t'
{
  return ( c==' ' || c=='\n' || c=='\r' || c=='\t' ) ? 1 : 0;
}


inline int is_letter( char c ) // 0-9, a-z, A-Z, _, -, 0x80-0xff
{
  return ( ('0'<=c && c<='9') || ('a'<=c && c<='z') || ('A'<=c && c<='Z') || (c=='_') || (c=='-') || (c<0) ) ? 1 : 0;
}


inline int is_letter_ascii( char c ) // 0-9, a-z, A-Z, _, -
{
  return ( ('0'<=c && c<='9') || ('a'<=c && c<='z') || ('A'<=c && c<='Z') || (c=='_') || (c=='-') ) ? 1 : 0;
}


inline int is_letter_not_ascii( char c ) // 0x80-0xff
{
  return ( (c<0) ) ? 1 : 0;
}



