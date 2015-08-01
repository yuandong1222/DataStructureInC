/*
 * generalized_list_test.c
 *
 *  Created on: 2009-8-12
 *      Author: yuandong
 */

#include <stdlib.h>

#include "include/array/generalized_list.h"

#include "CUnit/Basic.h"
#include "CUnit/Console.h"
#include "CUnit/Automated.h"
#include "CUnit/TestDB.h"

GENERALIZED_LIST_TYPE getGeneralizedList(char* string) {
	GENERALIZED_LIST_TYPE list = NULL;
	Status status = ERROR;

	status = Create(&list, string);

	CU_ASSERT_EQUAL(status, OK);
	CU_ASSERT_PTR_NOT_NULL(list);

	if (status != OK || list == NULL)
		return NULL;

	return list;
}

void test_Initial(void) {
	GENERALIZED_LIST_TYPE list = (GENERALIZED_LIST_TYPE) 1;
	Status status = ERROR;

	status = Initial(&list);
	CU_ASSERT_EQUAL(status, OK);
	CU_ASSERT_PTR_NULL(list);
}
void test_Create(void) {
	GENERALIZED_LIST_TYPE list = NULL;
	Status status = ERROR;

	status = Create(&list, "()");
	CU_ASSERT_EQUAL(status, OK);
	assertEqual(list, "()");

	status = Create(&list, "(1,2,3)");
	CU_ASSERT_EQUAL(status, OK);
	assertEqual(list, "(1,2,3)");

	status = Create(&list, "((11,12,13),2,3)");
	CU_ASSERT_EQUAL(status, OK);
	assertEqual(list, "((11,12,13),2,3)");

	status = Create(&list, "((11,12,13),(21,22,23,24,25),3)");
	CU_ASSERT_EQUAL(status, OK);
	assertEqual(list, "((11,12,13),(21,22,23,24,25),3)");

	status = Create(&list,
			"((11,12,13),(21,22,23,24,25),3, (4, (51, 52, 53, (501, 502))))");
	CU_ASSERT_EQUAL(status, OK);
	assertEqual(list,
			"((11,12,13),(21,22,23,24,25),3, (4, (51, 52, 53, (501, 502))))");
}
void test_Destory(void) {
	Status status = ERROR;
	GENERALIZED_LIST_TYPE list = getGeneralizedList("(1,2,3,4)");
	if (list == NULL)
		return;

	status = Destory(&list);
	CU_ASSERT_EQUAL(status, OK);
	CU_ASSERT_PTR_NULL(list);
}
void test_Copy(void) {
	Status status = ERROR;
	GENERALIZED_LIST_TYPE list = getGeneralizedList("(1,2,3,4)");
	if (list == NULL)
		return;

	GENERALIZED_LIST_TYPE duplication = NULL;
	status = Copy(list, &duplication);

	CU_ASSERT_EQUAL(status, OK);
	CU_ASSERT_NOT_EQUAL(list, duplication);
	assertEqual(duplication, "(1,2,3,4)");
}
void test_Length(void) {
	GENERALIZED_LIST_TYPE list = NULL;
	CU_ASSERT_EQUAL(Length(list), 0);

	list = getGeneralizedList("(1,2)");
	CU_ASSERT_EQUAL(Length(list), 2);

	list = getGeneralizedList("(1,2,3,4)");
	CU_ASSERT_EQUAL(Length(list), 4);

	list = getGeneralizedList(
			"((11,12,13),(21,22,23,24,25),3,(4,(51,52,53,(501,502))))");
	CU_ASSERT_EQUAL(Length(list), 4);
}
void test_Depth(void) {
	GENERALIZED_LIST_TYPE list = NULL;
	CU_ASSERT_EQUAL(Depth(list), 0);

	list = getGeneralizedList("(1,2)");
	CU_ASSERT_EQUAL(Depth(list), 1);

	list = getGeneralizedList("(1,2,3,4)");
	CU_ASSERT_EQUAL(Depth(list), 1);

	list = getGeneralizedList("((11,12,13),(21,22,23,24,25),3)");
	CU_ASSERT_EQUAL(Depth(list), 2);

	list = getGeneralizedList(
			"((11,12,13),(21,22,23,24,25),3,(4,(51,52,53,(501,502))))");
	CU_ASSERT_EQUAL(Depth(list), 4);
}
void test_Empty(void) {
	GENERALIZED_LIST_TYPE list = NULL;
	CU_ASSERT_EQUAL(Empty(list), TRUE);

	list = getGeneralizedList("(1,2)");
	CU_ASSERT_EQUAL(Empty(list), FALSE);

	list = getGeneralizedList("(1,2,3,4)");
	CU_ASSERT_EQUAL(Empty(list), FALSE);
}
void test_GetHead(void) {
	GENERALIZED_LIST_TYPE list = NULL;
	CU_ASSERT_EQUAL(GetHead(list), NULL);

	list = getGeneralizedList("(1,2)");
	assertEqual(GetHead(list), "(1)");

	list = getGeneralizedList("((11,12,13),(21,22,23,24,25),3)");
	assertEqual(GetHead(list), "(11,12,13)");
}
void test_GetTail(void) {
	GENERALIZED_LIST_TYPE list = NULL;
	CU_ASSERT_EQUAL(GetTail(list), NULL);

	list = getGeneralizedList("(1,2)");
	assertEqual(GetTail(list), "(2)");

	list = getGeneralizedList(
			"((11,12,13),(21,22,23,24,25),3,(4,(51,52,53,(501,502))))");
	assertEqual(GetTail(list), "(4,(51,52,53,(501,502)))");
}
void test_InsertFirst(void) {
	Status status = ERROR;
	GENERALIZED_LIST_TYPE element, list = getGeneralizedList("(1,2)");
	if (list == NULL)
		return;

	list = NULL;
	element = getGeneralizedList("(1)");
	status = InsertFirst(&list, &element);
	CU_ASSERT_EQUAL(status, OK);
	assertEqual(list, "(1)");

	list = getGeneralizedList("(2)");
	element = getGeneralizedList("(1)");
	status = InsertFirst(&list, &element);
	CU_ASSERT_EQUAL(status, OK);
	assertEqual(list, "(1,2)");

	list = getGeneralizedList("((21,22,23,24,25),3,(4,(51,52,53,(501,502))))");
	element = getGeneralizedList("(11,12,13)");
	status = InsertFirst(&list, &element);
	CU_ASSERT_EQUAL(status, OK);
	assertEqual(list,
			"((11,12,13),(21,22,23,24,25),3,(4,(51,52,53,(501,502))))");
}
void test_DeleteFirst(void) {
	Status status = ERROR;
	GENERALIZED_LIST_TYPE element = NULL, list = getGeneralizedList("(1,2)");
	if (list == NULL)
		return;

	list = NULL;
	status = DeleteFirst(&list, &element);
	CU_ASSERT_EQUAL(status, OK);
	assertEqual(list, "()");
	assertEqual(element, "()");

	list = getGeneralizedList("(1)");
	status = DeleteFirst(&list, &element);
	CU_ASSERT_EQUAL(status, OK);
	assertEqual(list, "()");
	assertEqual(element, "(1)");

	list = getGeneralizedList("(1, 2)");
	status = DeleteFirst(&list, &element);
	CU_ASSERT_EQUAL(status, OK);
	assertEqual(list, "(2)");
	assertEqual(element, "(1)");

	list = getGeneralizedList(
			"((11,12,13),(21,22,23,24,25),3,(4,(51,52,53,(501,502))))");
	status = DeleteFirst(&list, &element);
	CU_ASSERT_EQUAL(status, OK);
	assertEqual(list, "((21,22,23,24,25),3,(4,(51,52,53,(501,502))))");
	assertEqual(element, "(11,12,13)");
}
Status visit(ElementType *element) {
	*element += 1;
	return OK;
}
void test_Traverse(void) {
	Status status = ERROR;
	GENERALIZED_LIST_TYPE list = list = getGeneralizedList(
			"((11,12,13),(21,22,23,24,25),3,(4,(51,52,53,(501,502))))");
	if (list == NULL)
		return;

	status = Traverse(&list, &visit);
	CU_ASSERT_EQUAL(status, OK);
	assertEqual(list,
			"((12,13,14),(22,23,24,25,26),4,(5,(52,53,54,(502,503))))");
}

CU_pSuite buildTestSuite() {
	CU_initialize_registry();

	CU_pSuite pSuite = CU_add_suite("Generalized List Test Suite", NULL, NULL);
	CU_ADD_TEST(pSuite, test_Initial);
	CU_ADD_TEST(pSuite, test_Create);
	CU_ADD_TEST(pSuite, test_Destory);
	CU_ADD_TEST(pSuite, test_Copy);
	CU_ADD_TEST(pSuite, test_Length);
	CU_ADD_TEST(pSuite, test_Depth);
	CU_ADD_TEST(pSuite, test_Empty);
	CU_ADD_TEST(pSuite, test_GetHead);
	CU_ADD_TEST(pSuite, test_GetTail);
	CU_ADD_TEST(pSuite, test_InsertFirst);
	CU_ADD_TEST(pSuite, test_DeleteFirst);
	CU_ADD_TEST(pSuite, test_Traverse);

	return pSuite;
}
int runTestSuite() {
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

	CU_cleanup_registry();
	return CU_get_error();
}
