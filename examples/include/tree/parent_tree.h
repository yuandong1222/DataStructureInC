/*
 * parent_tree.h
 *
 *  Created on: 2009-9-3
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_TREE_PARENT_TREE_H_
#define DATA_STRUCTURE_IN_C_TREE_PARENT_TREE_H_

#define ElementType	int
#define TREE_TYPE	ParentTree
#define TREE_NODE	ParentTreeNode
#define MAX_NODE	100

#include "include/common.h"

typedef struct ParentTreeNode {
	ElementType value;
	int order;
	int parent;
} ParentTreeNode;

typedef struct ParentTreeHead {
	ParentTreeNode nodes[MAX_NODE];
	int length;
} ParentTreeHead, *ParentTree;

void build_definition_array(char* definition, int *length, int **array);

#endif /* DATA_STRUCTURE_IN_C_TREE_PARENT_TREE_H_ */
