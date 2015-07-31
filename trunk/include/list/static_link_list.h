/*
 * static_link_lis.h
 *
 *  Created on: 2009-4-26
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_LIST_STATIC_LINK_LIST_H_
#define DATA_STRUCTURE_IN_C_LIST_STATIC_LINK_LIST_H_

#include "include/common.h"

#define ElementType int
#define LIST_TYPE StaticLinkList

#define MAXSIZE	1000

//线性表的静态连接表存储
typedef struct StaticLinkListNode {
	ElementType data;
	int cursor;
	BOOLEAN isEmpty;
} StaticLinkListNode, *StaticLinkList;

#endif /* DATA_STRUCTURE_IN_C_LIST_STATIC_LINK_LIST_H_ */
