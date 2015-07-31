/*
 * child_tree.h
 *
 *  Created on: 2009-9-14
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_TREE_CHILD_TREE_H_
#define DATA_STRUCTURE_IN_C_TREE_CHILD_TREE_H_

#define ElementType	int
#define TREE_TYPE	ChildTree
#define TREE_NODE	ChildTreeNode
#define MAX_NODE	100

#include "include/common.h"

typedef struct ChildIndexNode {
	int child;
	struct ChildIndexNode *next;
} ChildIndexNode;

typedef struct TreeNode {
	ElementType value;
	int parent;
	int order;
	ChildIndexNode *child_list;
} ChildTreeNode;

typedef struct ChildTree {
	ChildTreeNode nodes[MAX_NODE];
	int length;
} ChildTreeHead, *ChildTree;

void build_definition_array(char* definition, int *length, int **array);

#endif /* DATA_STRUCTURE_IN_C_TREE_CHILD_TREE_H_ */
