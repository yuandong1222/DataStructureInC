/*
 * circular_link_list_test.c
 *
 *  Created on: 2009-4-10
 *      Author: yuandong
 */

#include <stdlib.h>

#include "include/list/circular_link_list.h"

#define TEST_LIST_LENGTH 3

LIST_TYPE getTestList(void) {
	CircularLinkList list;

	list = (CircularLinkListNode*) malloc(sizeof(CircularLinkListNode));
	list -> data = 0;

	list -> next = (CircularLinkListNode*) malloc(sizeof(CircularLinkListNode));
	list -> next -> data = 1;

	list -> next -> next = (CircularLinkListNode*) malloc(sizeof(CircularLinkListNode));
	list -> next -> next -> data = 2;

	list -> next -> next -> next = (CircularLinkListNode*) malloc(sizeof(CircularLinkListNode));
	list -> next -> next -> next -> data = 3;

	list -> next -> next -> next -> next = list;

	return list;
}

#include "test/list/list_test.c"
int main(void) {
	buildTestSuite();
	return runTestSuite();
}
