/*
 * thread_bianry_tree.c
 *
 *  Created on: 2009-9-2
 *      Author: yuandong
 */

#include <stdlib.h>
#include <stdio.h>

#include "include/common.h"
#include "include/tree/thread_binary_tree.h"
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

	if ((*tree) -> left != NULL && (*tree) -> left_tag == Child) {
		Destory(&((*tree) -> left));
	}
	if ((*tree) -> right != NULL && (*tree) -> right_tag == Child) {
		Destory(&((*tree) -> right));
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
		(*tree) -> left = NULL;
		(*tree) -> left_tag = Thread;
		(*tree) -> right_tag = Thread;

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
			node -> left = NULL;
			node -> right = NULL;
			node -> left_tag = Thread;
			node -> right_tag = Thread;

			if (current_level_node_index % 2 == 0) {
				last_level_node[last_level_node_index] -> left = node;
				last_level_node[last_level_node_index] -> left_tag = Child;
			} else {
				last_level_node[last_level_node_index] -> right = node;
				last_level_node[last_level_node_index] -> right_tag = Child;
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

	int left_child_depth = tree -> left_tag == Child ? Depth(tree -> left) : 0;
	int right_child_depth = tree -> right_tag == Child ? Depth(tree -> right)
			: 0;

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

	return order % 2 == 1 ? parent -> left : parent -> right;
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

	if (tree -> left == node && tree -> left_tag == Child)
		return tree;
	if (tree -> right == node && tree -> right_tag == Child)
		return tree;
	BINARY_TREE_NODE *parent = NULL;
	if (tree -> left_tag == Child) {
		parent = Parent(tree -> left, node);
		if (parent != NULL)
			return parent;
	}

	if (tree -> right_tag == Child) {
		parent = Parent(tree -> right, node);
		if (parent != NULL)
			return parent;
	}

	return NULL;
}

BINARY_TREE_NODE* LeftChild(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node) {
	return node -> left_tag == Child ? node -> left : NULL;
}

BINARY_TREE_NODE* RightChild(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node) {
	return node -> right_tag == Child ? node -> right : NULL;
}

BINARY_TREE_NODE* LeftSibling(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node) {
	BINARY_TREE_NODE *parent = Parent(tree, node);
	return parent == NULL || parent -> left_tag == Thread || node
			== parent -> left ? NULL : parent -> left;
}

BINARY_TREE_NODE* RightSibling(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node) {
	BINARY_TREE_NODE *parent = Parent(tree, node);
	return parent == NULL || parent -> right_tag == Thread || node
			== parent -> right ? NULL : parent -> right;
}

Status InsertChild(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* parent,
		enum LeftOrRight left_or_right, ElementType value) {

	if (left_or_right == Left && parent -> left && parent -> left_tag == Child)
		return ERROR;
	if (left_or_right == Right && parent -> right && parent -> right_tag
			== Child)
		return ERROR;
	BINARY_TREE_NODE *node = (BINARY_TREE_NODE*) malloc(
			sizeof(BINARY_TREE_NODE));
	node -> left = NULL;
	node -> right = NULL;
	node -> value = value;

	if (left_or_right == Left) {
		parent -> left = node;
		parent -> left_tag = Child;
	} else {
		parent -> right = node;
		parent -> right_tag = Child;
	}

	return OK;
}

Status DeleteChild(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node,
		enum LeftOrRight left_or_right) {

	if (left_or_right == Left && tree -> left_tag == Child) {
		return Destory(&(node -> left));
	}
	if (left_or_right == Right && tree -> right_tag == Child) {
		return Destory(&(node -> right));
	}

	return OK;
}
BINARY_TREE_NODE *pre_order_root = NULL, *pre_order_pre_node = NULL;
void pre_order_threading(BINARY_TREE_TYPE tree) {
	if (tree == NULL)
		return;

	if (tree -> left_tag == Thread) {
		tree -> left = pre_order_pre_node;
	}
	if (pre_order_pre_node -> right_tag == Thread) {
		pre_order_pre_node -> right = tree;
	}
	pre_order_pre_node = tree;

	if (tree -> left_tag == Child)
		pre_order_threading(tree -> left);
	if (tree -> right_tag == Child)
		pre_order_threading(tree -> right);
}
Status PreOrderTraverse(BINARY_TREE_TYPE tree, Status(*visit)(ElementType*)) {
	//build thread
	if (pre_order_root != NULL)
		free(pre_order_root);

	pre_order_root = (BINARY_TREE_NODE*) malloc(sizeof(BINARY_TREE_NODE));
	pre_order_root -> left_tag = Child;
	pre_order_root -> right_tag = Thread;
	pre_order_root -> right = pre_order_root;

	if (tree == NULL) {
		pre_order_root -> left = pre_order_root;
	} else {
		pre_order_root -> left = tree;
		pre_order_pre_node = pre_order_root;

		pre_order_threading(tree);

		pre_order_pre_node -> right = pre_order_root;
		pre_order_pre_node -> right_tag = Thread;
		pre_order_root -> right = pre_order_pre_node;
	}
	//traverse
	BINARY_TREE_NODE *node = pre_order_root -> left;
	while (node != pre_order_root) {
		visit(&(node -> value));

		while (node -> right_tag == Thread && node -> right != pre_order_root) {
			node = node -> right;
			visit(&(node -> value));
		}

		if (node -> left_tag == Child)
			node = node -> left;
		else
			node = node -> right;
	}

	return OK;

}
BINARY_TREE_NODE *in_order_root = NULL, *in_order_pre_node = NULL;
void in_order_threading(BINARY_TREE_TYPE tree) {
	if (tree == NULL)
		return;

	if (tree -> left_tag == Child)
		in_order_threading(tree -> left);

	if (tree -> left_tag == Thread) {
		tree -> left = in_order_pre_node;
	}
	if (in_order_pre_node -> right_tag == Thread) {
		in_order_pre_node -> right = tree;
	}
	in_order_pre_node = tree;

	if (tree -> right_tag == Child)
		in_order_threading(tree -> right);
}
Status InOrderTraverse(BINARY_TREE_TYPE tree, Status(*visit)(ElementType*)) {
	//build thread
	if (in_order_root != NULL)
		free(in_order_root);

	in_order_root = (BINARY_TREE_NODE*) malloc(sizeof(BINARY_TREE_NODE));
	in_order_root -> left_tag = Child;
	in_order_root -> right_tag = Thread;
	in_order_root -> right = in_order_root;

	if (tree == NULL) {
		in_order_root -> left = in_order_root;
	} else {
		in_order_root -> left = tree;
		in_order_pre_node = in_order_root;

		in_order_threading(tree);

		in_order_pre_node -> right = in_order_root;
		in_order_pre_node -> right_tag = Thread;
		in_order_root -> right = in_order_pre_node;
	}
	//traverse
	BINARY_TREE_NODE *node = in_order_root -> left;
	while (node != in_order_root) {
		while (node -> left_tag == Child) {
			node = node -> left;
		}

		visit(&(node -> value));

		while (node -> right_tag == Thread && node -> right != in_order_root) {
			node = node -> right;
			visit(&(node -> value));
		}
		node = node -> right;
	}

	return OK;
}
Status PostOrderTraverse(BINARY_TREE_TYPE tree, Status(*visit)(ElementType*)) {

	//后序遍历的线索二叉树基本上没有什么意义
	if (tree == NULL)
		return OK;

	if (tree -> left_tag == Child)
		PostOrderTraverse(tree -> left, visit);

	if (tree -> right_tag == Child)
		PostOrderTraverse(tree -> right, visit);

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

		if (node[i] -> left_tag == Child && node[i] -> left != NULL) {
			child_node[child_node_index++] = node[i] -> left;
		}

		if (node[i] -> right_tag == Child && node[i] -> right != NULL) {
			child_node[child_node_index++] = node[i] -> right;

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
