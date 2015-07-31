/*
 * cross_sparse_matrix.h
 *
 *  Created on: 2009-8-6
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_ARRAY_CROSS_SPARSE_MATRIX_H_
#define DATA_STRUCTURE_IN_C_ARRAY_CROSS_SPARSE_MATRIX_H_

#define ElementType int
#define SPARSE_MATRIX_TYPE CrossSparseMatrix

#include "include/common.h"

#define MAX_SIZE 100

typedef struct CrossSparseMatrixNode {
	int row_index, column_index;
	struct CrossSparseMatrixNode *right, *down;
	ElementType value;
} CrossSparseMatrixNode;

//Ê®×ÖÁ´±íÏ¡Êè¾ØÕó
typedef struct CrossSparseMatrixHead {
	CrossSparseMatrixNode **row, **column;
	int row_length, column_length, value_count;
} CrossSparseMatrixHead, *CrossSparseMatrix;

#endif /* DATA_STRUCTURE_IN_C_ARRAY_CROSS_SPARSE_MATRIX_H_ */
