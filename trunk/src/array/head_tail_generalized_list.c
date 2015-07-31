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
	int length = 0;
	while (string[length] != '\0') {
		length++;
	}
	return length;
}
int get_number(char* string, int start_index, int end_index) {
	int value = 0;
	int i = start_index;
	for (i = start_index; i <= end_index; i++) {
		value = value * 10 + string[i] - '0';
	}
	return value;
}

Status Initial(GENERALIZED_LIST_TYPE* list) {
	*list = NULL;
	return OK;
}

Status create_action(GENERALIZED_LIST_TYPE* list, char* string,
		int start_index, int end_index) {

	*list = NULL;
	Node *node = NULL;

	if (start_index + 1 == end_index && string[start_index] == '('
			&& string[end_index] == ')') {
		return OK;
	}

	int i = start_index + 1;
	while (i < end_index) {

		char c = string[i];

		//跳过空白
		if (c == ' ') {
			i++;
		}

		//元素
		if (c >= '0' && c <= '9') {
			int number_start = i, number_end = i + 1;
			while (string[number_end] != ',' && string[number_end] != ' '
					&& string[number_end] != ')')
				number_end++;
			int value = get_number(string, number_start, number_end - 1);

			//构造
			if (*list == NULL) {
				*list = (Node*) malloc(sizeof(Node));
				node = *list;
			} else {
				(node -> pointer).next = (Node*) malloc(sizeof(Node));
				node = (node -> pointer).next;
			}

			node -> tag = List;
			(node -> pointer).next = NULL;
			(node -> pointer).head = (Node*) malloc(sizeof(Node));
			(node -> pointer).head -> tag = Atom;
			(node -> pointer).head -> value = value;

			//next
			i = number_end + 1;
		}
		//子表
		if (c == '(') {
			int generation = 0;
			int next_start_index = i;
			int next_end_index = i + 1;

			while (next_end_index < end_index) {
				if (string[next_end_index] == '(')
					generation++;

				if (string[next_end_index] == ')') {
					if (generation == 0)
						break;
					else
						generation--;
				}
				next_end_index++;
			}

			//构造
			if (*list == NULL) {
				*list = (Node*) malloc(sizeof(Node));
				node = *list;
			} else {
				(node -> pointer).next = (Node*) malloc(sizeof(Node));
				node = (node -> pointer).next;
			}

			node -> tag = List;
			(node -> pointer).next = NULL;

			Status status = create_action(&((node -> pointer).head), string,
					next_start_index, next_end_index);
			if (status != OK)
				return status;

			//next
			i = next_end_index + 2;
		}
	}
	return OK;
}
Status Create(GENERALIZED_LIST_TYPE* list, char* string) {
	return create_action(list, string, 0, get_string_length(string) - 1);
}

Status Destory(GENERALIZED_LIST_TYPE* list) {
	if ((*list) == NULL)
		return OK;

	if ((*list) -> tag == Atom) {
		free(*list);
		*list = NULL;
		return OK;
	}

	Node *current = *list, *next = NULL;
	while (current != NULL) {
		next = (current -> pointer).next;
		Destory(&(current -> pointer).head);
		free(current);
		current = next;
	}

	*list = NULL;
	return OK;
}

Status Copy(GENERALIZED_LIST_TYPE list, GENERALIZED_LIST_TYPE* duplication) {
	if (list == NULL)
		return OK;

	if (list -> tag == Atom) {
		*duplication = (Node*) malloc(sizeof(Node));
		(*duplication) -> tag = Atom;
		(*duplication) -> value = list -> value;
		return OK;
	}

	Node *list_node = list, *duplication_node = NULL;
	while (list_node != NULL) {

		if (duplication_node == NULL) {
			*duplication = (Node*) malloc(sizeof(Node));
			duplication_node = *duplication;
		} else {
			(duplication_node -> pointer).next = (Node*) malloc(sizeof(Node));
			duplication_node = (duplication_node -> pointer).next;
		}

		duplication_node -> tag = List;
		(duplication_node -> pointer).next = NULL;
		Copy((list_node -> pointer).head, &((duplication_node -> pointer).head));

		list_node = (list_node -> pointer).next;
	}

	return OK;
}

int Length(GENERALIZED_LIST_TYPE list) {
	if (list == NULL)
		return 0;

	if (list -> tag == Atom)
		return 1;

	Node *node = list;
	int length = 0;
	while (node != NULL) {
		length++;
		node = (node -> pointer).next;
	}

	return length;
}

int Depth(GENERALIZED_LIST_TYPE list) {
	if (list == NULL)
		return 0;

	if (list -> tag == Atom)
		return 0;

	Node *node = list;
	int max_node_depth = 0, node_depth = 0;
	while (node != NULL) {
		node_depth = Depth((node -> pointer).head);

		if (node_depth > max_node_depth)
			max_node_depth = node_depth;

		node = (node -> pointer).next;
	}

	return max_node_depth + 1;
}

BOOLEAN Empty(GENERALIZED_LIST_TYPE list) {
	return list == NULL;
}

GENERALIZED_LIST_TYPE GetHead(GENERALIZED_LIST_TYPE list) {
	if (list == NULL)
		return NULL;

	Node *result = NULL, *temp = (list -> pointer).next;

	(list -> pointer).next = NULL;
	Copy(list, &result);
	(list -> pointer).next = temp;

	if ((result -> pointer).head -> tag == List) {
		temp = result;
		result = (result -> pointer).head;
		free(temp);
	}

	return result;
}

GENERALIZED_LIST_TYPE GetTail(GENERALIZED_LIST_TYPE list) {
	if (list == NULL)
		return NULL;

	Node *result = NULL, *temp = NULL;

	while ((list -> pointer).next != NULL)
		list = (list -> pointer).next;

	Copy(list, &result);

	if ((result -> pointer).head -> tag == List) {
		temp = result;
		result = (result -> pointer).head;
		free(temp);
	}

	return result;
}

Status InsertFirst(GENERALIZED_LIST_TYPE* list, GENERALIZED_LIST_TYPE* element) {
	if (*element == NULL)
		return OK;

	Node *temp = NULL, *new_head = NULL;
	Copy(*element, &temp);

	if ((temp -> pointer).head -> tag == Atom && (temp -> pointer).next == NULL) {
		(temp -> pointer).next = *list;
		*list = temp;
	} else {
		new_head = (Node*) malloc(sizeof(Node));
		new_head -> tag = List;
		(new_head -> pointer).head = temp;
		(new_head -> pointer).next = *list;
		*list = new_head;
	}

	return OK;
}

Status DeleteFirst(GENERALIZED_LIST_TYPE* list, GENERALIZED_LIST_TYPE* element) {

	*element = *list;
	if (*list == NULL)
		return OK;

	*list = ((*list) -> pointer).next;
	((*element) -> pointer).next = NULL;

	Node *temp = NULL;

	if ((((*element) -> pointer).head) -> tag == List) {
		temp = ((*element) -> pointer).head;
		free(*element);
		*element = temp;
	}

	if (*list != NULL && ((*list) -> pointer).next == NULL
			&& (((*list) -> pointer).head) -> tag == List) {
		temp = ((*list) -> pointer).head;
		free(*list);
		*list = temp;
	}

	return OK;
}

Status Traverse(GENERALIZED_LIST_TYPE* list, Status(*visit)(ElementType*)) {
	if (*list == NULL)
		return OK;

	if ((*list) -> tag == Atom) {
		return visit(&((*list) -> value));
	}

	Node *node = *list;
	while (node != NULL) {
		Traverse(&((node -> pointer).head), visit);
		node = (node -> pointer).next;
	}

	return OK;;
}
