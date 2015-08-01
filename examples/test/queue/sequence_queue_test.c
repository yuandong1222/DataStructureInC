/*
 * sequence_queue_test.c
 *
 *  Created on: 2009-4-10
 *      Author: yuandong
 */
#include <stdlib.h>

#include "CUnit/Basic.h"
#include "CUnit/Console.h"
#include "CUnit/Automated.h"
#include "CUnit/TestDB.h"

#include "include/queue/sequence_queue.h"
#include "include/queue/queue.h"

#define TEST_QUEUE_LENGTH 3

SequenceQueue getTestQueue() {
	SequenceQueue queue;
	queue = (SequenceQueue) malloc(sizeof(SequenceQueueHead));
	queue -> base = (ElementType*) malloc(sizeof(ElementType)
			* QUEUE_INITIAL_SIZE);
	queue -> front = QUEUE_INITIAL_SIZE - 2;
	queue -> rear = 1;
	queue -> size = QUEUE_INITIAL_SIZE;

	queue -> base[QUEUE_INITIAL_SIZE - 2] = 1;
	queue -> base[QUEUE_INITIAL_SIZE - 1] = 2;
	queue -> base[0] = 3;

	return queue;
}
void test_Increment(void) {
	QUEUE_TYPE queue = NULL;
	Status result = InitialQueue(&queue);
	int size = QUEUE_INITIAL_SIZE + QUEUE_INCREMENT;

	CU_ASSERT_EQUAL(result, OK);
	if (result != OK)
		return;

	int i = 0;
	for (i = 0; i < size - 1; i++) {
		result = Enqueue(queue, i);
		CU_ASSERT_EQUAL(result, OK);
		if (result != OK)
			return;
	}

	CU_ASSERT_EQUAL(queue -> size, size);
	for (i = 0; i < size - 1; i++) {
		CU_ASSERT_EQUAL(*(queue -> base + i), i);
	}
}

#include "test/queue/queue_test.c"
int main(void) {

	CU_pSuite suite = buildTestSuite();

	CU_ADD_TEST(suite, test_Increment);

	return runTestSuite();
}
