/*
 * extend_sequence_generalized_list.c
 *
 *  Created on: 2009-8-21
 *      Author: yuandong
 */

#include <stdlib.h>
#include <stdio.h>

#include "include/common.h"
#include "include/array/extend_sequence_generalized_list.h"
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
				node -> next = (Node*) malloc(sizeof(Node));
				node = node -> next;
			}

			node -> tag = Atom;
			node -> next = NULL;
			node -> value = value;

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
				node -> next = (Node*) malloc(sizeof(Node));
				node = node -> next;
			}

			node -> tag = List;
			node -> next = NULL;

			Status status = create_action(&(node -> head), string,
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

	Node *current = *list, *next = NULL;
	while (current != NULL) {
		next = current -> next;

		if ((*list) -> tag == List) {
			Destory(&(current -> head));
		}

		free(current);
		current = next;
	}

	*list = NULL;
	return OK;
}

Status Copy(GENERALIZED_LIST_TYPE list, GENERALIZED_LIST_TYPE* duplication) {

	*duplication = NULL;
	if (list == NULL)
		return OK;

	Node *list_node = list, *duplication_node = NULL;
	while (list_node != NULL) {

		if (duplication_node == NULL) {
			*duplication = (Node*) malloc(sizeof(Node));
			duplication_node = *duplication;
		} else {
			duplication_node -> next = (Node*) malloc(sizeof(Node));
			duplication_node = duplication_node -> next;
		}

		duplication_node -> tag = list_node -> tag;
		duplication_node -> next = NULL;

		if (list -> tag == Atom) {
			duplication_node -> value = list_node -> value;
		} else {
			Copy(list_node -> head, &(duplication_node -> head));
		}

		list_node = list_node -> next;
	}

	return OK;
}

int Length(GENERALIZED_LIST_TYPE list) {
	Node *node = list;
	int length = 0;
	while (node != NULL) {
		length++;
		node = node -> next;
	}

	return length;
}

int Depth(GENERALIZED_LIST_TYPE list) {
	if (list == NULL)
		return 0;

	Node *node = list;
	int max_node_depth = 0, node_depth = 0;
	while (node != NULL) {
		if (node -> tag == List) {
			node_depth = Depth(node -> head);

			if (node_depth > max_node_depth)
				max_node_depth = node_depth;
		}

		node = node -> next;
	}

	return max_node_depth + 1;
}

BOOLEAN Empty(GENERALIZED_LIST_TYPE list) {
	return list == NULL;
}

GENERALIZED_LIST_TYPE GetHead(GENERALIZED_LIST_TYPE list) {
	if (list == NULL)
		return NULL;

	Node *result = NULL, *temp = list -> next;

	list -> next = NULL;
	Copy(list, &result);
	list -> next = temp;

	if (result -> tag == List) {
		temp = result;
		result = result -> head;
		free(temp);
	}

	return result;
}

GENERALIZED_LIST_TYPE GetTail(GENERALIZED_LIST_TYPE list) {
	if (list == NULL)
		return NULL;

	Node *result = NULL, *temp = NULL;
	while (list -> next != NULL)
		list = list -> next;

	Copy(list, &result);

	if (result -> tag == List) {
		temp = result;
		result = result -> head;
		free(temp);
	}

	return result;
}

Status InsertFirst(GENERALIZED_LIST_TYPE* list, GENERALIZED_LIST_TYPE* element) {
	if (*element == NULL)
		return OK;

	Node *temp = NULL, *new_head = NULL;
	Copy(*element, &temp);

	if (temp -> tag == Atom && temp -> next == NULL) {
		temp -> next = *list;
		*list = temp;
	} else {
		new_head = (Node*) malloc(sizeof(Node));
		new_head -> tag = List;
		new_head -> head = temp;
		new_head -> next = *list;
		*list = new_head;
	}

	return OK;
}

Status DeleteFirst(GENERALIZED_LIST_TYPE* list, GENERALIZED_LIST_TYPE* element) {

	*element = *list;
	if (*list == NULL)
		return OK;

	*list = (*list) -> next;
	(*element) -> next = NULL;

	Node *temp = NULL;

	if ((*element) -> tag == List) {
		temp = (*element) -> head;
		free(*element);
		*element = temp;
	}

	if (*list != NULL && (*list) -> next == NULL && (*list) -> tag == List) {
		temp = (*list) -> head;
		free(*list);
		*list = temp;
	}

	return OK;
}

Status Traverse(GENERALIZED_LIST_TYPE* list, Status(*visit)(ElementType*)) {
	if (*list == NULL)
		return OK;

	Node *node = *list;
	while (node != NULL) {
		if (node -> tag == Atom) {
			visit(&(node -> value));
		} else {
			Traverse(&(node -> head), visit);
		}
		node = node -> next;
	}

	return OK;;
}
