/*
 * static_link_list_test.c
 *
 *  Created on: 2009-4-10
 *      Author: yuandong
 */
#include <stdlib.h>

#include "include/list/static_link_list.h"

#define TEST_LIST_LENGTH 3

StaticLinkList getTestList() {
	StaticLinkList list = (StaticLinkList) malloc(sizeof(StaticLinkListNode) * MAXSIZE);

	int i;
	for(i = 0; i < MAXSIZE; i++)
		list[i].isEmpty = TRUE;

	list[0].cursor = 1;

	list[1].data = 1;
	list[1].cursor = 2;
	list[1].isEmpty = FALSE;

	list[2].data = 2;
	list[2].cursor = 3;
	list[2].isEmpty = FALSE;

	list[3].data = 3;
	list[3].cursor = 0;
	list[3].isEmpty = FALSE;

	return list;
}

#include "test/list/list_test.c"
int main(void) {
	buildTestSuite();
	return runTestSuite();
}
