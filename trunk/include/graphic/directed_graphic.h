/*
 * directed_graphic.h
 *
 *  Created on: 2009-9-20
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_GRAPHIC_DIRECTED_GRAPHIC_H_
#define DATA_STRUCTURE_IN_C_GRAPHIC_DIRECTED_GRAPHIC_H_

#include "include/common.h"
#include "include/graphic/graphic.h"

//���
//��ڵ�����
//������
//	graphic:	�漰��ͼ
//	vertex��	����ڵ�
int InDegree(GRAPHIC_TYPE graphic, VERTEX_TYPE* vertex);

//����
//��ڵ�ĳ���
//������
//	graphic:	�漰��ͼ
//	vertex��	����ڵ�
int OutDegree(GRAPHIC_TYPE graphic, VERTEX_TYPE* vertex);

//��������
//�����޻�ͼ����������
//������
//	graphic:	�漰��ͼ
//	result:		������飬���ȵ���ͼ�Ľڵ���Ŀ��
Status TopologicalSort(GRAPHIC_TYPE graphic, ElementType** result);

//�ؼ�·��
//�����޻����Ĺؼ�·��
//������
//	graphic:		�漰��ͼ
//	result:			�û������ʾ�Ĺؼ�·��
//	result_lengh��	result����ĳ���
Status CriticalPath(GRAPHIC_TYPE graphic, GRAPHIC_TYPE* result);

typedef struct {
	VERTEX_TYPE  *end_vertex;
	GRAPHIC_TYPE graphic;
} ShortestPathResultNode;

//���·��
//������strat_vertex��ͼ�������ڵ�����·��
//������
//	graphic:		�漰��ͼ
//	strat_vertex��	��ʼ�ڵ�
//	result:			����Ϊͼ�нڵ���-1��ShortestPathResultNode���飬ÿһ��Ԫ�ر�ʾ��ͼ��һ���ڵ�����·����
Status ShortestPath(GRAPHIC_TYPE graphic, VERTEX_TYPE *strat_vertex,
		ShortestPathResultNode** result);

#endif /* DATA_STRUCTURE_IN_C_GRAPHIC_DIRECTED_GRAPHIC_H_ */
