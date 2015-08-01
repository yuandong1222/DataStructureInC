/*
 * parent_tree_test.c
 *
 *  Created on: 2009-9-3
 *      Author: yuandong
 */

#include <stdlib.h>

#include "CUnit/Basic.h"
#include "CUnit/Console.h"
#include "CUnit/Automated.h"
#include "CUnit/TestDB.h"

#include "include/tree/parent_tree.h"
#include "include/tree/tree.h"

TREE_NODE *get_test_node(TREE_TYPE tree, ElementType value) {
	if (tree == NULL)
		return NULL;

	int i = 0;
	for (i = 0; i < tree -> length; i++) {
		if ((tree -> nodes)[i].value == value)
			return (tree -> nodes) + i;
	}
	return NULL;
}

void assert_equal(TREE_TYPE tree, char* definition) {

	if (definition == "" || definition == NULL) {
		CU_ASSERT_EQUAL(tree -> length, 0);
		return;
	}

	int length, *array;
	build_definition_array(definition, &length, &array);

	CU_ASSERT_EQUAL(tree -> length, length / 2);
	if (tree -> length != length / 2)
		return;

	int i = 0;
	while (i < length) {
		int j = 0, isFound = 0, node_count = 0;
		while (node_count < tree -> length && j < MAX_NODE) {
			if (j != 0 && (tree -> nodes)[j].parent == -1) {
				j++;
				continue;
			}
			if (j == 0) {
				CU_ASSERT_EQUAL((tree -> nodes)[j].parent, -1);
				isFound = 1;
				i += 2;
				j++;
				continue;
			}

			if ((tree -> nodes)[j].value == array[i]) {
				int parent_index = array[i + 1];
				int parent_value = array[parent_index * 2];
				TREE_NODE *parent = get_test_node(tree, parent_value);
				CU_ASSERT_EQUAL((tree -> nodes)[j].parent, parent - tree -> nodes);
				i += 2;
				isFound = 1;
				node_count++;
				break;
			}
			j++;
		}
		CU_ASSERT_TRUE(isFound);
		if (!isFound)
			return;
	}
}
void assert_node_equal(TREE_NODE *node, ElementType value) {
	CU_ASSERT_EQUAL(node -> value, value);
}

void test_Initial() {
	TREE_TYPE tree = NULL;
	Status status = Initial(&tree);

	CU_ASSERT_EQUAL(status, OK);
	CU_ASSERT_PTR_NOT_NULL(tree);
	if (tree == NULL)
		return;

	CU_ASSERT_EQUAL(tree -> length, 0);
	int i = 0;
	for (i = 0; i < MAX_NODE; i++) {
		CU_ASSERT_EQUAL((tree -> nodes)[i].parent, -1);
	}
}

#include "test/tree/tree_test.c"
int main(void) {
	CU_pSuite suite = buildTestSuite();
	CU_ADD_TEST(suite, test_Initial);

	return runTestSuite();
}
