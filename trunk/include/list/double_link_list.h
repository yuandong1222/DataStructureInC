/*
 * double_link_list.h
 *
 *  Created on: 2009-4-10
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_DOUBLE_LIST_LINK_LIST_H_
#define DATA_STRUCTURE_IN_C_DOUBLE_LIST_LINK_LIST_H_

#define ElementType int
#define LIST_TYPE DoubleLinkList

#include "include/common.h"

//线性表的双向链表存储结构
typedef struct DoubleLinkListNode {
	ElementType data;
	struct DoubleLinkListNode *next;
	struct DoubleLinkListNode *prior;
} DoubleLinkListNode, *DoubleLinkList;

#endif /* DATA_STRUCTURE_IN_C_LDOUBLE_IST_LINK_LIST_H_ */
