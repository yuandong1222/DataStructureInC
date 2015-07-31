/*
 * generalized_list.h
 *
 *  Created on: 2009-8-10
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_ARRAY_GENERALIZED_LIST_H_
#define DATA_STRUCTURE_IN_C_ARRAY_GENERALIZED_LIST_H_

//初始化
//初始化广义表
//参数：
//	list:	用于返回广义表的指针
Status Initial(GENERALIZED_LIST_TYPE* list);

//创建
//创建广义表
//参数：
//	list	用于返回广义表的指针
//	string:	广义表的字符串表示形式
Status Create(GENERALIZED_LIST_TYPE* list, char* string);

//销毁
//销毁广义表
//参数：
//	list:	要销毁的广义表
Status Destory(GENERALIZED_LIST_TYPE* list);

//复制
//参数：
//	list:			要复制的广义表
//	duplication:	复制出的广义表
Status Copy(GENERALIZED_LIST_TYPE list, GENERALIZED_LIST_TYPE* duplication);

//长度
//求广义表的长度，即元素的个数
//参数：
//	list:	要求长度的广义表
int Length(GENERALIZED_LIST_TYPE list);

//深度
//求广义表的深度
//参数：
//	list:	要求深度的广义表
int Depth(GENERALIZED_LIST_TYPE list);

//判空
//判断list是否为空表
//参数：
//	list:	要判空的广义表
BOOLEAN Empty(GENERALIZED_LIST_TYPE list);

//取头元素
//取广义表的头元素，如果广义表为空表，返回空
//参数：
//	list:	要取头元素的广义表
GENERALIZED_LIST_TYPE GetHead(GENERALIZED_LIST_TYPE list);

//取尾元素
//取广义表的尾元素，如果广义表为空表，返回空
//参数：
//	list:	要取尾元素的广义表
GENERALIZED_LIST_TYPE GetTail(GENERALIZED_LIST_TYPE list);

//表头插入
//插入元素element作为list的第一元素
//参数：
//	list:		要插入元素的广义表
//	element:	要插入的元素
Status InsertFirst(GENERALIZED_LIST_TYPE* list, GENERALIZED_LIST_TYPE* element);

//表头删除
//删除list的第一个元素，并用element返回
//参数：
//	list:		要删除元素的广义表
//	element:	返回删除的元素
Status DeleteFirst(GENERALIZED_LIST_TYPE* list, GENERALIZED_LIST_TYPE* element);

//遍历
//使用visit函数遍历广利表的所有节点
//参数:
//	list:	要遍历的广义表
//	visit:	遍历函数
Status Traverse(GENERALIZED_LIST_TYPE* list, Status(*visit)(ElementType*));

#endif /* DATA_STRUCTURE_IN_C_ARRAY_GENERALIZED_LIST_H_ */
