/*
 * sequence_list.h
 *
 *  Created on: 2009-4-26
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_LIST_SEQUENCE_LIST_H_
#define DATA_STRUCTURE_IN_C_LIST_SEQUENCE_LIST_H_

#include "include/common.h"

#define ElementType int
#define LIST_TYPE SequenceList

#define LIST_INITIAL_SIZE	100
#define LIST_INCREMENT	10

//线性表的顺序存储
typedef struct SequenceListHead {
	ElementType *element;
	int length;
	int listsize;
} SequenceListHead, *SequenceList;

#endif /* DATA_STRUCTURE_IN_C_LIST_SEQUENCE_LIST_H_ */
