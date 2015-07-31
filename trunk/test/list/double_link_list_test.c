/*
 * double_link_list.c
 *
 *  Created on: 2009-4-10
 *      Author: yuandong
 */

#include <stdlib.h>

#include "include/list/double_link_list.h"

#define TEST_LIST_LENGTH 3

LIST_TYPE getTestList(void) {
	DoubleLinkList list;

	list = (DoubleLinkListNode*) malloc(sizeof(DoubleLinkListNode));
	list -> data = 0;
	list -> prior = NULL;

	list -> next = (DoubleLinkListNode*) malloc(sizeof(DoubleLinkListNode));
	list -> next -> prior = NULL;
	list -> next -> data = 1;

	list -> next -> next = (DoubleLinkListNode*) malloc(sizeof(DoubleLinkListNode));
	list -> next -> next -> prior = list -> next;
	list -> next -> next -> data = 2;

	list -> next -> next -> next = (DoubleLinkListNode*) malloc(
			sizeof(DoubleLinkListNode));
	list -> next -> next -> next -> prior = list -> next -> next;
	list -> next -> next -> next -> data = 3;

	list -> next -> next -> next -> next = NULL;

	return list;
}

#include "test/list/list_test.c"
int main(void) {
	buildTestSuite();
	return runTestSuite();
}
