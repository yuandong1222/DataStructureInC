/*
 * link_string.c
 *
 *  Created on: 2009-5-16
 *      Author: yuandong
 */

#include <stdlib.h>
#include <stdio.h>

#include "include/common.h"
#include "include/string/link_string.h"
#include "include/string/string.h"

#include "include/common.h"

Status Assign(STRING_TYPE *string, char chars[]) {
}

Status Copy(STRING_TYPE *new, STRING_TYPE string) {
}

Status Empty(STRING_TYPE string) {
}

int Compare(STRING_TYPE a, STRING_TYPE b) {
}

int Length(STRING_TYPE string) {
}

Status Clear(STRING_TYPE string) {
}

Status Concat(STRING_TYPE *result, STRING_TYPE a, STRING_TYPE b) {
}

Status SubString(STRING_TYPE *result, STRING_TYPE string, int position,
		int length) {
}
int Index(STRING_TYPE string, STRING_TYPE match, int position) {
}

Status Zip(STRING_TYPE *string) {
}

Status Replace(STRING_TYPE *string, STRING_TYPE match, STRING_TYPE replacement) {
}

Status Insert(STRING_TYPE *string, int position, STRING_TYPE s) {
}

Status Delete(STRING_TYPE *string, int position, int length) {
}

Status Destroy(STRING_TYPE *string) {
}
