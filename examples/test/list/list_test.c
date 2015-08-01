/*
 * list_test.c
 *
 *  Created on: 2009-4-10
 *      Author: yuandong
 */

#include <stdlib.h>

#include "include/list/list.h"

#include "CUnit/Basic.h"
#include "CUnit/Console.h"
#include "CUnit/Automated.h"
#include "CUnit/TestDB.h"

int test_ListTraverse_Count = 0;
Status test_ListTraverse_Function_Success(ElementType* element) {
	test_ListTraverse_Count += *element;
	return OK;
}

Status test_ListTraverse_Function_Error(ElementType* element) {
	return ERROR;
}

Status compare(ElementType e1, ElementType e2) {
	return e1 == e2;
}

void test_InitialList(void) {
	LIST_TYPE list = NULL;
	Status result = InitialList(&list);

	CU_ASSERT_EQUAL(result, OK);
	CU_ASSERT_PTR_NOT_NULL(list);
}
void test_DestroyList(void) {
	LIST_TYPE list = getTestList();
	Status result = DestroyList(&list);

	CU_ASSERT_EQUAL(result, OK);
	CU_ASSERT_PTR_NULL(list);
}
void test_ClearList(void) {
	LIST_TYPE list = getTestList();
	Status result = ClearList(list);

	CU_ASSERT_EQUAL(result, OK);
	CU_ASSERT_PTR_NOT_NULL(list);
	CU_ASSERT_TRUE(ListEmpty(list));
}
void test_ListEmpty(void) {
	LIST_TYPE list = getTestList();
	CU_ASSERT_FALSE(ListEmpty(list));

	ClearList(list);
	CU_ASSERT_TRUE(ListEmpty(list));
}
void test_ListLength(void) {
	LIST_TYPE list = getTestList();
	CU_ASSERT_EQUAL(ListLength(list), TEST_LIST_LENGTH);

	ClearList(list);
	CU_ASSERT_EQUAL(ListLength(list), 0);
}
void test_GetElement(void) {
	LIST_TYPE list = getTestList();
	ElementType element;
	Status result;

	int i = 0;
	for (i = 1; i <= TEST_LIST_LENGTH; i++) {
		result = GetElement(list, i, &element);
		CU_ASSERT_EQUAL(result, OK);
		CU_ASSERT_EQUAL(element, i);
	}

	result = GetElement(list, TEST_LIST_LENGTH + 1, &element);
	CU_ASSERT_EQUAL(result, ERROR);
}
void test_LocateElement(void) {
	LIST_TYPE list = getTestList();
	int position;

	int i = 0;
	for (i = 1; i <= TEST_LIST_LENGTH; i++) {
		position = LocateElement(list, i, &compare);
		CU_ASSERT_EQUAL(position, i);
	}

	position = LocateElement(list, TEST_LIST_LENGTH + 1, &compare);
	CU_ASSERT_EQUAL(position, 0);
}
void test_PriorElement(void) {
	LIST_TYPE list = getTestList();
	ElementType element;
	Status result;

	int i = 0;
	for (i = 2; i <= TEST_LIST_LENGTH; i++) {
		result = PriorElement(list, i, &element);
		CU_ASSERT_EQUAL(element, i - 1);
	}

	result = PriorElement(list, 1, &element);
	CU_ASSERT_EQUAL(result, INFEASIBLE);

	result = PriorElement(list, TEST_LIST_LENGTH + 1, &element);
	CU_ASSERT_EQUAL(result, INFEASIBLE);
}
void test_NextElement(void) {
	LIST_TYPE list = getTestList();
	ElementType element;
	Status result;

	int i = 0;
	for (i = 1; i <= TEST_LIST_LENGTH - 1; i++) {
		result = NextElement(list, i, &element);
		CU_ASSERT_EQUAL(element, i + 1);
	}

	result = NextElement(list, TEST_LIST_LENGTH, &element);
	CU_ASSERT_EQUAL(result, INFEASIBLE);
}
void test_ListInsert(void) {
	LIST_TYPE list = getTestList();
	ElementType element, element_to_insert = TEST_LIST_LENGTH + 1;
	Status result;

	//Position: TEST_LIST_LENGTH + 2
	result = ListInsert(list, TEST_LIST_LENGTH + 2, element_to_insert);
	CU_ASSERT_EQUAL(result, ERROR);

	int i = 0;
	for (i = 1; i <= TEST_LIST_LENGTH; i++) {
		result = ListInsert(list, i, element_to_insert);
		CU_ASSERT_EQUAL(result, OK);

		result = GetElement(list, i, &element);
		CU_ASSERT_EQUAL(result, OK);
		CU_ASSERT_EQUAL(element, element_to_insert);

		CU_ASSERT_EQUAL(ListLength(list), TEST_LIST_LENGTH + i);
	}
}
void test_ListDelete(void) {
	LIST_TYPE list = getTestList();
	ElementType element;
	Status result;

	//Position: TEST_LIST_LENGTH + 1
	result = ListDelete(list, TEST_LIST_LENGTH + 1, &element);
	CU_ASSERT_EQUAL(result, ERROR);

	int i = 0;
	for (i = 1; i <= TEST_LIST_LENGTH; i++) {
		result = ListDelete(list, 1, &element);
		CU_ASSERT_EQUAL(result, OK);
		CU_ASSERT_EQUAL(element, i);
		CU_ASSERT_EQUAL(ListLength(list), TEST_LIST_LENGTH - i);
	}
}
void test_ListTraverse(void) {
	LIST_TYPE list = getTestList();
	Status result;

	result = ListTraverse(list, &test_ListTraverse_Function_Error);
	CU_ASSERT_EQUAL(result, ERROR);

	int total = 0, i = 0;
	for (i = 1; i <= TEST_LIST_LENGTH; i++) {
		total += i;
	}

	result = ListTraverse(list, &test_ListTraverse_Function_Success);
	CU_ASSERT_EQUAL(result, OK);
	CU_ASSERT_EQUAL(test_ListTraverse_Count, total);
}
void test_ListMerge(void) {
	LIST_TYPE a, b;
	Status result;

	result = InitialList(&a);
	CU_ASSERT_EQUAL(result, OK);
	if (result != OK)
		return;

	result = InitialList(&b);
	CU_ASSERT_EQUAL(result, OK);
	if (result != OK)
		return;

	int i = 0;
	for (i = 1; i <= TEST_LIST_LENGTH * 2; i++) {
		if (i % 2 == 0)
			result = ListInsert(a, ListLength(a) + 1, i);
		else
			result = ListInsert(b, ListLength(b) + 1, i);

		CU_ASSERT_EQUAL(result, OK);
		if (result != OK)
			return;
	}

	result = ListMerge(&a, &b);

	CU_ASSERT_EQUAL(result, OK);
	CU_ASSERT_PTR_NOT_NULL(a);
	CU_ASSERT_PTR_NULL(b);

	if (a != NULL) {
		ElementType element;
		for (i = 1; i <= TEST_LIST_LENGTH * 2; i++) {
			result = GetElement(a, i, &element);
			CU_ASSERT_EQUAL(result, OK);
			CU_ASSERT_EQUAL(element, i);
		}
	}
}

CU_pSuite buildTestSuite() {
	CU_initialize_registry();

	CU_pSuite pSuite = CU_add_suite("List Test Suite", NULL, NULL);
	CU_ADD_TEST(pSuite, test_InitialList);
	CU_ADD_TEST(pSuite, test_DestroyList);
	CU_ADD_TEST(pSuite, test_ClearList);
	CU_ADD_TEST(pSuite, test_ListEmpty);
	CU_ADD_TEST(pSuite, test_ListLength);
	CU_ADD_TEST(pSuite, test_GetElement);
	CU_ADD_TEST(pSuite, test_LocateElement);
	CU_ADD_TEST(pSuite, test_PriorElement);
	CU_ADD_TEST(pSuite, test_NextElement);
	CU_ADD_TEST(pSuite, test_ListInsert);
	CU_ADD_TEST(pSuite, test_ListDelete);
	CU_ADD_TEST(pSuite, test_ListTraverse);
	CU_ADD_TEST(pSuite, test_ListMerge);

	return pSuite;
}
int runTestSuite() {
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

	CU_cleanup_registry();
	return CU_get_error();
}
