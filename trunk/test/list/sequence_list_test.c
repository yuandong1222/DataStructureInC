/*
 * sequence_list_test.c
 *
 *  Created on: 2009-4-10
 *      Author: yuandong
 */
#include <stdlib.h>

#include "include/CUnit/Basic.h"
#include "include/CUnit/Console.h"
#include "include/CUnit/Automated.h"
#include "include/CUnit/TestDB.h"

#include "include/list/sequence_list.h"
#include "include/list/list.h"

#define TEST_LIST_LENGTH 3

SequenceList getTestList() {
	SequenceList list;
	list = (SequenceList) malloc(sizeof(SequenceListHead));
	list -> element = (ElementType*) malloc(sizeof(ElementType)
			* LIST_INITIAL_SIZE);

	list -> length = 3;
	list -> listsize = 10;

	(list -> element)[0] = 1;
	(list -> element)[1] = 2;
	(list -> element)[2] = 3;

	return list;
}
void test_Increment(void) {
	LIST_TYPE list = NULL;
	Status result = InitialList(&list);
	int size = LIST_INITIAL_SIZE + LIST_INCREMENT;

	CU_ASSERT_EQUAL(result, OK);
	if (result != OK)
		return;

	int i = 0;
	for (i = 0; i < size - 1; i++) {
		result = ListInsert(list, 1, i);
		CU_ASSERT_EQUAL(result, OK);
		if (result != OK)
			return;
	}


	CU_ASSERT_EQUAL(list -> listsize, size);
	CU_ASSERT_EQUAL(list -> length, size - 1);
	for (i = 0; i < size - 1; i++) {
		CU_ASSERT_EQUAL(*(list -> element + i), size
				- i - 2);
	}
}
#include "test/list/list_test.c"
int main(void) {
	CU_pSuite suite = buildTestSuite();

	CU_ADD_TEST(suite, test_Increment);

	return runTestSuite();
}
