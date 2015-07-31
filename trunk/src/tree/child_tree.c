/*
 * child_tree.c
 *
 *  Created on: 2009-9-14
 *      Author: yuandong
 */

#include <stdlib.h>
#include <stdio.h>

#include "include/common.h"
#include "include/tree/child_tree.h"

Status Initial(TREE_TYPE* tree) {
}

Status Create(TREE_TYPE* tree, char* definition) {
}

Status Clear(TREE_TYPE* tree) {
}

Status Destory(TREE_TYPE* tree) {
}

Status Empty(TREE_TYPE tree) {
}

int Depth(TREE_TYPE tree) {
}

TREE_NODE* Root(TREE_TYPE tree) {
}

ElementType Value(TREE_TYPE tree, TREE_NODE *node) {
}

Status Assign(TREE_TYPE* tree, TREE_NODE *node, ElementType value) {
}

TREE_NODE* Parent(TREE_TYPE tree, TREE_NODE* node) {
}

TREE_NODE* LeftChild(TREE_TYPE tree, TREE_NODE* node) {
}

TREE_NODE* RightSibling(TREE_TYPE tree, TREE_NODE* node) {
}

Status InsertChild(TREE_TYPE tree, TREE_NODE* parent, int position,
		ElementType value) {
}

Status DeleteChild(TREE_TYPE tree, TREE_NODE* node, int position) {
}

Status Traverse(TREE_TYPE tree, Status(*visit)(ElementType*)) {
}
