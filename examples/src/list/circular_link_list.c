/*
 * circular_link_list.h
 *
 *  Created on: 2009-4-10
 *      Author: yuandong
 */

#include <stdlib.h>
#include <stdio.h>

#include "include/common.h"
#include "include/list/circular_link_list.h"
#include "include/list/list.h"

Status InitialList(LIST_TYPE *list) {
	//产生头结点,并使L指向此头结点
	*list = (LIST_TYPE) malloc(sizeof(CircularLinkListNode));

	//存储分配失败
	if (list == NULL)
		return (OVERFLOW);

	//指针域为空
	(*list) -> next = *list;

	return OK;
}

Status DestroyList(LIST_TYPE *list) {
	CircularLinkListNode *node = (*list) -> next, *next_node = NULL;

	while (node != *list) {
		next_node = node -> next;
		free(node);
		node = next_node;
	}

	free(*list);
	*list = NULL;

	return OK;
}

Status ClearList(LIST_TYPE list) {
	CircularLinkListNode *nextNode = NULL, *currentNode = list -> next;

	while (currentNode != NULL && currentNode != list) {
		nextNode = currentNode -> next;
		free(currentNode);
		currentNode = nextNode;
	}

	list -> next = list;
	return OK;
}

BOOLEAN ListEmpty(LIST_TYPE list) {
	return list -> next == list;
}

int ListLength(LIST_TYPE list) {
	CircularLinkListNode *node = list -> next;
	int length = 0;

	while (node != NULL && node != list) {
		length++;
		node = node -> next;
	}

	return length;
}

Status GetElement(LIST_TYPE list, int position, ElementType *element) {
	CircularLinkListNode *node = list -> next;
	int index = 1;

	while (node != NULL && node != list) {
		if (index == position) {
			*element = node -> data;
			return OK;
		}

		index++;
		node = node -> next;
	}

	return ERROR;
}

int LocateElement(LIST_TYPE list, ElementType element, Status(*compare)(
		ElementType, ElementType)) {
	CircularLinkListNode *node = list -> next;
	int index = 1;

	while (node != NULL && node != list) {
		if (compare(element, node -> data))
			return index;

		index++;
		node = node -> next;
	}

	return 0;
}

Status PriorElement(LIST_TYPE list, ElementType currentElement,
		ElementType *priorElement) {
	CircularLinkListNode *node = list -> next;

	while (node != NULL && node != list) {
		if (node -> next && node -> next -> data == currentElement) {
			*priorElement = node -> data;
			return OK;
		}
		node = node -> next;
	}

	return INFEASIBLE;
}

Status NextElement(LIST_TYPE list, ElementType currentElement,
		ElementType *nextElement) {
	CircularLinkListNode *node = list -> next;

	while (node != NULL && node != list) {
		if (node -> data == currentElement && node -> next != list) {
			*nextElement = node -> next -> data;
			return OK;
		}
		node = node -> next;
	}

	return INFEASIBLE;
}

Status ListInsert(LIST_TYPE list, int position, ElementType element) {
	CircularLinkListNode *node = list;
	int index = 0;

	do {
		if (index == position - 1) {
			CircularLinkListNode *new_node = (CircularLinkListNode*) malloc(
					sizeof(CircularLinkListNode));
			if (new_node == NULL)
				return OVERFLOW;

			new_node -> next = node -> next;
			new_node -> data = element;

			node -> next = new_node;

			return OK;
		}

		index++;
		node = node -> next;
	} while (node != list);

	return ERROR;
}

Status ListDelete(LIST_TYPE list, int position, ElementType *deletedElement) {
	CircularLinkListNode *node = list;
	int index = 0;

	do {
		if (index + 1 == position && node -> next != list) {
			CircularLinkListNode *deletedNode = node -> next;
			*deletedElement = deletedNode -> data;

			node -> next = deletedNode -> next;
			free(deletedNode);

			return OK;
		}

		index++;
		node = node -> next;
	} while (node != list);

	return ERROR;
}

Status ListTraverse(LIST_TYPE list, Status(*visit)(ElementType*)) {
	CircularLinkListNode *node = list -> next;

	while (node != NULL && node != list) {
		if (((*visit)(&(node -> data))) == ERROR)
			return ERROR;
		node = node -> next;
	}

	return OK;
}

Status ListMerge(LIST_TYPE *a, LIST_TYPE *b) {
	Status result;
	CircularLinkListNode *index_a = (*a) -> next, *index_b = (*b) -> next, *index_c =
			NULL, *c = NULL, *temp;

	result = InitialList(&c);
	if (result != OK)
		return result;

	index_c = c;

	while (index_a != (*a) && index_b != (*b)) {
		if (index_a -> data < index_b -> data) {
			temp = index_a;
			index_a = index_a -> next;
		} else {
			temp = index_b;
			index_b = index_b -> next;
		}

		index_c -> next = temp;
		index_c = temp;
	}

	index_c -> next = index_a == (*a) ? index_b : index_a;
	while(index_c -> next != (*a) && index_c -> next!= (*b)){
		index_c = index_c -> next;
	}
	index_c -> next = c;

	free(*a);
	free(*b);

	*a = c;
	*b = NULL;

	return OK;
}

