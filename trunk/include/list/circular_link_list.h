/*
 * circular_link_list.h
 *
 *  Created on: 2009-4-10
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_CIRCULAR_LIST_LINK_LIST_H_
#define DATA_STRUCTURE_IN_C_CIRCULAR_LIST_LINK_LIST_H_

#define ElementType int
#define LIST_TYPE CircularLinkList

#include "include/common.h"

//���Ա��ѭ������洢�ṹ
typedef struct CircularLinkListNode {
	ElementType data;
	struct CircularLinkListNode *next;
} CircularLinkListNode, *CircularLinkList;

#endif /* DATA_STRUCTURE_IN_C_CIRCULAR_LIST_LINK_LIST_H_ */
