/******************************************************************
 *       File Name: do_one_file.h
 *     Description: 
 *          Author: He Xiwen
 *           Email: hexiwen2000@163.com 
 *    Created Time: 2015-11-23 17:27:19
 *   Modified Time: 
 *          License: 
 *****************************************************************/

#ifndef _DO_ONE_FILE_H_
#define _DO_ONE_FILE_H_

#include <time.h>

#include "my_string.h"

extern clock_t clock_single_read;
extern clock_t clock_single_write;
extern clock_t clock_parallel;
extern double walltime_parallel;


// memory sort;
int do_one_file( const char *ifpath, const char *output_d, char *line, MyStringArr *msa_arr, MyStringArr *merge_msa_arr, int thread_cnt, MyString *ms, int file_cnt );

// single-thread multi-way merge sort;
void do_merge_sort( const char *input_d, const char *output_f, char *line, MyString *ms );

#endif /* _DO_ONE_FILE_H_ */
