/*
 * double_link_list.h
 *
 *  Created on: 2009-4-10
 *      Author: yuandong
 */

#include <stdlib.h>
#include <stdio.h>

#include "include/common.h"
#include "include/list/double_link_list.h"
#include "include/list/list.h"

Status InitialList(LIST_TYPE *list) {
	*list = (DoubleLinkList) malloc(sizeof(DoubleLinkListNode));
	if (list == NULL)
		return OVERFLOW;

	(*list) -> next = NULL;
	(*list) -> prior = NULL;

	return OK;
}

Status DestroyList(LIST_TYPE *list) {
	DoubleLinkListNode *node = NULL;

	while (*list != NULL) {
		node = (*list) -> next;
		free(*list);
		(*list) = node;
	}

	return OK;
}

Status ClearList(LIST_TYPE list) {
	DoubleLinkListNode *nextNode = NULL, *currentNode = list -> next;

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
	DoubleLinkListNode *node = list -> next;
	int length = 0;

	while (node != NULL) {
		length++;
		node = node -> next;
	}

	return length;
}

Status GetElement(LIST_TYPE list, int position, ElementType *element) {
	DoubleLinkListNode *node = list -> next;
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
	DoubleLinkListNode *node = list -> next;
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
	DoubleLinkListNode *node = list -> next;

	while (node != NULL) {
		if (node -> data == currentElement && node -> prior) {
			*priorElement = node -> prior -> data;
			return OK;
		}
		node = node -> next;
	}

	return INFEASIBLE;
}

Status NextElement(LIST_TYPE list, ElementType currentElement,
		ElementType *nextElement) {
	DoubleLinkListNode *node = list -> next;

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
	DoubleLinkListNode *node = list;
	int index = 0;

	do {
		if (index == position - 1) {
			DoubleLinkListNode *new_node = (DoubleLinkListNode*) malloc(
					sizeof(DoubleLinkListNode));
			if (new_node == NULL)
				return OVERFLOW;

			new_node -> next = node -> next;
			new_node -> prior = node;
			new_node -> data = element;

			node -> next = new_node;
			if (new_node -> next)
				new_node -> next -> prior = new_node;

			return OK;
		}

		index++;
		node = node -> next;
	} while (node != NULL);

	return ERROR;

}

Status ListDelete(LIST_TYPE list, int position, ElementType *deletedElement) {
	DoubleLinkListNode *node = list;
	int index = 0;

	while (node != NULL) {
		if (index + 1 == position && node -> next != NULL) {
			DoubleLinkListNode *deletedNode = node -> next;
			*deletedElement = deletedNode -> data;

			node -> next = deletedNode -> next;
			if (deletedNode -> next != NULL)
				deletedNode -> next -> prior = node;

			free(deletedElement);

			return OK;
		}

		index++;
		node = node -> next;
	}

	return ERROR;

}

Status ListTraverse(LIST_TYPE list, Status(*visit)(ElementType*)) {
	DoubleLinkListNode *node = list -> next;

	while (node != NULL) {
		if (((*visit)(&(node -> data))) == ERROR)
			return ERROR;
		node = node -> next;
	}

	return OK;

}

Status ListMerge(LIST_TYPE *a, LIST_TYPE *b) {
	Status result;
	DoubleLinkListNode *index_a = (*a) -> next, *index_b = (*b) -> next, *index_c =
			NULL, *c = NULL, *temp;

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
		temp -> prior = index_c;

		index_c = temp;
	}

	index_c -> next = index_a == NULL ? index_b : index_a;
	index_c -> next -> prior = index_c;


	free(*a);
	free(*b);

	*a = c;
	*b = NULL;

	return OK;
}

