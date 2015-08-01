/*
 * sequence_stack_test.c
 *
 *  Created on: 2009-4-10
 *      Author: yuandong
 */
#include <stdlib.h>

#include "CUnit/Basic.h"
#include "CUnit/Console.h"
#include "CUnit/Automated.h"
#include "CUnit/TestDB.h"

#include "include/stack/sequence_stack.h"
#include "include/stack/stack.h"

#define TEST_STACK_LENGTH 3

SequenceStack getTestStack() {
	SequenceStack stack;
	stack = (SequenceStack) malloc(sizeof(SequenceStackHead));
	stack -> base = (ElementType*) malloc(sizeof(ElementType)
			* STACK_INITIAL_SIZE);
	stack -> top = stack -> base + 3;
	stack -> size = STACK_INITIAL_SIZE;

	stack -> base[0] = 1;
	stack -> base[1] = 2;
	stack -> base[2] = 3;

	return stack;
}
void test_Increment(void) {
	STACK_TYPE stack = NULL;
	Status result = InitialStack(&stack);
	int size = STACK_INITIAL_SIZE + STACK_INCREMENT;

	CU_ASSERT_EQUAL(result, OK);
	if (result != OK)
		return;

	int i = 0;
	for (i = 0; i < size - 1; i++) {
		result = Push(stack, i);
		CU_ASSERT_EQUAL(result, OK);
		if (result != OK)
			return;
	}

	CU_ASSERT_EQUAL(stack -> size, size);
	for (i = 0; i < size - 1; i++) {
		CU_ASSERT_EQUAL(*(stack -> base + i), i);
	}
}

#include "test/stack/stack_test.c"
int main(void) {

	CU_pSuite suite = buildTestSuite();

	CU_ADD_TEST(suite, test_Increment);

	return runTestSuite();
}
