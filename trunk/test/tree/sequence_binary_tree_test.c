/*
 * sequence_binary_tree_test.c
 *
 *  Created on: 2009-8-23
 *      Author: yuandong
 */

#include <stdlib.h>

#include "CUnit/Basic.h"
#include "CUnit/Console.h"
#include "CUnit/Automated.h"
#include "CUnit/TestDB.h"

#include "include/tree/sequence_binary_tree.h"
#include "include/tree/binary_tree.h"

void assert_equal(BINARY_TREE_TYPE tree, char* definition) {

	CU_ASSERT_PTR_NOT_NULL(tree);
	if (tree == NULL)
		return;

	int i = 0, node_index = 0;
	while (definition[i] != '\0') {

		if (definition[i] == ',') {
			CU_ASSERT_EQUAL(tree[node_index], Nil);
			node_index++;
		}

		if (definition[i] >= '0' && definition[i] <= '9') {
			int number_start = i, number_end = i + 1;
			while (definition[number_end] != ',' && definition[number_end]
					!= ' ' && definition[number_end] != '\0')
				number_end++;
			int value = get_number(definition, number_start, number_end - 1);

			//еп╣х
			CU_ASSERT_EQUAL(tree[node_index], value);

			//next
			node_index++;
			while (definition[number_end] != ',' && definition[number_end]
					!= '\0')
				number_end++;
			i = number_end;
		}
		if (definition[i] != '\0')
			i++;
	}
	while (node_index < MAX_NODE) {
		CU_ASSERT_EQUAL(tree[node_index], Nil);
		node_index++;
	}
}
void assert_node_equal(BINARY_TREE_NODE *node, ElementType value) {
	CU_ASSERT_PTR_NOT_NULL(node);
	if (node == NULL)
		return;

	CU_ASSERT_EQUAL(*node ,value);
}

BINARY_TREE_NODE *get_node(BINARY_TREE_TYPE tree, ElementType value) {
	BINARY_TREE_NODE *index = tree;
	while (index - tree < MAX_NODE) {
		if (*index == value)
			return index;
		index++;
	}
	return NULL;
}

void test_Initial() {
	BINARY_TREE_TYPE tree = NULL;
	Status status = Initial(&tree);

	CU_ASSERT_EQUAL(status, OK);
	CU_ASSERT_PTR_NOT_NULL(tree);
}

#include "test/tree/binary_tree_test.c"
int main(void) {
	CU_pSuite suite = buildTestSuite();
	CU_ADD_TEST(suite, test_Initial);

	return runTestSuite();
}
