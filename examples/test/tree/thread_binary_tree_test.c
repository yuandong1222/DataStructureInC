/*
 * thread_binary_tree.c
 *
 *  Created on: 2009-9-2
 *      Author: yuandong
 */

#include <stdlib.h>

#include "include/CUnit/Basic.h"
#include "include/CUnit/Console.h"
#include "include/CUnit/Automated.h"
#include "include/CUnit/TestDB.h"

#include "include/tree/thread_binary_tree.h"
#include "include/tree/binary_tree.h"

int *assert_equal_visit_result, assert_equal_visit_result_index = 0;
void assert_equal_action(BINARY_TREE_NODE **node, int size) {
	BINARY_TREE_NODE **child_node = (BINARY_TREE_NODE**) malloc(
			sizeof(BINARY_TREE_NODE*) * size * 2);

	int i = 0, child_node_index = 0, has_node = 0;
	for (i = 0; i < size * 2; i++) {
		child_node[i] = NULL;
	}

	for (i = 0; i < size; i++) {

		if (node[i] == NULL) {
			child_node[child_node_index++] = NULL;
			child_node[child_node_index++] = NULL;

			assert_equal_visit_result[assert_equal_visit_result_index] = -1;
			assert_equal_visit_result_index++;
			continue;
		}

		if (node[i] -> left != NULL && node[i] -> left_tag == Child) {
			child_node[child_node_index++] = node[i] -> left;
			has_node = 1;
		} else {
			child_node[child_node_index++] = NULL;

		}
		if (node[i] -> right != NULL && node[i] -> right_tag == Child) {
			child_node[child_node_index++] = node[i] -> right;
			has_node = 1;
		} else {
			child_node[child_node_index++] = NULL;
		}

		assert_equal_visit_result[assert_equal_visit_result_index]
				= node[i] -> value;
		assert_equal_visit_result_index++;
	}

	if (has_node > 0) {
		assert_equal_action(child_node, size * 2);
	}
	free(child_node);
}
void assert_equal(BINARY_TREE_TYPE tree, char* definition) {

	if (definition[0] == '\0') {
		CU_ASSERT_PTR_NULL(tree);
		return;
	}

	CU_ASSERT_PTR_NOT_NULL(tree);
	if (tree == NULL)
		return;

	assert_equal_visit_result = (int*) malloc(sizeof(int) * 100);
	for (assert_equal_visit_result_index = 0; assert_equal_visit_result_index
			< 100; assert_equal_visit_result_index++) {
		assert_equal_visit_result[assert_equal_visit_result_index] = -1;
	}

	assert_equal_visit_result_index = 0;
	BINARY_TREE_NODE **node = (BINARY_TREE_NODE**) malloc(
			sizeof(BINARY_TREE_NODE*));
	*node = tree;
	assert_equal_action(node, 1);
	free(node);

	int i = 0;
	assert_equal_visit_result_index = 0;
	while (definition[i] != '\0') {

		if (definition[i] == ',') {
			CU_ASSERT_EQUAL(assert_equal_visit_result[assert_equal_visit_result_index], -1);
			assert_equal_visit_result_index++;
		}

		if (definition[i] >= '0' && definition[i] <= '9') {
			int number_start = i, number_end = i + 1;
			while (definition[number_end] != ',' && definition[number_end]
					!= ' ' && definition[number_end] != '\0')
				number_end++;
			int value = get_number(definition, number_start, number_end - 1);

			//еп╣х
			CU_ASSERT_EQUAL(assert_equal_visit_result[assert_equal_visit_result_index], value);

			//next
			assert_equal_visit_result_index++;
			while (definition[number_end] != ',' && definition[number_end]
					!= '\0')
				number_end++;
			i = number_end;
		}
		if (definition[i] != '\0')
			i++;
	}
	while (assert_equal_visit_result_index < 100) {
		CU_ASSERT_EQUAL(assert_equal_visit_result[assert_equal_visit_result_index], -1);
		assert_equal_visit_result_index++;
	}

	free(assert_equal_visit_result);
}

void assert_node_equal(BINARY_TREE_NODE *node, ElementType value) {
	CU_ASSERT_PTR_NOT_NULL(node);
	if (node == NULL)
		return;

	CU_ASSERT_EQUAL(node -> value ,value);
}

BINARY_TREE_NODE *get_node(BINARY_TREE_TYPE tree, ElementType value) {
	if (tree -> value == value)
		return tree;

	ThreadBinaryTreeNode *node;
	if (tree -> left != NULL && tree -> left_tag == Child) {
		node = get_node(tree -> left, value);
		if (node != NULL)
			return node;
	}
	if (tree -> right != NULL && tree -> right_tag == Child) {
		node = get_node(tree -> right, value);
		if (node != NULL)
			return node;
	}
	return NULL;
}

void test_Initial() {
	BINARY_TREE_TYPE tree = NULL;
	Status status = Initial(&tree);

	CU_ASSERT_EQUAL(status, OK);
	CU_ASSERT_PTR_NULL(tree);
}

#include "test/tree/binary_tree_test.c"
int main(void) {
	CU_pSuite suite = buildTestSuite();
	CU_ADD_TEST(suite, test_Initial);

	return runTestSuite();
}
