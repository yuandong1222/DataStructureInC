/*
 * sparse_matrix_test.c
 *
 *  Created on: 2009-7-25
 *      Author: yuandong
 */

#include <stdlib.h>

#include "include/array/sparse_matrix.h"

#include "CUnit/Basic.h"
#include "CUnit/Console.h"
#include "CUnit/Automated.h"
#include "CUnit/TestDB.h"

SPARSE_MATRIX_TYPE getSparseMatrix(int row_length, int column_length,
		int* values, int value_length) {

	SPARSE_MATRIX_TYPE matrix = NULL;
	Status status = ERROR;

	status = Initial(&matrix, row_length, column_length);
	CU_ASSERT_EQUAL(status, OK);
	if (status != OK)
		return NULL;

	int index = 0;
	for (index = 0; index < value_length * 3; index += 3) {
		status = Assign(matrix, values[index], values[index + 1], values[index
				+ 2]);
		CU_ASSERT_EQUAL(status, OK);
		if (status != OK)
			return NULL;
	}

	return matrix;
}

//(1, 1, 13), (2, 3, 11), (3, 4, 12)
SPARSE_MATRIX_TYPE getExampleSparseMatrix() {
	int values[3][3] = { { 1, 1, 13 }, { 2, 3, 11 }, { 3, 4, 12 } };
	return getSparseMatrix(4, 5, ((int*) values), 3);
}

int getValue(int* values, int value_length, int row_index, int column_index) {
	int index = 0;
	for (index = 0; index < value_length * 3; index += 3) {
		if (values[index] == row_index && values[index + 1] == column_index)
			return values[index + 2];
	}
	return 0;
}
void assertMatrixEqual(SPARSE_MATRIX_TYPE matrix, int row_length,
		int column_length, int* values, int value_length) {

	int row_index = 1, column_index = 1, value = 0, expect_value = 0;
	Status status;

	for (row_index = 1; row_index <= row_length; row_index++) {
		for (column_index = 1; column_index <= column_length; column_index++) {

			expect_value = getValue(values, value_length, row_index,
					column_index);

			status = Value(matrix, &value, row_index, column_index);
			CU_ASSERT_EQUAL(status, OK);
			CU_ASSERT_EQUAL(value, expect_value);
		}
	}
}

void test_Destory(void) {
	SPARSE_MATRIX_TYPE matrix = getExampleSparseMatrix();
	CU_ASSERT_PTR_NOT_NULL(matrix);
	if (matrix == NULL)
		return;

	Status status;

	status = Destory(&matrix);
	CU_ASSERT_EQUAL(status, OK);
	CU_ASSERT_PTR_NULL(matrix);
}

void test_Assign_Error(void) {
	SPARSE_MATRIX_TYPE matrix = getExampleSparseMatrix();
	CU_ASSERT_PTR_NOT_NULL(matrix);
	if (matrix == NULL)
		return;

	Status status;

	status = Assign(matrix, -1, 1, 1);
	CU_ASSERT_EQUAL(status, ERROR);

	status = Assign(matrix, 1, -1, 1);
	CU_ASSERT_EQUAL(status, ERROR);

	status = Assign(matrix, 5, 1, 1);
	CU_ASSERT_EQUAL(status, ERROR);

	status = Assign(matrix, 1, 6, 1);
	CU_ASSERT_EQUAL(status, ERROR);
}

void test_Value(void) {
	SPARSE_MATRIX_TYPE matrix = getExampleSparseMatrix();
	CU_ASSERT_PTR_NOT_NULL(matrix);
	if (matrix == NULL)
		return;

	//(1, 1, 13), (2, 3, 11), (3, 4, 12)
	int values[3][3] = { { 1, 1, 13 }, { 2, 3, 11 }, { 3, 4, 12 } };
	assertMatrixEqual(matrix, 4, 5, ((int*) values), 3);
}

void test_Copy(void) {
	SPARSE_MATRIX_TYPE matrix = getExampleSparseMatrix();
	CU_ASSERT_PTR_NOT_NULL(matrix);
	if (matrix == NULL)
		return;

	SPARSE_MATRIX_TYPE matrix_duplication = NULL;
	Status status = ERROR;

	status = Copy(matrix, &matrix_duplication);

	CU_ASSERT_EQUAL(status, OK);
	CU_ASSERT_PTR_NOT_NULL(matrix_duplication);
	CU_ASSERT_NOT_EQUAL(matrix, matrix_duplication);
	if (matrix_duplication == NULL)
		return;

	//(1, 1, 13), (2, 3, 11), (3, 4, 12)
	int values[3][3] = { { 1, 1, 13 }, { 2, 3, 11 }, { 3, 4, 12 } };
	assertMatrixEqual(matrix_duplication, 4, 5, ((int*) values), 3);
}

void test_Add(void) {
	int value_a[4][3] = { { 1, 1, 1 }, { 2, 3, 5 }, { 3, 2, 2 }, { 4, 2, 3 } };
	int value_b[3][3] = { { 1, 1, 13 }, { 2, 2, 9 }, { 3, 2, -2 } };
	int
			value_sum[4][3] = { { 1, 1, 14 }, { 2, 2, 9 }, { 2, 3, 5 }, { 4, 2,
					3 } };

	SPARSE_MATRIX_TYPE matrix_a = getSparseMatrix(4, 5, ((int*) value_a), 4);
	SPARSE_MATRIX_TYPE matrix_b = getSparseMatrix(4, 5, ((int*) value_b), 3);
	SPARSE_MATRIX_TYPE matrix_sum = NULL;

	Status status = ERROR;

	status = Add(matrix_a, matrix_b, &matrix_sum);
	CU_ASSERT_EQUAL(status, OK);
	if (status != OK)
		return;

	assertMatrixEqual(matrix_sum, 4, 5, ((int*) value_sum), 4);
}
void test_Subtract(void) {
	int value_a[4][3] = { { 1, 1, 1 }, { 2, 3, 5 }, { 3, 2, 2 }, { 4, 2, 3 } };
	int value_b[3][3] = { { 1, 1, 13 }, { 2, 2, 9 }, { 3, 2, 2 } };
	int value_sub[4][3] = { { 1, 1, -12 }, { 2, 2, -9 }, { 2, 3, 5 },
			{ 4, 2, 3 } };

	SPARSE_MATRIX_TYPE matrix_a = getSparseMatrix(4, 5, ((int*) value_a), 4);
	SPARSE_MATRIX_TYPE matrix_b = getSparseMatrix(4, 5, ((int*) value_b), 3);
	SPARSE_MATRIX_TYPE matrix_sub = NULL;

	Status status = ERROR;

	status = Subtract(matrix_a, matrix_b, &matrix_sub);
	CU_ASSERT_EQUAL(status, OK);
	if (status != OK)
		return;

	assertMatrixEqual(matrix_sub, 4, 5, ((int*) value_sub), 4);
}
void test_Multiply(void) {
	int value_a[5][3] = { { 1, 1, 1 }, { 1, 3, 2 }, { 2, 1, -1 }, { 2, 2, 3 },
			{ 2, 3, 1 } };
	int value_b[5][3] = { { 1, 1, 3 }, { 1, 2, 1 }, { 2, 1, 2 }, { 2, 2, 1 }, {
			3, 1, 1 } };
	int value_product[4][3] = { { 1, 1, 5 }, { 1, 2, 1 }, { 2, 1, 4 }, { 2, 2,
			2 } };

	SPARSE_MATRIX_TYPE matrix_a = getSparseMatrix(2, 3, ((int*) value_a), 5);
	SPARSE_MATRIX_TYPE matrix_b = getSparseMatrix(3, 2, ((int*) value_b), 5);
	SPARSE_MATRIX_TYPE matrix_product = NULL;

	Status status = ERROR;

	status = Multiply(matrix_a, matrix_b, &matrix_product);
	CU_ASSERT_EQUAL(status, OK);
	if (status != OK)
		return;

	assertMatrixEqual(matrix_product, 2, 2, ((int*) value_product), 4);
}

void test_Transpose(void) {
	int value[3][3] = { { 1, 1, 1 }, { 2, 1, 3 }, { 2, 3, 6 } };
	int value_transposed[3][3] = { { 1, 1, 1 }, { 1, 2, 3 }, { 3, 2, 6 } };

	SPARSE_MATRIX_TYPE matrix = getSparseMatrix(2, 3, ((int*) value), 3);
	SPARSE_MATRIX_TYPE matrix_transposed = NULL;

	Status status = ERROR;

	status = Transpose(matrix, &matrix_transposed);
	CU_ASSERT_EQUAL(status, OK);
	if (status != OK)
		return;

	assertMatrixEqual(matrix_transposed, 3, 2, ((int*) value_transposed), 3);
}

CU_pSuite buildTestSuite() {
	CU_initialize_registry();

	CU_pSuite pSuite = CU_add_suite("Sparse Matrix Test Suite", NULL, NULL);
	CU_ADD_TEST(pSuite, test_Assign_Error);
	CU_ADD_TEST(pSuite, test_Destory);
	CU_ADD_TEST(pSuite, test_Value);
	CU_ADD_TEST(pSuite, test_Copy);
	CU_ADD_TEST(pSuite, test_Add);
	CU_ADD_TEST(pSuite, test_Subtract);
	CU_ADD_TEST(pSuite, test_Multiply);
	CU_ADD_TEST(pSuite, test_Transpose);

	return pSuite;
}
int runTestSuite() {
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

	CU_cleanup_registry();
	return CU_get_error();
}
