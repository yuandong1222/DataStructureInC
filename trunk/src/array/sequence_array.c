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
}
Status Destory(SequenceArray* array) {
}

int getOffset(SequenceArray array, int dimension, va_list ap) {
}

Status Assign(SequenceArray array, ElementType element, int dimension, ...) {
}

Status Value(SequenceArray array, ElementType *element, int dimension, ...) {
}
