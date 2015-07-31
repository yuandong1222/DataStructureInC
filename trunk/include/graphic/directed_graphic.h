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

//入度
//求节点的入度
//参数：
//	graphic:	涉及的图
//	vertex：	所求节点
int InDegree(GRAPHIC_TYPE graphic, VERTEX_TYPE* vertex);

//出度
//求节点的出度
//参数：
//	graphic:	涉及的图
//	vertex：	所求节点
int OutDegree(GRAPHIC_TYPE graphic, VERTEX_TYPE* vertex);

//拓扑排序
//有向无环图的拓扑排序
//参数：
//	graphic:	涉及的图
//	result:		结果数组，长度等于图的节点数目。
Status TopologicalSort(GRAPHIC_TYPE graphic, ElementType** result);

//关键路径
//有向无环网的关键路径
//参数：
//	graphic:		涉及的图
//	result:			用弧数组表示的关键路径
//	result_lengh：	result数组的长度
Status CriticalPath(GRAPHIC_TYPE graphic, GRAPHIC_TYPE* result);

typedef struct {
	VERTEX_TYPE  *end_vertex;
	GRAPHIC_TYPE graphic;
} ShortestPathResultNode;

//最短路径
//计算由strat_vertex到图中其它节点的最短路径
//参数：
//	graphic:		涉及的图
//	strat_vertex：	起始节点
//	result:			长度为图中节点数-1的ShortestPathResultNode数组，每一个元素表示到图中一个节点的最短路径。
Status ShortestPath(GRAPHIC_TYPE graphic, VERTEX_TYPE *strat_vertex,
		ShortestPathResultNode** result);

#endif /* DATA_STRUCTURE_IN_C_GRAPHIC_DIRECTED_GRAPHIC_H_ */
