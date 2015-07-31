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
}

Status DestroyList(LIST_TYPE *list) {
}

Status ClearList(LIST_TYPE list) {
}

BOOLEAN ListEmpty(LIST_TYPE list) {
}

int ListLength(LIST_TYPE list) {
}

Status GetElement(LIST_TYPE list, int position, ElementType *element) {
}

int LocateElement(LIST_TYPE list, ElementType element, Status(*compare)(
		ElementType, ElementType)) {
}

Status PriorElement(LIST_TYPE list, ElementType currentElement,
		ElementType *priorElement) {
}

Status NextElement(LIST_TYPE list, ElementType currentElement,
		ElementType *nextElement) {
}

Status ListInsert(LIST_TYPE list, int position, ElementType element) {
}

Status ListDelete(LIST_TYPE list, int position, ElementType *deletedElement) {
}

Status ListTraverse(LIST_TYPE list, Status(*visit)(ElementType*)) {
}

Status ListMerge(LIST_TYPE *a, LIST_TYPE *b) {
}

