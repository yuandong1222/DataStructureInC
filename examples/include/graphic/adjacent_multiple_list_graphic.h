/*
 * adjacent_multiple_list_graphic.h
 *
 *  Created on: 2009-10-19
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_GRAPHIC_ADJACENT_MULTIPLE_LIST_GRAPHIC_H_
#define DATA_STRUCTURE_IN_C_GRAPHIC_ADJACENT_MULTIPLE_LIST_GRAPHIC_H_

#define ElementType 	int
#define GRAPHIC_TYPE 	AdjacentMultipleListGraphic
#define VERTEX_TYPE		AdjacentMultipleListGraphicVertex
#define MAX_VERTEX_SIZE 20

#include "include/common.h"

typedef struct ArcNode {
	int start_vertex_index;
	int end_vertex_index;
	int weight;
	struct ArcNode* start_link_next;
	struct ArcNode* end_link_next;
} ArcNode;

typedef struct {
	ElementType value;
	BOOLEAN     is_empty;
	ArcNode 	*arc_list;
} AdjacentMultipleListGraphicVertex;

typedef struct {
	AdjacentMultipleListGraphicVertex *vertex_list;
	int vertex_count;
	int arc_count;
} AdjacentMultipleListGraphicHead, *AdjacentMultipleListGraphic;

int get_vertex_index_by_value(GRAPHIC_TYPE graphic, ElementType value);
ArcNode* get_arc_node(GRAPHIC_TYPE graphic, int start_vertex_index, int end_vertex_index);

#endif /* DATA_STRUCTURE_IN_C_GRAPHIC_ADJACENT_MULTIPLE_LIST_GRAPHIC_H_ */
