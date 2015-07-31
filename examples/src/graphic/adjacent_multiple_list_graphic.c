/*
 * adjacent_multiple_list_graphic.c
 *
 *  Created on; 2009-10-19
 *      Author; yuandong
 */

#include <stdlib.h>
#include <stdio.h>

#include "include/common.h"
#include "include/graphic/adjacent_multiple_list_graphic.h"
#include "include/graphic/undirected_graphic.h"

int get_vertex_index_by_value(GRAPHIC_TYPE graphic, ElementType value) {
	int i = 0;
	for (i = 0; i < MAX_VERTEX_SIZE; i++) {
		VERTEX_TYPE *vertex = graphic -> vertex_list + i;
		if(vertex -> is_empty == FALSE && vertex -> value == value)
			return i;
	}
	return -1;
}

ArcNode* get_arc_node(GRAPHIC_TYPE graphic, int start_vertex_index, int end_vertex_index) {
	AdjacentMultipleListGraphicVertex *start_vertex = graphic -> vertex_list + start_vertex_index;
	ArcNode *arc_node = start_vertex -> arc_list;
	while (arc_node != NULL) {
		if (arc_node -> start_vertex_index == start_vertex_index) {
			if (arc_node -> end_vertex_index == end_vertex_index)
				break;
			arc_node = arc_node -> start_link_next;
		} else {
			if (arc_node -> start_vertex_index == end_vertex_index)
				break;
			arc_node = arc_node -> end_link_next;
		}
	}
	return arc_node;
}

void remove_arc_node(AdjacentMultipleListGraphic graphic, ArcNode* arc_node) {
	ArcNode *node = NULL;
	AdjacentMultipleListGraphicVertex *start_vertex = graphic -> vertex_list + arc_node -> start_vertex_index;
	AdjacentMultipleListGraphicVertex *end_vertex = graphic -> vertex_list + arc_node -> end_vertex_index;

	if (start_vertex -> arc_list == arc_node) {
		start_vertex -> arc_list = arc_node -> start_link_next;
	} else {
		node = start_vertex -> arc_list;
		while (node != NULL && node -> start_link_next != arc_node && node -> end_link_next != arc_node) {
			node = node -> start_vertex_index == arc_node -> start_vertex_index ? 
				node -> start_link_next : node -> end_link_next;
		}
		if (node -> start_link_next == arc_node)
			node -> start_link_next = arc_node -> start_link_next;
		if (node -> end_link_next == arc_node)
			node -> end_link_next = arc_node -> start_link_next;
	}

	if (end_vertex -> arc_list == arc_node) {
		end_vertex -> arc_list = arc_node -> end_link_next;
	} else {
		node = end_vertex -> arc_list;
		while (node != NULL && node -> start_link_next != arc_node && node -> end_link_next != arc_node) {
			node = node -> start_vertex_index == arc_node -> end_vertex_index ? 
				node -> start_link_next : node -> end_link_next;
		}
		if (node -> start_link_next == arc_node)
			node -> start_link_next = arc_node -> end_link_next;
		if (node -> end_link_next == arc_node)
			node -> end_link_next = arc_node -> end_link_next;
	}

	free(arc_node);
}

Status Initial(GRAPHIC_TYPE* graphic) {
	*graphic = (GRAPHIC_TYPE)malloc(sizeof(AdjacentMultipleListGraphicHead));
	(*graphic) -> vertex_list = (AdjacentMultipleListGraphicVertex*)malloc(sizeof(AdjacentMultipleListGraphicVertex) * MAX_VERTEX_SIZE);
	(*graphic) -> vertex_count = 0;
	(*graphic) -> arc_count = 0;

	int i = 0;
	for (i = 0; i < MAX_VERTEX_SIZE; i++) {
		((*graphic) -> vertex_list)[i].is_empty = TRUE;
		((*graphic) -> vertex_list)[i].arc_list = NULL;
	}

	return OK;
}

Status Destory(GRAPHIC_TYPE* graphic) {
	int i = 0;
	ArcNode *node = NULL;

	for (i = 0; i < MAX_VERTEX_SIZE; i++) {
		node = ((*graphic) -> vertex_list + i) -> arc_list;
		while (node != NULL) {
			remove_arc_node(*graphic, node);
			node =  ((*graphic) -> vertex_list + i) -> arc_list;
		}
	}

	free((*graphic) -> vertex_list);
	free(*graphic);

	*graphic = NULL;
	return OK;
}

Status Create(GRAPHIC_TYPE* graphic, Graphic* definition) {
	int i = 0;
	for (i = 0; i < definition -> vertex_length; i++) {
		((*graphic) -> vertex_list)[i].is_empty = FALSE;
		((*graphic) -> vertex_list)[i].value = *(definition -> vertex_list + i);
	}

	ArcNode *arc_node = NULL;
	for (i = 0; i < definition -> arc_length; i++) {
		Arc	*arc = definition -> arc_list + i;
		int start_vertex_index = get_vertex_index_by_value(*graphic, arc -> start_vertex);
		int end_vertex_index = get_vertex_index_by_value(*graphic, arc -> end_vertex);

		AdjacentMultipleListGraphicVertex *start_vertex = (*graphic) -> vertex_list + start_vertex_index;
		AdjacentMultipleListGraphicVertex *end_vertex = (*graphic) -> vertex_list + end_vertex_index;

		arc_node = (ArcNode*)malloc(sizeof(ArcNode));
		arc_node -> start_vertex_index = start_vertex_index;
		arc_node -> end_vertex_index = end_vertex_index;
		arc_node -> start_link_next = start_vertex -> arc_list;
		arc_node -> end_link_next = end_vertex -> arc_list;
		arc_node -> weight = arc -> weight;

		start_vertex -> arc_list = arc_node;
		end_vertex -> arc_list = arc_node;
	}

	(*graphic) -> vertex_count = definition -> vertex_length;
	(*graphic) -> arc_count = definition -> arc_length;
	return OK;
}

VERTEX_TYPE* GetVertex(GRAPHIC_TYPE graphic, ElementType value) {
	int vertex_index = get_vertex_index_by_value(graphic, value);
	return vertex_index == -1 ? NULL : graphic -> vertex_list + vertex_index;
}

ElementType Value(GRAPHIC_TYPE graphic, VERTEX_TYPE* vertex) {
	return vertex == NULL ? 0 : vertex -> value;
}

Status Assign(GRAPHIC_TYPE* graphic, VERTEX_TYPE* vertex, ElementType value) {
	vertex -> value = value;
	return OK;
}

VERTEX_TYPE* FirstAdjacentVertex(GRAPHIC_TYPE graphic, VERTEX_TYPE* vertex) {
	return NextAdjacentVertex(graphic, vertex, NULL);
}

VERTEX_TYPE* NextAdjacentVertex(GRAPHIC_TYPE graphic, VERTEX_TYPE* vertex, VERTEX_TYPE* adjacent_vertex) {
	AdjacentMultipleListGraphicVertex *result = NULL;
	ArcNode *arc_node = vertex -> arc_list;
	int vertex_index = vertex - graphic -> vertex_list;

	while (arc_node != NULL) {
		AdjacentMultipleListGraphicVertex *v = arc_node -> start_vertex_index == vertex_index ?
		   graphic -> vertex_list + arc_node -> end_vertex_index :
		   graphic -> vertex_list + arc_node -> start_vertex_index;

		if (adjacent_vertex != NULL && v -> value <= adjacent_vertex -> value) {
			arc_node = arc_node -> start_vertex_index == vertex_index ? 
				arc_node -> start_link_next : arc_node -> end_link_next;
			continue;
		}

		if (result == NULL || v -> value < result -> value)
			result = v;

		arc_node = arc_node -> start_vertex_index == vertex_index ? 
			arc_node -> start_link_next : arc_node -> end_link_next;
	}
	return result;
}

Status InsertVertex(GRAPHIC_TYPE* graphic, ElementType value, VERTEX_TYPE** vertex) {
	int i = 0;
	for (i = 0; i < MAX_VERTEX_SIZE; i++) {
		if (((*graphic) -> vertex_list + i) -> is_empty == FALSE) 
			continue;

		((*graphic) -> vertex_list + i) -> is_empty = FALSE;
		((*graphic) -> vertex_list + i) -> value = value;
		((*graphic) -> vertex_count)++;
		
		*vertex = (*graphic) -> vertex_list + i;
		return OK;
	}
	return OK;
}

Status DeleteVertex(GRAPHIC_TYPE* graphic, VERTEX_TYPE** vertex) {
	ArcNode *arc_node = NULL;

    arc_node = (*vertex) -> arc_list;
	while (arc_node != NULL) {
		remove_arc_node(*graphic, arc_node);
		arc_node = (*vertex) -> arc_list;
		(*graphic) -> arc_count--;
	}

	(*vertex) -> is_empty = TRUE;
	(*vertex) -> arc_list = NULL;
	(*graphic) -> vertex_count--;

	*vertex = NULL;
	return OK;
}

Status InsertArc(GRAPHIC_TYPE* graphic, VERTEX_TYPE* start_vertex, VERTEX_TYPE* end_vertex, int weight) {
	int start_vertex_index = start_vertex - (*graphic) -> vertex_list;
	int end_vertex_index = end_vertex - (*graphic) -> vertex_list;

	ArcNode *arc_node = get_arc_node(*graphic, start_vertex_index, end_vertex_index);
	if (arc_node != NULL) {
		remove_arc_node(*graphic, arc_node);
		(*graphic) -> arc_count--;
	}

	arc_node = (ArcNode*)malloc(sizeof(ArcNode));
	arc_node -> start_vertex_index = start_vertex_index;
	arc_node -> end_vertex_index = end_vertex_index;
	arc_node -> start_link_next = start_vertex -> arc_list;
	arc_node -> end_link_next = end_vertex -> arc_list;
	arc_node -> weight = weight;
	
	start_vertex -> arc_list = arc_node;
	end_vertex -> arc_list = arc_node;

	(*graphic) -> arc_count++;
	return OK;
}

Status DeleteArc(GRAPHIC_TYPE* graphic, VERTEX_TYPE* start_vertex, VERTEX_TYPE* end_vertex) {
	int start_vertex_index = start_vertex - (*graphic) -> vertex_list;
	int end_vertex_index = end_vertex - (*graphic) -> vertex_list;

	ArcNode *arc_node = get_arc_node(*graphic, start_vertex_index, end_vertex_index);
	if (arc_node != NULL) {
		remove_arc_node(*graphic, arc_node);
		(*graphic) -> arc_count--;
	}
	return OK;
}

BOOLEAN is_marked(GRAPHIC_TYPE graphic, int* traverse_mark, int vertex_index) {
	int j = 0;
	for (j = 0; j < graphic -> vertex_count; j++) {
		if (traverse_mark[j] == vertex_index) {
			return TRUE;
		}
	}
	return FALSE;
}

void mark(int* traverse_mark, int vertex_index) {
	int i = 0;
	while (traverse_mark[i] != -1) {
		i++;
	}
	traverse_mark[i] = vertex_index;
}

int get_min_value_vertex_index(GRAPHIC_TYPE graphic, int* traverse_mark) {
	int i = 0;
	VERTEX_TYPE *min_vertex = NULL;

	for (i = 0; i < MAX_VERTEX_SIZE; i++) {
		VERTEX_TYPE *vertex = graphic -> vertex_list + i;
		if (vertex -> is_empty)
			continue;

		if (is_marked(graphic, traverse_mark, i)) {
			continue;
		}

		if (min_vertex == NULL || min_vertex -> value > vertex -> value) {
			min_vertex = vertex;
		}
	}

	return min_vertex == NULL ? -1 : min_vertex - graphic -> vertex_list;
}

Status DepthFirstTravese_Action(GRAPHIC_TYPE graphic, int* traverse_mark,
		int vertex_index, Status(*visit)(ElementType*)) {
	VERTEX_TYPE *vertex = graphic -> vertex_list + vertex_index;

	visit(&(vertex -> value));
	mark(traverse_mark, vertex_index);

	VERTEX_TYPE *adjacent_vertex = FirstAdjacentVertex(graphic, vertex);
	while (adjacent_vertex != NULL) {
		int adjacent_vertex_index = adjacent_vertex - graphic -> vertex_list;
		if (!is_marked(graphic, traverse_mark, adjacent_vertex_index))
			DepthFirstTravese_Action(graphic, traverse_mark, adjacent_vertex_index, visit);
		adjacent_vertex = NextAdjacentVertex(graphic, vertex, adjacent_vertex);
	}
	return OK;
}

Status DepthFirstTraverse(GRAPHIC_TYPE graphic, Status(*visit)(ElementType*)) {
	int *traverse_mark = (int*)malloc(sizeof(int) * graphic -> vertex_count);
	int i = 0;
	for (i = 0; i < graphic -> vertex_count; i++)
		traverse_mark[i] = -1;

	int min_vertex_index = get_min_value_vertex_index(graphic, traverse_mark);
	while (min_vertex_index != -1) {
		DepthFirstTravese_Action(graphic, traverse_mark, min_vertex_index, visit);

		min_vertex_index = get_min_value_vertex_index(graphic, traverse_mark);
	}

	free(traverse_mark);
	return OK;
}

Status BreadthFirstTravese_Action(GRAPHIC_TYPE graphic, int* traverse_mark,
	int *mark_index, int *mark_length, Status(*visit)(ElementType*)) {
	while (*mark_index < *mark_length ) {

		VERTEX_TYPE *vertex = graphic -> vertex_list + traverse_mark[(*mark_index)++];

		visit(&(vertex -> value));

		VERTEX_TYPE *adjacent_vertex = FirstAdjacentVertex(graphic, vertex);
		while (adjacent_vertex != NULL) {
			int adjacent_vertex_index = adjacent_vertex - graphic -> vertex_list;
			if (!is_marked(graphic, traverse_mark, adjacent_vertex_index))
				traverse_mark[(*mark_length)++] = adjacent_vertex_index;
			adjacent_vertex = NextAdjacentVertex(graphic, vertex, adjacent_vertex);
		}
	}
	return OK;
}

Status BreadthFirstTraverse(GRAPHIC_TYPE graphic, Status(*visit)(ElementType*)) {
	int *traverse_mark = (int*)malloc(sizeof(int) * graphic -> vertex_count);
	int i = 0;
	for (i = 0; i < graphic -> vertex_count; i++)
		traverse_mark[i] = -1;

	int min_vertex_index = get_min_value_vertex_index(graphic, traverse_mark);
	int mark_index = 0, mark_length = 0;
	while (min_vertex_index != -1) {
		traverse_mark[mark_length++] = min_vertex_index;

		BreadthFirstTravese_Action(graphic, traverse_mark, &mark_index, &mark_length, visit);

		min_vertex_index = get_min_value_vertex_index(graphic, traverse_mark);
	}

	free(traverse_mark);
	return OK;
}

int Degree(GRAPHIC_TYPE graphic, VERTEX_TYPE* vertex) {
	ArcNode *arc_node = vertex -> arc_list;
	int count = 0;
	int vertex_index = vertex - graphic -> vertex_list;

	while (arc_node) {
		count++;
		arc_node = arc_node -> start_vertex_index == vertex_index ? 
			arc_node -> start_link_next : arc_node -> end_link_next;
	}

	return count;
}

void result_insert_arc(
		AdjacentMultipleListGraphic graphic,
		int start_vertex_index,
		int end_vertex_index,
		int weight,
		AdjacentMultipleListGraphic* result) {
	ElementType start_vertex_value = (graphic -> vertex_list + start_vertex_index) -> value;
	ElementType end_vertex_value = (graphic -> vertex_list + end_vertex_index) -> value;

	AdjacentMultipleListGraphicVertex* start_vertex = GetVertex(*result, start_vertex_value);
	AdjacentMultipleListGraphicVertex* end_vertex = GetVertex(*result, end_vertex_value);
	if (start_vertex == NULL)
		InsertVertex(result, start_vertex_value, &start_vertex);
	if (end_vertex == NULL)
		InsertVertex(result, end_vertex_value, &end_vertex);

	InsertArc(result, start_vertex, end_vertex, weight);
}

void mini_span_tree_prim_calculate_min_weight_arc(
		AdjacentMultipleListGraphic graphic,
		int* mark,
		int* start_vertex_index,
		int* end_vertex_index,
		int* weight) {
	int i = 0;
	ArcNode *arc_node = NULL;
	*weight = -1;

	for (i = 0; i < graphic -> vertex_count; i++) {
		arc_node = (graphic -> vertex_list + i) -> arc_list;
		while (arc_node) {
			int s_vertex_index = i;
			int e_vertex_index = arc_node -> start_vertex_index == i ? 
				arc_node -> end_vertex_index : arc_node -> start_vertex_index;
			ArcNode *next_node = arc_node -> start_vertex_index == i ?
				arc_node -> start_link_next : arc_node -> end_link_next;

			if (mark != NULL) {
				if (!is_marked(graphic, mark, i) || is_marked(graphic, mark, e_vertex_index)) {
					arc_node = next_node;
					continue;
				}
			}

			if (*weight == -1 || arc_node -> weight < *weight) {
				*start_vertex_index = s_vertex_index;
				*end_vertex_index = e_vertex_index;
				*weight = arc_node -> weight;
			}
			arc_node = next_node;
		}
	}
}

Status MiniSpanTree_Prim(GRAPHIC_TYPE graphic, GRAPHIC_TYPE* result) {
	Initial(result);

	int *mark = (int*)malloc(sizeof(int) * graphic -> vertex_count);
	int i = 0;

	for (i = 0; i < graphic -> vertex_count; i++)
		mark[i] = -1;
	
	int start_vertex_index = -1, end_vertex_index = -1, weight = -1;
	mini_span_tree_prim_calculate_min_weight_arc(graphic, NULL, &start_vertex_index, &end_vertex_index, &weight);
	result_insert_arc(graphic, start_vertex_index, end_vertex_index, weight, result);
	mark[0] = start_vertex_index;
	mark[1] = end_vertex_index;

	for (i = 2; i < graphic -> vertex_count; i++) {
		mini_span_tree_prim_calculate_min_weight_arc(graphic, mark, &start_vertex_index, &end_vertex_index, &weight);
		result_insert_arc(graphic, start_vertex_index, end_vertex_index, weight, result);
		mark[i] = end_vertex_index;
	}
	return OK;
}

void mini_span_tree_kruskal_mark(int* mark, int vertex_count, int start_vertex_index, int end_vertex_index) {
	int i = 0;
	for (i = 0; i < vertex_count; i++) {
		if (mark[i * vertex_count + start_vertex_index] == 1) {
			start_vertex_index = i;
			break;
		}
	}
	for (i = 0; i < vertex_count; i++) {
		if (mark[i * vertex_count + end_vertex_index] == 1) {
			end_vertex_index = i;
			break;
		}
	}
	for (i = 0; i < vertex_count; i++) {
		mark[start_vertex_index * vertex_count + i] = 
			mark[end_vertex_index * vertex_count + i] == 1 ? 1 : mark[start_vertex_index * vertex_count + i];
		mark[end_vertex_index * vertex_count + i] = 0;
	}
}
BOOLEAN mini_span_tree_kruskal_is_connected(int* mark, int vertex_count, int start_vertex_index, int end_vertex_index) {
	int i = 0;
	for (i = 0; i < vertex_count; i++) {
		if (mark[i * vertex_count + start_vertex_index] == 1
				&& mark[i * vertex_count + end_vertex_index] == 1)
			return TRUE;
	}
	return FALSE;
}
void mini_span_tree_kruskal_calculate_min_weight_arc(
		AdjacentMultipleListGraphic graphic,
		int* mark,
		int* start_vertex_index,
		int* end_vertex_index,
		int* weight) {
	int i = 0;
	ArcNode *arc_node = NULL, *next_node = NULL;
	*weight = -1;

	for (i = 0; i < graphic -> vertex_count; i++) {
		arc_node = (graphic -> vertex_list + i) -> arc_list;
		while (arc_node) {
			int s_vertex_index = i;
			int e_vertex_index = arc_node -> start_vertex_index == i ? 
				arc_node -> end_vertex_index : arc_node -> start_vertex_index;
			next_node = arc_node -> start_vertex_index == i ?
				arc_node -> start_link_next : arc_node -> end_link_next;

			if (mini_span_tree_kruskal_is_connected(mark, graphic -> vertex_count, s_vertex_index, e_vertex_index)) {
				arc_node = next_node;
				continue;
			}

			if (*weight == -1 || arc_node -> weight < *weight) {
				*start_vertex_index = s_vertex_index;
				*end_vertex_index = e_vertex_index;
				*weight = arc_node -> weight;
			}
			arc_node = next_node;
		}
	}
}
Status MiniSpanTree_Kruskal(GRAPHIC_TYPE graphic, GRAPHIC_TYPE* result) {
	Initial(result);

	int vertex_count = graphic -> vertex_count;
	int *mark = (int*)malloc(sizeof(int) * vertex_count * vertex_count);
	int i = 0;

	for (i = 0; i < vertex_count * vertex_count; i++)
		mark[i] = i / vertex_count == i % vertex_count ? 1 : 0;
	
	int start_vertex_index = -1, end_vertex_index = -1, weight = -1;
	for (i = 0; i < graphic -> vertex_count - 1; i++) {
		mini_span_tree_kruskal_calculate_min_weight_arc(graphic, mark, &start_vertex_index, &end_vertex_index, &weight);
		result_insert_arc(graphic, start_vertex_index, end_vertex_index, weight, result);
		mini_span_tree_kruskal_mark(mark, vertex_count, start_vertex_index, end_vertex_index);
	}
	return OK;
}

int* find_articul_visit_result;
int* find_articul_low_result;
int* find_articul_mark;

int find_articul_visit_result_index;
Status find_articul_visit_function(ElementType* element) {
	find_articul_visit_result[find_articul_visit_result_index++] = *element;
	return OK;
}
void find_articul_calculate_visit_result(AdjacentMultipleListGraphic graphic) {
	int i = 0;
	for (i = 0; i < graphic -> vertex_count; i++) {
		find_articul_visit_result[i] = get_vertex_index_by_value(graphic, find_articul_visit_result[i]);
	}
}
void find_articul_calculate_low_result(AdjacentMultipleListGraphic graphic) {
	int i = 0, j = 0;
	int vertex_count = graphic -> vertex_count;

	for (i = vertex_count - 1; i >= 0 ; i--) {
		find_articul_low_result[i] = i + 1;

		int vertex_index = find_articul_visit_result[i];
		AdjacentMultipleListGraphicVertex *vertex = graphic -> vertex_list + vertex_index;
		ArcNode *arc_node = vertex -> arc_list;
		while (arc_node) {
			int is_child = 1;
			int adjacent_vertex_index  = vertex_index == arc_node -> start_vertex_index ?
				arc_node -> end_vertex_index : arc_node -> start_vertex_index;
			ArcNode *next_node = vertex_index == arc_node -> start_vertex_index ?
				arc_node -> start_link_next : arc_node -> end_link_next;

			int adjacent_vertex_position = 0;
			for (j = 0; j < vertex_count; j++) {
				if (adjacent_vertex_index == find_articul_visit_result[j]) {
					is_child = j > i;
					adjacent_vertex_position = j;
					break;
				}
			}

			if (is_child) {
				if (find_articul_low_result[adjacent_vertex_position] < find_articul_low_result[i]) {
					find_articul_low_result[i] = find_articul_low_result[adjacent_vertex_position];
				}
			} else {
				if (adjacent_vertex_position + 1 < find_articul_low_result[i]) {
					find_articul_low_result[i] = adjacent_vertex_position + 1;
				}
			}

			arc_node = next_node;
		}
	}
}
void find_articul_make_mark(AdjacentMultipleListGraphic graphic) {
	int i = 0, j = 0;
	int vertex_count = graphic -> vertex_count;

	for (i = 0; i < vertex_count ; i++) {
		find_articul_mark[i] = 0;

		int vertex_index = find_articul_visit_result[i];
		AdjacentMultipleListGraphicVertex *vertex = graphic -> vertex_list + vertex_index;
		ArcNode *arc_node = vertex -> arc_list;
		while (arc_node) {
			int is_child = 1;
			int adjacent_vertex_index  = vertex_index == arc_node -> start_vertex_index ?
				arc_node -> end_vertex_index : arc_node -> start_vertex_index;
			ArcNode *next_node = vertex_index ==arc_node -> start_vertex_index ?
				arc_node -> start_link_next : arc_node -> end_link_next;

			int adjacent_vertex_position = 0;
			for (j = 0; j < vertex_count; j++) {
				if (adjacent_vertex_index == find_articul_visit_result[j]) {
					is_child = j > i;
					adjacent_vertex_position = j;
					break;
				}
			}

			if (!is_child) {
				arc_node = next_node;
				continue;
			}
			
			if (find_articul_low_result[adjacent_vertex_position] >= i + 1) {
				find_articul_mark[i] = 1;
				break;
			}

			arc_node = next_node;
		}
	}

}
void find_articul_build_result(GRAPHIC_TYPE graphic, ElementType** result, int* result_length) {
	int i = 0;
	int vertex_count = graphic -> vertex_count;
	*result_length = 0;
	for (i = 0; i < vertex_count; i++) {
		if (find_articul_mark[i]) {
			(*result_length)++;
		}
	}

	*result = (ElementType*)malloc(sizeof(ElementType) * (*result_length));
	int result_index = 0;
	while (result_index < *result_length) {
		(*result)[result_index] = -1;
		for (i = 0; i < vertex_count; i++) {
			if (!find_articul_mark[i]) 
				continue;

			ElementType value = (graphic -> vertex_list + find_articul_visit_result[i]) -> value;

			if (result_index == 0) {
				if ((*result)[result_index] == -1 || (*result)[result_index] > value)
					(*result)[result_index] = value;
			} else {
				if ((value > (*result)[result_index - 1]) && ((*result)[result_index] == -1 || (*result)[result_index] > value))
					(*result)[result_index] = value;
			}
		}
		result_index++;
	}
}
Status FindArticul(GRAPHIC_TYPE graphic, ElementType** result, int* result_length) {
	int vertex_count = graphic -> vertex_count;

	find_articul_visit_result_index = 0;
	find_articul_visit_result = (ElementType*)malloc(sizeof(ElementType) * vertex_count);
	find_articul_low_result = (ElementType*)malloc(sizeof(ElementType) * vertex_count);
	find_articul_mark = (ElementType*)malloc(sizeof(ElementType) * vertex_count);

	DepthFirstTraverse(graphic, find_articul_visit_function);
	find_articul_calculate_visit_result(graphic);
	find_articul_calculate_low_result(graphic);
	find_articul_make_mark(graphic);
	find_articul_build_result(graphic, result, result_length);

	free(find_articul_visit_result);
	free(find_articul_low_result);
	free(find_articul_make_mark);

	return OK;
}
