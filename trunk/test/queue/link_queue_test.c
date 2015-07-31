/*
 * link_queue_test.c
 *
 *  Created on: 2009-4-10
 *      Author: yuandong
 */
#include <stdlib.h>

#include "include/queue/link_queue.h"

#define TEST_QUEUE_LENGTH 3

LinkQueue getTestQueue() {
	LinkQueue queue;

	queue = (LinkQueue) malloc(sizeof(LinkQueueHeadNode));

	queue -> front = (LinkQueueNode*) malloc(sizeof(LinkQueueNode));
	queue -> front -> data = 1;

	queue -> front -> next = (LinkQueueNode*) malloc(sizeof(LinkQueueNode));
	queue -> front -> next -> data = 2;

	queue -> front -> next -> next = (LinkQueueNode*) malloc(
			sizeof(LinkQueueNode));
	queue -> front -> next -> next -> data = 3;

	queue -> front -> next -> next -> next = NULL;
	queue -> rear = queue -> front -> next -> next;

	return queue;
}

#include "test/queue/queue_test.c"
int main(void) {
	buildTestSuite();
	return runTestSuite();
}
