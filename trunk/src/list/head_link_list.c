/*
 * head_link_list.h
 *
 *  Created on: 2009-4-10
 *      Author: yuandong
 */

#include <stdlib.h>
#include <stdio.h>

#include "include/common.h"
#include "include/list/head_link_list.h"

Status MakeNode(HeadLinkListNode **node, ElementType element) {
}

void FreeNode(HeadLinkListNode **node) {
}

Status InitialList(LIST_TYPE *list) {
}

Status DestroyList(LIST_TYPE *list) {
}

Status ClearList(LIST_TYPE list) {
}

Status InsertFirst(LIST_TYPE list, HeadLinkListNode *node) {
}

Status DeleteFirst(LIST_TYPE list, HeadLinkListNode **node) {
}

Status Append(LIST_TYPE list, Link link) {
}

Status Remove(LIST_TYPE list, HeadLinkListNode **node) {
}

Status InsertBefore(LIST_TYPE list, Position *position, HeadLinkListNode *node) {
}

Status InsertAfter(LIST_TYPE list, Position *position, HeadLinkListNode *node) {
}

Status SetElement(Position position, ElementType element) {
}

ElementType GetElement(Position position) {
}

BOOLEAN ListEmpty(LIST_TYPE list) {
}

int ListLength(LIST_TYPE list) {
}

Position GetFirst(LIST_TYPE list) {
}

Position GetLast(LIST_TYPE list) {
}

Position PriorPosition(LIST_TYPE list, Position position) {
}

Position NextPosition(LIST_TYPE list, Position position) {
}

Status LocatePosition(LIST_TYPE list, int positionIndex, Position *position) {
}

Position LocateElement(LIST_TYPE list, ElementType element, Status(*compare)(
		ElementType, ElementType)) {
}

Status ListTraverse(LIST_TYPE list, Status(*visit)(ElementType*)) {
}

Status ListMerge(LIST_TYPE *a, LIST_TYPE *b) {
}

