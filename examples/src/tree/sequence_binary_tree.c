/*
 * sequence_bianry_tree.c
 *
 *  Created on: 2009-8-23
 *      Author: yuandong
 */

#include <stdlib.h>
#include <stdio.h>

#include "include/common.h"
#include "include/tree/sequence_binary_tree.h"
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
	*tree = (ElementType*) malloc(sizeof(ElementType) * MAX_NODE);
	return Clear(tree);
}

Status Destory(BINARY_TREE_TYPE* tree) {
	free(*tree);
	*tree = NULL;
	return OK;
}

Status Create(BINARY_TREE_TYPE* tree, char* definition) {

	int i = 0, node_index = 0;
	while (definition[i] != '\0') {

		if (definition[i] == ',') {
			(*tree)[node_index] = Nil;
			node_index++;
		}

		if (definition[i] >= '0' && definition[i] <= '9') {
			int number_start = i, number_end = i + 1;
			while (definition[number_end] != ',' && definition[number_end]
					!= ' ' && definition[number_end] != '\0')
				number_end++;
			int value = get_number(definition, number_start, number_end - 1);

			//еп╣х
			(*tree)[node_index] = value;

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

	return OK;
}

Status Clear(BINARY_TREE_TYPE* tree) {
	int i = 0;
	for (i = 0; i < MAX_NODE; i++) {
		(*tree)[i] = Nil;
	}
	return OK;
}

Status Empty(BINARY_TREE_TYPE tree) {
	return *tree == Nil;
}

Status Depth(BINARY_TREE_TYPE tree) {
	if (Empty(tree))
		return 0;

	int n = MAX_NODE - 1;
	while (tree[n] == Nil)
		n--;

	int depth = 1, max_node = 1;
	while (max_node < n + 2) {
		max_node *= 2;
		depth++;
	}
	return depth - 1;
}

BINARY_TREE_NODE* Root(BINARY_TREE_TYPE tree) {
	return *tree == Nil ? NULL : tree;
}

ElementType Value(BINARY_TREE_TYPE tree, Position position) {
	if (position.level == 1) {
		return *tree == Nil ? 0 : *tree;
	}

	int offset = 1, i = 0, temp = 1;
	for (i = 0; i < position.level - 2; i++) {
		temp *= 2;
		offset += temp;
	}
	offset += position.order - 1;

	return tree[offset] == Nil ? 0 : tree[offset];
}

Status Assign(BINARY_TREE_TYPE* tree, Position position, ElementType value) {
	if (position.level == 1) {
		**tree = value;
		return OK;
	}

	int offset = 1, i = 0, temp = 1;
	for (i = 0; i < position.level - 2; i++) {
		temp *= 2;
		offset += temp;
	}
	offset += position.order - 1;

	if ((*tree)[offset] == Nil)
		return ERROR;

	(*tree)[offset] = value;
	return OK;
}

BINARY_TREE_NODE* Parent(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node) {

	if (node == tree)
		return NULL;

	int node_index = node - tree + 1;
	int parent_offset = node_index / 2;

	return tree + parent_offset - 1;
}

BINARY_TREE_NODE* getChildPointer(BINARY_TREE_TYPE tree,
		BINARY_TREE_NODE* node, int left_or_right) {

	int node_index = node - tree;
	return tree + node_index * 2 + 1 + left_or_right;
}
BINARY_TREE_NODE* getChild(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node,
		int left_or_right) {
	int* left_child_pointer = getChildPointer(tree, node, left_or_right);
	return *left_child_pointer == Nil ? NULL : left_child_pointer;
}

BINARY_TREE_NODE* LeftChild(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node) {
	return getChild(tree, node, 0);
}

BINARY_TREE_NODE* RightChild(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node) {
	return getChild(tree, node, 1);
}

BINARY_TREE_NODE* LeftSibling(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node) {
	if (tree == node)
		return NULL;

	int offset = node - tree;
	if (offset % 2 == 1)
		return NULL;

	int* left_sibling_pointer = node - 1;

	return *left_sibling_pointer == Nil ? NULL : left_sibling_pointer;
}

BINARY_TREE_NODE* RightSibling(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node) {
	int offset = node - tree;
	if (offset % 2 == 0)
		return NULL;

	int* right_sibling_pointer = node + 1;

	return *right_sibling_pointer == Nil ? NULL : right_sibling_pointer;
}

Status InsertChild(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* parent,
		enum LeftOrRight left_or_right, ElementType value) {
	int left_or_right_value = left_or_right == Left ? 0 : 1;
	int* child_pointer = getChildPointer(tree, parent, left_or_right_value);

	if (*child_pointer != Nil)
		return ERROR;

	*child_pointer = value;
	return OK;
}

Status DeleteChild(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node,
		enum LeftOrRight left_or_right) {

	int left_or_right_value = left_or_right == Left ? 0 : 1;
	int* child_pointer = getChildPointer(tree, node, left_or_right_value);

	if (*child_pointer == Nil)
		return OK;

	DeleteChild(tree, child_pointer, Left);
	DeleteChild(tree, child_pointer, Right);
	*child_pointer = Nil;

	return OK;
}

void PreOrderTraverseAction(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* parent,
		Status(*visit)(ElementType*)) {

	int* left_child_pointer = getChildPointer(tree, parent, 0);
	int* right_child_pointer = getChildPointer(tree, parent, 1);

	visit(parent);
	if (*left_child_pointer != Nil)
		PreOrderTraverseAction(tree, left_child_pointer, visit);
	if (*right_child_pointer != Nil)
		PreOrderTraverseAction(tree, right_child_pointer, visit);
}

Status PreOrderTraverse(BINARY_TREE_TYPE tree, Status(*visit)(ElementType*)) {
	PreOrderTraverseAction(tree, tree, visit);
	return OK;
}

void InOrderTraverseAction(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* parent,
		Status(*visit)(ElementType*)) {

	int* left_child_pointer = getChildPointer(tree, parent, 0);
	int* right_child_pointer = getChildPointer(tree, parent, 1);

	if (*left_child_pointer != Nil)
		InOrderTraverseAction(tree, left_child_pointer, visit);

	visit(parent);

	if (*right_child_pointer != Nil)
		InOrderTraverseAction(tree, right_child_pointer, visit);
}
Status InOrderTraverse(BINARY_TREE_TYPE tree, Status(*visit)(ElementType*)) {
	InOrderTraverseAction(tree, tree, visit);
	return OK;
}

void PostOrderTraverseAction(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* parent,
		Status(*visit)(ElementType*)) {

	int* left_child_pointer = getChildPointer(tree, parent, 0);
	int* right_child_pointer = getChildPointer(tree, parent, 1);

	if (*left_child_pointer != Nil)
		PostOrderTraverseAction(tree, left_child_pointer, visit);
	if (*right_child_pointer != Nil)
		PostOrderTraverseAction(tree, right_child_pointer, visit);

	visit(parent);
}
Status PostOrderTraverse(BINARY_TREE_TYPE tree, Status(*visit)(ElementType*)) {
	PostOrderTraverseAction(tree, tree, visit);
	return OK;
}

Status LevelOrderTraverse(BINARY_TREE_TYPE tree, Status(*visit)(ElementType*)) {
	int i = 0, length = MAX_NODE - 1;
	while (tree[length] == Nil)
		length--;
	for (i = 0; i <= length; i++)
		if (tree[i] != Nil)
			visit(tree + i);
	return OK;
}
