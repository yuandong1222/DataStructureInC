/*
 * adjacent_matrix_graphic.h
 *
 *  Created on: 2009-9-20
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_GRAPHIC_ADJACENT_MATRIX_GRAPHIC_H_
#define DATA_STRUCTURE_IN_C_GRAPHIC_ADJACENT_MATRIX_GRAPHIC_H_

#define ElementType 	int
#define GRAPHIC_TYPE 	AdjacentMatrixGraphic
#define VERTEX_TYPE		AdjacentMatrixGraphicVertex
#define MAX_VERTEX_SIZE	20

#include "include/common.h"

typedef struct {
	ElementType value;
	BOOLEAN is_empty;
} AdjacentMatrixGraphicVertex;

typedef struct {
	AdjacentMatrixGraphicVertex vertex_list[MAX_VERTEX_SIZE];
	int arc_list[MAX_VERTEX_SIZE][MAX_VERTEX_SIZE];
	int vertex_count, arc_count;
} AdjacentMatrixGraphicHead, *AdjacentMatrixGraphic;

int get_vertex_index_by_value(GRAPHIC_TYPE graphic, ElementType value);

#endif /* DATA_STRUCTURE_IN_C_GRAPHIC_ADJACENT_MATRIX_GRAPHIC_H_ */
