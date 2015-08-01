/*
 * cross_sparse_matrix_test.c
 *
 *  Created on: 2009-8-6
 *      Author: yuandong
 */

#include <stdlib.h>

#include "include/array/cross_sparse_matrix.h"
#include "test/array/sparse_matrix_test.c"

void test_Initial(void) {
	CrossSparseMatrix matrix;
	Status status;

	matrix = NULL;
	status = ERROR;

	status = Initial(&matrix, 4, 5);

	CU_ASSERT_EQUAL(status, OK);
	CU_ASSERT_PTR_NOT_NULL(matrix);

	if (matrix != NULL) {
		CU_ASSERT_EQUAL(matrix -> row_length, 4);
		CU_ASSERT_EQUAL(matrix -> column_length, 5);
		CU_ASSERT_EQUAL(matrix -> value_count, 0);
		CU_ASSERT_PTR_NOT_NULL(matrix -> row);
		CU_ASSERT_PTR_NOT_NULL(matrix -> column);

		if (matrix -> row != NULL) {
			int i = 0;
			for (i = 0; i < 4; i++) {
				CU_ASSERT_PTR_NULL((matrix -> row)[i]);
			}
			for (i = 0; i < 5; i++) {
				CU_ASSERT_PTR_NULL((matrix -> column)[i]);
			}
		}
	}
}
void assertEuqal(CrossSparseMatrix matrix, int row_index, int column_index,
		int value) {

	CrossSparseMatrixNode *node = (matrix -> row)[row_index - 1];
	while (node != NULL && node -> column_index != column_index)
		node = node -> right;

	CU_ASSERT_PTR_NOT_NULL(node);
	if (node == NULL)
		return;
	CU_ASSERT_EQUAL(row_index, node -> row_index);
	CU_ASSERT_EQUAL(column_index, node -> column_index);
	CU_ASSERT_EQUAL(value, node -> value);

	node = (matrix -> column)[column_index - 1];
	while (node != NULL && node -> row_index != row_index)
		node = node -> down;
	CU_ASSERT_PTR_NOT_NULL(node);
	if (node == NULL)
		return;
	CU_ASSERT_EQUAL(row_index, node -> row_index);
	CU_ASSERT_EQUAL(column_index, node -> column_index);
	CU_ASSERT_EQUAL(value, node -> value);
}
void test_Assign(void) {
	CrossSparseMatrix matrix = NULL;
	Status status = Initial(&matrix, 4, 5);

	CU_ASSERT_EQUAL(status, OK);
	if (status != OK)
		return;

	//insert
	status = Assign(matrix, 1, 1, 1);
	status = Assign(matrix, 1, 3, 3);
	status = Assign(matrix, 3, 1, 7);
	status = Assign(matrix, 3, 3, 9);
	status = Assign(matrix, 1, 2, 2);
	status = Assign(matrix, 2, 1, 4);
	status = Assign(matrix, 2, 3, 6);
	status = Assign(matrix, 3, 2, 8);
	status = Assign(matrix, 2, 2, 5);
	CU_ASSERT_EQUAL(status, OK);
	if (status != OK)
		return;

	CU_ASSERT_EQUAL(matrix -> value_count, 9);
	assertEuqal(matrix, 1, 1, 1);
	assertEuqal(matrix, 1, 3, 3);
	assertEuqal(matrix, 3, 1, 7);
	assertEuqal(matrix, 3, 3, 9);
	assertEuqal(matrix, 1, 2, 2);
	assertEuqal(matrix, 2, 1, 4);
	assertEuqal(matrix, 2, 3, 6);
	assertEuqal(matrix, 3, 2, 8);
	assertEuqal(matrix, 2, 2, 5);

	//set
	Assign(matrix, 1, 1, 11);
	Assign(matrix, 1, 3, 13);
	Assign(matrix, 3, 1, 17);
	Assign(matrix, 3, 3, 19);
	Assign(matrix, 1, 2, 12);
	Assign(matrix, 2, 1, 14);
	Assign(matrix, 2, 3, 16);
	Assign(matrix, 3, 2, 18);
	Assign(matrix, 2, 2, 15);

	CU_ASSERT_EQUAL(matrix -> value_count, 9);
	assertEuqal(matrix, 1, 1, 11);
	assertEuqal(matrix, 1, 3, 13);
	assertEuqal(matrix, 3, 1, 17);
	assertEuqal(matrix, 3, 3, 19);
	assertEuqal(matrix, 1, 2, 12);
	assertEuqal(matrix, 2, 1, 14);
	assertEuqal(matrix, 2, 3, 16);
	assertEuqal(matrix, 3, 2, 18);
	assertEuqal(matrix, 2, 2, 15);

	//clear
	Assign(matrix, 1, 1, 0);
	Assign(matrix, 1, 3, 0);
	Assign(matrix, 3, 1, 0);
	Assign(matrix, 3, 3, 0);
	Assign(matrix, 1, 2, 0);
	Assign(matrix, 2, 1, 0);
	Assign(matrix, 2, 3, 0);
	Assign(matrix, 3, 2, 0);
	Assign(matrix, 2, 2, 0);

	int i = 0;
	for (i = 0; i < 4; i++) {
		CU_ASSERT_PTR_NULL((matrix -> row)[i]);
	}
	for (i = 0; i < 5; i++) {
		CU_ASSERT_PTR_NULL((matrix -> column)[i]);
	}
	CU_ASSERT_EQUAL(matrix -> value_count, 0);
}

int main(void) {
	CU_pSuite pSuite = buildTestSuite();
	CU_ADD_TEST(pSuite, test_Initial);
	CU_ADD_TEST(pSuite, test_Assign);

	return runTestSuite();
}
