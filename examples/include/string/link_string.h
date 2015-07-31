/*
 * link_string.h
 *
 *  Created on: 2009-5-16
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_STRING_LINK_STRING_H_
#define DATA_STRUCTURE_IN_C_STRING_LINK_STRING_H_

#define STRING_TYPE LinkString

#include "include/common.h"

#define CHUNK_SIZE	4
#define BLANK 		'\0'

typedef struct Chunk {
	char* data;
	struct Chunk *next;
} Chunk;

typedef struct LinkStringHead {
	int length;
	Chunk *head;
	Chunk *tail;
} LinkStringHead, *LinkString;

//Ñ¹Ëõ
//È¥µôStringÖÐ¶àÓàµÄ¿Õ°××Ö·û
Status Zip(STRING_TYPE *string);

#endif /* DATA_STRUCTURE_IN_C_STRING_HEAP_STRING_H_ */
