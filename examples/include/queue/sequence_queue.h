/*
 * queue.h
 *
 *  Created on: 2009-5-19
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_QUEUE_SEQUENCE_QUEUE_H_
#define DATA_STRUCTURE_IN_C_QUEUE_SEQUENCE_QUEUE_H_

#define QUEUE_INITIAL_SIZE	100
#define QUEUE_INCREMENT		10

#define ElementType int
#define QUEUE_TYPE SequenceQueue

#include "include/common.h"

typedef struct SequenceQueueHead {
	ElementType *base;
	int front;
	int rear;
	int size;
} SequenceQueueHead, *SequenceQueue;


#endif /* DATA_STRUCTURE_IN_C_QUEUE_SEQUENCE_QUEUE_H_ */
