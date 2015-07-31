/*
 * sequence_stack.h
 *
 *  Created on: 2009-5-16
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_STACK_SEQUENCE_STACK_H_
#define DATA_STRUCTURE_IN_C_STACK_SEQUENCE_STACK_H_

#define STACK_INITIAL_SIZE	100
#define STACK_INCREMENT		10

#define ElementType int
#define STACK_TYPE SequenceStack

#include "include/common.h"

typedef struct SequenceStackHead {
	ElementType *base;
	ElementType *top;
	int size;
} SequenceStackHead, *SequenceStack;

#endif /* DATA_STRUCTURE_IN_C_STACK_SEQUENCE_STACK_H_ */
