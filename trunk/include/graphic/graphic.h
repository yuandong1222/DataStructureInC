/*
 * graphic.h
 *
 *  Created on: 2009-9-17
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_GRAPHIC_GRAPHIC_H_
#define DATA_STRUCTURE_IN_C_GRAPHIC_GRAPHIC_H_

#include "include/common.h"

typedef ElementType Vertex;

typedef struct {
	ElementType start_vertex;
	ElementType end_vertex;
	int weight;
} Arc;

typedef struct {
	int vertex_length;
	int arc_length;
	Vertex *vertex_list;
	Arc *arc_list;
} Graphic;

//��ʼ��
//��ʼ��ͼ
//������
//	graphic:	Ҫ��ʼ����ͼ
Status Initial(GRAPHIC_TYPE* graphic);

//����
//����ͼ
//������
//	graphic:	Ҫ���ٵ�ͼ
Status Destory(GRAPHIC_TYPE* graphic);

//����
//���ݸ������ַ�����ʾ������Ӧ��ͼ
//������
//	graphic:	������ͼ
//	definition:	ͼ���ַ�����ʾ
Status Create(GRAPHIC_TYPE* graphic, Graphic* definition);

//ȡ�ýڵ�
//ȡ�õ�һ��ֵΪvalue�Ľڵ㣬��������������Ľڵ㣬����NULL������ж���ڵ㣬�򷵻ص�һ����
//������
//	graphic:	��ص�ͼ
//	value:		Ҫ���ҵĽڵ��ֵ
VERTEX_TYPE* GetVertex(GRAPHIC_TYPE graphic, ElementType value);

//ȡֵ
//ȡ�ýڵ��ֵ
//������
//	graphic:	��ص�ͼ
//	vertex:		Ҫȡֵ�Ľڵ�
ElementType Value(GRAPHIC_TYPE graphic, VERTEX_TYPE* vertex);

//��ֵ
//���������ڵ��ֵ
//������
//	graphic:	��ص�ͼ
//	vertex:		Ҫȡ��ֵ�Ľڵ�
Status Assign(GRAPHIC_TYPE* graphic, VERTEX_TYPE* vertex, ElementType value);

//�����ڽڵ�
//���ؽڵ�����ڽڵ㣬����ڵ�û�����ڽڵ㣬����NULL
//������
//	graphic:	��ص�ͼ
//	vertex:		Ҫȡ��ֵ�Ľڵ�
VERTEX_TYPE* FirstAdjacentVertex(GRAPHIC_TYPE graphic, VERTEX_TYPE* vertex);

//�����ڽڵ�
//���ؽڵ㲻ͬ��adjacent_vertex����һ�����ڽڵ㣬����ڵ�û����һ�����ڽڵ㣬����NULL
//������
//	graphic:		��ص�ͼ
//	vertex:			Ҫȡ��ֵ�Ľڵ�
//	adjacent_vertex:	��ǰ���ڽڵ�
VERTEX_TYPE* NextAdjacentVertex(GRAPHIC_TYPE graphic, VERTEX_TYPE* vertex,
		VERTEX_TYPE* adjacent_vertex);

//����ڵ�
//����ֵΪvalue�Ľڵ㣬����vertex���ز���Ľڵ�
//������
//	graphic:	��ص�ͼ
//	value:		����Ľڵ��ֵ
//	vertex:		����Ľڵ�
Status InsertVertex(GRAPHIC_TYPE* graphic, ElementType value, VERTEX_TYPE** vertex);

//ɾ���ڵ�
//ɾ���ڵ�vertex������node�ÿ�
//������
//	graphic:	��ص�ͼ
//	vertex:		Ҫɾ���Ľڵ�
Status DeleteVertex(GRAPHIC_TYPE* graphic, VERTEX_TYPE** vertex);

//���뻡
//��start_vertex��end_node֮�����һ���������ͼΪ����ͼ���������յ����㡣
//������
//	graphic:	��ص�ͼ
//	start_vertex:	�������
//	end_vertex:	�����յ�
//	weight:		����Ȩ��
Status InsertArc(GRAPHIC_TYPE* graphic, VERTEX_TYPE* start_vertex,
		VERTEX_TYPE* end_vertex, int weight);

//ɾ����
//ɾ����start_vertexΪ��㣬end_nodeΪ�յ�Ļ������ͼΪ����ͼ���������յ����㡣
//������
//	graphic:	��ص�ͼ
//	start_vertex:	�������
//	end_vertex:	�����յ�
Status DeleteArc(GRAPHIC_TYPE* graphic, VERTEX_TYPE* start_vertex,
		VERTEX_TYPE* end_vertex);

//������ȱ���
//��ͼ����������ȱ�����
//������
//	graphic:	��ص�ͼ
//	visit��		��������
Status DepthFirstTraverse(GRAPHIC_TYPE graphic, Status(*visit)(ElementType*));

//������ȱ���
//��ͼ���й�����ȱ�����
//������
//	graphic:	��ص�ͼ
//	visit��		��������
Status BreadthFirstTraverse(GRAPHIC_TYPE graphic, Status(*visit)(ElementType*));

#endif /* DATA_STRUCTURE_IN_C_GRAPHIC_GRAPHIC_H_ */
