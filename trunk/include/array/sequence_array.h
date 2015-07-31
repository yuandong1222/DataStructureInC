/*
 * sequence_array.h
 *
 *  Created on: 2009-7-19
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_ARRAY_SEQUENCE_ARRAY_H_
#define DATA_STRUCTURE_IN_C_ARRAY_SEQUENCE_ARRAY_H_

#define ElementType int

#include "include/common.h"

typedef struct {
	int dimension;
	ElementType *base;
	int *bounds;
	int *constants;

} SequenceArrayHead, *SequenceArray;

//��ʼ��
//���ݸ�����ά�Ⱥ�ÿ��ά�ȵ�ά�繹������
//������
//	array:		���ڷ��������ָ��
//	dimension:	�����ά��
//	...:		��ά�ȵ�ά��
Status Initial(SequenceArray* array, int dimension, ...);

//����
//��������
//������
//	array:		Ҫ���ٵ�����
Status Destory(SequenceArray* array);

//��ֵ
//�Ը����±��Ԫ�ظ�ֵ
//������
//	array:		Ҫ����������
//	element:	Ԫ��ֵ
//	...:		�±�
Status Assign(SequenceArray array, ElementType element, int dimension, ...);

//ȡֵ
//ȡ�ø����±��Ԫ��ֵ
//������
//	array:		Ҫ����������
//	element:	Ԫ��ֵ
//	...:		�±�
Status Value(SequenceArray array, ElementType *element, int dimension, ...);

#endif /* DATA_STRUCTURE_IN_C_ARRAY_SEQUENCE_ARRAY_H_ */
