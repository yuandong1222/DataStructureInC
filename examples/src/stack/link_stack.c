/*
 * link_stack.c
 *
 *  Created on: 2009-5-16
 *      Author: yuandong
 */

#include <stdlib.h>
#include <stdio.h>

#include "include/common.h"
#include "include/stack/link_stack.h"
#include "include/stack/stack.h"

Status InitialStack(STACK_TYPE *stack) {
	(*stack) = (LinkStack) malloc(sizeof(LinkStackHeadNode));
	if (*stack == NULL)
		return OVERFLOW;

	(*stack) -> base = (*stack) -> top = NULL;

	return OK;
}

Status DestroyStack(STACK_TYPE *stack) {
	LinkStackNode *node = (*stack) -> base, *temp = NULL;

	while (node != NULL) {
		temp = node -> next;
		free(node);
		node = temp;
	}

	free(*stack);
	*stack = NULL;

	return OK;
}

Status ClearStack(STACK_TYPE stack) {
	LinkStackNode *node = stack -> base, *temp = NULL;

	while (node != NULL) {
		temp = node -> next;
		free(node);
		node = temp;
	}

	stack -> base = stack -> top = NULL;

	return OK;
}

BOOLEAN StackEmpty(STACK_TYPE stack) {
	return stack -> base == NULL;
}

int StackLength(STACK_TYPE stack) {
	LinkStackNode *node = stack -> base;
	int length = 0;

	while (node != NULL) {
		length++;
		node = node -> next;
	}

	return length;
}

Status GetTop(STACK_TYPE stack, ElementType *element) {
	if (StackEmpty(stack))
		return ERROR;

	*element = stack -> top -> data;

	return OK;
}

Status Push(STACK_TYPE stack, ElementType element) {
	LinkStackNode *node = (LinkStackNode*) malloc(sizeof(LinkStackNode));
	if (node == NULL)
		return OVERFLOW;

	node -> data = element;
	node -> next = NULL;

	if (stack -> base == NULL) {
		stack -> base = stack -> top = node;
	} else {
		stack -> top -> next = node;
		stack -> top = node;
	}
	return OK;
}

Status Pop(STACK_TYPE stack, ElementType *element) {
	if(StackEmpty(stack))
		return ERROR;

	if(stack -> base == stack -> top) {
		*element = stack -> base -> data;
		free(stack -> base);
		stack -> base = stack -> top = NULL;
		return OK;
	}

	LinkStackNode *node = stack -> base;
	while(node -> next != stack -> top){
		node = node -> next;
	}

	*element = stack -> top -> data;
	free(stack -> top);
	stack -> top = node;

	return OK;
}

Status Traverse(STACK_TYPE stack, Status(*visit)(ElementType *element)) {
	LinkStackNode *node = stack -> base;

	while (node != NULL) {
		if (((*visit)(&(node -> data))) == ERROR)
			return ERROR;
		node = node -> next;
	}

	return OK;
}
