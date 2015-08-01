/*
 * tree_test.c
 *
 *  Created on: 2009-9-2
 *      Author: yuandong
 */

#include <stdlib.h>

#include "include/tree/tree.h"

#include "CUnit/Basic.h"
#include "CUnit/Console.h"
#include "CUnit/Automated.h"
#include "CUnit/TestDB.h"

TREE_TYPE get_test_tree(char* definition) {
	TREE_TYPE tree = NULL;
	Status status = ERROR;

	status = Initial(&tree);
	CU_ASSERT_EQUAL(status, OK);
	if (status != OK)
		return NULL;

	status = Create(&tree, definition);
	CU_ASSERT_EQUAL(status, OK);
	if (status != OK)
		return NULL;

	return tree;
}

void test_Destory(void) {
	TREE_TYPE tree = get_test_tree("1, -1; 2, 0; 3, 0; 4, 1;");
	if (tree == NULL)
		return;

	Status status = Destory(&tree);
	CU_ASSERT_EQUAL(status, OK);
	CU_ASSERT_PTR_NULL(tree);
}
void test_Create(void) {
	TREE_TYPE tree = NULL;
	Status status = Initial(&tree);
	CU_ASSERT_EQUAL(status, OK);
	if (status != OK)
		return;

	Initial(&tree);
	status = Create(&tree, "");
	CU_ASSERT_EQUAL(status, OK);
	assert_equal(tree, "");

	Initial(&tree);
	status = Create(&tree, "1, -1;");
	CU_ASSERT_EQUAL(status, OK);
	assert_equal(tree, "1, -1;");

	Initial(&tree);
	status = Create(&tree, "1, -1; 2, 0; 3, 0; 4, 0;");
	CU_ASSERT_EQUAL(status, OK);
	assert_equal(tree, "1, -1; 2, 0; 3, 0; 4, 0;");

	Initial(&tree);
	status = Create(&tree, "1, -1; 2, 0; 3, 0; 4, 0; 5, 1; 6, 1;");
	CU_ASSERT_EQUAL(status, OK);
	assert_equal(tree, "1, -1; 2, 0; 3, 0; 4, 0; 5, 1; 6, 1;");

	Initial(&tree);
	status = Create(&tree,
			"1, -1; 2, 0; 3, 0; 4, 0; 5, 1; 6, 1; 7, 5; 8, 6; 9, 6;");
	CU_ASSERT_EQUAL(status, OK);
	assert_equal(tree, "1, -1; 2, 0; 3, 0; 4, 0; 5, 1; 6, 1; 7, 5; 8, 6; 9, 6;");
}
void test_Clear(void) {
	TREE_TYPE tree = get_test_tree("1, -1; 2, 0; 3, 0; 4, 1;");
	if (tree == NULL)
		return;

	Status status = Clear(&tree);
	CU_ASSERT_EQUAL(status, OK);
	CU_ASSERT_TRUE(Empty(tree));
}
void test_Empty(void) {
	TREE_TYPE tree = get_test_tree("1, -1; 2, 0; 3, 0; 4, 1;");
	if (tree == NULL)
		return;

	tree = get_test_tree("1, -1; 2, 0; 3, 0; 4, 1;");
	CU_ASSERT_FALSE(Empty(tree));

	tree = get_test_tree("");
	CU_ASSERT_TRUE(Empty(tree));
}
void test_Depth(void) {
	TREE_TYPE tree = NULL;

	tree = get_test_tree("");
	CU_ASSERT_EQUAL(Depth(tree), 0);

	tree = get_test_tree("1, -1;");
	CU_ASSERT_EQUAL(Depth(tree), 1);

	tree = get_test_tree("1, -1; 2, 0; 3, 0; 4, 0;");
	CU_ASSERT_EQUAL(Depth(tree), 2);

	tree = get_test_tree("1, -1; 2, 0; 3, 0; 4, 0; 5, 1; 6, 1;");
	CU_ASSERT_EQUAL(Depth(tree), 3);

	tree = get_test_tree(
			"1, -1; 2, 0; 3, 0; 4, 0; 5, 1; 6, 1; 7, 5; 8, 6; 9, 6;");
	CU_ASSERT_EQUAL(Depth(tree), 5);
}
void test_Root(void) {
	TREE_TYPE tree = get_test_tree("1, -1; 2, 0; 3, 0; 4, 1;");
	if (tree == NULL)
		return;

	TREE_NODE *node = NULL;

	tree = get_test_tree("");
	node = Root(tree);
	CU_ASSERT_PTR_NULL(node);

	tree = get_test_tree("1, -1; 2, 0; 3, 0; 4, 0;");
	node = Root(tree);
	assert_node_equal(node, 1);

	tree = get_test_tree("101, -1; 2, 0; 3, 0; 4, 0;");
	node = Root(tree);
	assert_node_equal(node, 101);
}
void test_Value(void) {
	TREE_TYPE tree = get_test_tree(
			"1, -1; 2, 0; 3, 0; 4, 0; 5, 1; 6, 1; 7, 5; 8, 6; 9, 6;");
	if (tree == NULL)
		return;

	TREE_NODE *node = NULL;
	ElementType value;

	node = get_test_node(tree, 1);
	value = Value(tree, node);
	CU_ASSERT_EQUAL(value, 1);

	node = get_test_node(tree, 5);
	value = Value(tree, node);
	CU_ASSERT_EQUAL(value, 5);

	node = NULL;
	value = Value(tree, node);
	CU_ASSERT_EQUAL(value, 0);
}
void test_Assign(void) {
	TREE_TYPE tree = get_test_tree(
			"1, -1; 2, 0; 3, 0; 4, 0; 5, 1; 6, 1; 7, 5; 8, 6; 9, 6;");
	if (tree == NULL)
		return;

	TREE_NODE *node = NULL;
	Status status;

	node = get_test_node(tree, 1);
	status = Assign(&tree, node, 101);
	CU_ASSERT_EQUAL(status, OK);
	CU_ASSERT_EQUAL(Value(tree,node), 101);

	node = get_test_node(tree, 3);
	status = Assign(&tree, node, 33);
	CU_ASSERT_EQUAL(status, OK);
	CU_ASSERT_EQUAL(Value(tree,node), 33);

	node = get_test_node(tree, 8);
	status = Assign(&tree, node, 88);
	CU_ASSERT_EQUAL(status, OK);
	CU_ASSERT_EQUAL(Value(tree,node), 88);
}
void test_Parent(void) {
	TREE_TYPE tree = get_test_tree(
			"1, -1; 2, 0; 3, 0; 4, 0; 5, 1; 6, 1; 7, 5; 8, 6; 9, 6;");
	if (tree == NULL)
		return;

	TREE_NODE *node, *parent;

	node = get_test_node(tree, 1);
	parent = Parent(tree, node);
	CU_ASSERT_PTR_NULL(parent);

	node = get_test_node(tree, 3);
	parent = Parent(tree, node);
	assert_node_equal(parent, 1);

	node = get_test_node(tree, 8);
	parent = Parent(tree, node);
	assert_node_equal(parent, 7);
}
void test_LeftChild(void) {
	TREE_TYPE tree = get_test_tree(
			"1, -1; 2, 0; 3, 0; 4, 0; 5, 1; 6, 1; 7, 5; 8, 6; 9, 6;");
	if (tree == NULL)
		return;

	TREE_NODE *node, *left_child;

	node = get_test_node(tree, 1);
	left_child = LeftChild(tree, node);
	assert_node_equal(left_child, 2);

	node = get_test_node(tree, 6);
	left_child = LeftChild(tree, node);
	assert_node_equal(left_child, 7);

	node = get_test_node(tree, 5);
	left_child = LeftChild(tree, node);
	CU_ASSERT_PTR_NULL(left_child);
}
void test_RightSibling(void) {
	TREE_TYPE tree = get_test_tree(
			"1, -1; 2, 0; 3, 0; 4, 0; 5, 1; 6, 1; 7, 5; 8, 6; 9, 6;");
	if (tree == NULL)
		return;

	TREE_NODE *node, *right_sibling;

	node = get_test_node(tree, 2);
	right_sibling = RightSibling(tree, node);
	assert_node_equal(right_sibling, 3);

	node = get_test_node(tree, 5);
	right_sibling = RightSibling(tree, node);
	assert_node_equal(right_sibling, 6);

	node = get_test_node(tree, 1);
	right_sibling = RightSibling(tree, node);
	CU_ASSERT_PTR_NULL(right_sibling);

	node = get_test_node(tree, 4);
	right_sibling = RightSibling(tree, node);
	CU_ASSERT_PTR_NULL(right_sibling);
}

void test_InsertChild(void) {
	TREE_TYPE tree = get_test_tree(
			"1, -1; 2, 0; 3, 0; 4, 0; 5, 1; 6, 1; 7, 5; 8, 6; 9, 6;");
	if (tree == NULL)
		return;

	TREE_NODE *node = get_test_node(tree, 4);
	Status status = ERROR;

	status = InsertChild(tree, node, 1, 41);
	CU_ASSERT_EQUAL(status, OK);
	assert_equal(tree,
			"1, -1; 2, 0; 3, 0; 4, 0; 5, 1; 6, 1; 7, 5; 8, 6; 9, 6; 41, 3;");
	return;

	status = InsertChild(tree, node, 1, 42);
	CU_ASSERT_EQUAL(status, OK);
	assert_equal(tree,
			"1, -1; 2, 0; 3, 0; 4, 0; 5, 1; 6, 1; 7, 5; 8, 6; 9, 6; 42, 3; 41, 3;");

	status = InsertChild(tree, node, 3, 43);
	CU_ASSERT_EQUAL(status, OK);
	assert_equal(tree,
			"1, -1; 2, 0; 3, 0; 4, 0; 5, 1; 6, 1; 7, 5; 8, 6; 9, 6; 42, 3; 41, 3; 43, 3;");

	status = InsertChild(tree, node, 2, 44);
	CU_ASSERT_EQUAL(status, OK);
	assert_equal(
			tree,
			"1, -1; 2, 0; 3, 0; 4, 0; 5, 1; 6, 1; 7, 5; 8, 6; 9, 6; 42, 3; 44, 2; 41, 3; 43, 3;");
}
void test_DeleteChild(void) {
	TREE_TYPE tree = get_test_tree(
			"1, -1; 2, 0; 3, 0; 4, 0; 5, 1; 6, 1; 7, 5; 8, 6; 9, 6;");
	if (tree == NULL)
		return;

	TREE_NODE *node = get_test_node(tree, 1);
	Status status = ERROR;

	status = DeleteChild(tree, node, 2);
	CU_ASSERT_EQUAL(status, OK);
	assert_equal(tree, "1, -1; 2, 0; 4, 0; 5, 1; 6, 1; 7, 4; 8, 5; 9, 5;");

	status = DeleteChild(tree, node, 2);
	CU_ASSERT_EQUAL(status, OK);
	assert_equal(tree, "1, -1; 2, 0; 5, 1; 6, 1; 7, 3; 8, 4; 9, 4;");

	status = DeleteChild(tree, node, 1);
	CU_ASSERT_EQUAL(status, OK);
	assert_equal(tree, "1, -1;");
}

int visit_result = 0;
Status visit(ElementType *value) {
	CU_ASSERT_PTR_NOT_NULL(value);
	if (value == NULL)
		return ERROR;

	visit_result += *value;

	return OK;
}
void test_Traverse(void) {
	TREE_TYPE tree = get_test_tree(
			"1, -1; 2, 0; 3, 0; 4, 0; 5, 1; 6, 1; 7, 5; 8, 6; 9, 6;");
	if (tree == NULL)
		return;

	visit_result = 0;

	Status status = Traverse(tree, visit);
	CU_ASSERT_EQUAL(status, OK);

	CU_ASSERT_EQUAL(visit_result, 45);
}
CU_pSuite buildTestSuite() {
	CU_initialize_registry();

	CU_pSuite pSuite = CU_add_suite("Tree Test Suite", NULL, NULL);
	CU_ADD_TEST(pSuite, test_Destory);
	CU_ADD_TEST(pSuite, test_Create);
	CU_ADD_TEST(pSuite, test_Clear);
	CU_ADD_TEST(pSuite, test_Empty);
	CU_ADD_TEST(pSuite, test_Depth);
	CU_ADD_TEST(pSuite, test_Root);
	CU_ADD_TEST(pSuite, test_Value);
	CU_ADD_TEST(pSuite, test_Assign);
	CU_ADD_TEST(pSuite, test_Parent);
	CU_ADD_TEST(pSuite, test_LeftChild);
	CU_ADD_TEST(pSuite, test_RightSibling);
	CU_ADD_TEST(pSuite, test_InsertChild);
	CU_ADD_TEST(pSuite, test_DeleteChild);
	CU_ADD_TEST(pSuite, test_Traverse);

	return pSuite;
}
int runTestSuite() {
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

	CU_cleanup_registry();
	return CU_get_error();
}
