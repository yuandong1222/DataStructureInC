/*
 * string.h
 *
 *  Created on: 2009-7-15
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_STRING_WORD_INDEX_LIST_H_
#define DATA_STRUCTURE_IN_C_STRING_WORD_INDEX_LIST_H_

#include "include/common.h"

#define MAX_INDEX_WORD_COUNT 100

//定义字符串为堆存储
#define	String char*

//定义书号链表结点
typedef struct BookNumberListNode {
	int book_number;
	struct BookNumberListNode *next;

} BookNumberListNode, *BookNumberList;

//定义索引项
typedef struct {
	String word;
	BookNumberList book_number_list;
} WordIndexListItem;

//定义词索引表
typedef struct {
	int length;
	WordIndexListItem* items[MAX_INDEX_WORD_COUNT];
} WordIndexListHead, *WordIndexList;

//初始化
//构造词索引表
Status Initial(WordIndexList *list);

//销毁
//销毁词索引表，释放其所占用的内存
Status Destory(WordIndexList *list);

//索引
//根据关键字索引书的编号
//参数：
//	word_index_list:	存放索引的词索引表
//	word:				索引关键字
//	book_number:		书号
Status Index(WordIndexList list, int book_number, String word);

//查找
//根据关键字在给出的词索引表中查找书号
//查找结果将以int数组的形式给出，如果没有找到任何匹配的记录，返回NULL
//参数：
//	word_index_list:	要查询的词索引表
//	word:				查找的关键字
int* Search(WordIndexList list, String word);

#endif /* DATA_STRUCTURE_IN_C_STRING_WORD_INDEX_LIST_H_ */
