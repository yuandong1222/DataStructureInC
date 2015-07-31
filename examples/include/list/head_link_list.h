/*
 * head_link_list.h
 *
 *  Created on: 2009-4-10
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_HEAD_LIST_LINK_LIST_H_
#define DATA_STRUCTURE_IN_C_HEAD_LIST_LINK_LIST_H_

#define ElementType int
#define LIST_TYPE HeadLinkList

#include "include/common.h"

//线性表的单链表存储结构
typedef struct HeadLinkListNode {
	ElementType data;
	struct HeadLinkListNode *next;
} HeadLinkListNode, *Position, *Link;

//有头的线性连接表的表头
typedef struct HeadLinkListHeadNode {
	int length;
	HeadLinkListNode *head, *tail;
} HeadLinkListHeadNode, *HeadLinkList;

//构造节点
//操作结果：将node构造为值为element的节点，并返回OK；若分配失败，返回ERROR
//参数
//	node：		返回的节点
//	element：	节点的值
Status MakeNode(HeadLinkListNode **node, ElementType element);

//释放节点
//操作结果：释放node所指向的节点
//参数
//	node：	要释放的节点
void FreeNode(HeadLinkListNode **node);

//构造一个线性表
//操作结果：构造一个空的线性表list
//参数
//	list:	要求构造的线性表
Status InitialList(LIST_TYPE *list);

//销毁一个线性表
//初始条件：线性表list已存在。
//操作结果：销毁线性表list
//参数
//	list:	要求销毁的线性表
Status DestroyList(LIST_TYPE *list);

//清除一个线性表
//初始条件：线性表list已存在。
//操作结果：将list重置为空表,不改变list
//参数
//	list:	要求清除的线性表
Status ClearList(LIST_TYPE list);

//在第一位插入
//初始条件：list已存在
//操作结果：将node所指向的节点插入list的第一个位置上
//参数
//	list：	要插入的线性表
//	node：	要插入的节点
Status InsertFirst(LIST_TYPE list, HeadLinkListNode *node);

//删除第一个节点
//初始条件：list已存在
//操作结果：删除第一个节点，并以node返回。如果线性表为空，则返回NULL
//参数
//	list：	要删除节点的线性表
//	node：	删除的节点
Status DeleteFirst(LIST_TYPE list, HeadLinkListNode **node);

//附加
//初始条件：list已存在
//操作结果：将link所指向的一串结点链接在list的最后一个结点之后，并改变list的尾指针指向新的尾结点
//参数
//	list：	要附加结点的链表
//	link：	要附加的结点（链）
Status Append(LIST_TYPE list, Link link);

//去除
//初始条件：list已存在
//操作结果：删除list中尾结点并以node返回，并改变list的尾指针指向新的尾结点
//参数
//	list：	要去除结点的链表
//	node：	去除的结点
Status Remove(LIST_TYPE list, HeadLinkListNode **node);

//在位置前插入
//初始条件：list已存在
//操作结果：已知position指向list中的一个结点，将node所指向的结点插入在position所指结点之前，并修改position指向新插入的结点
//参数
//	list：		要插入结点的链表
//	position：	结点位置
//	node：		要插入的结点
Status InsertBefore(LIST_TYPE list, Position *position, HeadLinkListNode *node);

//在位置后插入
//初始条件：list已存在
//操作结果：已知position指向list中的一个结点，将node所指向的结点插入在position所指结点之后，并修改position指向新插入的结点
//参数
//	list：		要插入结点的链表
//	position：	结点位置
//	node：		要插入的结点
Status InsertAfter(LIST_TYPE list, Position *position, HeadLinkListNode *node);

//设置结点值
//初始条件：position指向list中的一个结点
//操作结果：用element更新position所指结点中元素数据的值
//参数
//	position：	要更新的结点
//	node：		新结点值
Status SetElement(Position position, ElementType element);

//取得结点值
//初始条件：position指向list中的一个结点
//操作结果：返回position指向的结点的值
//参数
//	position：	要取得值的结点
ElementType GetElement(Position position);

//判断链表是否为空
//初始条件：线性表list已存在。
//操作结果：若list为空表，则返回TRUE，否则返回FALSE
//参数
//	list:	要判断的线性表
BOOLEAN ListEmpty(LIST_TYPE list);

//求线性表长度
//初始条件：线性表list已存在。
//操作结果：返回list中数据元素个数
//参数
//	list:	要求长度的线性表
int ListLength(LIST_TYPE list);

//取得线性表的第一个结点
//初始条件：线性表list已存在。
//操作结果：返回list中第一个结点的位置，如果list为空，返回NULL
//参数
//	list:	要取得第一个结点的线性表
Position GetFirst(LIST_TYPE list);

//取得线性表的最后一个结点
//初始条件：线性表list已存在。
//操作结果：返回list中最后一个结点的位置，如果list为空，返回NULL
//参数
//	list:	要取得最后一个结点的线性表
Position GetLast(LIST_TYPE list);

//前驱
//初始条件：线性表list已存在。position指向list中的结点
//操作结果：返回position的前驱，如果没有前驱，就返回NULL
//参数
//	list:		相关线性表
//	position：	要取得前驱的结点
Position PriorPosition(LIST_TYPE list, Position position);

//后继
//初始条件：线性表list已存在。position指向list中的结点
//操作结果：返回position的后继，如果没有后继，就返回NULL
//参数
//	list:		相关线性表
//	position：	要取得后继的结点
Position NextPosition(LIST_TYPE list, Position position);

//定位位置
//初始条件: 线性表list已存在
//操作结果: 返回list中positionIndex位置的结点，并返回OK；若positionIndex非法，则返回ERROR
//参数
//	list:			要查找的线性表
//	positionIndex:	要查找的结点位置
//	position:		找到的结点
Status LocatePosition(LIST_TYPE list, int positionIndex, Position *position);

//定位元素
//初始条件: 线性表list已存在,compare()是数据元素判定函数(满足为TRUE,否则为FALSE)
//操作结果: 返回list中第一个与element满足关系compare()的数据元素的位置。若这样的数据元素不存在,则返回值为NULL
//参数
//	list:		要查找的线性表
//	element:	要查找的元素
//	compare:	比较元素是否相等的函数
Position LocateElement(LIST_TYPE list, ElementType element, Status(*compare)(
		ElementType, ElementType));

//遍历
//初始条件：线性表list已存在
//操作结果：依次对list的每个数据元素调用函数visit()。一旦visit()失败，则操作失败,visit()的形参加'*'，表明可通过调用visit()改变元素的值
//参数
//	list:	要遍历的线性表
//	visit:	在每个元素上要执行的函数
Status ListTraverse(LIST_TYPE list, Status(*visit)(ElementType*));

#endif /* DATA_STRUCTURE_IN_C_HEAD_LIST_LINK_LIST_H_ */
