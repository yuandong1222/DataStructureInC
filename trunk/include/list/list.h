/*
 * list.inc
 *
 *  Created on: 2009-4-10
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_LIST_H_
#define DATA_STRUCTURE_IN_C_LIST_H_

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

//取得元素
//初始条件: 线性表list已存在，1<=position<=ListLength(L)
//当第position个元素存在时,其值赋给element并返回OK,否则返回ERROR
//参数
//	list:		要查找的线性表
//	position:	要取得的元素的位置
//	element:	取得的元素
Status GetElement(LIST_TYPE list, int position, ElementType *element);

//定位
//初始条件: 线性表list已存在,compare()是数据元素判定函数(满足为TRUE,否则为FALSE)
//操作结果: 返回list中第一个与element满足关系compare()的数据元素的位序。若这样的数据元素不存在,则返回值为0
//参数
//	list:		要查找的线性表
//	element:	要查找的元素
//	compare:	比较元素是否相等的函数
int LocateElement(LIST_TYPE list, ElementType element, Status(*compare)(
		ElementType, ElementType));

//前驱
//初始条件: 线性表list已存在
//操作结果: 若currentElement是L的数据元素,且不是第一个,则用priorElement返回它的前驱,返回OK;否则操作失败,priorElement无定义,返回INFEASIBLE
//参数
//	list:			要查找的线性表
//	currentElement:	要查找的位置
//	nextElement:	查找元素的前驱
Status PriorElement(LIST_TYPE list, ElementType currentElement,
		ElementType *priorElement);

//后继
//初始条件：线性表list已存在
//操作结果：若currentElement是list的数据元素，且不是最后一个，则用nextElement返回它的后继，返回OK;否则操作失败，nextElement无定义，返回INFEASIBLE
//参数
//	list:			要查找的线性表
//	currentElement:	要查找的位置
//	nextElement:	查找元素的后继
Status NextElement(LIST_TYPE list, ElementType currentElement,
		ElementType *nextElement);

//插入元素
//初始条件：线性表list已存在，1<=position<=ListLength(L)+1
//操作结果：在list中第position个位置之前插入新的数据元素element，list的长度加1
//参数
//	list:		要插入的线性表
//	position:	要插入的位置
//	element:	要插入的元素的值
Status ListInsert(LIST_TYPE list, int position, ElementType element);

//删除元素
//初始条件：线性表list已存在，1<=position<=ListLength(L)
//操作结果：删除list的第position个数据元素，并用deletedElement返回其值，L的长度减1
//参数
//	list:			要删除元素的线性表
//	position:		要删除的元素的位置
//	deletedElement:	被删除的元素的值
Status ListDelete(LIST_TYPE list, int position, ElementType *deletedElement);

//遍历
//初始条件：线性表list已存在
//操作结果：依次对list的每个数据元素调用函数visit()。一旦visit()失败，则操作失败,visit()的形参加'*'，表明可通过调用visit()改变元素的值
//参数
//	list:	要遍历的线性表
//	visit:	在每个元素上要执行的函数
Status ListTraverse(LIST_TYPE list, Status(*visit)(ElementType*));

//合并
//初始条件：线性表a，b都存在，且a，b都已排好顺序
//操作结果：合并a，b两个线性表，将结果放在a中，并释放b
//参数
//	a:	线性表a
//	b:	线性表b
Status ListMerge(LIST_TYPE *a, LIST_TYPE *b);

#endif /* DATA_STRUCTURE_IN_C_LIST_H_ */
