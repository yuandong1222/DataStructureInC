/*
 * adjacent_list_graphic.h
 *
 *  Created on: 2009-9-23
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_GRAPHIC_ADJACENT_LIST_GRAPHIC_H_
#define DATA_STRUCTURE_IN_C_GRAPHIC_ADJACENT_LIST_GRAPHIC_H_

#define ElementType 	int
#define GRAPHIC_TYPE 	AdjacentListGraphic
#define VERTEX_TYPE		AdjacentListGraphicVertex
#define MAX_VERTEX_SIZE 20

#include "include/common.h"

typedef struct ArcNode {
	int vertex_index;
	int weight;
	struct ArcNode* next;
} ArcNode;

typedef struct {
	ElementType value;
	BOOLEAN     is_empty;
	ArcNode 	*arc_list;
} AdjacentListGraphicVertex;

typedef struct {
	AdjacentListGraphicVertex *vertex_list;
	int vertex_count;
	int arc_count;
} AdjacentListGraphicHead, *AdjacentListGraphic;

int get_vertex_index_by_value(GRAPHIC_TYPE graphic, ElementType value);
ArcNode* get_arc_node(GRAPHIC_TYPE graphic, int start_vertex_index, int end_vertex_index);

#endif /* DATA_STRUCTURE_IN_C_GRAPHIC_ADJACENT_LIST_GRAPHIC_H_ */
