/*
 * extend_sequence_generalized_list.h
 *
 *  Created on: 2009-8-21
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_ARRAY_EXTEND_SEQUENCE_GENERALIZED_LIST_H_
#define DATA_STRUCTURE_IN_C_ARRAY_EXTEND_SEQUENCE_GENERALIZED_LIST_H_

#define ElementType int
#define GENERALIZED_LIST_TYPE ExtendSequenceGeneralizedList

#include "include/common.h"

enum Tag {
	Atom, List
};

typedef struct Node {
	enum Tag tag;
	union {
		ElementType value;
		struct Node *head;
	};
	struct Node *next;
} Node, *ExtendSequenceGeneralizedList;

int get_string_length(char* string);
int get_number(char* string, int start_index, int end_index);

#endif /* DATA_STRUCTURE_IN_C_ARRAY_EXTEND_SEQUENCE_GENERALIZED_LIST_H_ */
