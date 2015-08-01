/*
 * binary_tree_test.c
 *
 *  Created on: 2009-8-23
 *      Author: yuandong
 */

#include <stdlib.h>

#include "include/tree/binary_tree.h"

#include "CUnit/Basic.h"
#include "CUnit/Console.h"
#include "CUnit/Automated.h"
#include "CUnit/TestDB.h"

BINARY_TREE_TYPE get_test_tree(char* definition) {
	BINARY_TREE_TYPE tree = NULL;
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
	BINARY_TREE_TYPE tree = get_test_tree("1,2,3,4,5");
	if (tree == NULL)
		return;

	Status status = Destory(&tree);
	CU_ASSERT_EQUAL(status, OK);
	CU_ASSERT_PTR_NULL(tree);
}
void test_Create(void) {
	BINARY_TREE_TYPE tree = NULL;
	Status status = Initial(&tree);
	CU_ASSERT_EQUAL(status, OK);
	if (status != OK)
		return;

	Initial(&tree);
	status = Create(&tree, "");
	CU_ASSERT_EQUAL(status, OK);
	assert_equal(tree, "");

	Initial(&tree);
	status = Create(&tree, "1");
	CU_ASSERT_EQUAL(status, OK);
	assert_equal(tree, "1");

	Initial(&tree);
	status = Create(&tree, "1, 2, 3, 4, 5");
	CU_ASSERT_EQUAL(status, OK);
	assert_equal(tree, "1, 2, 3, 4, 5");

	Initial(&tree);
	status = Create(&tree, "1, , 3, , , 6, 7");
	CU_ASSERT_EQUAL(status, OK);
	assert_equal(tree, "1, , 3, , , 6, 7");

	Initial(&tree);
	status = Create(&tree, "1, , 3, , , 6, 7, , , , , 61, 62, 71, 72");
	CU_ASSERT_EQUAL(status, OK);
	assert_equal(tree, "1, , 3, , , 6, 7, , , , , 61, 62, 71, 72");
}
void test_Clear(void) {
	BINARY_TREE_TYPE tree = get_test_tree("1,2,3,4,5");
	if (tree == NULL)
		return;

	Status status = Clear(&tree);
	CU_ASSERT_EQUAL(status, OK);
	CU_ASSERT_TRUE(Empty(tree));
}
void test_Empty(void) {
	BINARY_TREE_TYPE tree = get_test_tree("1,2,3,4,5");
	if (tree == NULL)
		return;

	tree = get_test_tree("1,2,3,4,5");
	CU_ASSERT_FALSE(Empty(tree));

	tree = get_test_tree("");
	CU_ASSERT_TRUE(Empty(tree));
}
void test_Depth(void) {
	BINARY_TREE_TYPE tree = NULL;

	tree = get_test_tree("");
	CU_ASSERT_EQUAL(Depth(tree), 0);

	tree = get_test_tree("1");
	CU_ASSERT_EQUAL(Depth(tree), 1);

	tree = get_test_tree("1, 2");
	CU_ASSERT_EQUAL(Depth(tree), 2);

	tree = get_test_tree("1, 2, 3, 4");
	CU_ASSERT_EQUAL(Depth(tree), 3);

	tree = get_test_tree("1, , 3, , , 6, 7, , , , , 61, 62, 71, 72");
	CU_ASSERT_EQUAL(Depth(tree), 4);
}
void test_Root(void) {
	BINARY_TREE_TYPE tree = NULL;
	BINARY_TREE_NODE *node = NULL;

	tree = get_test_tree("");
	node = Root(tree);
	CU_ASSERT_PTR_NULL(node);

	tree = get_test_tree("1");
	node = Root(tree);
	assert_node_equal(node, 1);

	tree = get_test_tree("101, 2, 3, 4, 5");
	node = Root(tree);
	assert_node_equal(node, 101);
}
void test_Value(void) {
	BINARY_TREE_TYPE tree = get_test_tree(
			"1, 2, 3, , 5, 6, , , , 51, 52, 61, 62, , ");
	if (tree == NULL)
		return;

	Position position;

	position.level = 1;
	position.order = 1;
	CU_ASSERT_EQUAL(Value(tree, position), 1);

	position.level = 2;
	position.order = 2;
	CU_ASSERT_EQUAL(Value(tree, position), 3);

	position.level = 3;
	position.order = 3;
	CU_ASSERT_EQUAL(Value(tree, position), 6);

	position.level = 4;
	position.order = 6;
	CU_ASSERT_EQUAL(Value(tree, position), 62);

	position.level = 3;
	position.order = 1;
	CU_ASSERT_EQUAL(Value(tree, position), 0);
}
void test_Assign(void) {
	BINARY_TREE_TYPE tree = get_test_tree(
			"1, 2, 3, , 5, 6, , , , 51, 52, 61, 62, , ");
	if (tree == NULL)
		return;

	Position position;
	Status status = ERROR;

	position.level = 1;
	position.order = 1;
	status = Assign(&tree, position, 101);
	CU_ASSERT_EQUAL(status, OK);
	CU_ASSERT_EQUAL(Value(tree, position), 101);

	position.level = 2;
	position.order = 2;
	status = Assign(&tree, position, 103);
	CU_ASSERT_EQUAL(status, OK);
	CU_ASSERT_EQUAL(Value(tree, position), 103);

	position.level = 3;
	position.order = 1;
	status = Assign(&tree, position, 1000);
	CU_ASSERT_EQUAL(status, ERROR);
}
void test_Parent(void) {
	BINARY_TREE_TYPE tree = get_test_tree(
			"1, 2, 3, , 5, 6, , , , 51, 52, 61, 62, , ");
	if (tree == NULL)
		return;

	BINARY_TREE_NODE *node, *parent;

	node = get_node(tree, 1);
	parent = Parent(tree, node);
	CU_ASSERT_PTR_NULL(parent);

	node = get_node(tree, 3);
	parent = Parent(tree, node);
	assert_node_equal(parent, 1);

	node = get_node(tree, 6);
	parent = Parent(tree, node);
	assert_node_equal(parent, 3);
}
void test_LeftChild(void) {
	BINARY_TREE_TYPE tree = get_test_tree(
			"1, 2, 3, , 5, 6, , , , 51, 52, 61, 62, , ");
	if (tree == NULL)
		return;

	BINARY_TREE_NODE *node, *left_child;

	node = get_node(tree, 1);
	left_child = LeftChild(tree, node);
	assert_node_equal(left_child, 2);

	node = get_node(tree, 3);
	left_child = LeftChild(tree, node);
	assert_node_equal(left_child, 6);

	node = get_node(tree, 2);
	left_child = LeftChild(tree, node);
	CU_ASSERT_PTR_NULL(left_child);
}
void test_RightChild(void) {
	BINARY_TREE_TYPE tree = get_test_tree(
			"1, 2, 3, , 5, 6, , , , 51, 52, 61, 62, , ");
	if (tree == NULL)
		return;

	BINARY_TREE_NODE *node, *right_child;

	node = get_node(tree, 1);
	right_child = RightChild(tree, node);
	assert_node_equal(right_child, 3);

	node = get_node(tree, 2);
	right_child = RightChild(tree, node);
	assert_node_equal(right_child, 5);

	node = get_node(tree, 3);
	right_child = RightChild(tree, node);
	CU_ASSERT_PTR_NULL(right_child);
}

void test_LeftSibling(void) {
	BINARY_TREE_TYPE tree = get_test_tree(
			"1, 2, 3, , 5, 6, , , , 51, 52, 61, 62, , ");
	if (tree == NULL)
		return;

	BINARY_TREE_NODE *node, *left_sibling;

	node = get_node(tree, 3);
	left_sibling = LeftSibling(tree, node);
	assert_node_equal(left_sibling, 2);

	node = get_node(tree, 52);
	left_sibling = LeftSibling(tree, node);
	assert_node_equal(left_sibling, 51);

	node = get_node(tree, 1);
	left_sibling = LeftSibling(tree, node);
	CU_ASSERT_PTR_NULL(left_sibling);

	node = get_node(tree, 2);
	left_sibling = LeftSibling(tree, node);
	CU_ASSERT_PTR_NULL(left_sibling);

	node = get_node(tree, 61);
	left_sibling = LeftSibling(tree, node);
	CU_ASSERT_PTR_NULL(left_sibling);
}
void test_RightSibling(void) {
	BINARY_TREE_TYPE tree = get_test_tree(
			"1, 2, 3, , 5, 6, , , , 51, 52, 61, 62, , ");
	if (tree == NULL)
		return;

	BINARY_TREE_NODE *node, *right_sibling;

	node = get_node(tree, 2);
	right_sibling = RightSibling(tree, node);
	assert_node_equal(right_sibling, 3);

	node = get_node(tree, 51);
	right_sibling = RightSibling(tree, node);
	assert_node_equal(right_sibling, 52);

	node = get_node(tree, 1);
	right_sibling = RightSibling(tree, node);
	CU_ASSERT_PTR_NULL(right_sibling);

	node = get_node(tree, 3);
	right_sibling = RightSibling(tree, node);
	CU_ASSERT_PTR_NULL(right_sibling);

	node = get_node(tree, 52);
	right_sibling = RightSibling(tree, node);
	CU_ASSERT_PTR_NULL(right_sibling);
}

void test_InsertChild(void) {
	BINARY_TREE_TYPE tree = get_test_tree(
			"1, 2, 3, , 5, 6, , , , 51, 52, 61, 62, , ");
	if (tree == NULL)
		return;

	BINARY_TREE_NODE *node;
	Status status = ERROR;
	Position position;

	node = get_node(tree, 2);
	status = InsertChild(tree, node, Left, 4);
	CU_ASSERT_EQUAL(status, OK);
	position.level = 3;
	position.order = 1;
	CU_ASSERT_EQUAL(Value(tree, position), 4);

	node = get_node(tree, 2);
	status = InsertChild(tree, node, Right, 5);
	CU_ASSERT_EQUAL(status, ERROR);
}
void test_DeleteChild(void) {
	BINARY_TREE_TYPE tree = get_test_tree(
			"1, 2, 3, , 5, 6, , , , 51, 52, 61, 62, , ");
	if (tree == NULL)
		return;

	BINARY_TREE_NODE *node;
	Status status = ERROR;
	Position position;

	node = get_node(tree, 2);
	status = DeleteChild(tree, node, Right);
	CU_ASSERT_EQUAL(status, OK);
	position.level = 3;
	position.order = 2;
	CU_ASSERT_EQUAL(Value(tree, position), 0);

	node = get_node(tree, 2);
	status = DeleteChild(tree, node, Left);
	CU_ASSERT_EQUAL(status, OK);
}

ElementType *visit_result = NULL;
int visit_result_index = 0;
Status visit(ElementType *value) {
	CU_ASSERT_PTR_NOT_NULL(value);
	if (value == NULL)
		return ERROR;

	visit_result[visit_result_index] = *value;
	visit_result_index++;

	return OK;
}
void assert_visit_result(ElementType *expect_result, int length) {
	int i = 0;
	for (i = 0; i < length; i++) {
		CU_ASSERT_EQUAL(visit_result[i], expect_result[i]);
	}
}

void test_PreOrderTraverse(void) {
	BINARY_TREE_TYPE tree = get_test_tree(
			"1, 2, 3, , 5, 6, , , , 51, 52, 61, 62, , ");
	if (tree == NULL)
		return;

	visit_result = (ElementType*) malloc(sizeof(ElementType) * 9);
	visit_result_index = 0;

	Status status = PreOrderTraverse(tree, visit);
	CU_ASSERT_EQUAL(status, OK);

	int expert_result[] = { 1, 2, 5, 51, 52, 3, 6, 61, 62 };
	assert_visit_result(expert_result, 9);
}
void test_InOrderTraverse(void) {
	BINARY_TREE_TYPE tree = get_test_tree(
			"1, 2, 3, , 5, 6, , , , 51, 52, 61, 62, , ");
	if (tree == NULL)
		return;

	visit_result = (ElementType*) malloc(sizeof(ElementType) * 9);
	visit_result_index = 0;

	Status status = InOrderTraverse(tree, visit);
	CU_ASSERT_EQUAL(status, OK);

	int expert_result[] = { 2, 51, 5, 52, 1, 61, 6, 62, 3 };
	assert_visit_result(expert_result, 9);
}
void test_PostOrderTraverse(void) {
	BINARY_TREE_TYPE tree = get_test_tree(
			"1, 2, 3, , 5, 6, , , , 51, 52, 61, 62, , ");
	if (tree == NULL)
		return;

	visit_result = (ElementType*) malloc(sizeof(ElementType) * 9);
	visit_result_index = 0;

	Status status = PostOrderTraverse(tree, visit);
	CU_ASSERT_EQUAL(status, OK);

	int expert_result[] = { 51, 52, 5, 2, 61, 62, 6, 3, 1 };
	assert_visit_result(expert_result, 9);
}
void test_LevelOrderTraverse(void) {
	BINARY_TREE_TYPE tree = get_test_tree(
			"1, 2, 3, , 5, 6, , , , 51, 52, 61, 62, , ");
	if (tree == NULL)
		return;

	visit_result = (ElementType*) malloc(sizeof(ElementType) * 9);
	visit_result_index = 0;

	Status status = LevelOrderTraverse(tree, visit);
	CU_ASSERT_EQUAL(status, OK);

	int expert_result[] = { 1, 2, 3, 5, 6, 51, 52, 61, 62 };
	assert_visit_result(expert_result, 9);
}
CU_pSuite buildTestSuite() {
	CU_initialize_registry();

	CU_pSuite pSuite = CU_add_suite("Binary Tree Test Suite", NULL, NULL);
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
	CU_ADD_TEST(pSuite, test_RightChild);
	CU_ADD_TEST(pSuite, test_LeftSibling);
	CU_ADD_TEST(pSuite, test_RightSibling);
	CU_ADD_TEST(pSuite, test_InsertChild);
	CU_ADD_TEST(pSuite, test_DeleteChild);
	CU_ADD_TEST(pSuite, test_PreOrderTraverse);
	CU_ADD_TEST(pSuite, test_InOrderTraverse);
	CU_ADD_TEST(pSuite, test_PostOrderTraverse);
	CU_ADD_TEST(pSuite, test_LevelOrderTraverse);

	return pSuite;
}
int runTestSuite() {
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

	CU_cleanup_registry();
	return CU_get_error();
}
