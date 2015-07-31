/*
 * child_sibling_tree.c
 *
 *  Created on: 2009-9-16
 *      Author: yuandong
 */

#include <stdlib.h>
#include <stdio.h>

#include "include/common.h"
#include "include/tree/child_sibling_tree.h"

int get_number(char* string, int start_index, int end_index) {
	int value = 0;
	int i = string[start_index] == '-' ? start_index + 1 : start_index;
	for (i = i; i <= end_index; i++) {
		value = value * 10 + string[i] - '0';
	}
	return string[start_index] == '-' ? value * -1 : value;
}
void build_definition_array(char* definition, int *length, int **array) {
	int index = 0;
	*length = 0;
	while (definition[index] != '\0') {
		if (definition[index] == ';' || definition[index] == ',')
			(*length)++;
		index++;
	}

	*array = (int*) malloc(sizeof(int) * (*length));

	index = 0;
	int i = 0;
	while (definition[i] != '\0') {

		if ((definition[i] >= '0' && definition[i] <= '9') || definition[i]
				== '-') {
			int number_start = i, number_end = i + 1;
			while (definition[number_end] >= '0' && definition[number_end]
					<= '9')
				number_end++;
			int value = get_number(definition, number_start, number_end - 1);

			(*array)[index++] = value;
			i = number_end;
		}
		if (definition[i] != '\0')
			i++;
	}
}

Status Initial(TREE_TYPE* tree) {
	*tree = NULL;
	return OK;
}
TREE_NODE *get_node_by_value(TREE_TYPE tree, ElementType value) {
	if (tree == NULL)
		return NULL;
	if (tree -> value == value)
		return tree;

	ChildSiblingTreeNode *node;
	node = get_node_by_value(tree -> first_child, value);
	if (node != NULL)
		return node;

	node = get_node_by_value(tree -> next_sibling, value);
	if (node != NULL)
		return node;

	return NULL;
}
Status Create(TREE_TYPE* tree, char* definition) {

	if (definition == "" || definition == NULL) {
		return OK;
	}

	int length, *array;
	build_definition_array(definition, &length, &array);

	int i = 0;
	while (i < length) {

		if (array[i + 1] == -1) {
			(*tree) = (TREE_TYPE) malloc(sizeof(ChildSiblingTreeNode));
			(*tree) -> first_child = NULL;
			(*tree) -> next_sibling = NULL;
			(*tree) -> value = array[i];
			i += 2;
			continue;
		}

		int node_value = array[i];
		int parent_index = array[i + 1];
		int parent_value = array[parent_index * 2];
		int order = 1, j = 0;
		for (j = 0; j < i; j += 2) {
			if (array[j + 1] == parent_index)
				order++;
		}
		TREE_NODE *node = (TREE_NODE*) malloc(sizeof(TREE_NODE));
		node -> value = node_value;
		node -> first_child = NULL;
		node -> next_sibling = NULL;
		TREE_NODE *parent = get_node_by_value(*tree, parent_value);
		if (order == 1) {
			parent -> first_child = node;
		} else {
			j = 1;
			TREE_NODE *child = parent -> first_child;
			while (j < order - 1) {
				child = child -> next_sibling;
				j++;
			}
			node -> next_sibling = child -> next_sibling;
			child -> next_sibling = node;
		}

		i += 2;
	}

	free(array);
	array = NULL;

	return OK;
}

Status Destory(TREE_TYPE* tree) {
	if (*tree == NULL)
		return OK;

	Destory(&((*tree) -> first_child));
	Destory(&((*tree) -> next_sibling));

	free(*tree);
	*tree = NULL;

	return OK;
}

Status Clear(TREE_TYPE* tree) {
	return Destory(tree);
}

Status Empty(TREE_TYPE tree) {
	return tree == NULL;
}

int Depth(TREE_TYPE tree) {
	if (tree == NULL)
		return 0;

	int depth = 0, child_depth = 0;
	TREE_NODE *child = tree -> first_child;
	while (child) {
		child_depth = Depth(child);
		if (child_depth > depth)
			depth = child_depth;
		child = child -> next_sibling;
	}
	return depth + 1;
}

TREE_NODE* Root(TREE_TYPE tree) {
	return tree;
}

ElementType Value(TREE_TYPE tree, TREE_NODE *node) {
	return node == NULL ? 0 : node -> value;
}

Status Assign(TREE_TYPE* tree, TREE_NODE *node, ElementType value) {
	node -> value = value;
	return OK;
}
TREE_NODE* Parent(TREE_TYPE tree, TREE_NODE* node) {

	if (tree == NULL || tree == node)
		return NULL;
	TREE_NODE *child = tree -> first_child;
	while (child) {
		if (child == node)
			return tree;
		TREE_NODE *parent = Parent(child, node);
		if (parent != NULL)
			return parent;

		child = child -> next_sibling;
	}

	return NULL;
}

TREE_NODE* LeftChild(TREE_TYPE tree, TREE_NODE* node) {
	return node -> first_child;
}

TREE_NODE* RightSibling(TREE_TYPE tree, TREE_NODE* node) {
	return node -> next_sibling;
}

Status InsertChild(TREE_TYPE tree, TREE_NODE* parent, int position,
		ElementType value) {
	TREE_NODE *node = (TREE_NODE*) malloc(sizeof(TREE_NODE));
	node -> value = value;
	node -> first_child = NULL;
	node -> next_sibling = NULL;

	if (position == 1) {
		node -> next_sibling = parent -> first_child;
		parent -> first_child = node;
	} else {
		int order = 1;
		TREE_NODE *child = parent -> first_child;
		while (order < position - 1) {
			child = child -> next_sibling;
			order++;
		}
		node -> next_sibling = child -> next_sibling;
		child -> next_sibling = node;
	}
	return OK;
}

Status DeleteChild(TREE_TYPE tree, TREE_NODE* node, int position) {
	if (position == 1) {
		Destory(&(node -> first_child));
	} else {
		int order = 1;
		TREE_NODE *child = node -> first_child;
		while (order < position - 1) {
			child = child -> next_sibling;
			order++;
		}
		TREE_NODE *n = child -> next_sibling;
		child -> next_sibling = child -> next_sibling -> next_sibling;

		n -> next_sibling = NULL;
		Destory(&n);
	}
	return OK;
}

Status Traverse(TREE_TYPE tree, Status(*visit)(ElementType*)) {
	if (tree == NULL)
	return OK;

	visit(&(tree -> value));

	Traverse(tree -> first_child, visit);
	Traverse(tree -> next_sibling, visit);

	return OK;
}
