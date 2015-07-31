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
}

Status DestroyQueue(QUEUE_TYPE *queue) {
}

Status ClearQueue(QUEUE_TYPE queue) {
}

BOOLEAN QueueEmpty(QUEUE_TYPE queue) {
}

int QueueLength(QUEUE_TYPE queue) {
}

Status GetHead(QUEUE_TYPE queue, ElementType *element) {
}

Status Enqueue(QUEUE_TYPE queue, ElementType element) {
}

Status Dequeue(QUEUE_TYPE queue, ElementType *element) {
}

Status Traverse(QUEUE_TYPE queue, Status(*visit)(ElementType *element)) {
}
