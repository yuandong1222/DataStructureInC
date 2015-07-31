#include <stdlib.h>
#include <stdio.h>

#include "include/common.h"
#include "include/list/sequence_list.h"
#include "include/list/list.h"

Status InitialList(LIST_TYPE *list) {
	*list = (SequenceList) malloc(sizeof(SequenceListHead));
	if (*list == NULL)
		return OVERFLOW;

	(*list) -> element = (ElementType*) malloc(sizeof(ElementType)
			* LIST_INITIAL_SIZE);
	if (*list == NULL)
		return OVERFLOW;

	(*list) -> length = 0;
	(*list) -> listsize = LIST_INITIAL_SIZE;

	return OK;
}

Status DestroyList(LIST_TYPE *list) {
	free((*list) -> element);
	free(*list);

	(*list) = NULL;
	return OK;
}

Status ClearList(LIST_TYPE list) {
	list -> length = 0;
	return OK;
}

BOOLEAN ListEmpty(LIST_TYPE list) {
	return list -> length == 0;
}

int ListLength(LIST_TYPE list) {
	return list -> length;
}

Status GetElement(LIST_TYPE list, int position, ElementType *element) {
	if (position < 1 || position > ListLength(list))
		return ERROR;

	*element = (list -> element)[position - 1];
	return OK;
}

int LocateElement(LIST_TYPE list, ElementType element, Status(*compare)(
		ElementType, ElementType)) {
	int i = 0;
	for (i = 0; i < list -> length; i++) {
		if (compare((list -> element)[i], element))
			return i + 1;
	}
	return 0;
}

Status PriorElement(LIST_TYPE list, ElementType currentElement,
		ElementType *priorElement) {
	int i;
	for (i = 1; i < list -> length; i++) {
		if ((list -> element)[i] == currentElement) {
			*priorElement = (list -> element)[i - 1];
			return OK;
		}
	}
	return INFEASIBLE;
}

Status NextElement(LIST_TYPE list, ElementType currentElement,
		ElementType *nextElement) {
	int i;
	for (i = 0; i < list -> length - 1; i++) {
		if ((list -> element)[i] == currentElement) {
			*nextElement = (list -> element)[i + 1];
			return OK;
		}
	}
	return INFEASIBLE;
}

Status ListInsert(LIST_TYPE list, int position, ElementType element) {
	if (position < 1 || position > ListLength(list) + 1)
		return ERROR;
	int i;

	//expend size
	if (list -> length == list -> listsize) {
		ElementType *newElement = malloc(sizeof(ElementType)
				* (list -> listsize + LIST_INCREMENT));

		for (i = 0; i < list -> length; i++) {
			(newElement)[i] = (list -> element)[i];
		}
		free(list -> element);
		list -> element = newElement;
		list -> listsize = list -> listsize + LIST_INCREMENT;
	}

	//insert
	for (i = list -> length; i > position - 1; i--) {
		(list -> element)[i] = (list -> element)[i - 1];
	}
	(list -> element)[position - 1] = element;
	(list -> length)++;

	return OK;
}

Status ListDelete(LIST_TYPE list, int position, ElementType *deletedElement) {
	if (position < 1 || position > ListLength(list))
		return ERROR;

	*deletedElement = (list -> element)[position - 1];

	int i;
	for (i = position - 1; i < list -> length - 1; i++) {
		(list -> element)[i] = (list -> element)[i + 1];
	}
	(list -> length)--;

	return OK;
}

Status ListTraverse(LIST_TYPE list, Status(*visit)(ElementType*)) {
	int i;
	for (i = 0; i < list -> length; i++) {
		if (visit((&(list -> element)[i])) != OK)
			return ERROR;
	}
	return OK;
}

Status ListMerge(LIST_TYPE *a, LIST_TYPE *b) {

	int length = (*a) -> length + (*b) -> length;
	int size = length <= LIST_INITIAL_SIZE ? LIST_INITIAL_SIZE : (length
			/ LIST_INCREMENT + 1) * LIST_INCREMENT;

	SequenceList c = (SequenceList) malloc(sizeof(SequenceListHead));
	if (c == NULL)
		return OVERFLOW;

	c -> listsize = size;
	c -> length = length;
	c -> element = (ElementType*) malloc(sizeof(ElementType) * size);
	if (c -> element == NULL)
		return OVERFLOW;

	int index_a = 0, index_b = 0, index_c = 0;
	ElementType element_a, element_b;

	while (index_a < (*a) -> length && index_b < (*b) -> length) {
		element_a = *((*a) -> element + index_a);
		element_b = *((*b) -> element + index_b);
		if (element_a <= element_b) {
			*(c -> element + index_c) = element_a;
			index_a++;
		} else {
			*(c -> element + index_c) = element_b;
			index_b++;
		}
		index_c++;
	}

	while(index_a < (*a) -> length){
		*(c -> element + index_c) = *((*a) -> element + index_a);
		index_a++;
		index_c++;
	}
	while(index_b < (*b) -> length){
		*(c -> element + index_c) =  *((*b) -> element + index_b);
		index_b++;
		index_c++;
	}

	free((*a) -> element);
	free((*b) -> element);
	free(*a);
	free(*b);

	*a = c;
	*b = NULL;

	return OK;
}

