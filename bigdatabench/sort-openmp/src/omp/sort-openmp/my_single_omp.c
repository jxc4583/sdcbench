/******************************************************************
 *       File Name: my_single_omp.c
 *     Description: 
 *          Author: He Xiwen
 *           Email: hexiwen2000@163.com 
 *    Created Time: 2015-11-23 21:00:59
 *   Modified Time: 
 *          License: 
 *****************************************************************/

#include "my_single_omp.h"


#ifndef _OPENMP

int omp_get_num_threads() {
  return 1;
}

int omp_get_thread_num() {
  return 0;
}

void omp_set_num_threads( int n ) {
  return ;
}

#endif

