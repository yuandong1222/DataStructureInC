/*
 * link_queue.c
 *
 *  Created on: 2009-5-16
 *      Author: yuandong
 */

#include <stdlib.h>
#include <stdio.h>

#include "include/common.h"
#include "include/queue/link_queue.h"
#include "include/queue/queue.h"

Status InitialQueue(QUEUE_TYPE *queue) {
	(*queue) = (LinkQueue) malloc(sizeof(LinkQueueHeadNode));
	if (*queue == NULL)
		return OVERFLOW;

	(*queue) -> front = (*queue) -> rear = NULL;

	return OK;
}

Status DestroyQueue(QUEUE_TYPE *queue) {
	LinkQueueNode *node = (*queue) -> front, *temp = NULL;

	while (node != NULL) {
		temp = node -> next;
		free(node);
		node = temp;
	}

	free(*queue);
	*queue = NULL;

	return OK;
}

Status ClearQueue(QUEUE_TYPE queue) {
	LinkQueueNode *node = queue -> front, *temp = NULL;

	while (node != NULL) {
		temp = node -> next;
		free(node);
		node = temp;
	}

	queue -> front = queue -> rear = NULL;

	return OK;
}

BOOLEAN QueueEmpty(QUEUE_TYPE queue) {
	return queue -> front == NULL;
}

int QueueLength(QUEUE_TYPE queue) {
	LinkQueueNode *node = queue -> front;
	int length = 0;

	while (node != NULL) {
		length++;
		node = node -> next;
	}

	return length;
}

Status GetHead(QUEUE_TYPE queue, ElementType *element) {
	if (QueueEmpty(queue))
		return ERROR;

	*element = queue -> front -> data;

	return OK;
}

Status Enqueue(QUEUE_TYPE queue, ElementType element) {
	LinkQueueNode *node = (LinkQueueNode*)malloc(sizeof(LinkQueueNode));
	if(node == NULL)
		return OVERFLOW;

	node -> data = element;
	node -> next = NULL;

	if(queue -> front == NULL){
		queue -> front = queue -> rear = node;
		return OK;
	}

	queue -> rear -> next = node;
	queue -> rear = node;

	return OK;

}

Status Dequeue(QUEUE_TYPE queue, ElementType *element) {
	if(QueueEmpty(queue))
		return ERROR;

	if(queue -> front == queue -> rear){
		*element = queue -> front -> data;
		free(queue -> front);
		queue -> front = queue -> rear = NULL;
		return OK;
	}

	LinkQueueNode *node = queue -> front -> next;

	*element = queue -> front -> data;
	free(queue -> front);
	queue -> front = node;

	return OK;
}

Status Traverse(QUEUE_TYPE queue, Status(*visit)(ElementType *element)) {
	LinkQueueNode *node = queue -> front;

	while (node != NULL) {
		if (((*visit)(&(node -> data))) == ERROR)
			return ERROR;
		node = node -> next;
	}

	return OK;
}
