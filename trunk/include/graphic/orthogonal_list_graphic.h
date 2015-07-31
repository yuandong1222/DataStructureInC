/*
 * orthogonal_list_graphic.h
 *
 *  Created on: 2009-10-18
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_GRAPHIC_ORTHOGONAL_LIST_GRAPHIC_H_
#define DATA_STRUCTURE_IN_C_GRAPHIC_ORTHOGONAL_LIST_GRAPHIC_H_

#define ElementType 	int
#define GRAPHIC_TYPE 	OrthogonalListGraphic
#define VERTEX_TYPE		OrthogonalListGraphicVertex
#define MAX_VERTEX_SIZE	20

#include "include/common.h"

typedef struct ArcNode {
	int start_vertex_index;
	int end_vertex_index;
	struct ArcNode *start_link_next;
	struct ArcNode *end_link_next;
	int weight;
} ArcNode;

typedef struct {
	ElementType value;
	ArcNode *start_link_list;
	ArcNode *end_link_list;
	BOOLEAN is_empty;
} OrthogonalListGraphicVertex;

typedef struct {
	OrthogonalListGraphicVertex *vertex_list;
	int vertex_count;
	int arc_count;
} OrthogonalListGraphicHead, *OrthogonalListGraphic;

int get_vertex_index_by_value(GRAPHIC_TYPE graphic, ElementType value);
ArcNode* get_arc_node(GRAPHIC_TYPE graphic, int start_vertex_index, int end_vertex_index);

#endif /* DATA_STRUCTURE_IN_C_GRAPHIC_ORTHOGONAL_LIST_GRAPHIC_H_ */
