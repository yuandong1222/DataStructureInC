/*
 * undirected_graphic.h
 *
 *  Created on: 2009-9-20
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_GRAPHIC_UNDIRECTED_GRAPHIC_H_
#define DATA_STRUCTURE_IN_C_GRAPHIC_UNDIRECTED_GRAPHIC_H_

#include "include/common.h"
#include "include/graphic/graphic.h"

//�ڵ�Ķ�
//��ڵ�Ķ�
//������
//	graphic:	�漰��ͼ
//	vertex��	����ڵ�
int Degree(GRAPHIC_TYPE graphic, VERTEX_TYPE* vertex);

//��С������
//����������С��������Prim�㷨
//������
//	graphic:	�漰��ͼ
//	result:		��С��������
Status MiniSpanTree_Prim(GRAPHIC_TYPE graphic, GRAPHIC_TYPE* result);

//��С������
//����������С��������Kruskal�㷨
//������
//	graphic:	�漰��ͼ
//	result:		��С��������
Status MiniSpanTree_Kruskal(GRAPHIC_TYPE graphic, GRAPHIC_TYPE* result);

//�ؼ��ڵ�
//������ͼ�Ĺؼ��ڵ�
//������
//	graphic:		�漰��ͼ
//	result:			���еĹؽڵ���ɵ�����
//	result_length��	result����ĳ���
Status FindArticul(GRAPHIC_TYPE graphic, ElementType** result,
		int* result_length);

#endif /* DATA_STRUCTURE_IN_C_GRAPHIC_UNDIRECTED_GRAPHIC_H_ */
