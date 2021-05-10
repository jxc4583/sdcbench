/******************************************************************
 *       File Name: my_seq_ops.h
 *     Description: 
 *          Author: He Xiwen
 *           Email: hexiwen2000@163.com 
 *    Created Time: 2015-11-18 15:49:37
 *   Modified Time: 
 *          License: 
 *****************************************************************/

#ifndef _MY_SEQ_OPS_H_
#define _MY_SEQ_OPS_H_

extern void my_seq_ops_init();
extern void my_seq_ops_end();

// sequential memory-management ops for multi-thread;
// using mutex: static pthread_mutex_t mtx_mem_mng;
extern void *my_malloc( size_t nbytes ); // malloc();
extern void my_free( void *ptr ); // free();

#endif /* _MY_SEQ_OPS_H_ */
