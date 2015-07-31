/*
 * child_sibling_tree.h
 *
 *  Created on: 2009-9-16
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_TREE_CHILD_SIBLING_TREE_H_
#define DATA_STRUCTURE_IN_C_TREE_CHILD_SIBLING_TREE_H_

#define ElementType	int
#define TREE_TYPE	ChildSiblingTree
#define TREE_NODE	ChildSiblingTreeNode

#include "include/common.h"

typedef struct ChildSiblingNode {
	ElementType value;
	struct ChildSiblingNode *first_child, *next_sibling;
} ChildSiblingTreeNode, *ChildSiblingTree;

void build_definition_array(char* definition, int *length, int **array);

#endif /* DATA_STRUCTURE_IN_C_TREE_CHILD_SIBLING_TREE_H_ */
