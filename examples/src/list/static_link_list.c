#include <stdlib.h>
#include <stdio.h>

#include "include/common.h"
#include "include/list/static_link_list.h"
#include "include/list/list.h"

Status InitialList(LIST_TYPE *list) {
	*list = (StaticLinkList) malloc(sizeof(StaticLinkListNode) * MAXSIZE);
	if (*list == NULL)
		return OVERFLOW;

	int i = 0;
	for (i = 0; i < MAXSIZE; i++) {
		(*list)[i].cursor = 0;
		(*list)[i].isEmpty = TRUE;
	}
	return OK;
}

Status DestroyList(LIST_TYPE *list) {
	free(*list);
	*list = NULL;

	return OK;
}

Status ClearList(LIST_TYPE list) {
	int i = 0;
	for (i = 0; i < MAXSIZE; i++) {
		list[i].cursor = 0;
		list[i].isEmpty = TRUE;
	}
	return OK;
}

BOOLEAN ListEmpty(LIST_TYPE list) {
	return list[0].cursor == 0;
}

int ListLength(LIST_TYPE list) {
	int length = 0, cursor = 0;
	while (list[cursor].cursor != 0) {
		cursor = list[cursor].cursor;
		length++;
	}
	return length;
}

Status GetElement(LIST_TYPE list, int position, ElementType *element) {
	int currentCursor = list[0].cursor;
	int index = 1;
	while (currentCursor != 0) {
		if (index == position) {
			*element = list[currentCursor].data;
			return OK;
		}
		currentCursor = list[currentCursor].cursor;
		index++;
	}
	return ERROR;
}

int LocateElement(LIST_TYPE list, ElementType element, Status(*compare)(
		ElementType, ElementType)) {
	int currentCursor = list[0].cursor;
	int index = 1;
	while (currentCursor != 0) {
		if (compare(element, list[currentCursor].data)) {
			return index;
		}
		currentCursor = list[currentCursor].cursor;
		index++;
	}
	return 0;
}

Status PriorElement(LIST_TYPE list, ElementType currentElement,
		ElementType *priorElement) {
	int currentCursor = list[0].cursor;
	while (currentCursor != 0) {
		if (list[currentCursor].cursor != 0
				&& list[list[currentCursor].cursor].data == currentElement) {
			*priorElement = list[currentCursor].data;
			return OK;
		}
		currentCursor = list[currentCursor].cursor;
	}
	return INFEASIBLE;
}

Status NextElement(LIST_TYPE list, ElementType currentElement,
		ElementType *nextElement) {
	int currentCursor = list[0].cursor;
	while (currentCursor != 0) {
		if (list[currentCursor].cursor != 0 && list[currentCursor].data
				== currentElement) {
			*nextElement = list[list[currentCursor].cursor].data;
			return OK;
		}
		currentCursor = list[currentCursor].cursor;
	}
	return INFEASIBLE;
}

Status ListInsert(LIST_TYPE list, int position, ElementType element) {
	int position_to_insert = 1;
	while (list[position_to_insert].isEmpty == FALSE && position_to_insert
			< MAXSIZE)
		position_to_insert++;
	if (position_to_insert == MAXSIZE)
		return OVERFLOW;

	int cursor = 0;
	int index = 0;
	do {
		if (index + 1 == position) {
			list[position_to_insert].data = element;
			list[position_to_insert].isEmpty = FALSE;
			list[position_to_insert].cursor = list[cursor].cursor;
			list[cursor].cursor = position_to_insert;

			return OK;
		}
		cursor = list[cursor].cursor;
		index++;
	} while (cursor != 0);

	return ERROR;
}

Status ListDelete(LIST_TYPE list, int position, ElementType *deletedElement) {
	int cursor = 0;
	int index = 0;
	do {
		if (index + 1 == position) {
			int t = list[cursor].cursor;
			list[cursor].cursor = list[t].cursor;

			*deletedElement = list[t].data;
			list[t].cursor = 0;
			list[t].isEmpty = TRUE;

			return OK;
		}
		cursor = list[cursor].cursor;
		index++;
	} while (cursor != 0 && list[cursor].cursor != 0);

	return ERROR;
}

Status ListTraverse(LIST_TYPE list, Status(*visit)(ElementType*)) {
	int cursor = list[0].cursor;
	while (cursor != 0) {
		if (!visit(&(list[cursor].data)))
			return ERROR;

		cursor = list[cursor].cursor;
	}
	return OK;
}

Status ListMerge(LIST_TYPE *a, LIST_TYPE *b) {
	Status result;
	int cursor_a = (*a) -> cursor, cursor_b = (*b) -> cursor, cursor_c = 0,
			last_cursor = 0;
	StaticLinkList c = NULL, last_list = NULL;
	ElementType temp;

	result = InitialList(&c);
	if (result != OK)
		return result;

	while (cursor_a != 0 && cursor_b != 0) {
		if ((*a + cursor_a) -> data < (*b + cursor_b) -> data) {
			temp = (*a + cursor_a) -> data;
			cursor_a = (*a + cursor_a) -> cursor;
		} else {
			temp = (*b + cursor_b) -> data;
			cursor_b = (*b + cursor_b) -> cursor;
		}

		(c + cursor_c) -> cursor = cursor_c + 1;
		(c + cursor_c + 1) -> isEmpty = FALSE;
		(c + cursor_c + 1) -> data = temp;
		cursor_c++;
	}

	if (cursor_a != 0) {
		last_list = *a;
		last_cursor = cursor_a;
	} else {

		last_list = *b;
		last_cursor = cursor_b;
	}
	while (last_cursor != 0) {
		(c + cursor_c) -> cursor = cursor_c + 1;
		(c + cursor_c + 1) -> isEmpty = FALSE;
		(c + cursor_c + 1) -> data = (last_list + last_cursor) -> data;

		cursor_c++;
		last_cursor = (last_list + last_cursor) -> cursor;
	}

	free(*a);
	free(*b);

	*a = c;
	*b = NULL;

	return OK;
}
