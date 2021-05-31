/******************************************************************
 *       File Name: my_single_omp.h
 *     Description: 
 *          Author: He Xiwen
 *           Email: hexiwen2000@163.com 
 *    Created Time: 2015-11-18 00:42:33
 *   Modified Time: 
 *          License: 
 *****************************************************************/

#ifndef _MY_SINGLE_OMP_H_
#define _MY_SINGLE_OMP_H_

#ifndef _OPENMP

extern int omp_get_num_threads();

extern int omp_get_thread_num();

extern void omp_set_num_threads( int n );

#endif

#endif /* _MY_SINGLE_OMP_H_ */
