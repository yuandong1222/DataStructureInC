/*
 * link_bianry_tree.c
 *
 *  Created on: 2009-8-28
 *      Author: yuandong
 */

#include <stdlib.h>
#include <stdio.h>

#include "include/common.h"
#include "include/tree/link_binary_tree.h"
#include "include/tree/binary_tree.h"

Status Initial(BINARY_TREE_TYPE* tree) {
}

Status Destory(BINARY_TREE_TYPE* tree) {
}

Status Create(BINARY_TREE_TYPE* tree, char* definition) {
}

Status Clear(BINARY_TREE_TYPE* tree) {
}

Status Empty(BINARY_TREE_TYPE tree) {
}

Status Depth(BINARY_TREE_TYPE tree) {
}

BINARY_TREE_NODE* Root(BINARY_TREE_TYPE tree) {
}

BINARY_TREE_NODE* getNodeByPosition(BINARY_TREE_TYPE tree, int level, int order) {
}

ElementType Value(BINARY_TREE_TYPE tree, Position position) {
}

Status Assign(BINARY_TREE_TYPE* tree, Position position, ElementType value) {
}

BINARY_TREE_NODE* Parent(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node) {
}

BINARY_TREE_NODE* LeftChild(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node) {
}

BINARY_TREE_NODE* RightChild(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node) {
}

BINARY_TREE_NODE* LeftSibling(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node) {
}

BINARY_TREE_NODE* RightSibling(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node) {
}

Status InsertChild(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* parent,
		enum LeftOrRight left_or_right, ElementType value) {
}

Status DeleteChild(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node,
		enum LeftOrRight left_or_right) {
}

Status PreOrderTraverse(BINARY_TREE_TYPE tree, Status(*visit)(ElementType*)) {
}

Status InOrderTraverse(BINARY_TREE_TYPE tree, Status(*visit)(ElementType*)) {
}

Status PostOrderTraverse(BINARY_TREE_TYPE tree, Status(*visit)(ElementType*)) {
}
void LevelOrderTraverseAction(BINARY_TREE_NODE **node,
		int size,
		Status(*visit)(ElementType*)) {
}
Status LevelOrderTraverse(BINARY_TREE_TYPE tree, Status(*visit)(ElementType*)) {
}
