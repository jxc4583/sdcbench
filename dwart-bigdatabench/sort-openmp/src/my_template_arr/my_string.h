/*********************************************************************
 *       File Name: my_string.h
 *     Description: my_string and my_string_array;
 *          Author: He Xiwen
 *           Email: hexiwen2000@163.com 
 *    Created Time: 2015-09-23 17:00:45
 *   Modified Time: 2015-09-23 17:01:30
 ********************************************************************/

// not thread safe; 
// bacause sometimes there is malloc() and free() calls in con(), des(), cpy(), append(), recapacity(), push(), pop(), insert(), delete(), sort(), so these funcs are strongly suggested not to be called in multi-thread funcs, unless you can make sure malloc() and free() will not be called in these funcs;
// maybe someday, i need to change all malloc() and free() in .c file to the sequential memory-management ops in my_seq_ops.h;


#ifndef MyString_H
#define MyString_H

#include <stdint.h>
//#include "type.h"

typedef struct S_MyString
{
  char *data;
  uint32_t capacity;
} MyString;

// all MyStringArrr::arr[i] ( 0<=i<capacity ) is already conMyString();
typedef struct S_MyStringArr // array
{
  MyString *arr;
  uint32_t capacity;
  uint32_t size;
} MyStringArr;


extern int conMyString( MyString *ms );
extern int desMyString( MyString *ms );
extern int cpyMyString( MyString *ms1, MyString *ms2 ); // *ms1 = *ms2;
extern int cpyStrMyString( MyString *ms1, const char *str ); // *ms1 = str;
extern int cpynStrMyString( MyString *ms1, const char *str, int len ); // *ms1 = str; copy at most len chars;
extern int clearMyString( MyString *ms );
extern int cmpMyString( const MyString *ms1, const MyString *ms2 ); // compare;
extern int appendMyString( MyString *ms, const char *str ); // *ms += str;
extern int appendnMyString( MyString *ms, const char *str, int len ); // *ms += str; append at most len chars;
//extern uint32_t findMyString( MyString *ms, char c ); // return first one found;
extern int recapacityMyString( MyString *ms, uint32_t cap );

extern int conMyStringArr( MyStringArr *msa );
extern int desMyStringArr( MyStringArr *msa );
extern int cpyMyStringArr( MyStringArr *msa1, MyStringArr *msa2 ); // *msa1 = *msa2;
extern int clearMyStringArr( MyStringArr *msa );
extern MyString* getMyStringArr( MyStringArr *msa1, uint32_t loc );
extern int pushMyStringArr( MyStringArr *msa1, MyString *ms );
extern int popMyStringArr( MyStringArr *msa1 );
extern int insertFirstMyStringArr( MyStringArr *msa1, MyString *ms );
extern int deleteFirstMyStringArr( MyStringArr *msa1 );
extern int recapacityMyStringArr( MyStringArr *msa1, uint32_t cap );
extern uint32_t findMyStringArr( MyStringArr *msa1, MyString *ms ); // first one found;
extern int sortMyStringArr( MyStringArr *msa ); // sort; ascending order;
extern int mergeSortMyStringArr( MyStringArr *msa, MyStringArr *merge_msa ); // sort; ascending order;
#ifdef DEBUG_TEST
extern int displayMyString( MyString *ms );
extern int displayMyStringArr( MyStringArr *msa );
#endif
extern int displayToFileMyString( FILE *ofp, MyString *ms );
extern int displayToFileMyStringArr( FILE *ofp, MyStringArr *msa );


// char *str util
extern int findChar( const char *str, char c ); // return pos;
extern int is_blank( char c ); // ' ', '\n', '\r', '\t'
extern int is_letter( char c ); // 0-9, a-z, A-Z, _, -, 0x80-0xff
extern int is_letter_ascii( char c ); // 0-9, a-z, A-Z, _, -
extern int is_letter_not_ascii( char c ); // 0x80-0xff

#endif /* MyString_H */
