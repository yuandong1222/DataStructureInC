/*
 * sequence_queue.c
 *
 *  Created on: 2009-5-16
 *      Author: yuandong
 */

#include <stdlib.h>
#include <stdio.h>

#include "include/common.h"
#include "include/queue/sequence_queue.h"
#include "include/queue/queue.h"

Status InitialQueue(QUEUE_TYPE *queue) {
	(*queue) = (SequenceQueue) malloc(sizeof(SequenceQueueHead));
	if (*queue == NULL)
		return OVERFLOW;

	(*queue) -> base = (ElementType*) malloc(sizeof(ElementType)
			* QUEUE_INITIAL_SIZE);
	if ((*queue) -> base == NULL)
		return OVERFLOW;

	(*queue) -> front = (*queue) -> rear = 0;
	(*queue) -> size = QUEUE_INITIAL_SIZE;

	return OK;
}

Status DestroyQueue(QUEUE_TYPE *queue) {
	free((*queue) -> base);
	free(*queue);

	*queue = NULL;
	return OK;
}

Status ClearQueue(QUEUE_TYPE queue) {
	queue -> front = queue -> rear = 0;
	return OK;
}

BOOLEAN QueueEmpty(QUEUE_TYPE queue) {
	return queue -> front == queue -> rear;
}

int QueueLength(QUEUE_TYPE queue) {
	return queue -> rear >= queue -> front ? queue -> rear - queue -> front
			: queue -> size + queue -> rear - queue -> front;
}

Status GetHead(QUEUE_TYPE queue, ElementType *element) {
	if (QueueEmpty(queue))
		return ERROR;

	*element = *(queue -> base + queue -> front);

	return OK;
}

Status Enqueue(QUEUE_TYPE queue, ElementType element) {
	int nextRear = queue -> rear + 1 == queue -> size ? 0 : queue -> rear + 1;
	if (nextRear == queue -> front) {
		ElementType *newBase = (ElementType*) malloc(sizeof(ElementType)
				* (queue -> size + QUEUE_INCREMENT));
		if (newBase == NULL)
			return OVERFLOW;

		int oldIndex = queue -> front, newIndex = 0;
		while (oldIndex != queue -> rear) {
			*(newBase + newIndex) = *(queue -> base + oldIndex);

			newIndex++;
			oldIndex++;

			if (oldIndex == queue -> size)
				oldIndex = 0;
		}
		free(queue -> base);

		queue -> base = newBase;
		queue -> size += QUEUE_INCREMENT;
		queue -> front = 0;
		queue -> rear = newIndex;
		}

	*(queue -> base + queue -> rear) = element;
	(queue -> rear)++;

	return OK;
}

Status Dequeue(QUEUE_TYPE queue, ElementType *element) {
	if (QueueEmpty(queue))
		return ERROR;

	*element = *(queue -> base + queue -> front);

	(queue -> front)++;
	if (queue -> front == queue -> size)
		queue -> front = 0;

	return OK;
}

Status Traverse(QUEUE_TYPE queue, Status(*visit)(ElementType *element)) {
	int index = queue -> front;
	Status result;

	while (index != queue -> rear) {
		result = (*visit)(queue -> base + index);
		if (result != OK)
			return result;

		index++;
		if (index == queue -> size)
			index = 0;
	}
	return OK;
}
