/*
 * sequence_array_test.c
 *
 *  Created on: 2009-7-19
 *      Author: yuandong
 */

#include <stdlib.h>

#include "include/array/sequence_array.h"

#include "include/CUnit/Basic.h"
#include "include/CUnit/Console.h"
#include "include/CUnit/Automated.h"
#include "include/CUnit/TestDB.h"

SequenceArray getTestArray() {
	SequenceArray array = NULL;
	Status status = ERROR;

	status = Initial(&array, 4, 2, 3, 4, 5);
	CU_ASSERT_EQUAL(status, OK);
	CU_ASSERT_PTR_NOT_NULL(array);

	if (status != OK)
		return NULL;
	return array;
}

void test_Initial(void) {
	SequenceArray array = NULL;
	Status status;

	//dimension error
	status = OK;
	array = NULL;
	status = Initial(&array, 0, 2, 3, 4, 5);
	CU_ASSERT_EQUAL(status, ERROR);

	//OK
	status = ERROR;
	array = NULL;
	status = Initial(&array, 4, 2, 3, 4, 5);
	CU_ASSERT_EQUAL(status, OK);
	CU_ASSERT_PTR_NOT_NULL(array);
	if (array != NULL) {
		CU_ASSERT_EQUAL(array -> dimension, 4);
		CU_ASSERT_PTR_NOT_NULL(array -> base);
		CU_ASSERT_PTR_NOT_NULL(array -> bounds);
		CU_ASSERT_PTR_NOT_NULL(array -> constants);

		if (array -> bounds != NULL) {
			CU_ASSERT_EQUAL((array -> bounds)[0], 2);
			CU_ASSERT_EQUAL((array -> bounds)[1], 3);
			CU_ASSERT_EQUAL((array -> bounds)[2], 4);
			CU_ASSERT_EQUAL((array -> bounds)[3], 5);
		}

		if (array -> constants != NULL) {
			CU_ASSERT_EQUAL((array -> constants)[0], 60);
			CU_ASSERT_EQUAL((array -> constants)[1], 20);
			CU_ASSERT_EQUAL((array -> constants)[2], 5);
			CU_ASSERT_EQUAL((array -> constants)[3], 1);
		}
	}
}
void test_Destory(void) {
	Status status;
	SequenceArray array = getTestArray();

	if (array == NULL)
		return;

	status = ERROR;
	status = Destory(&array);
	CU_ASSERT_EQUAL(status, OK);
	CU_ASSERT_PTR_NULL(array);
}
void test_Assign(void) {
	SequenceArray array = getTestArray();
	if (array == NULL)
		return;

	Status status;
	int a, b, c, d, count;

	//清零
	for (a = 0; a < 2; a++) {
		for (b = 0; b < 3; b++) {
			for (c = 0; c < 4; c++) {
				for (d = 0; d < 5; d++) {
					status = Assign(array, 0, 4, a, b, c, d);
					CU_ASSERT_EQUAL(status, OK);
					if (status != OK)
						return;
				}
			}
		}
	}
	count = 0;
	for (a = 0; a < 2; a++) {
		for (b = 0; b < 3; b++) {
			for (c = 0; c < 4; c++) {
				for (d = 0; d < 5; d++) {
					CU_ASSERT_EQUAL((array -> base)[count], 0);
					count++;
				}
			}
		}
	}
	//数列
	count = 0;
	for (a = 0; a < 2; a++) {
		for (b = 0; b < 3; b++) {
			for (c = 0; c < 4; c++) {
				for (d = 0; d < 5; d++) {
					status = Assign(array, count, 4, a, b, c, d);
					CU_ASSERT_EQUAL(status, OK);
					if (status != OK)
						return;
					count++;
				}
			}
		}
	}
	count = 0;
	for (a = 0; a < 2; a++) {
		for (b = 0; b < 3; b++) {
			for (c = 0; c < 4; c++) {
				for (d = 0; d < 5; d++) {
					CU_ASSERT_EQUAL((array -> base)[count], count);
					count++;
				}
			}
		}
	}
}
void test_Value(void) {
	SequenceArray array = getTestArray();
	if (array == NULL)
		return;

	Status status;
	int a, b, c, d, count;
	int value;

	//数列
	count = 0;
	for (a = 0; a < 2; a++) {
		for (b = 0; b < 3; b++) {
			for (c = 0; c < 4; c++) {
				for (d = 0; d < 5; d++) {
					(array -> base)[count] = count;
					count++;
				}
			}
		}
	}
	count = 0;
	for (a = 0; a < 2; a++) {
		for (b = 0; b < 3; b++) {
			for (c = 0; c < 4; c++) {
				for (d = 0; d < 5; d++) {
					status = Value(array, &value, 4, a, b, c, d);
					CU_ASSERT_EQUAL(status, OK);
					if (status != OK)
						return;
					CU_ASSERT_EQUAL(value, count);
					count++;
				}
			}
		}
	}
}
int main(void) {
	CU_initialize_registry();

	CU_pSuite pSuite = CU_add_suite("Sequence Array Test Suite", NULL, NULL);
	CU_ADD_TEST(pSuite, test_Initial);
	CU_ADD_TEST(pSuite, test_Destory);
	CU_ADD_TEST(pSuite, test_Assign);
	CU_ADD_TEST(pSuite, test_Value);

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

	CU_cleanup_registry();
	return CU_get_error();
}
