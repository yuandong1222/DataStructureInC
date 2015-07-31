/*
 * child_sibling_tree_test.c
 *
 *  Created on: 2009-9-16
 *      Author: yuandong
 */

#include <stdlib.h>

#include "include/CUnit/Basic.h"
#include "include/CUnit/Console.h"
#include "include/CUnit/Automated.h"
#include "include/CUnit/TestDB.h"

#include "include/tree/child_sibling_tree.h"
#include "include/tree/tree.h"

TREE_NODE *get_test_node(TREE_TYPE tree, ElementType value) {
	if (tree == NULL)
		return NULL;
	if (tree -> value == value)
		return tree;

	ChildSiblingTreeNode *node;
	node = get_test_node(tree -> first_child, value);
	if (node != NULL)
		return node;

	node = get_test_node(tree -> next_sibling, value);
	if (node != NULL)
		return node;

	return NULL;
}
void assert_equal(TREE_TYPE tree, char* definition) {

	if (definition == "" || definition == NULL) {
		CU_ASSERT_PTR_NULL(tree);
		return;
	}

	int length, *array;
	build_definition_array(definition, &length, &array);

	CU_ASSERT_PTR_NOT_NULL(tree);
	if (tree == NULL)
		return;

	int i = 0;
	while (i < length) {

		if (array[i + 1] == -1) {
			CU_ASSERT_EQUAL(tree -> value, array[i]);
			i += 2;
			continue;
		}

		int node_value = array[i];
		int parent_index = array[i + 1];
		int parent_value = array[parent_index * 2];
		int order = 1;

		int j = 0;
		for (j = 0; j < i; j += 2) {
			if (array[j + 1] == parent_index)
				order++;
		}
		TREE_NODE *parent = get_test_node(tree, parent_value);
		CU_ASSERT_PTR_NOT_NULL(parent);
		if (parent == NULL)
			return;
		TREE_NODE *node = parent -> first_child;
		int count = 1;
		while (node && count < order) {
			node = node -> next_sibling;
			count++;
		}
		CU_ASSERT_PTR_NOT_NULL(node);
		if (node != NULL)
			CU_ASSERT_EQUAL(node_value, node -> value);

		i += 2;
	}
}
void assert_node_equal(TREE_NODE *node, ElementType value) {
	CU_ASSERT_EQUAL(node -> value,value);
}

void test_Initial() {
	TREE_TYPE tree = (TREE_TYPE) 1;
	Status status = Initial(&tree);

	CU_ASSERT_EQUAL(status, OK);
	CU_ASSERT_PTR_NULL(tree);
}

#include "test/tree/tree_test.c"
int main(void) {
	CU_pSuite suite = buildTestSuite();
	CU_ADD_TEST(suite, test_Initial);

	return runTestSuite();
}
