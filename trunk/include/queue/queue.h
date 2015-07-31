/*
 * queue.h
 *
 *  Created on: 2009-5-19
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_QUEUE_QUEUE_H_
#define DATA_STRUCTURE_IN_C_QUEUE_QUEUE_H_

#include "include/common.h"

//初始化
//操作结果：queue指向新构造的队列
//参数：
//	queue：指向新构造队列的指针
Status InitialQueue(QUEUE_TYPE *queue);

//销毁
//操作结果：销毁queue指向的队列
//参数：
//	queue：要销毁的队列
Status DestroyQueue(QUEUE_TYPE *queue);

//清除
//操作结果：清除queue指向的队列中的所有的元素
//参数：
//	queue：要清除的队列
Status ClearQueue(QUEUE_TYPE queue);

//判断是否为空
//操作结果：如果队列为空，返回TRUE，否则返回FALSE
//参数：
//	queue：	要判断是否为空的队列
BOOLEAN QueueEmpty(QUEUE_TYPE queue);

//求长度
//操作结果：返回queue指向队列的元素数目
//参数：
//	queue：要求长度的队列
int QueueLength(QUEUE_TYPE queue);

//取队列头元素
//操作结果：用element返回queue队列的队列头元素，但不改变队列。如果队列为空，则返回ERROR
//参数：
//	queue：		要求队列头元素的队列
//	element:	用于返回队列顶元素的指针
Status GetHead(QUEUE_TYPE queue, ElementType *element);

//入队列
//操作结果：插入element为新的队列头元素
//参数：
//	queue：		要插入元素的队列
//	element:	新的队列头元素
Status Enqueue(QUEUE_TYPE queue, ElementType element);

//出队列
//操作结果：删除queue中的队尾元素，并以element返回。如果队列为空，则返回ERROR
//参数：
//	queue：		要删除队尾元素的队列
//	element:	用于返回队尾元素的指针
Status Dequeue(QUEUE_TYPE queue, ElementType *element);

//遍历
//操作结果：遍历队列，对队列中的每一个元素，调用visit方法
//参数：
//	queue：要遍历的队列
//	visit：遍历时调用的方法
Status Traverse(QUEUE_TYPE queue, Status(*visit)(ElementType *element));

#endif /* DATA_STRUCTURE_IN_C_QUEUE_QUEUE_H_ */
