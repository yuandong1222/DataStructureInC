/*
 * stack.h
 *
 *  Created on: 2009-5-16
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_STACK_STACK_H_
#define DATA_STRUCTURE_IN_C_STACK_STACK_H_

#include "include/common.h"

//��ʼ��
//���������stackָ���¹����ջ
//������
//	stack��ָ���¹���ջ��ָ��
Status InitialStack(STACK_TYPE *stack);

//����
//�������������stackָ���ջ
//������
//	stack��Ҫ���ٵ�ջ
Status DestroyStack(STACK_TYPE *stack);

//���
//������������stackָ���ջ�е����е�Ԫ��
//������
//	stack��Ҫ�����ջ
Status ClearStack(STACK_TYPE stack);

//�ж��Ƿ�Ϊ��
//������������ջΪ�գ�����TRUE�����򷵻�FALSE
//������
//	stack��	Ҫ�ж��Ƿ�Ϊ�յ�ջ
BOOLEAN StackEmpty(STACK_TYPE stack);

//�󳤶�
//�������������stackָ��ջ��Ԫ����Ŀ
//������
//	stack��Ҫ�󳤶ȵ�ջ
int StackLength(STACK_TYPE stack);

//ȡջ��Ԫ��
//�����������element����stackջ��ջ��Ԫ�أ������ı�ջ�����ջΪ�գ��򷵻�ERROR
//������
//	stack��		Ҫ��ջ��Ԫ�ص�ջ
//	element:	���ڷ���ջ��Ԫ�ص�ָ��
Status GetTop(STACK_TYPE stack, ElementType *element);

//��ջ
//�������������elementΪ�µ�ջ��Ԫ��
//������
//	stack��		Ҫ����Ԫ�ص�ջ
//	element:	�µ�ջ��Ԫ��
Status Push(STACK_TYPE stack, ElementType element);

//��ջ
//���������ɾ��stack�е�ջ��Ԫ�أ�����element���ء����ջΪ�գ��򷵻�ERROR
//������
//	stack��		Ҫɾ��ջ��Ԫ�ص�ջ
//	element:	���ڷ���ջ��Ԫ�ص�ָ��
Status Pop(STACK_TYPE stack, ElementType *element);

//����
//�������������ջ����ջ�е�ÿһ��Ԫ�أ�����visit����
//������
//	stack��Ҫ������ջ
//	visit������ʱ���õķ���
Status Traverse(STACK_TYPE stack, Status(*visit)(ElementType *element));

#endif /* DATA_STRUCTURE_IN_C_STACK_STACK_H_ */
