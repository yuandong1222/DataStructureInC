/*
 * triplet_sparse_matrix.h
 *
 *  Created on: 2009-7-25
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_ARRAY_TRIPLET_SPARSE_MATRIX_H_
#define DATA_STRUCTURE_IN_C_ARRAY_TRIPLET_SPARSE_MATRIX_H_

#define ElementType int
#define SPARSE_MATRIX_TYPE TripletSparseMatrix

#include "include/common.h"

#define MAX_SIZE 100

typedef struct {
	int row_index, column_index;
	ElementType value;
} Triplet;

//ÈýÔª×éÏ¡Êè¾ØÕó
typedef struct TripletSparseMatrixHead {
	Triplet data[MAX_SIZE];
	int row_length, column_length, value_count;
} TripletSparseMatrixHead, *TripletSparseMatrix;

#endif /* DATA_STRUCTURE_IN_C_ARRAY_TRIPLET_SPARSE_MATRIX_H_ */
