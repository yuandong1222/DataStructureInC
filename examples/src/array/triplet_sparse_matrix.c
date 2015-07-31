/*
 * triplet_sparse_matrix.c
 *
 *  Created on: 2009-7-25
 *      Author: yuandong
 */

#include <stdlib.h>
#include <stdio.h>

#include "include/common.h"
#include "include/array/triplet_sparse_matrix.h"
#include "include/array/sparse_matrix.h"

int compareIndex(Triplet *a, Triplet *b) {
	if (a -> row_index > b -> row_index)
		return 1;

	if (a -> row_index < b -> row_index)
		return -1;

	if (a -> row_index == b -> row_index) {
		if (a -> column_index > b -> column_index)
			return 1;

		if (a -> column_index < b -> column_index)
			return -1;

		return 0;
	}

	return 0;
}

Status Initial(SPARSE_MATRIX_TYPE *matrix, int row_length, int column_length) {

	(*matrix) = (TripletSparseMatrix) malloc(sizeof(TripletSparseMatrixHead));
	if (*matrix == NULL)
		return OVERFLOW;

	(*matrix) -> row_length = row_length;
	(*matrix) -> column_length = column_length;
	(*matrix) -> value_count = 0;

	return OK;
}

Status Destory(SPARSE_MATRIX_TYPE *matrix) {
	free(*matrix);
	*matrix = NULL;
	return OK;
}

Status Assign(SPARSE_MATRIX_TYPE matrix, int row_index, int column_index,
		ElementType element) {

	if (row_index <= 0 || row_index > matrix -> row_length || column_index <= 0
			|| column_index > matrix -> column_length) {
		return ERROR;
	}

	//find position
	int i = 0, position = 0;
	Triplet * triplet = NULL;
	for (i = 0; i < matrix -> value_count; i++) {
		triplet = (matrix -> data) + i;
		if ((triplet -> row_index > row_index) || (triplet -> row_index
				== row_index && triplet -> column_index >= column_index))
			break;
	}
	position = i;

	//append
	if (position == matrix -> value_count) {
		(matrix -> data)[position].row_index = row_index;
		(matrix -> data)[position].column_index = column_index;
		(matrix -> data)[position].value = element;

		(matrix -> value_count)++;

		return OK;
	}
	//replace
	if (triplet -> row_index == row_index && triplet -> column_index
			== column_index) {
		triplet -> value = element;

		if (element != 0)
			return OK;

		//delete
		for (i = position; i < matrix -> value_count - 1; i++) {
			(matrix -> data)[i].row_index = (matrix -> data)[i + 1].row_index;
			(matrix -> data)[i].column_index
					= (matrix -> data)[i + 1].column_index;
			(matrix -> data)[i].value = (matrix -> data)[i + 1].value;
		}

		(matrix -> value_count)--;
		return OK;
	}
	//insert
	for (i = matrix -> value_count; i > position; i--) {
		(matrix -> data)[i].row_index = (matrix -> data)[i - 1].row_index;
		(matrix -> data)[i].column_index = (matrix -> data)[i - 1].column_index;
		(matrix -> data)[i].value = (matrix -> data)[i - 1].value;
	}

	(matrix -> data)[position].row_index = row_index;
	(matrix -> data)[position].column_index = column_index;
	(matrix -> data)[position].value = element;

	(matrix -> value_count)++;

	return OK;
}

Status Value(SPARSE_MATRIX_TYPE matrix, ElementType *element, int row_index,
		int column_index) {
	int i = 0;
	Triplet * triplet = NULL;
	for (i = 0; i < matrix -> value_count; i++) {
		triplet = (matrix -> data) + i;
		if (triplet -> row_index == row_index && triplet -> column_index
				== column_index) {

			*element = triplet -> value;
			return OK;

		}
	}
	*element = 0;
	return OK;
}

Status Copy(SPARSE_MATRIX_TYPE matrix, SPARSE_MATRIX_TYPE *matrix_duplication) {
	Status status = Initial(matrix_duplication, matrix -> row_length,
			matrix -> column_length);

	if (status != OK)
		return status;

	int i = 0;
	for (i = 0; i < matrix -> value_count; i++) {
		((*matrix_duplication) -> data)[i].row_index
				= (matrix -> data)[i].row_index;
		((*matrix_duplication) -> data)[i].column_index
				= (matrix -> data)[i].column_index;
		((*matrix_duplication) -> data)[i].value = (matrix -> data)[i].value;
	}
	(*matrix_duplication) -> value_count = matrix -> value_count;

	return OK;
}

Status Add(SPARSE_MATRIX_TYPE a, SPARSE_MATRIX_TYPE b, SPARSE_MATRIX_TYPE *sum) {

	if (a -> row_length != b -> row_length || a -> column_length
			!= b -> column_length)
		return ERROR;

	Status status = Initial(sum, a -> row_length, b -> column_length);
	if (status != OK)
		return status;

	int index_a = 0, index_b = 0, index_sum = 0, value_count_a =
			a -> value_count, value_count_b = b -> value_count;
	while (index_a < value_count_a && index_b < value_count_b) {

		Triplet *triplet_a = (a -> data + index_a);
		Triplet *triplet_b = (b -> data + index_b);
		int compare_result = compareIndex(triplet_a, triplet_b);

		if (compare_result < 0) {
			((*sum) -> data)[index_sum].row_index = triplet_a -> row_index;
			((*sum) -> data)[index_sum].column_index
					= triplet_a -> column_index;
			((*sum) -> data)[index_sum].value = triplet_a -> value;

			index_a++;
			index_sum++;
			continue;
		}
		if (compare_result > 0) {
			((*sum) -> data)[index_sum].row_index = triplet_b -> row_index;
			((*sum) -> data)[index_sum].column_index
					= triplet_b -> column_index;
			((*sum) -> data)[index_sum].value = triplet_b -> value;

			index_b++;
			index_sum++;
			continue;
		}

		ElementType value = triplet_a -> value + triplet_b -> value;
		if (value != 0) {
			((*sum) -> data)[index_sum].row_index = triplet_b -> row_index;
			((*sum) -> data)[index_sum].column_index
					= triplet_b -> column_index;
			((*sum) -> data)[index_sum].value = value;
			index_sum++;
		}
		index_a++;
		index_b++;
	}

	while (index_a < value_count_a) {
		Triplet *triplet_a = (a -> data + index_a);
		((*sum) -> data)[index_sum].row_index = triplet_a -> row_index;
		((*sum) -> data)[index_sum].column_index = triplet_a -> column_index;
		((*sum) -> data)[index_sum].value = triplet_a -> value;

		index_a++;
		index_sum++;
	}
	while (index_b < value_count_b) {
		Triplet *triplet_b = (b -> data + index_b);
		((*sum) -> data)[index_sum].row_index = triplet_b -> row_index;
		((*sum) -> data)[index_sum].column_index = triplet_b -> column_index;
		((*sum) -> data)[index_sum].value = triplet_b -> value;

		index_b++;
		index_sum++;
	}

	(*sum) -> value_count = index_sum;

	return OK;
}

Status Subtract(SPARSE_MATRIX_TYPE a, SPARSE_MATRIX_TYPE b,
		SPARSE_MATRIX_TYPE *sub) {

	if (a -> row_length != b -> row_length || a -> column_length
			!= b -> column_length)
		return ERROR;

	TripletSparseMatrix b_duplication = NULL;
	Status status = Copy(b, &b_duplication);
	if (status != OK)
		return status;

	int i = 0;
	for (i = 0; i < b_duplication -> value_count; i++) {
		(b_duplication -> data)[i].value *= -1;
	}

	status = Add(a, b_duplication, sub);
	Destory(&b_duplication);

	return status;
}

Status Multiply(SPARSE_MATRIX_TYPE a, SPARSE_MATRIX_TYPE b,
		SPARSE_MATRIX_TYPE *product) {

	if (a -> column_length != b -> row_length)
		return ERROR;

	Status status = Initial(product, a -> row_length, b -> column_length);
	if (status != OK)
		return status;

	int index_a = 0, index_b = 0;
	ElementType element;
	for (index_a = 0; index_a < a -> value_count; index_a++) {
		for (index_b = 0; index_b < b -> value_count; index_b++) {
			Triplet *triplet_a = (a -> data) + index_a;
			Triplet *triplet_b = (b -> data) + index_b;

			if (triplet_a -> column_index != triplet_b -> row_index)
				continue;

			Value(*product, &element, triplet_a -> row_index,
					triplet_b -> column_index);
			element += (triplet_a -> value) * (triplet_b -> value);
			Assign(*product, triplet_a -> row_index, triplet_b -> column_index,
					element);
		}
	}
	return OK;
}

Status Transpose(SPARSE_MATRIX_TYPE matrix,
		SPARSE_MATRIX_TYPE *matrix_transposed) {

	int *offset = (int*) malloc(sizeof(int) * (matrix -> column_length + 1));
	if (offset == NULL)
		return OVERFLOW;

	int i = 0;

	for (i = 0; i < matrix -> column_length + 1; i++) {
		offset[i] = 0;
	}

	for (i = 0; i < matrix -> value_count; i++) {
		offset[(matrix -> data)[i].column_index]++;
	}

	for (i = 1; i < matrix -> column_length + 1; i++) {
		offset[i] += offset[i - 1];
	}

	Status status = Initial(matrix_transposed, matrix -> column_length,
			matrix -> row_length);
	if (status != OK)
		return status;

	for (i = 0; i < matrix -> value_count; i++) {
		Triplet *triplet = (matrix -> data) + i;
		int position = offset[triplet -> column_index - 1];

		((*matrix_transposed) -> data)[position].column_index
				= triplet -> row_index;
		((*matrix_transposed) -> data)[position].row_index
				= triplet -> column_index;
		((*matrix_transposed) -> data)[position].value = triplet -> value;

		offset[triplet -> column_index - 1]++;
	}

	(*matrix_transposed) -> value_count = matrix -> value_count;

	free(offset);

	return OK;
}
