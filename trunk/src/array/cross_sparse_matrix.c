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

	int i = 0;

	(*matrix) = (CrossSparseMatrixHead*) malloc(sizeof(CrossSparseMatrixHead));
	(*matrix) -> row_length = row_length;
	(*matrix) -> column_length = column_length;
	(*matrix) -> value_count = 0;
	(*matrix) -> column = (CrossSparseMatrixNode**) malloc(
			sizeof(CrossSparseMatrixNode*) * column_length);
	(*matrix) -> row = (CrossSparseMatrixNode**) malloc(
			sizeof(CrossSparseMatrixNode*) * row_length);

	for (i = 0; i < column_length; i++)
		((*matrix) -> column)[i] = NULL;
	for (i = 0; i < row_length; i++)
		((*matrix) -> row)[i] = NULL;

	return OK;
}

Status Destory(SPARSE_MATRIX_TYPE *matrix) {
	CrossSparseMatrixNode *current, *next;

	int i = 0;
	for (i = 0; i < (*matrix) -> row_length; i++) {
		current = ((*matrix) -> row)[i];
		while (current != NULL) {
			next = current -> right;
			free(current);
			current = next;
		}
	}
	free((*matrix) -> column);
	free((*matrix) -> row);
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

	CrossSparseMatrixNode *up = NULL, *left = NULL;

	up = (matrix -> column)[column_index - 1];
	while (up != NULL && up -> down != NULL && up -> row_index < row_index
			&& up -> down -> row_index < row_index)
		up = up -> down;

	left = (matrix -> row)[row_index - 1];
	while (left != NULL && left -> right != NULL && left -> column_index
			< column_index && left -> right -> column_index < column_index)
		left = left -> right;

	//the whole row or column is NULL
	if (up == NULL || left == NULL) {
		if (element == 0)
			return OK;

		CrossSparseMatrixNode *node = (CrossSparseMatrixNode*) malloc(
				sizeof(CrossSparseMatrixNode));

		node -> row_index = row_index;
		node -> column_index = column_index;
		node -> value = element;

		if (up == NULL) {
			node -> down = NULL;
			(matrix -> column)[column_index - 1] = node;
		} else {
			node -> down = up -> down;
			up -> down = node;
		}

		if (left == NULL) {
			node -> right = NULL;
			(matrix -> row)[row_index - 1] = node;
		} else {
			node -> right = left -> right;
			left -> right = node;
		}

		(matrix -> value_count)++;
		return OK;
	}

	//find node
	CrossSparseMatrixNode *node = NULL;

	node = up != NULL && up -> row_index == row_index && up -> column_index
			== column_index ? up : node;
	node = left != NULL && left -> row_index == row_index
			&& left -> column_index == column_index ? left : node;
	node = up -> down != NULL && up -> down -> row_index == row_index
			&& up -> down -> column_index == column_index ? up -> down : node;
	node = left -> right != NULL && left -> right -> row_index == row_index
			&& left -> right -> column_index == column_index ? left -> right
			: node;

	//find
	if (node != NULL) {
		if (element == 0) {
			if (node == (matrix -> column)[column_index - 1]) {
				(matrix -> column)[column_index - 1] = node -> down;
			} else {
				up -> down = node -> down;
			}
			if (node == (matrix -> row)[row_index - 1]) {
				(matrix -> row)[row_index - 1] = node -> right;
			} else {
				left -> right = node -> right;
			}
			free(node);
			(matrix -> value_count)--;
			return OK;
		}

		node -> value = element;
		return OK;
	}

	//not find
	if (element == 0)
		return OK;

	node = (CrossSparseMatrixNode*) malloc(sizeof(CrossSparseMatrixNode));

	node -> row_index = row_index;
	node -> column_index = column_index;
	node -> value = element;
	node -> right = left -> right;
	node -> down = up -> down;

	up -> down = node;
	left -> right = node;

	(matrix -> value_count)++;
	return OK;

}

Status Value(SPARSE_MATRIX_TYPE matrix, ElementType *element, int row_index,
		int column_index) {

	CrossSparseMatrixNode *node = (matrix -> row)[row_index - 1];
	while (node != NULL && node -> column_index != column_index)
		node = node -> right;

	*element = node == NULL ? 0 : node -> value;
	return OK;

}

Status Copy(SPARSE_MATRIX_TYPE matrix, SPARSE_MATRIX_TYPE *matrix_duplication) {
	Status status = Initial(matrix_duplication, matrix -> row_length,
			matrix -> column_length);
	if (status != OK)
		return status;

	int i = 0;
	CrossSparseMatrixNode *node, *up, *left;
	for (i = 0; i < matrix -> row_length; i++) {
		node = (matrix -> row)[i];
		while (node != NULL) {
			CrossSparseMatrixNode *new_node = (CrossSparseMatrixNode*) malloc(
					sizeof(CrossSparseMatrixNode));

			new_node -> row_index = node -> row_index;
			new_node -> column_index = node -> column_index;
			new_node -> value = node -> value;
			new_node -> right = NULL;
			new_node -> down = NULL;

			if (((*matrix_duplication) -> row)[i] == NULL) {
				((*matrix_duplication) -> row)[i] = new_node;
				left = new_node;
			} else {
				left -> right = new_node;
				left = new_node;
			}
			if (((*matrix_duplication) -> column)[node -> column_index - 1]
					== NULL) {
				((*matrix_duplication) -> column)[node -> column_index - 1]
						= new_node;
			} else {
				up
						= ((*matrix_duplication) -> column)[node -> column_index
								- 1];
				while (up -> down != NULL)
					up = up -> down;

				up -> down = new_node;
			}

			node = node -> right;
		}
	}

	(*matrix_duplication) -> value_count = matrix -> value_count;

	return OK;
}

Status Add(SPARSE_MATRIX_TYPE a, SPARSE_MATRIX_TYPE b, SPARSE_MATRIX_TYPE *sum) {
	Status status = Initial(sum, a -> row_length, a -> column_length);
	if (status != OK)
		return status;

	int i = 0;
	CrossSparseMatrixNode *a_node = NULL, *b_node = NULL, *up = NULL, *left =
			NULL;
	for (i = 0; i < a -> row_length; i++) {
		a_node = a_node == NULL && (a -> row)[i] != NULL ? (a -> row)[i]
				: a_node;
		b_node = b_node == NULL && (b -> row)[i] != NULL ? (b -> row)[i]
				: b_node;
	}

	int column_index = 0, row_index = 0, value_count = 0, use_a, use_b;
	ElementType value;
	while (a_node != NULL || b_node != NULL) {
		if (a_node != NULL && b_node != NULL) {
			int compareResult = comparePosition(a_node, b_node);
			use_a = compareResult <= 0;
			use_b = compareResult >= 0;
		}
		if (a_node == NULL && b_node != NULL) {
			use_a = 0;
			use_b = 1;
		}
		if (a_node != NULL && b_node == NULL) {
			use_a = 1;
			use_b = 0;
		}

		if (use_a) {
			value = a_node -> value;
			column_index = a_node -> column_index;
			row_index = a_node -> row_index;

			a_node = a_node -> right;
			if (a_node == NULL) {
				for (i = row_index; i < a -> row_length; i++) {
					a_node = (a -> row)[i];
					if (a_node != NULL)
						break;
				}
			}
		}
		if (use_b) {
			value = use_a ? value + b_node -> value : b_node -> value;
			column_index = b_node -> column_index;
			row_index = b_node -> row_index;

			b_node = b_node -> right;

			if (b_node == NULL) {
				for (i = row_index; i < b -> row_length; i++) {
					b_node = (b -> row)[i];
					if (b_node != NULL)
						break;
				}
			}
		}

		if (value != 0) {
			CrossSparseMatrixNode *new_node = (CrossSparseMatrixNode*) malloc(
					sizeof(CrossSparseMatrixNode));

			new_node -> row_index = row_index;
			new_node -> column_index = column_index;
			new_node -> value = value;
			new_node -> right = NULL;
			new_node -> down = NULL;

			if (((*sum) -> row)[row_index - 1] == NULL) {
				((*sum) -> row)[row_index - 1] = new_node;
				left = new_node;
			} else {
				left -> right = new_node;
				left = new_node;
			}
			if (((*sum) -> column)[column_index - 1] == NULL) {
				((*sum) -> column)[column_index - 1] = new_node;
			} else {
				up = ((*sum) -> column)[column_index];
				while (up -> down != NULL)
					up = up -> down;

				up -> down = new_node;
			}

			value_count++;
		}
	}

	(*sum) -> value_count = value_count;

	return OK;
}

Status Subtract(SPARSE_MATRIX_TYPE a, SPARSE_MATRIX_TYPE b,
		SPARSE_MATRIX_TYPE *sub) {

	CrossSparseMatrixNode *node = NULL;
	int i = 0;
	for (i = 0; i < b -> row_length; i++) {
		node = (b -> row)[i];
		while (node != NULL) {
			node -> value *= -1;
			node = node -> right;
		}
	}

	Status status = Add(a, b, sub);

	for (i = 0; i < b -> row_length; i++) {
		node = (b -> row)[i];
		while (node != NULL) {
			node -> value *= -1;
			node = node -> right;
		}
	}

	return status;
}

Status Multiply(SPARSE_MATRIX_TYPE a, SPARSE_MATRIX_TYPE b,
		SPARSE_MATRIX_TYPE *product) {

	Initial(product, a -> row_length, b -> column_length);

	ElementType value = 0;
	int row_index_a = 0, column_index_b = 0, value_count = 0;
	CrossSparseMatrixNode *node_a = NULL, *node_b = NULL, *left = NULL, *up =
			NULL;
	for (row_index_a = 0; row_index_a < a -> row_length; row_index_a++) {
		for (column_index_b = 0; column_index_b < b -> column_length; column_index_b++) {

			value = 0;
			node_a = (a -> row)[row_index_a];
			node_b = (b -> column)[column_index_b];

			while (node_a != NULL && node_b != NULL) {
				if (node_a -> column_index > node_b -> row_index)
					node_b = node_b -> down;
				else if (node_a -> column_index < node_b -> row_index)
					node_a = node_a -> right;
				else {
					value += node_a -> value * node_b -> value;
					node_b = node_b -> down;
					node_a = node_a -> right;
				}
			}

			if (value != 0) {
				CrossSparseMatrixNode *new_node =
						(CrossSparseMatrixNode*) malloc(
								sizeof(CrossSparseMatrixNode));

				new_node -> row_index = row_index_a + 1;
				new_node -> column_index = column_index_b + 1;
				new_node -> value = value;
				new_node -> right = NULL;
				new_node -> down = NULL;

				if (((*product) -> row)[row_index_a] == NULL) {
					((*product) -> row)[row_index_a] = new_node;
					left = new_node;
				} else {
					left -> right = new_node;
					left = new_node;
				}
				if (((*product) -> column)[column_index_b] == NULL) {
					((*product) -> column)[column_index_b] = new_node;
				} else {
					up = ((*product) -> column)[column_index_b];
					while (up -> down != NULL)
						up = up -> down;

					up -> down = new_node;
				}

				value_count++;
			}

		} // end of column
	} // end of row

	(*product) -> value_count = value_count;

	return OK;
}

Status Transpose(SPARSE_MATRIX_TYPE matrix,
		SPARSE_MATRIX_TYPE *matrix_transposed) {

	Copy(matrix, matrix_transposed);

	int temp_length = (*matrix_transposed) -> row_length;
	CrossSparseMatrixNode **temp_head = (*matrix_transposed) -> row;

	(*matrix_transposed) -> row_length = (*matrix_transposed) -> column_length;
	(*matrix_transposed) -> row = (*matrix_transposed) -> column;
	(*matrix_transposed) -> column_length = temp_length;
	(*matrix_transposed) -> column = temp_head;

	CrossSparseMatrixNode *node = NULL, *temp_node = NULL;
	int i = 0, temp_index;
	for (i = 0; i < (*matrix_transposed) -> row_length; i++) {
		node = ((*matrix_transposed) -> row)[i];
		while (node != NULL) {
			temp_node = node -> right;
			temp_index = node -> row_index;
			node -> right = node -> down;
			node -> row_index = node -> column_index;
			node -> down = temp_node;
			node -> column_index = temp_index;

			node = node -> right;
		}
	}

	return OK;

}
