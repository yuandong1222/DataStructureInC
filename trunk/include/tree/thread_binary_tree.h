/*
 * thread_binary_tree.h
 *
 *  Created on: 2009-9-2
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_TREE_THREAD_BINARY_TREE_H_
#define DATA_STRUCTURE_IN_C_TREE_THREAD_BINARY_TREE_H_

#define ElementType 		int
#define BINARY_TREE_TYPE	ThreadBinaryTree
#define BINARY_TREE_NODE	ThreadBinaryTreeNode

#include "include/common.h"
#include "include/tree/binary_tree_position.h"

enum ChildTag {
	Child, Thread
};

typedef struct ThreadBinaryTreeNode {
	ElementType value;

	struct ThreadBinaryTreeNode *left;
	enum ChildTag left_tag;

	struct ThreadBinaryTreeNode *right;
	enum ChildTag right_tag;
} ThreadBinaryTreeNode, *ThreadBinaryTree;

int get_number(char* string, int start_index, int end_index);

#endif /* DATA_STRUCTURE_IN_C_TREE_THREAD_BINARY_TREE_H_ */
