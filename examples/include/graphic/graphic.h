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

//初始化
//初始化图
//参数：
//	graphic:	要初始化的图
Status Initial(GRAPHIC_TYPE* graphic);

//销毁
//销毁图
//参数：
//	graphic:	要销毁的图
Status Destory(GRAPHIC_TYPE* graphic);

//构造
//根据给出的字符串表示构造相应的图
//参数：
//	graphic:	构造后的图
//	definition:	图的字符串表示
Status Create(GRAPHIC_TYPE* graphic, Graphic* definition);

//取得节点
//取得第一个值为value的节点，如果不存在这样的节点，返回NULL。如果有多个节点，则返回第一个。
//参数：
//	graphic:	相关的图
//	value:		要查找的节点的值
VERTEX_TYPE* GetVertex(GRAPHIC_TYPE graphic, ElementType value);

//取值
//取得节点的值
//参数：
//	graphic:	相关的图
//	vertex:		要取值的节点
ElementType Value(GRAPHIC_TYPE graphic, VERTEX_TYPE* vertex);

//赋值
//返回所给节点的值
//参数：
//	graphic:	相关的图
//	vertex:		要取得值的节点
Status Assign(GRAPHIC_TYPE* graphic, VERTEX_TYPE* vertex, ElementType value);

//求相邻节点
//返回节点的相邻节点，如果节点没有相邻节点，返回NULL
//参数：
//	graphic:	相关的图
//	vertex:		要取得值的节点
VERTEX_TYPE* FirstAdjacentVertex(GRAPHIC_TYPE graphic, VERTEX_TYPE* vertex);

//求相邻节点
//返回节点不同于adjacent_vertex的下一个相邻节点，如果节点没有下一个相邻节点，返回NULL
//参数：
//	graphic:		相关的图
//	vertex:			要取得值的节点
//	adjacent_vertex:	当前相邻节点
VERTEX_TYPE* NextAdjacentVertex(GRAPHIC_TYPE graphic, VERTEX_TYPE* vertex,
		VERTEX_TYPE* adjacent_vertex);

//插入节点
//插入值为value的节点，并以vertex返回插入的节点
//参数：
//	graphic:	相关的图
//	value:		插入的节点的值
//	vertex:		插入的节点
Status InsertVertex(GRAPHIC_TYPE* graphic, ElementType value, VERTEX_TYPE** vertex);

//删除节点
//删除节点vertex，并将node置空
//参数：
//	graphic:	相关的图
//	vertex:		要删除的节点
Status DeleteVertex(GRAPHIC_TYPE* graphic, VERTEX_TYPE** vertex);

//插入弧
//在start_vertex和end_node之间插入一条弧。如果图为无向图，则不区分终点和起点。
//参数：
//	graphic:	相关的图
//	start_vertex:	弧的起点
//	end_vertex:	弧的终点
//	weight:		弧的权重
Status InsertArc(GRAPHIC_TYPE* graphic, VERTEX_TYPE* start_vertex,
		VERTEX_TYPE* end_vertex, int weight);

//删除弧
//删除以start_vertex为起点，end_node为终点的弧。如果图为无向图，则不区分终点和起点。
//参数：
//	graphic:	相关的图
//	start_vertex:	弧的起点
//	end_vertex:	弧的终点
Status DeleteArc(GRAPHIC_TYPE* graphic, VERTEX_TYPE* start_vertex,
		VERTEX_TYPE* end_vertex);

//深度优先遍历
//对图进行深度优先遍历。
//参数：
//	graphic:	相关的图
//	visit：		遍历函数
Status DepthFirstTraverse(GRAPHIC_TYPE graphic, Status(*visit)(ElementType*));

//广度优先遍历
//对图进行广度优先遍历。
//参数：
//	graphic:	相关的图
//	visit：		遍历函数
Status BreadthFirstTraverse(GRAPHIC_TYPE graphic, Status(*visit)(ElementType*));

#endif /* DATA_STRUCTURE_IN_C_GRAPHIC_GRAPHIC_H_ */
