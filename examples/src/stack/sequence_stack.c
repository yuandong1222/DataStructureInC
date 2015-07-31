/*
 * sequence_stack.c
 *
 *  Created on: 2009-5-16
 *      Author: yuandong
 */

#include <stdlib.h>
#include <stdio.h>

#include "include/common.h"
#include "include/stack/sequence_stack.h"
#include "include/stack/stack.h"

Status InitialStack(STACK_TYPE *stack) {
	(*stack) = (SequenceStack) malloc(sizeof(SequenceStackHead));
	if ((*stack) == NULL)
		return OVERFLOW;

	(*stack) -> base = (ElementType*) malloc(sizeof(ElementType)
			* STACK_INITIAL_SIZE);
	if ((*stack) -> base == NULL)
		return OVERFLOW;

	(*stack) -> top = (*stack) -> base;
	(*stack) -> size = STACK_INITIAL_SIZE;

	return OK;
}

Status DestroyStack(STACK_TYPE *stack) {
	free((*stack) -> base);
	free(*stack);

	*stack = NULL;

	return OK;
}

Status ClearStack(STACK_TYPE stack) {
	stack -> top = stack -> base;
	return OK;
}

BOOLEAN StackEmpty(STACK_TYPE stack) {
	return stack -> top == stack -> base;
}

int StackLength(STACK_TYPE stack) {
	return stack -> top - stack -> base;
}

Status GetTop(STACK_TYPE stack, ElementType *element) {
	if (StackEmpty(stack))
		return ERROR;

	*element = *(stack -> top - 1);
	return OK;
}

Status Push(STACK_TYPE stack, ElementType element) {

	//expend size
	if (StackLength(stack) == stack -> size) {
		ElementType *newElement = malloc(sizeof(ElementType)
				* (stack -> size + STACK_INCREMENT));
		if(newElement == NULL)
			return OVERFLOW;

		int i;
		for (i = 0; i < stack -> size; i++) {
			(newElement)[i] = (stack -> base)[i];
		}
		free(stack -> base);
		stack -> base = newElement;
		stack -> top = stack -> base + stack -> size;
		stack -> size = stack -> size + STACK_INCREMENT;
	}

	//insert
	*(stack -> top) = element;
	(stack -> top)++;

	return OK;

}

Status Pop(STACK_TYPE stack, ElementType *element) {
	if (StackEmpty(stack))
		return ERROR;

	*element = *(stack -> top - 1);
	(stack -> top)--;
	return OK;
}

Status Traverse(STACK_TYPE stack, Status(*visit)(ElementType *element)) {
	ElementType *element = stack -> base;
	Status result;

	while (element != stack -> top) {
		result = (*visit)(element);
		if (result != OK)
			return result;
		element++;
	}

	return OK;
}
