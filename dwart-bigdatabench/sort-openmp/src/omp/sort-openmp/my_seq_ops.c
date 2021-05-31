/******************************************************************
 *       File Name: my_seq_ops.c
 *     Description: to implement funcs in .h;
 *          Author: He Xiwen
 *           Email: hexiwen2000@163.com 
 *    Created Time: 2015-11-18 16:13:49
 *   Modified Time: 
 *          License: 
 *****************************************************************/


#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP
#include <pthread.h>
// static pthread_mutex_t mtx_mem_mng = PTHREAD_MUTEX_INITIALIZER; // so do not need init() for this mtx;
static pthread_mutex_t mtx_mem_mng;
#endif

#include "my_seq_ops.h"


#ifdef _OPENMP
#else
#endif

void my_seq_ops_init(){
#ifdef _OPENMP
  int ret;
  ret = pthread_mutex_init( &mtx_mem_mng, NULL );
  if( ret != 0 ){
    perror( "mtx_mem_mng: init failure" );
    exit( EXIT_FAILURE );
  }
#else
  // nothing;
#endif
}

void my_seq_ops_end(){
#ifdef _OPENMP
  pthread_mutex_destroy( &mtx_mem_mng );
#else
  // nothing;
#endif
}


// sequential memory-management ops for multi-thread;
// using mutex: static pthread_mutex_t mtx_mem_mng;
void *my_malloc( size_t nbytes ){
  void *p;
#ifdef _OPENMP
  pthread_mutex_lock( &mtx_mem_mng );
  p = malloc( nbytes );
  pthread_mutex_unlock( &mtx_mem_mng );
#else
  p = malloc( nbytes );
#endif
  if( !p ){
    fprintf( stderr, "malloc() failed for size %zu\n", nbytes );
    exit( EXIT_FAILURE );
  }
  return p;
}

void my_free( void *ptr ){
#ifdef _OPENMP
  pthread_mutex_lock( &mtx_mem_mng );
  free( ptr );
  pthread_mutex_unlock( &mtx_mem_mng );
#else
  free( ptr );
#endif
}

