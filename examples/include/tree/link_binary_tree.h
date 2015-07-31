/*
 * link_binary_tree.h
 *
 *  Created on: 2009-8-28
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_TREE_LINK_BINARY_TREE_H_
#define DATA_STRUCTURE_IN_C_TREE_LINK_BINARY_TREE_H_

#define ElementType 		int
#define BINARY_TREE_TYPE	LinkBinaryTree
#define BINARY_TREE_NODE	LinkBinaryTreeNode

#include "include/common.h"
#include "include/tree/binary_tree_position.h"

typedef struct LinkBinaryTreeNode {
	ElementType value;
	struct LinkBinaryTreeNode *left_child;
	struct LinkBinaryTreeNode *right_child;
} LinkBinaryTreeNode, *LinkBinaryTree;

int get_number(char* string, int start_index, int end_index);

#endif /* DATA_STRUCTURE_IN_C_TREE_LINK_BINARY_TREE_H_ */
