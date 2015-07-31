/*
 * sequence_array.c
 *
 *  Created on: 2009-7-19
 *      Author: yuandong
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "include/common.h"
#include "include/array/sequence_array.h"

Status Initial(SequenceArray* array, int dimension, ...) {
	if (dimension <= 0)
		return ERROR;

	int i, element_length = 0;

	*array = (SequenceArray) malloc(sizeof(SequenceArrayHead));
	if (*array == NULL)
		return OVERFLOW;

	//dimension
	(*array) -> dimension = dimension;

	//bounds
	(*array) -> bounds = (int*) malloc(sizeof(int) * dimension);
	if ((*array) -> bounds == NULL)
		return OVERFLOW;

	va_list ap;
	va_start(ap, dimension);

	element_length = 1;
	for (i = 0; i < dimension; i++) {
		((*array) -> bounds)[i] = va_arg(ap, int);
		if (((*array) -> bounds)[i] < 0)
			return ERROR;

		element_length *= ((*array) -> bounds)[i];
	}

	va_end(ap);

	//constants
	(*array) -> constants = (int*) malloc(sizeof(int) * dimension);
	if ((*array) -> constants == NULL)
		return OVERFLOW;

	((*array) -> constants)[dimension - 1] = 1;
	for (i = dimension - 2; i >= 0; i--) {
		((*array) -> constants)[i] = ((*array) -> constants)[i + 1]
				* ((*array) -> bounds)[i + 1];
	}

	//base
	(*array) -> base = (ElementType*) malloc(sizeof(ElementType)
			* element_length);
	if ((*array) -> base == NULL)
		return OVERFLOW;

	//return
	return OK;
}
Status Destory(SequenceArray* array) {

	free((*array) -> bounds);
	free((*array) -> constants);
	free((*array) -> base);
	free(*array);

	*array = NULL;
	return OK;

}

int getOffset(SequenceArray array, int dimension, va_list ap) {

	int offset = 0, i = 0;
	for (i = 0; i < dimension; i++) {
		offset += (array -> constants)[i] * va_arg(ap, int);
	}

	return offset;
}

Status Assign(SequenceArray array, ElementType element, int dimension, ...) {
	va_list ap;
	va_start(ap, dimension);
	int offset = getOffset(array, dimension, ap);
	va_end(ap);

	(array -> base)[offset] = element;
	return OK;
}

Status Value(SequenceArray array, ElementType *element, int dimension, ...) {
	va_list ap;
	va_start(ap, dimension);
	int offset = getOffset(array, dimension, ap);
	va_end(ap);

	*element = (array -> base)[offset];
	return OK;

}
