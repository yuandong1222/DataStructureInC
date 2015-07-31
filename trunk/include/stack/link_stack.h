/*
 * link_stack.h
 *
 *  Created on: 2009-5-16
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_STACK_LINK_STACK_H_
#define DATA_STRUCTURE_IN_C_STACK_LINK_STACK_H_

#define ElementType int
#define STACK_TYPE LinkStack

#include "include/common.h"

typedef struct LinkStackNode {
	ElementType data;
	struct LinkStackNode *next;
} LinkStackNode;


typedef struct LinkStackHeadNode {
	LinkStackNode *base;
	LinkStackNode *top;
} LinkStackHeadNode, *LinkStack;

#endif /* DATA_STRUCTURE_IN_C_STACK_LINK_STACK_H_ */
