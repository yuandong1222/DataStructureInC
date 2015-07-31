/*
 * list_test.c
 *
 *  Created on: 2009-4-10
 *      Author: yuandong
 */

#include <stdlib.h>

#include "include/list/head_link_list.h"

#include "include/CUnit/Basic.h"
#include "include/CUnit/Console.h"
#include "include/CUnit/Automated.h"
#include "include/CUnit/TestDB.h"

#define TEST_LIST_LENGTH 3

LIST_TYPE getTestList(void) {
	HeadLinkList list;

	list = (HeadLinkList) malloc(sizeof(HeadLinkListHeadNode));
	list -> length = TEST_LIST_LENGTH;

	list -> head = (HeadLinkListNode*) malloc(sizeof(HeadLinkListNode));
	list -> head -> data = 1;

	list -> head -> next = (HeadLinkListNode*) malloc(sizeof(HeadLinkListNode));
	list -> head -> next -> data = 2;

	list -> head -> next -> next = (HeadLinkListNode*) malloc(
			sizeof(HeadLinkListNode));
	list -> head -> next -> next -> data = 3;

	list -> head -> next -> next -> next = NULL;
	list -> tail = list -> head -> next -> next;

	return list;
}
HeadLinkListNode* getTestNode(void) {
	HeadLinkListNode *node = (HeadLinkListNode*) malloc(
			sizeof(HeadLinkListNode));

	node -> data = TEST_LIST_LENGTH + 1;
	node -> next = NULL;

	return node;
}
Link getTestLink(void) {
	HeadLinkListNode *node = (HeadLinkListNode*) malloc(
			sizeof(HeadLinkListNode));

	node -> data = TEST_LIST_LENGTH + 2;
	node -> next = (HeadLinkListNode*) malloc(sizeof(HeadLinkListNode));

	node -> next -> data = TEST_LIST_LENGTH + 3;
	node -> next -> next = NULL;

	return node;
}

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

void test_MakeNode(void) {
	HeadLinkListNode *node = NULL;
	ElementType element = 1;
	Status result;

	result = MakeNode(&node, element);

	CU_ASSERT_EQUAL(result, OK);
	CU_ASSERT_PTR_NOT_NULL(node);
	if (node != NULL) {
		CU_ASSERT_EQUAL(node -> data, element);
		CU_ASSERT_PTR_NULL(node -> next);
	}
}
void test_FreeNode(void) {
	HeadLinkListNode *node = getTestNode();

	FreeNode(&node);

	CU_ASSERT_PTR_NULL(node);
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
	CU_ASSERT_TRUE(ListEmpty(list));
}
void test_InsertFirst(void) {
	LIST_TYPE list = getTestList();
	HeadLinkListNode *node = getTestNode();
	Status result;

	result = InsertFirst(list, node);

	CU_ASSERT_EQUAL(result, OK);
	CU_ASSERT_PTR_EQUAL(list -> head, node);
	CU_ASSERT_PTR_EQUAL(list -> length, TEST_LIST_LENGTH + 1);
}
void test_DeleteFirst(void) {
	LIST_TYPE list = getTestList();
	HeadLinkListNode *node = NULL, *head = list -> head;
	Status result;

	int i;
	for (i = 1; i <= TEST_LIST_LENGTH; i++) {
		head = list -> head;
		result = DeleteFirst(list, &node);
		CU_ASSERT_EQUAL(result, OK);
		CU_ASSERT_PTR_EQUAL(node, head);
		CU_ASSERT_PTR_EQUAL(list -> length, TEST_LIST_LENGTH - i);
	}

	result = DeleteFirst(list, &node);
	CU_ASSERT_EQUAL(result, ERROR);
}
void test_Append(void) {
	LIST_TYPE list = getTestList();
	Link link = getTestLink();
	Status result;

	result = Append(list, link);

	CU_ASSERT_EQUAL(result, OK);
	CU_ASSERT_PTR_EQUAL(list -> tail, link -> next);
	CU_ASSERT_PTR_EQUAL(list -> length, TEST_LIST_LENGTH + 2);

	ClearList(list);
	result = Append(list, link);

	CU_ASSERT_EQUAL(result, OK);
	CU_ASSERT_PTR_EQUAL(list -> head, link);
	CU_ASSERT_PTR_EQUAL(list -> tail, link -> next);
	CU_ASSERT_PTR_EQUAL(list -> length, 2);
}
void test_Remove(void) {
	LIST_TYPE list = getTestList();
	HeadLinkListNode *node = NULL, *tail = list -> tail;
	Status result;

	int i;
	for (i = 1; i <= TEST_LIST_LENGTH; i++) {
		tail = list -> tail;
		result = Remove(list, &node);
		CU_ASSERT_EQUAL(result, OK);
		CU_ASSERT_PTR_EQUAL(node, tail);
		CU_ASSERT_PTR_EQUAL(list -> length, TEST_LIST_LENGTH - i);
	}

	result = Remove(list, &node);
	CU_ASSERT_EQUAL(result, ERROR);
	CU_ASSERT_PTR_EQUAL(node, NULL);
}
void test_InsertBefore(void) {
	LIST_TYPE list;
	Position position;
	HeadLinkListNode *node;
	Status result;

	list = getTestList();
	node = getTestNode();
	position = list -> head;
	result = InsertBefore(list, &position, node);
	CU_ASSERT_EQUAL(result, OK);
	CU_ASSERT_PTR_EQUAL(node, list -> head);
	CU_ASSERT_PTR_EQUAL(position, node);
	CU_ASSERT_PTR_EQUAL(list -> length, TEST_LIST_LENGTH + 1);

	list = getTestList();
	node = getTestNode();
	position = list -> head -> next;
	result = InsertBefore(list, &position, node);
	CU_ASSERT_EQUAL(result, OK);
	CU_ASSERT_PTR_EQUAL(node, list -> head -> next);
	CU_ASSERT_PTR_EQUAL(position, node);
	CU_ASSERT_PTR_EQUAL(list -> length, TEST_LIST_LENGTH + 1);
}
void test_InsertAfter(void) {
	LIST_TYPE list = getTestList();
	Position position = list -> head -> next;
	HeadLinkListNode *node = getTestNode();
	Status result;

	result = InsertAfter(list, &position, node);

	CU_ASSERT_EQUAL(result, OK);
	CU_ASSERT_PTR_EQUAL(node, list -> head -> next -> next);
	CU_ASSERT_PTR_EQUAL(position, node);
	CU_ASSERT_PTR_EQUAL(list -> length, TEST_LIST_LENGTH + 1);
}
void test_SetElement(void) {
	LIST_TYPE list = getTestList();
	Position position = list -> head -> next;
	ElementType element = TEST_LIST_LENGTH + 1;
	Status result;

	result = SetElement(position, element);

	CU_ASSERT_EQUAL(result, OK);
	CU_ASSERT_PTR_EQUAL(element, list -> head -> next -> data);
}

void test_GetElement(void) {
	LIST_TYPE list = getTestList();
	ElementType element;
	Position position = list -> head -> next;

	element = GetElement(position);

	CU_ASSERT_PTR_EQUAL(element, list -> head -> next -> data);
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
void test_GetFirst(void) {
	LIST_TYPE list = getTestList();
	Position position;

	position = GetFirst(list);
	CU_ASSERT_EQUAL(position, list -> head);

	ClearList(list);
	position = GetFirst(list);
	CU_ASSERT_EQUAL(position, NULL);
}
void test_GetLast(void) {
	LIST_TYPE list = getTestList();
	Position position;

	position = GetLast(list);
	CU_ASSERT_EQUAL(position, list -> tail);

	ClearList(list);
	position = GetLast(list);
	CU_ASSERT_EQUAL(position, NULL);
}
void test_PriorPosition(void) {
	LIST_TYPE list = getTestList();

	CU_ASSERT_EQUAL(PriorPosition(list, list -> head), NULL);
	CU_ASSERT_EQUAL(PriorPosition(list ,list -> head -> next), list -> head);
}
void test_NextPosition(void) {
	LIST_TYPE list = getTestList();

	CU_ASSERT_EQUAL(NextPosition(list, list -> tail), NULL);
	CU_ASSERT_EQUAL(NextPosition(list ,list -> head), list -> head -> next);
}
void test_LocatePosition(void) {
	LIST_TYPE list = getTestList();
	Position position;
	Status result;

	result = LocatePosition(list, 0, &position);
	CU_ASSERT_EQUAL(result, ERROR);
	CU_ASSERT_PTR_NULL(position);

	result = LocatePosition(list, TEST_LIST_LENGTH + 1, &position);
	CU_ASSERT_EQUAL(result, ERROR);
	CU_ASSERT_PTR_NULL(position);

	result = LocatePosition(list, 1, &position);
	CU_ASSERT_EQUAL(result, OK);
	CU_ASSERT_EQUAL(position, list -> head);

	result = LocatePosition(list, 2, &position);
	CU_ASSERT_EQUAL(result, OK);
	CU_ASSERT_EQUAL(position, list -> head -> next);

	result = LocatePosition(list, 3, &position);
	CU_ASSERT_EQUAL(result, OK);
	CU_ASSERT_EQUAL(position, list -> tail);
}

void test_LocateElement(void) {
	LIST_TYPE list = getTestList();

	CU_ASSERT_PTR_NULL(LocateElement(list, 0, &compare));
	CU_ASSERT_PTR_NULL(LocateElement(list, TEST_LIST_LENGTH + 1, &compare));

	CU_ASSERT_EQUAL(LocateElement(list, 1, &compare), list -> head);
	CU_ASSERT_EQUAL(LocateElement(list, 2, &compare), list -> head -> next);
	CU_ASSERT_EQUAL(LocateElement(list, 3, &compare), list -> tail);
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

int main(void) {
	CU_initialize_registry();

	CU_pSuite pSuite = CU_add_suite("List Test Suite", NULL, NULL);
	CU_ADD_TEST(pSuite, test_MakeNode);
	CU_ADD_TEST(pSuite, test_FreeNode);
	CU_ADD_TEST(pSuite, test_InitialList);
	CU_ADD_TEST(pSuite, test_DestroyList);
	CU_ADD_TEST(pSuite, test_ClearList);
	CU_ADD_TEST(pSuite, test_InsertFirst);
	CU_ADD_TEST(pSuite, test_DeleteFirst);
	CU_ADD_TEST(pSuite, test_Append);
	CU_ADD_TEST(pSuite, test_Remove);
	CU_ADD_TEST(pSuite, test_InsertBefore);
	CU_ADD_TEST(pSuite, test_InsertAfter);
	CU_ADD_TEST(pSuite, test_SetElement);
	CU_ADD_TEST(pSuite, test_GetElement);
	CU_ADD_TEST(pSuite, test_ListEmpty);
	CU_ADD_TEST(pSuite, test_ListLength);
	CU_ADD_TEST(pSuite, test_GetFirst);
	CU_ADD_TEST(pSuite, test_GetLast);
	CU_ADD_TEST(pSuite, test_PriorPosition);
	CU_ADD_TEST(pSuite, test_NextPosition);
	CU_ADD_TEST(pSuite, test_LocatePosition);
	CU_ADD_TEST(pSuite, test_LocateElement);
	CU_ADD_TEST(pSuite, test_ListTraverse);

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

	CU_cleanup_registry();
	return CU_get_error();
}
