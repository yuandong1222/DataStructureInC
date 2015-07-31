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

//节点的度
//求节点的度
//参数：
//	graphic:	涉及的图
//	vertex：	所求节点
int Degree(GRAPHIC_TYPE graphic, VERTEX_TYPE* vertex);

//最小生成树
//无向网的最小生成树的Prim算法
//参数：
//	graphic:	涉及的图
//	result:		最小生成树。
Status MiniSpanTree_Prim(GRAPHIC_TYPE graphic, GRAPHIC_TYPE* result);

//最小生成树
//无向网的最小生成树的Kruskal算法
//参数：
//	graphic:	涉及的图
//	result:		最小生成树。
Status MiniSpanTree_Kruskal(GRAPHIC_TYPE graphic, GRAPHIC_TYPE* result);

//关键节点
//求无向图的关键节点
//参数：
//	graphic:		涉及的图
//	result:			所有的关节点组成的数组
//	result_length：	result数组的长度
Status FindArticul(GRAPHIC_TYPE graphic, ElementType** result,
		int* result_length);

#endif /* DATA_STRUCTURE_IN_C_GRAPHIC_UNDIRECTED_GRAPHIC_H_ */
