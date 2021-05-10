/******************************************************************
 *       File Name: sort.h
 *     Description: 
 *          Author: He Xiwen
 *           Email: hexiwen2000@163.com 
 *    Created Time: 2015-11-25 10:08:11
 *   Modified Time: 
 *          License: 
 *****************************************************************/

#ifndef _SORT_H_
#define _SORT_H_ 1

#include "my_string.h"

#define MEMORY_SORT_SIZE 0X10000000 // 256M;

// in my_string.h and my_string.c;
// int sortMyStringArr( MyStringArr *msa );

extern int merge_sort( const char *output_dir_tmp, const char *output_f, char *line, MyStringArr *msa_out_buf, MyStringArr *msa_merge_buf, MyString *ms );

#endif /* _SORT_H_ */
