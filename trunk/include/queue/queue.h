/*
 * queue.h
 *
 *  Created on: 2009-5-19
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_QUEUE_QUEUE_H_
#define DATA_STRUCTURE_IN_C_QUEUE_QUEUE_H_

#include "include/common.h"

//��ʼ��
//���������queueָ���¹���Ķ���
//������
//	queue��ָ���¹�����е�ָ��
Status InitialQueue(QUEUE_TYPE *queue);

//����
//�������������queueָ��Ķ���
//������
//	queue��Ҫ���ٵĶ���
Status DestroyQueue(QUEUE_TYPE *queue);

//���
//������������queueָ��Ķ����е����е�Ԫ��
//������
//	queue��Ҫ����Ķ���
Status ClearQueue(QUEUE_TYPE queue);

//�ж��Ƿ�Ϊ��
//����������������Ϊ�գ�����TRUE�����򷵻�FALSE
//������
//	queue��	Ҫ�ж��Ƿ�Ϊ�յĶ���
BOOLEAN QueueEmpty(QUEUE_TYPE queue);

//�󳤶�
//�������������queueָ����е�Ԫ����Ŀ
//������
//	queue��Ҫ�󳤶ȵĶ���
int QueueLength(QUEUE_TYPE queue);

//ȡ����ͷԪ��
//�����������element����queue���еĶ���ͷԪ�أ������ı���С��������Ϊ�գ��򷵻�ERROR
//������
//	queue��		Ҫ�����ͷԪ�صĶ���
//	element:	���ڷ��ض��ж�Ԫ�ص�ָ��
Status GetHead(QUEUE_TYPE queue, ElementType *element);

//�����
//�������������elementΪ�µĶ���ͷԪ��
//������
//	queue��		Ҫ����Ԫ�صĶ���
//	element:	�µĶ���ͷԪ��
Status Enqueue(QUEUE_TYPE queue, ElementType element);

//������
//���������ɾ��queue�еĶ�βԪ�أ�����element���ء��������Ϊ�գ��򷵻�ERROR
//������
//	queue��		Ҫɾ����βԪ�صĶ���
//	element:	���ڷ��ض�βԪ�ص�ָ��
Status Dequeue(QUEUE_TYPE queue, ElementType *element);

//����
//����������������У��Զ����е�ÿһ��Ԫ�أ�����visit����
//������
//	queue��Ҫ�����Ķ���
//	visit������ʱ���õķ���
Status Traverse(QUEUE_TYPE queue, Status(*visit)(ElementType *element));

#endif /* DATA_STRUCTURE_IN_C_QUEUE_QUEUE_H_ */
