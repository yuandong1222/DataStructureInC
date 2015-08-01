/*
 * stack_test.c
 *
 *  Created on: 2009-4-10
 *      Author: yuandong
 */

#include <stdlib.h>

#include "include/stack/stack.h"

#include "CUnit/Basic.h"
#include "CUnit/Console.h"
#include "CUnit/Automated.h"
#include "CUnit/TestDB.h"

int test_StackTraverse_Count = 0;
Status test_StackTraverse_Function_Success(ElementType* element) {
	test_StackTraverse_Count += *element;
	return OK;
}

Status test_StackTraverse_Function_Error(ElementType* element) {
	return ERROR;
}

Status compare(ElementType e1, ElementType e2) {
	return e1 == e2;
}

void test_InitialStack(void) {
	STACK_TYPE stack = NULL;
	Status result = InitialStack(&stack);

	CU_ASSERT_EQUAL(result, OK);
	CU_ASSERT_PTR_NOT_NULL(stack);
}
void test_DestroyStack(void) {
	STACK_TYPE stack = getTestStack();
	Status result = DestroyStack(&stack);

	CU_ASSERT_EQUAL(result, OK);
	CU_ASSERT_PTR_NULL(stack);
}
void test_ClearStack(void) {
	STACK_TYPE stack = getTestStack();
	Status result = ClearStack(stack);

	CU_ASSERT_EQUAL(result, OK);
	CU_ASSERT_PTR_NOT_NULL(stack);
	CU_ASSERT_TRUE(StackEmpty(stack));
}
void test_StackEmpty(void) {
	STACK_TYPE stack = getTestStack();
	CU_ASSERT_FALSE(StackEmpty(stack));

	ClearStack(stack);
	CU_ASSERT_TRUE(StackEmpty(stack));
}
void test_StackLength(void) {
	STACK_TYPE stack = getTestStack();
	CU_ASSERT_EQUAL(StackLength(stack), TEST_STACK_LENGTH);

	ClearStack(stack);
	CU_ASSERT_EQUAL(StackLength(stack), 0);
}
void test_GetTop(void) {
	STACK_TYPE stack = getTestStack();
	ElementType element;
	Status result;

	result = GetTop(stack, &element);
	CU_ASSERT_EQUAL(result, OK);
	CU_ASSERT_EQUAL(element, 3);

	ClearStack(stack);
	result = GetTop(stack, &element);
	CU_ASSERT_EQUAL(result, ERROR);
}
void test_Pop(void) {
	STACK_TYPE stack = getTestStack();
	ElementType element;
	Status result;
	int i;

	for (i = 0; i < TEST_STACK_LENGTH; i++) {
		result = Pop(stack, &element);
		CU_ASSERT_EQUAL(result, OK);
		CU_ASSERT_EQUAL(element, TEST_STACK_LENGTH - i);
	}

	result = Pop(stack, &element);
	CU_ASSERT_EQUAL(result, ERROR);
}
void test_Push(void) {
	STACK_TYPE stack;;
	ElementType element;
	Status result;
	int i;

	InitialStack(&stack);

	for (i = 0; i < TEST_STACK_LENGTH; i++) {
		result = Push(stack, i);
		CU_ASSERT_EQUAL(result, OK);
	}

	for (i = 0; i < TEST_STACK_LENGTH; i++) {
		result = Pop(stack, &element);
		CU_ASSERT_EQUAL(result, OK);
		CU_ASSERT_EQUAL(element, TEST_STACK_LENGTH - i - 1);
	}
}
void test_StackTraverse(void) {
	STACK_TYPE stack = getTestStack();
	Status result;

	result = Traverse(stack, &test_StackTraverse_Function_Error);
	CU_ASSERT_EQUAL(result, ERROR);

	int total = 0, i = 0;
	for (i = 1; i <= TEST_STACK_LENGTH; i++) {
		total += i;
	}

	result = Traverse(stack, &test_StackTraverse_Function_Success);
	CU_ASSERT_EQUAL(result, OK);
	CU_ASSERT_EQUAL(test_StackTraverse_Count, total);
}

CU_pSuite buildTestSuite() {
	CU_initialize_registry();

	CU_pSuite pSuite = CU_add_suite("Stack Test Suite", NULL, NULL);
	CU_ADD_TEST(pSuite, test_InitialStack);
	CU_ADD_TEST(pSuite, test_DestroyStack);
	CU_ADD_TEST(pSuite, test_ClearStack);
	CU_ADD_TEST(pSuite, test_StackEmpty);
	CU_ADD_TEST(pSuite, test_StackLength);
	CU_ADD_TEST(pSuite, test_GetTop);
	CU_ADD_TEST(pSuite, test_Pop);
	CU_ADD_TEST(pSuite, test_Push);
	CU_ADD_TEST(pSuite, test_StackTraverse);

	return pSuite;
}
int runTestSuite() {
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

	CU_cleanup_registry();
	return CU_get_error();
}
