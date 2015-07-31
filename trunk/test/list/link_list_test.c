/*
 * link_list_test.c
 *
 *  Created on: 2009-4-10
 *      Author: yuandong
 */

#include <stdlib.h>

#include "include/list/link_list.h"

#define TEST_LIST_LENGTH 3

LIST_TYPE getTestList(void) {
	LinkList list;

	list = (LinkListNode*) malloc(sizeof(LinkListNode));
	list -> data = 0;

	list -> next = (LinkListNode*) malloc(sizeof(LinkListNode));
	list -> next -> data = 1;

	list -> next -> next = (LinkListNode*) malloc(sizeof(LinkListNode));
	list -> next -> next -> data = 2;

	list -> next -> next -> next = (LinkListNode*) malloc(sizeof(LinkListNode));
	list -> next -> next -> next -> data= 3;

	list -> next -> next -> next -> next= NULL;

	return list;
}

#include "test/list/list_test.c"
int main(void) {
	buildTestSuite();
	return runTestSuite();
}
