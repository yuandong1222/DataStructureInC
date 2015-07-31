/*
 * sparse_matrix_test.c
 *
 *  Created on: 2009-7-25
 *      Author: yuandong
 */

#include <stdlib.h>

#include "include/array/triplet_sparse_matrix.h"
#include "test/array/sparse_matrix_test.c"

void test_Initial(void) {
	TripletSparseMatrix matrix;
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
	}
}
void test_Assign(void) {
	TripletSparseMatrix matrix = NULL;
	Status status;

	status = Initial(&matrix, 4, 5);
	CU_ASSERT_EQUAL(status, OK);
	if (status != OK)
		return;

	//(2, 3, 11)
	status = Assign(matrix, 2, 3, 11);
	CU_ASSERT_EQUAL(status, OK);
	if (status != OK)
		return;

	CU_ASSERT_EQUAL(matrix -> value_count, 1);
	CU_ASSERT_EQUAL((matrix -> data)[0].row_index, 2);
	CU_ASSERT_EQUAL((matrix -> data)[0].column_index, 3);
	CU_ASSERT_EQUAL((matrix -> data)[0].value, 11);

	//(2, 3, 11), (3, 4, 12)
	status = Assign(matrix, 3, 4, 12);
	CU_ASSERT_EQUAL(status, OK);
	if (status != OK)
		return;

	CU_ASSERT_EQUAL(matrix -> value_count, 2);
	CU_ASSERT_EQUAL((matrix -> data)[0].row_index, 2);
	CU_ASSERT_EQUAL((matrix -> data)[0].column_index, 3);
	CU_ASSERT_EQUAL((matrix -> data)[0].value, 11);

	CU_ASSERT_EQUAL((matrix -> data)[1].row_index, 3);
	CU_ASSERT_EQUAL((matrix -> data)[1].column_index, 4);
	CU_ASSERT_EQUAL((matrix -> data)[1].value, 12);

	//(2, 3, 11), (3, 4, 12), (1, 1, 13)
	status = Assign(matrix, 1, 1, 13);
	CU_ASSERT_EQUAL(status, OK);
	if (status != OK)
		return;

	CU_ASSERT_EQUAL(matrix -> value_count, 3);
	CU_ASSERT_EQUAL((matrix -> data)[0].row_index, 1);
	CU_ASSERT_EQUAL((matrix -> data)[0].column_index, 1);
	CU_ASSERT_EQUAL((matrix -> data)[0].value, 13);

	CU_ASSERT_EQUAL((matrix -> data)[1].row_index, 2);
	CU_ASSERT_EQUAL((matrix -> data)[1].column_index, 3);
	CU_ASSERT_EQUAL((matrix -> data)[1].value, 11);

	CU_ASSERT_EQUAL((matrix -> data)[2].row_index, 3);
	CU_ASSERT_EQUAL((matrix -> data)[2].column_index, 4);
	CU_ASSERT_EQUAL((matrix -> data)[2].value, 12);

	//(2, 3, 14), (3, 4, 12), (1, 1, 13)
	status = Assign(matrix, 2, 3, 14);
	CU_ASSERT_EQUAL(status, OK);
	if (status != OK)
		return;

	CU_ASSERT_EQUAL(matrix -> value_count, 3);
	CU_ASSERT_EQUAL((matrix -> data)[0].row_index, 1);
	CU_ASSERT_EQUAL((matrix -> data)[0].column_index, 1);
	CU_ASSERT_EQUAL((matrix -> data)[0].value, 13);

	CU_ASSERT_EQUAL((matrix -> data)[1].row_index, 2);
	CU_ASSERT_EQUAL((matrix -> data)[1].column_index, 3);
	CU_ASSERT_EQUAL((matrix -> data)[1].value, 14);

	CU_ASSERT_EQUAL((matrix -> data)[2].row_index, 3);
	CU_ASSERT_EQUAL((matrix -> data)[2].column_index, 4);
	CU_ASSERT_EQUAL((matrix -> data)[2].value, 12);

	//(2, 3, 14), (3, 4, 12)
	status = Assign(matrix, 1, 1, 0);
	CU_ASSERT_EQUAL(status, OK);
	if (status != OK)
		return;

	CU_ASSERT_EQUAL(matrix -> value_count, 2);
	CU_ASSERT_EQUAL((matrix -> data)[0].row_index, 2);
	CU_ASSERT_EQUAL((matrix -> data)[0].column_index, 3);
	CU_ASSERT_EQUAL((matrix -> data)[0].value, 14);

	CU_ASSERT_EQUAL((matrix -> data)[1].row_index, 3);
	CU_ASSERT_EQUAL((matrix -> data)[1].column_index, 4);
	CU_ASSERT_EQUAL((matrix -> data)[1].value, 12);

}

int main(void) {
	CU_pSuite pSuite = buildTestSuite();
	CU_ADD_TEST(pSuite, test_Initial);
	CU_ADD_TEST(pSuite, test_Assign);

	return runTestSuite();
}
