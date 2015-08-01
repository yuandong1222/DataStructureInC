/*
 * queue_test.c
 *
 *  Created on: 2009-4-10
 *      Author: yuandong
 */

#include <stdlib.h>

#include "include/queue/queue.h"

#include "CUnit/Basic.h"
#include "CUnit/Console.h"
#include "CUnit/Automated.h"
#include "CUnit/TestDB.h"

int test_QueueTraverse_Count = 0;
Status test_QueueTraverse_Function_Success(ElementType* element) {
	test_QueueTraverse_Count += *element;
	return OK;
}

Status test_QueueTraverse_Function_Error(ElementType* element) {
	return ERROR;
}

Status compare(ElementType e1, ElementType e2) {
	return e1 == e2;
}

void test_InitialQueue(void) {
	QUEUE_TYPE queue = NULL;
	Status result = InitialQueue(&queue);

	CU_ASSERT_EQUAL(result, OK);
	CU_ASSERT_PTR_NOT_NULL(queue);
}
void test_DestroyQueue(void) {
	QUEUE_TYPE queue = getTestQueue();
	Status result = DestroyQueue(&queue);

	CU_ASSERT_EQUAL(result, OK);
	CU_ASSERT_PTR_NULL(queue);
}
void test_ClearQueue(void) {
	QUEUE_TYPE queue = getTestQueue();
	Status result = ClearQueue(queue);

	CU_ASSERT_EQUAL(result, OK);
	CU_ASSERT_PTR_NOT_NULL(queue);
	CU_ASSERT_TRUE(QueueEmpty(queue));
}
void test_QueueEmpty(void) {
	QUEUE_TYPE queue = getTestQueue();
	CU_ASSERT_FALSE(QueueEmpty(queue));

	ClearQueue(queue);
	CU_ASSERT_TRUE(QueueEmpty(queue));
}
void test_QueueLength(void) {
	QUEUE_TYPE queue = getTestQueue();
	CU_ASSERT_EQUAL(QueueLength(queue), TEST_QUEUE_LENGTH);

	ClearQueue(queue);
	CU_ASSERT_EQUAL(QueueLength(queue), 0);
}
void test_GetHead(void) {
	QUEUE_TYPE queue = getTestQueue();
	ElementType element;
	Status result;

	result = GetHead(queue, &element);
	CU_ASSERT_EQUAL(result, OK);
	CU_ASSERT_EQUAL(element, 1);

	ClearQueue(queue);
	result = GetHead(queue, &element);
	CU_ASSERT_EQUAL(result, ERROR);
}
void test_Dequeue(void) {
	QUEUE_TYPE queue = getTestQueue();
	ElementType element;
	Status result;
	int i;

	for (i = 0; i < TEST_QUEUE_LENGTH; i++) {
		result = Dequeue(queue, &element);
		CU_ASSERT_EQUAL(result, OK);
		CU_ASSERT_EQUAL(element,  i + 1);
	}

	result = Dequeue(queue, &element);
	CU_ASSERT_EQUAL(result, ERROR);
}
void test_Enqueue(void) {
	QUEUE_TYPE queue;;
	ElementType element;
	Status result;
	int i;

	InitialQueue(&queue);

	for (i = 0; i < TEST_QUEUE_LENGTH; i++) {
		result = Enqueue(queue, i);
		CU_ASSERT_EQUAL(result, OK);
	}

	for (i = 0; i < TEST_QUEUE_LENGTH; i++) {
		result = Dequeue(queue, &element);
		CU_ASSERT_EQUAL(result, OK);
		CU_ASSERT_EQUAL(element, i);
	}
}
void test_QueueTraverse(void) {
	QUEUE_TYPE queue = getTestQueue();
	Status result;

	result = Traverse(queue, &test_QueueTraverse_Function_Error);
	CU_ASSERT_EQUAL(result, ERROR);

	int total = 0, i = 0;
	for (i = 1; i <= TEST_QUEUE_LENGTH; i++) {
		total += i;
	}

	result = Traverse(queue, &test_QueueTraverse_Function_Success);
	CU_ASSERT_EQUAL(result, OK);
	CU_ASSERT_EQUAL(test_QueueTraverse_Count, total);
}

CU_pSuite buildTestSuite() {
	CU_initialize_registry();

	CU_pSuite pSuite = CU_add_suite("Queue Test Suite", NULL, NULL);
	CU_ADD_TEST(pSuite, test_InitialQueue);
	CU_ADD_TEST(pSuite, test_DestroyQueue);
	CU_ADD_TEST(pSuite, test_ClearQueue);
	CU_ADD_TEST(pSuite, test_QueueEmpty);
	CU_ADD_TEST(pSuite, test_QueueLength);
	CU_ADD_TEST(pSuite, test_GetHead);
	CU_ADD_TEST(pSuite, test_Dequeue);
	CU_ADD_TEST(pSuite, test_Enqueue);
	CU_ADD_TEST(pSuite, test_QueueTraverse);

	return pSuite;
}
int runTestSuite() {
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

	CU_cleanup_registry();
	return CU_get_error();
}
