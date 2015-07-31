/*
 * parent_tree.c
 *
 *  Created on: 2009-9-3
 *      Author: yuandong
 */

#include <stdlib.h>
#include <stdio.h>

#include "include/common.h"
#include "include/tree/parent_tree.h"

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
	*tree = (ParentTree) malloc(sizeof(ParentTreeHead));
	(*tree) -> length = 0;

	int i = 0;
	for (i = 0; i < MAX_NODE; i++) {
		((*tree) -> nodes)[i].parent = -1;
	}

	return OK;
}

Status Destory(TREE_TYPE* tree) {
	free(*tree);
	*tree = NULL;
	return OK;
}

Status Create(TREE_TYPE* tree, char* definition) {
	if (definition == "")
		return OK;

	int length, *array;
	build_definition_array(definition, &length, &array);

	int i = 0, index = 1, order = 1, j = 0;
	while (i < length) {
		if (array[i + 1] == -1) {
			((*tree) -> nodes)[0].value = array[i];
			((*tree) -> nodes)[0].parent = array[i + 1];
			((*tree) -> nodes)[0].order = 1;
		} else {
			((*tree) -> nodes)[index].value = array[i];
			((*tree) -> nodes)[index].parent = array[i + 1];

			order = 1;
			for (j = 0; j < index; j++) {
				if (((*tree) -> nodes)[j].parent == array[i + 1]) {
					order++;
				}
			}

			((*tree) -> nodes)[index].order = order;
			index++;
		}
		i += 2;
	}
	(*tree) -> length = length / 2;

	free(array);
	array = NULL;

	return OK;
}

Status Clear(TREE_TYPE* tree) {
	(*tree) -> length = 0;
	return OK;
}

Status Empty(TREE_TYPE tree) {
	return tree -> length == 0;
}

int Depth(TREE_TYPE tree) {

	if (tree -> length == 0)
		return 0;

	int i = 0, depth = 0, node_depth = 1;
	for (i = 0; i < MAX_NODE; i++) {
		if (i != 0 && (tree -> nodes)[i].parent == -1)
			continue;

		node_depth = 1;

		int current_node_parent = (tree -> nodes)[i].parent;
		while (current_node_parent != -1) {
			current_node_parent = (tree -> nodes)[current_node_parent].parent;
			node_depth++;
		}

		if (node_depth > depth)
			depth = node_depth;
	}
	return depth;
}

TREE_NODE* Root(TREE_TYPE tree) {
	return tree -> length == 0 ? NULL : tree -> nodes;
}

ElementType Value(TREE_TYPE tree, TREE_NODE *node) {
	return node == NULL ? 0 : node -> value;
}

Status Assign(TREE_TYPE* tree, TREE_NODE *node, ElementType value) {
	node -> value = value;
	return OK;
}

TREE_NODE* Parent(TREE_TYPE tree, TREE_NODE* node) {
	return node -> parent == -1 ? NULL : tree -> nodes + node -> parent;
}

TREE_NODE* LeftChild(TREE_TYPE tree, TREE_NODE* node) {
	int i = 0;
	for (i = 0; i < MAX_NODE; i++) {
		if (i != 0 && (tree -> nodes)[i].parent == -1)
			continue;

		if ((tree -> nodes)[i].parent == node - tree -> nodes
				&& (tree -> nodes)[i].order == 1)
			return tree -> nodes + i;
	}
	return NULL;
}

TREE_NODE* RightSibling(TREE_TYPE tree, TREE_NODE* node) {
	int i = 0;
	for (i = 0; i < MAX_NODE; i++) {
		if (i != 0 && (tree -> nodes)[i].parent == -1)
			continue;

		if ((tree -> nodes)[i].parent == node -> parent
				&& (tree -> nodes)[i].order == node -> order + 1)
			return tree -> nodes + i;
	}
	return NULL;
}

Status InsertChild(TREE_TYPE tree, TREE_NODE* parent, int position,
		ElementType value) {
	if (tree -> length == 0) {
		(tree -> nodes)[0].parent = -1;
		(tree -> nodes)[0].order = 1;
		(tree -> nodes)[0].value = value;
		tree -> length++;
		return OK;
	}

	int i = 0, node_count = 1;
	for (i = 1; i < MAX_NODE; i++) {
		if ((tree -> nodes)[i].parent == -1) {
			continue;
		}

		if ((tree -> nodes)[i].parent == parent - tree -> nodes
				&& (tree -> nodes)[i].order >= position) {
			(tree -> nodes)[i].order++;
		}
		node_count++;
		if (node_count == tree -> length)
			break;
	}

	int index_to_insert = 1;
	while ((tree -> nodes)[index_to_insert].parent != -1) {
		index_to_insert++;
	}

	(tree -> nodes)[index_to_insert].parent = parent - tree -> nodes;
	(tree -> nodes)[index_to_insert].value = value;
	(tree -> nodes)[index_to_insert].order = position;

	tree -> length++;

	return OK;
}

Status DeleteChild(TREE_TYPE tree, TREE_NODE* node, int position) {

	ParentTreeNode *child = NULL;
	int i = 0, child_index = 0;

	for (i = 0; i < MAX_NODE; i++) {
		if (i != 0 && (tree -> nodes)[i].parent == -1)
			continue;

		if ((tree -> nodes)[i].parent == node - tree -> nodes
				&& (tree -> nodes)[i].order == position) {
			child = tree -> nodes + i;
			child_index = i;
			break;
		}
	}
	if (child == NULL)
		return OK;

	for (i = 0; i < MAX_NODE; i++) {
		if (i != 0 && (tree -> nodes)[i].parent == -1)
			continue;

		if ((tree -> nodes)[i].parent == child -> parent
				&& (tree -> nodes)[i].order > child -> order)
			(tree -> nodes)[i].order--;
	}

	for (i = 0; i < MAX_NODE; i++) {
		if (i != 0 && (tree -> nodes)[i].parent == -1)
			continue;

		int current_node_parent = (tree -> nodes)[i].parent;
		while (current_node_parent != -1) {
			if (current_node_parent == child_index) {
				(tree -> nodes)[i].order = -1;
				break;
			}
			current_node_parent = (tree -> nodes)[current_node_parent].parent;
		}
	}

	child -> order = -1;
	for (i = 0; i < MAX_NODE; i++) {
		if (i != 0 && (tree -> nodes)[i].parent == -1)
			continue;

		if ((tree -> nodes)[i].order == -1) {
			(tree -> nodes)[i].parent = -1;
			(tree -> length)--;
		}
	}
	return OK;
}

Status Traverse(TREE_TYPE tree, Status(*visit)(ElementType*)) {
	int i = 0;
	for (i = 0; i < MAX_NODE; i++) {
		if (i != 0 && (tree -> nodes)[i].parent == -1)
			continue;

		visit(&((tree -> nodes)[i].value));
	}
	return OK;
}
