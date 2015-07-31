/*
 * link_bianry_tree.c
 *
 *  Created on: 2009-8-28
 *      Author: yuandong
 */

#include <stdlib.h>
#include <stdio.h>

#include "include/common.h"
#include "include/tree/link_binary_tree.h"
#include "include/tree/binary_tree.h"

int get_number(char* string, int start_index, int end_index) {
	int value = 0;
	int i = start_index;
	for (i = start_index; i <= end_index; i++) {
		value = value * 10 + string[i] - '0';
	}
	return value;
}

Status Initial(BINARY_TREE_TYPE* tree) {
	*tree = NULL;
	return OK;
}

Status Destory(BINARY_TREE_TYPE* tree) {
	if (*tree == NULL)
		return OK;

	if ((*tree) -> left_child != NULL) {
		Destory(&((*tree) -> left_child));
	}
	if ((*tree) -> right_child != NULL) {
		Destory(&((*tree) -> right_child));
	}

	free(*tree);
	*tree = NULL;
	return OK;
}

Status Create(BINARY_TREE_TYPE* tree, char* definition) {
	*tree = NULL;
	if (definition == NULL)
		return OK;

	BINARY_TREE_NODE **last_level_node = NULL;
	BINARY_TREE_NODE **current_level_node = NULL;
	int i = 0, last_level_size = 1, last_level_node_index = 0,
			current_level_node_index = 0;

	//Root
	last_level_node = (BINARY_TREE_NODE**) malloc(sizeof(BINARY_TREE_NODE*));
	current_level_node = (BINARY_TREE_NODE**) malloc(sizeof(BINARY_TREE_NODE*)
			* 2);

	int j = 0;
	for (j = 0; j < 2; j++) {
		current_level_node[j] = NULL;
	}
	if (definition[i] >= '0' && definition[i] <= '9') {
		int number_start = i, number_end = i + 1;
		while (definition[number_end] != ',' && definition[number_end] != ' '
				&& definition[number_end] != '\0')
			number_end++;
		int value = get_number(definition, number_start, number_end - 1);

		*tree = (BINARY_TREE_NODE*) malloc(sizeof(BINARY_TREE_NODE));
		(*tree) -> value = value;
		(*tree) -> left_child = NULL;
		(*tree) -> right_child = NULL;

		last_level_node[0] = *tree;

		//next
		while (definition[number_end] != ',' && definition[number_end] != '\0')
			number_end++;
		i = number_end;
		if (definition[i] != '\0')
			i++;
	}

	//Children
	int has_new_node = 0;
	while (definition[i] != '\0') {

		has_new_node = 0;

		if (definition[i] == ',') {
			current_level_node_index++;
			has_new_node = 1;
		}

		if (definition[i] >= '0' && definition[i] <= '9') {
			int number_start = i, number_end = i + 1;
			while (definition[number_end] != ',' && definition[number_end]
					!= ' ' && definition[number_end] != '\0')
				number_end++;
			int value = get_number(definition, number_start, number_end - 1);

			//create
			BINARY_TREE_NODE *node = (BINARY_TREE_NODE*) malloc(
					sizeof(BINARY_TREE_NODE));
			node -> value = value;
			node -> left_child = NULL;
			node -> right_child = NULL;

			if (current_level_node_index % 2 == 0) {
				last_level_node[last_level_node_index] -> left_child = node;
			} else {
				last_level_node[last_level_node_index] -> right_child = node;
			}

			//next
			current_level_node[current_level_node_index] = node;
			current_level_node_index++;
			has_new_node = 1;
			while (definition[number_end] != ',' && definition[number_end]
					!= '\0')
				number_end++;
			i = number_end;
		}

		if (has_new_node && current_level_node_index % 2 == 0) {
			last_level_node_index++;

			if (last_level_node_index >= last_level_size) {
				free(last_level_node);
				last_level_node = current_level_node;
				last_level_size *= 2;

				current_level_node = (BINARY_TREE_NODE**) malloc(
						sizeof(BINARY_TREE_NODE*) * last_level_size * 2);

				int j = 0;
				for (j = 0; j < last_level_size * 2; j++) {
					current_level_node[j] = NULL;
				}

				current_level_node_index = 0;
				last_level_node_index = 0;
			}
		}

		if (definition[i] != '\0')
			i++;
	}

	free(last_level_node);
	free(current_level_node);
	return OK;
}

Status Clear(BINARY_TREE_TYPE* tree) {
	return Destory(tree);
}

Status Empty(BINARY_TREE_TYPE tree) {
	return tree == NULL;
}

Status Depth(BINARY_TREE_TYPE tree) {
	if (tree == NULL)
		return 0;

	int left_child_depth = Depth(tree -> left_child);
	int right_child_depth = Depth(tree -> right_child);

	return left_child_depth > right_child_depth ? left_child_depth + 1
			: right_child_depth + 1;
}

BINARY_TREE_NODE* Root(BINARY_TREE_TYPE tree) {
	return tree;
}

BINARY_TREE_NODE* getNodeByPosition(BINARY_TREE_TYPE tree, int level, int order) {
	if (level == 1)
		return tree;

	BINARY_TREE_NODE* parent = getNodeByPosition(tree, level - 1, (order + 1)
			/ 2);
	if (parent == NULL)
		return NULL;

	return order % 2 == 1 ? parent -> left_child : parent -> right_child;
}

ElementType Value(BINARY_TREE_TYPE tree, Position position) {
	BINARY_TREE_NODE* node = getNodeByPosition(tree, position.level,
			position.order);
	return node ? node -> value : 0;
}

Status Assign(BINARY_TREE_TYPE* tree, Position position, ElementType value) {
	BINARY_TREE_NODE* node = getNodeByPosition(*tree, position.level,
			position.order);

	if (node == NULL)
		return ERROR;

	node -> value = value;
	return OK;
}

BINARY_TREE_NODE* Parent(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node) {
	if (tree == NULL || tree == node)
		return NULL;

	if (tree -> left_child == node || tree -> right_child == node)
		return tree;

	BINARY_TREE_NODE *parent = NULL;

	parent = Parent(tree -> left_child, node);
	if (parent != NULL)
		return parent;

	parent = Parent(tree -> right_child, node);
	return parent;
}

BINARY_TREE_NODE* LeftChild(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node) {
	return node -> left_child;
}

BINARY_TREE_NODE* RightChild(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node) {
	return node -> right_child;
}

BINARY_TREE_NODE* LeftSibling(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node) {
	BINARY_TREE_NODE *parent = Parent(tree, node);
	return parent == NULL || node == parent -> left_child ? NULL
			: parent -> left_child;
}

BINARY_TREE_NODE* RightSibling(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node) {
	BINARY_TREE_NODE *parent = Parent(tree, node);
	return parent == NULL || node == parent -> right_child ? NULL
			: parent -> right_child;
}

Status InsertChild(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* parent,
		enum LeftOrRight left_or_right, ElementType value) {

	if (left_or_right == Left && parent -> left_child)
		return ERROR;
	if (left_or_right == Right && parent -> right_child)
		return ERROR;

	BINARY_TREE_NODE *node = (BINARY_TREE_NODE*) malloc(
			sizeof(BINARY_TREE_NODE));
	node -> left_child = NULL;
	node -> right_child = NULL;
	node -> value = value;

	if (left_or_right == Left)
		parent -> left_child = node;
	else
		parent -> right_child = node;

	return OK;
}

Status DeleteChild(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node,
		enum LeftOrRight left_or_right) {

	return left_or_right == Left ? Destory(&(node -> left_child)) : Destory(
			&(node -> right_child));
}

Status PreOrderTraverse(BINARY_TREE_TYPE tree, Status(*visit)(ElementType*)) {
	if (tree == NULL)
		return OK;

	visit(&(tree -> value));
	PreOrderTraverse(tree -> left_child, visit);
	PreOrderTraverse(tree -> right_child, visit);

	return OK;
}

Status InOrderTraverse(BINARY_TREE_TYPE tree, Status(*visit)(ElementType*)) {
	if (tree == NULL)
		return OK;

	InOrderTraverse(tree -> left_child, visit);
	visit(&(tree -> value));
	InOrderTraverse(tree -> right_child, visit);

	return OK;
}

Status PostOrderTraverse(BINARY_TREE_TYPE tree, Status(*visit)(ElementType*)) {
	if (tree == NULL)
		return OK;

	PostOrderTraverse(tree -> left_child, visit);
	PostOrderTraverse(tree -> right_child, visit);
	visit(&(tree -> value));

	return OK;
}
void LevelOrderTraverseAction(BINARY_TREE_NODE **node,
		int size,
		Status(*visit)(ElementType*)) {
	BINARY_TREE_NODE **child_node = (BINARY_TREE_NODE**) malloc(
			sizeof(BINARY_TREE_NODE*) * size * 2);

	int i = 0, child_node_index = 0;
	for (i = 0; i < size * 2; i++) {
		child_node[i] = NULL;
	}

	for (i = 0; i < size; i++) {

		if (node[i] == NULL) {
			continue;
		}

		if (node[i] -> left_child != NULL) {
			child_node[child_node_index++] = node[i] -> left_child;
		}

		if (node[i] -> right_child != NULL) {
			child_node[child_node_index++] = node[i] -> right_child;

		}

		visit(&(node[i] -> value));
	}

	if (child_node_index > 0) {
		LevelOrderTraverseAction(child_node, child_node_index, visit);
	}
	free(child_node);
}
Status LevelOrderTraverse(BINARY_TREE_TYPE tree, Status(*visit)(ElementType*)) {

	if (tree == NULL)
		return OK;

	BINARY_TREE_NODE **node = (BINARY_TREE_NODE**) malloc(
			sizeof(BINARY_TREE_NODE*));
	*node = tree;

	LevelOrderTraverseAction(node, 1, visit);

	free(node);

	return OK;

}
