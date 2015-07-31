/*
 * stack.h
 *
 *  Created on: 2009-5-16
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_STACK_STACK_H_
#define DATA_STRUCTURE_IN_C_STACK_STACK_H_

#include "include/common.h"

//初始化
//操作结果：stack指向新构造的栈
//参数：
//	stack：指向新构造栈的指针
Status InitialStack(STACK_TYPE *stack);

//销毁
//操作结果：销毁stack指向的栈
//参数：
//	stack：要销毁的栈
Status DestroyStack(STACK_TYPE *stack);

//清除
//操作结果：清除stack指向的栈中的所有的元素
//参数：
//	stack：要清除的栈
Status ClearStack(STACK_TYPE stack);

//判断是否为空
//操作结果：如果栈为空，返回TRUE，否则返回FALSE
//参数：
//	stack：	要判断是否为空的栈
BOOLEAN StackEmpty(STACK_TYPE stack);

//求长度
//操作结果：返回stack指向栈的元素数目
//参数：
//	stack：要求长度的栈
int StackLength(STACK_TYPE stack);

//取栈顶元素
//操作结果：用element返回stack栈的栈顶元素，但不改变栈。如果栈为空，则返回ERROR
//参数：
//	stack：		要求栈顶元素的栈
//	element:	用于返回栈顶元素的指针
Status GetTop(STACK_TYPE stack, ElementType *element);

//入栈
//操作结果：插入element为新的栈顶元素
//参数：
//	stack：		要插入元素的栈
//	element:	新的栈顶元素
Status Push(STACK_TYPE stack, ElementType element);

//出栈
//操作结果：删除stack中的栈顶元素，并以element返回。如果栈为空，则返回ERROR
//参数：
//	stack：		要删除栈顶元素的栈
//	element:	用于返回栈顶元素的指针
Status Pop(STACK_TYPE stack, ElementType *element);

//遍历
//操作结果：遍历栈，对栈中的每一个元素，调用visit方法
//参数：
//	stack：要遍历的栈
//	visit：遍历时调用的方法
Status Traverse(STACK_TYPE stack, Status(*visit)(ElementType *element));

#endif /* DATA_STRUCTURE_IN_C_STACK_STACK_H_ */
