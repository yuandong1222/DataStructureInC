/*
 * head_tail_generalized_list.h
 *
 *  Created on: 2009-8-12
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_ARRAY_HEAD_TAIL_GENERALIZED_LIST_H_
#define DATA_STRUCTURE_IN_C_ARRAY_HEAD_TAIL_GENERALIZED_LIST_H_

#define ElementType int
#define GENERALIZED_LIST_TYPE HeadTailGeneralizedList

#include "include/common.h"

enum Tag {
	Atom, List
};

typedef struct Node {
	enum Tag tag;
	union {
		ElementType value;
		struct {
			struct Node *head;
			struct Node *next;
		} pointer;
	};
} Node, *HeadTailGeneralizedList;

int get_string_length(char* string);
int get_number(char* string, int start_index, int end_index);

#endif /* DATA_STRUCTURE_IN_C_ARRAY_HEAD_TAIL_GENERALIZED_LIST_H_ */
