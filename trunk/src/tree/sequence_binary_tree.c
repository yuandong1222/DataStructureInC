/*
 * sequence_bianry_tree.c
 *
 *  Created on: 2009-8-23
 *      Author: yuandong
 */

#include <stdlib.h>
#include <stdio.h>

#include "include/common.h"
#include "include/tree/sequence_binary_tree.h"
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

ElementType Value(BINARY_TREE_TYPE tree, Position position) {
}

Status Assign(BINARY_TREE_TYPE* tree, Position position, ElementType value) {
}

BINARY_TREE_NODE* Parent(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node) {
}

BINARY_TREE_NODE* getChildPointer(BINARY_TREE_TYPE tree,
		BINARY_TREE_NODE* node, int left_or_right) {
}
BINARY_TREE_NODE* getChild(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node,
		int left_or_right) {
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

void PreOrderTraverseAction(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* parent,
		Status(*visit)(ElementType*)) {
}

Status PreOrderTraverse(BINARY_TREE_TYPE tree, Status(*visit)(ElementType*)) {
}

void InOrderTraverseAction(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* parent,
		Status(*visit)(ElementType*)) {
}
Status InOrderTraverse(BINARY_TREE_TYPE tree, Status(*visit)(ElementType*)) {
}

void PostOrderTraverseAction(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* parent,
		Status(*visit)(ElementType*)) {
}
Status PostOrderTraverse(BINARY_TREE_TYPE tree, Status(*visit)(ElementType*)) {
}

Status LevelOrderTraverse(BINARY_TREE_TYPE tree, Status(*visit)(ElementType*)) {
}
