/*
 * cross_sparse_matrix.c
 *
 *  Created on: 2009-8-6
 *      Author: yuandong
 */

#include <stdlib.h>
#include <stdio.h>

#include "include/common.h"
#include "include/array/cross_sparse_matrix.h"
#include "include/array/sparse_matrix.h"

int comparePosition(CrossSparseMatrixNode *a, CrossSparseMatrixNode *b) {
}

Status Initial(SPARSE_MATRIX_TYPE *matrix, int row_length, int column_length) {
}

Status Destory(SPARSE_MATRIX_TYPE *matrix) {
}

Status Assign(SPARSE_MATRIX_TYPE matrix, int row_index, int column_index,
		ElementType element) {
}

Status Value(SPARSE_MATRIX_TYPE matrix, ElementType *element, int row_index,
		int column_index) {
}

Status Copy(SPARSE_MATRIX_TYPE matrix, SPARSE_MATRIX_TYPE *matrix_duplication) {
}

Status Add(SPARSE_MATRIX_TYPE a, SPARSE_MATRIX_TYPE b, SPARSE_MATRIX_TYPE *sum) {
}

Status Subtract(SPARSE_MATRIX_TYPE a, SPARSE_MATRIX_TYPE b,
		SPARSE_MATRIX_TYPE *sub) {
}

Status Multiply(SPARSE_MATRIX_TYPE a, SPARSE_MATRIX_TYPE b,
		SPARSE_MATRIX_TYPE *product) {
}

Status Transpose(SPARSE_MATRIX_TYPE matrix,
		SPARSE_MATRIX_TYPE *matrix_transposed) {
}
