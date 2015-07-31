/*
 * queue.h
 *
 *  Created on: 2009-5-19
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_QUEUE_LINK_QUEUE_H_
#define DATA_STRUCTURE_IN_C_QUEUE_LINK_QUEUE_H_

#define ElementType int
#define QUEUE_TYPE LinkQueue

#include "include/common.h"

typedef struct LinkQueueNode {
	ElementType data;
	struct LinkQueueNode *next;
} LinkQueueNode;


typedef struct LinkQueueHeadNode {
	LinkQueueNode *front;
	LinkQueueNode *rear;
} LinkQueueHeadNode, *LinkQueue;

#endif /* DATA_STRUCTURE_IN_C_QUEUE_LINK_QUEUE_H_ */
