/*
 * link_list.h
 *
 *  Created on: 2009-4-10
 *      Author: yuandong
 */

#include <stdlib.h>
#include <stdio.h>

#include "include/common.h"
#include "include/list/link_list.h"
#include "include/list/list.h"

Status InitialList(LIST_TYPE *list) {
	//产生头结点,并使L指向此头结点
	*list = (LIST_TYPE) malloc(sizeof(LinkListNode));

	//存储分配失败
	if (list == NULL)
		return (OVERFLOW);

	//指针域为空
	(*list) -> next = NULL;

	return OK;
}

Status DestroyList(LIST_TYPE *list) {
	LinkListNode *node = NULL;

	while (*list != NULL) {
		node = (*list) -> next;
		free(*list);
		(*list) = node;
	}

	return OK;
}

Status ClearList(LIST_TYPE list) {
	LinkListNode *nextNode = NULL, *currentNode = list -> next;

	while (currentNode != NULL) {
		nextNode = currentNode -> next;
		free(currentNode);
		currentNode = nextNode;
	}

	list -> next = NULL;
	return OK;
}

BOOLEAN ListEmpty(LIST_TYPE list) {
	return list -> next == NULL;
}

int ListLength(LIST_TYPE list) {
	LinkListNode *node = list -> next;
	int length = 0;

	while (node != NULL) {
		length++;
		node = node -> next;
	}

	return length;
}

Status GetElement(LIST_TYPE list, int position, ElementType *element) {
	LinkListNode *node = list -> next;
	int index = 1;

	while (node != NULL) {
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
	LinkListNode *node = list -> next;
	int index = 1;

	while (node != NULL) {
		if (compare(element, node -> data))
			return index;

		index++;
		node = node -> next;
	}

	return 0;
}

Status PriorElement(LIST_TYPE list, ElementType currentElement,
		ElementType *priorElement) {
	LinkListNode *node = list -> next;

	while (node != NULL) {
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
	LinkListNode *node = list -> next;

	while (node != NULL) {
		if (node -> data == currentElement && node -> next) {
			*nextElement = node -> next -> data;
			return OK;
		}
		node = node -> next;
	}

	return INFEASIBLE;
}

Status ListInsert(LIST_TYPE list, int position, ElementType element) {
	LinkListNode *node = list;
	int index = 0;

	do {
		if (index == position - 1) {
			LinkListNode *new_node = (LinkListNode*) malloc(
					sizeof(LinkListNode));
			if (new_node == NULL)
				return OVERFLOW;

			new_node -> next = node -> next;
			new_node -> data = element;

			node -> next = new_node;

			return OK;
		}

		index++;
		node = node -> next;
	} while (node != NULL);

	return ERROR;
}

Status ListDelete(LIST_TYPE list, int position, ElementType *deletedElement) {
	LinkListNode *node = list;
	int index = 0;

	while (node != NULL) {
		if (index + 1 == position && node -> next != NULL) {
			LinkListNode *deletedNode = node -> next;
			*deletedElement = deletedNode -> data;

			node -> next = deletedNode -> next;
			free(deletedElement);

			return OK;
		}

		index++;
		node = node -> next;
	}

	return ERROR;
}

Status ListTraverse(LIST_TYPE list, Status(*visit)(ElementType*)) {
	LinkListNode *node = list -> next;

	while (node != NULL) {
		if (((*visit)(&(node -> data))) == ERROR)
			return ERROR;
		node = node -> next;
	}

	return OK;
}

Status ListMerge(LIST_TYPE *a, LIST_TYPE *b) {
	Status result;
	LinkListNode *index_a = (*a) -> next, *index_b = (*b) -> next, *index_c = NULL, *c = NULL,
			*temp;

	result = InitialList(&c);
	if (result != OK)
		return result;

	index_c = c;

	while (index_a != NULL && index_b != NULL) {
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

	index_c -> next = index_a == NULL ? index_b : index_a;

	free(*a);
	free(*b);

	*a = c;
	*b = NULL;

	return OK;
}
