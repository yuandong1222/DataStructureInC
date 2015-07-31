/*
 * link_list.h
 *
 *  Created on: 2009-4-10
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_LIST_LINK_LIST_H_
#define DATA_STRUCTURE_IN_C_LIST_LINK_LIST_H_

#define ElementType int
#define LIST_TYPE LinkList

#include "include/common.h"

//线性表的单链表存储结构
typedef struct LinkListNode {
	ElementType data;
	struct LinkListNode *next;
} LinkListNode, *LinkList;

#endif /* DATA_STRUCTURE_IN_C_LIST_LINK_LIST_H_ */
