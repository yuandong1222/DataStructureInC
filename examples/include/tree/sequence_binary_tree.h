/*
 * sequence_binary_tree.h
 *
 *  Created on: 2009-8-23
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_TREE_SEQUENCE_BINARY_TREE_H_
#define DATA_STRUCTURE_IN_C_TREE_SEQUENCE_BINARY_TREE_H_

#define	MAX_NODE			100
#define ElementType 		int
#define BINARY_TREE_TYPE	SequenceBinaryTree
#define BINARY_TREE_NODE	int
#define	Nil					-1

#include "include/common.h"
#include "include/tree/binary_tree_position.h"

typedef ElementType *SequenceBinaryTree;

int get_number(char* string, int start_index, int end_index);

#endif /* DATA_STRUCTURE_IN_C_TREE_SEQUENCE_BINARY_TREE_H_ */
