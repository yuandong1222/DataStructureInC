/*
 * head_tail_generalized_list.c
 *
 *  Created on: 2009-8-12
 *      Author: yuandong
 */

#include <stdlib.h>
#include <stdio.h>

#include "include/common.h"
#include "include/array/head_tail_generalized_list.h"
#include "include/array/generalized_list.h"

int get_string_length(char* string) {
}
int get_number(char* string, int start_index, int end_index) {
}

Status Initial(GENERALIZED_LIST_TYPE* list) {
}

Status create_action(GENERALIZED_LIST_TYPE* list, char* string,
		int start_index, int end_index) {
}
Status Create(GENERALIZED_LIST_TYPE* list, char* string) {
	return create_action(list, string, 0, get_string_length(string) - 1);
}

Status Destory(GENERALIZED_LIST_TYPE* list) {
}

Status Copy(GENERALIZED_LIST_TYPE list, GENERALIZED_LIST_TYPE* duplication) {
}

int Length(GENERALIZED_LIST_TYPE list) {
}

int Depth(GENERALIZED_LIST_TYPE list) {
}

BOOLEAN Empty(GENERALIZED_LIST_TYPE list) {
}

GENERALIZED_LIST_TYPE GetHead(GENERALIZED_LIST_TYPE list) {
}

GENERALIZED_LIST_TYPE GetTail(GENERALIZED_LIST_TYPE list) {
}

Status InsertFirst(GENERALIZED_LIST_TYPE* list, GENERALIZED_LIST_TYPE* element) {
}

Status DeleteFirst(GENERALIZED_LIST_TYPE* list, GENERALIZED_LIST_TYPE* element) {
}

Status Traverse(GENERALIZED_LIST_TYPE* list, Status(*visit)(ElementType*)) {
}
