/*
 * link_stack_test.c
 *
 *  Created on: 2009-4-10
 *      Author: yuandong
 */
#include <stdlib.h>

#include "include/stack/link_stack.h"

#define TEST_STACK_LENGTH 3

LinkStack getTestStack() {
	LinkStack stack;

	stack = (LinkStack) malloc(sizeof(LinkStackHeadNode));

	stack -> base = (LinkStackNode*) malloc(sizeof(LinkStackNode));
	stack -> base -> data = 1;

	stack -> base -> next = (LinkStackNode*) malloc(sizeof(LinkStackNode));
	stack -> base -> next -> data = 2;

	stack -> base -> next -> next = (LinkStackNode*) malloc(
			sizeof(LinkStackNode));
	stack -> base -> next -> next -> data = 3;

	stack -> base -> next -> next -> next = NULL;
	stack -> top = stack -> base -> next -> next;

	return stack;
}

#include "test/stack/stack_test.c"
int main(void) {
	buildTestSuite();
	return runTestSuite();
}
