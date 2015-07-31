/*
 * head_link_list.c
 *
 *  Created on: 2009-4-10
 *      Author: yuandong
 */

#include <stdlib.h>
#include <stdio.h>

#include "include/common.h"
#include "include/list/head_link_list.h"

Status MakeNode(HeadLinkListNode **node, ElementType element) {
	*node = (HeadLinkListNode*) malloc(sizeof(HeadLinkListNode));
	if (*node == NULL)
		return OVERFLOW;

	(*node) -> data = element;
	(*node) -> next = NULL;

	return OK;
}

void FreeNode(HeadLinkListNode **node) {
	free(*node);
	*node = NULL;
}

Status InitialList(LIST_TYPE *list) {
	*list = (HeadLinkList) malloc(sizeof(HeadLinkListHeadNode));
	if (*list == NULL)
		return OVERFLOW;

	(*list) -> head = NULL;
	(*list) -> tail = NULL;
	(*list) -> length = 0;

	return OK;
}

Status DestroyList(LIST_TYPE *list) {
	HeadLinkListNode *node = (*list) -> head, *next_node = NULL;

	while (node != NULL) {
		next_node = node -> next;
		free(node);
		node = next_node;
	}

	free(*list);
	*list = NULL;

	return OK;
}

Status ClearList(LIST_TYPE list) {
	HeadLinkListNode *nextNode = NULL, *currentNode = list -> head;

	while (currentNode != NULL) {
		nextNode = currentNode -> next;
		free(currentNode);
		currentNode = nextNode;
	}

	list -> head = NULL;
	list -> tail = NULL;
	list -> length = 0;

	return OK;
}

Status InsertFirst(LIST_TYPE list, HeadLinkListNode *node) {
	node -> next = list -> head;
	list -> head = node;
	list -> length++;

	return OK;
}

Status DeleteFirst(LIST_TYPE list, HeadLinkListNode **node) {
	*node = list -> head;
	if (list -> head == NULL)
		return ERROR;

	list -> head = (*node) -> next;
	list -> length--;

	return OK;
}

Status Append(LIST_TYPE list, Link link) {
	if (list -> head == NULL)
		list -> head = link;
	else
		list -> tail -> next = link;

	list -> tail = list -> head;
	list -> length = 1;
	while (list -> tail -> next != NULL) {
		list -> length++;
		list -> tail = list -> tail -> next;
	}

	return OK;
}

Status Remove(LIST_TYPE list, HeadLinkListNode **node) {
	if (list -> head == NULL) {
		*node = NULL;
		return ERROR;
	}

	*node = list -> tail;
	list -> length--;

	if (list -> head == list -> tail) {
		list -> head = list -> tail = NULL;
	} else {
		list -> tail = list -> head;
		while (list -> tail -> next -> next != NULL) {
			list -> tail = list -> tail -> next;
		}
		list -> tail -> next = NULL;
	}

	return OK;
}

Status InsertBefore(LIST_TYPE list, Position *position, HeadLinkListNode *node) {
	if (*position == list -> head) {
		node -> next = list -> head;
		list -> head = node;
	} else {
		HeadLinkListNode* prior_node = PriorPosition(list, *position);
		node -> next = prior_node -> next;
		prior_node -> next = node;
	}

	*position = node;
	list -> length++;
	return OK;
}

Status InsertAfter(LIST_TYPE list, Position *position, HeadLinkListNode *node) {
	node -> next = (*position) -> next;
	(*position) -> next = node;
	*position = node;
	list -> length++;
	return OK;
}

Status SetElement(Position position, ElementType element) {
	position -> data = element;
	return OK;
}

ElementType GetElement(Position position) {
	return position -> data;
}

BOOLEAN ListEmpty(LIST_TYPE list) {
	return list -> head == NULL;
}

int ListLength(LIST_TYPE list) {
	return list -> length;
}

Position GetFirst(LIST_TYPE list) {
	return list -> head;
}

Position GetLast(LIST_TYPE list) {
	return list -> tail;
}

Position PriorPosition(LIST_TYPE list, Position position) {
	if (position == list -> head) {
		return NULL;
	}

	HeadLinkListNode* prior_node = list -> head;
	while (prior_node -> next != position) {
		prior_node = prior_node -> next;
	}
	return prior_node;
}

Position NextPosition(LIST_TYPE list, Position position) {
	return position -> next;
}

Status LocatePosition(LIST_TYPE list, int positionIndex, Position *position) {
	if (positionIndex < 1 || positionIndex > list -> length) {
		*position = NULL;
		return ERROR;
	}

	int index = 1;
	*position = list -> head;
	while (index < positionIndex && *position != NULL) {
		*position = (*position) -> next;
		index++;
	}

	return *position == NULL ? ERROR : OK;
}

Position LocateElement(LIST_TYPE list, ElementType element, Status(*compare)(
		ElementType, ElementType)) {

	Position position = list -> head;
	while (position != NULL && !(*compare)(position -> data, element))
		position = position -> next;

	return position;
}

Status ListTraverse(LIST_TYPE list, Status(*visit)(ElementType*)) {
	HeadLinkListNode *node = list -> head;

	while (node != NULL) {
		if (((*visit)(&(node -> data))) == ERROR)
			return ERROR;
		node = node -> next;
	}

	return OK;
}

Status ListMerge(LIST_TYPE *a, LIST_TYPE *b) {
	Status result;
	HeadLinkListNode *index_a = (*a) -> head, *index_b = (*b) -> head,
			*index_c = NULL, *temp;

	HeadLinkList c;

	result = InitialList(&c);
	if (result != OK)
		return result;

	while (index_a != NULL && index_b != NULL) {
		if (index_a -> data < index_b -> data) {
			temp = index_a;
			index_a = index_a -> next;
		} else {
			temp = index_b;
			index_b = index_b -> next;
		}

		if (index_c == NULL) {
			c -> head = index_c = temp;
		} else {
			index_c -> next = temp;
			index_c = temp;
		}
	}

	temp = index_a == NULL ? index_b : index_a;
	if (index_c == NULL) {
		c -> head = index_c = temp;
	} else {
		index_c -> next = temp;
		index_c = temp;
	}
	free(*a);
	free(*b);

	*a = c;
	*b = NULL;

	return OK;
}

