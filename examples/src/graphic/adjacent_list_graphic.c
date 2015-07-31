/*
 * adjacent_list_graphic.c
 *
 *  Created on; 2009-9-23
 *      Author; yuandong
 */

#include <stdlib.h>
#include <stdio.h>

#include "include/common.h"
#include "include/graphic/adjacent_list_graphic.h"
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
	AdjacentListGraphicVertex *start_vertex = graphic -> vertex_list + start_vertex_index;
	ArcNode *arc_node = start_vertex -> arc_list;
	while (arc_node != NULL && arc_node -> vertex_index != end_vertex_index) {
		arc_node = (ArcNode*)(arc_node -> next);
	}
	return arc_node;
}

Status Initial(GRAPHIC_TYPE* graphic) {
	*graphic = (GRAPHIC_TYPE)malloc(sizeof(AdjacentListGraphicHead));
	(*graphic) -> vertex_list = (AdjacentListGraphicVertex*)malloc(sizeof(AdjacentListGraphicVertex) * MAX_VERTEX_SIZE);
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
	ArcNode *node = NULL, *next_node = NULL;

	for (i = 0; i < MAX_VERTEX_SIZE; i++) {
		node = ((*graphic) -> vertex_list + i) -> arc_list;
		while (node != NULL) {
			next_node = (ArcNode*)(node -> next);
			free(node);
			node = next_node;
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
	AdjacentListGraphicVertex *vertex = NULL;
	for (i = 0; i < definition -> arc_length; i++) {
		Arc	*arc = definition -> arc_list + i;
		int start_vertex_index = get_vertex_index_by_value(*graphic, arc -> start_vertex);
		int end_vertex_index = get_vertex_index_by_value(*graphic, arc -> end_vertex);

		vertex = (*graphic) -> vertex_list + start_vertex_index;
		arc_node = (ArcNode*)malloc(sizeof(ArcNode));
		arc_node -> vertex_index = end_vertex_index;
		arc_node -> weight = arc -> weight;
		arc_node -> next = vertex -> arc_list;
		vertex -> arc_list = arc_node;

		vertex = (*graphic) -> vertex_list + end_vertex_index;
		arc_node = (ArcNode*)malloc(sizeof(ArcNode));
		arc_node -> vertex_index = start_vertex_index;
		arc_node -> weight = arc -> weight;
		arc_node -> next = vertex -> arc_list;
		vertex -> arc_list = arc_node;
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
	AdjacentListGraphicVertex *result = NULL;
	ArcNode *arc_node = vertex -> arc_list;
	while (arc_node != NULL) {
		AdjacentListGraphicVertex *v = graphic -> vertex_list + arc_node -> vertex_index;
		if (result == NULL || v -> value < result -> value)
			result = v;

		arc_node = arc_node -> next;
	}

	return result;
}

VERTEX_TYPE* NextAdjacentVertex(GRAPHIC_TYPE graphic, VERTEX_TYPE* vertex, VERTEX_TYPE* adjacent_vertex) {
	AdjacentListGraphicVertex *result = NULL;
	ArcNode *arc_node = vertex -> arc_list;
	while (arc_node != NULL) {
		AdjacentListGraphicVertex *v = graphic -> vertex_list + arc_node -> vertex_index;

		if (v -> value <= adjacent_vertex -> value) {
			arc_node = arc_node -> next;
			continue;
		}

		if (result == NULL || v -> value < result -> value)
			result = v;

		arc_node = arc_node -> next;
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

void remove_arc_node(AdjacentListGraphicVertex* vertex, int vertex_index) {
	ArcNode *arc_node = NULL, *pre_node = NULL;
	if (vertex -> arc_list == NULL)
		return;

	if (vertex -> arc_list -> vertex_index == vertex_index) {
		arc_node = vertex -> arc_list;
		vertex -> arc_list = arc_node -> next;
	} else {
		pre_node = vertex -> arc_list;
		while (pre_node && pre_node -> next && pre_node -> next -> vertex_index != vertex_index)
			pre_node = pre_node -> next;
		if(pre_node -> next == NULL)
			return;
		
		arc_node = pre_node -> next;
		pre_node -> next = arc_node -> next;
	}
	free(arc_node);
}

Status DeleteVertex(GRAPHIC_TYPE* graphic, VERTEX_TYPE** vertex) {
	int vertex_index = *vertex - (*graphic) -> vertex_list;
	ArcNode *arc_node = (*vertex) -> arc_list, *next_arc_node = NULL;
	while (arc_node != NULL) {
		next_arc_node = arc_node -> next;

		AdjacentListGraphicVertex *adjacent_vertex = (*graphic) -> vertex_list + arc_node -> vertex_index;
		remove_arc_node(adjacent_vertex, vertex_index);

		free(arc_node);
		(*graphic) -> arc_count--;

		arc_node = next_arc_node;
	}

	(*vertex) -> is_empty = TRUE;
	(*vertex) -> arc_list = NULL;
	(*graphic) -> vertex_count--;

	*vertex = NULL;
	return OK;
}

Status InsertArc(GRAPHIC_TYPE* graphic, VERTEX_TYPE* start_vertex, VERTEX_TYPE* end_vertex, int weight) {
	AdjacentListGraphicVertex *vertex = NULL;
	ArcNode *arc_node = NULL;
	int start_vertex_index = start_vertex - (*graphic) -> vertex_list;
	int end_vertex_index = end_vertex - (*graphic) -> vertex_list;

	if (get_arc_node(*graphic, start_vertex_index, end_vertex_index) == NULL)
		(*graphic) -> arc_count++;

	remove_arc_node(start_vertex, end_vertex_index);
	remove_arc_node(end_vertex,	start_vertex_index);

	vertex = start_vertex;
	arc_node = (ArcNode*)malloc(sizeof(ArcNode));
	arc_node -> vertex_index = end_vertex_index;
	arc_node -> weight = weight;
	arc_node -> next = vertex -> arc_list;
	vertex -> arc_list = arc_node;

	vertex = end_vertex;
	arc_node = (ArcNode*)malloc(sizeof(ArcNode));
	arc_node -> vertex_index = start_vertex_index;
	arc_node -> weight = weight;
	arc_node -> next = vertex -> arc_list;
	vertex -> arc_list = arc_node;

	return OK;
}

Status DeleteArc(GRAPHIC_TYPE* graphic, VERTEX_TYPE* start_vertex, VERTEX_TYPE* end_vertex) {
	int start_vertex_index = start_vertex - (*graphic) -> vertex_list;
	int end_vertex_index = end_vertex - (*graphic) -> vertex_list;

	remove_arc_node(start_vertex, end_vertex_index);
	remove_arc_node(end_vertex,	start_vertex_index);

	(*graphic) -> arc_count--;
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

	while (arc_node) {
		count++;
		arc_node = arc_node -> next;
	}

	return count;
}
void result_insert_arc(
		AdjacentListGraphic graphic,
		int start_vertex_index,
		int end_vertex_index,
		int weight,
		AdjacentListGraphic* result) {
	ElementType start_vertex_value = (graphic -> vertex_list + start_vertex_index) -> value;
	ElementType end_vertex_value = (graphic -> vertex_list + end_vertex_index) -> value;

	AdjacentListGraphicVertex* start_vertex = GetVertex(*result, start_vertex_value);
	AdjacentListGraphicVertex* end_vertex = GetVertex(*result, end_vertex_value);
	if (start_vertex == NULL)
		InsertVertex(result, start_vertex_value, &start_vertex);
	if (end_vertex == NULL)
		InsertVertex(result, end_vertex_value, &end_vertex);

	InsertArc(result, start_vertex, end_vertex, weight);
}

void mini_span_tree_prim_calculate_min_weight_arc(
		AdjacentListGraphic graphic,
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
			if (mark != NULL) {
				if (!is_marked(graphic, mark, i) || is_marked(graphic, mark, arc_node -> vertex_index)) {
					arc_node = arc_node -> next;
					continue;
				}
			}

			if (*weight == -1 || arc_node -> weight < *weight) {
				*start_vertex_index = i;
				*end_vertex_index = arc_node -> vertex_index;
				*weight = arc_node -> weight;
			}
			arc_node = arc_node -> next;
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
		AdjacentListGraphic graphic,
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
			if (mini_span_tree_kruskal_is_connected(mark, graphic -> vertex_count, i, arc_node -> vertex_index)) {
				arc_node = arc_node -> next;
				continue;
			}

			if (*weight == -1 || arc_node -> weight < *weight) {
				*start_vertex_index = i;
				*end_vertex_index = arc_node -> vertex_index;
				*weight = arc_node -> weight;
			}
			arc_node = arc_node -> next;
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
void find_articul_calculate_visit_result(AdjacentListGraphic graphic) {
	int i = 0;
	for (i = 0; i < graphic -> vertex_count; i++) {
		find_articul_visit_result[i] = get_vertex_index_by_value(graphic, find_articul_visit_result[i]);
	}
}
void find_articul_calculate_low_result(AdjacentListGraphic graphic) {
	int i = 0, j = 0;
	int vertex_count = graphic -> vertex_count;

	for (i = vertex_count - 1; i >= 0 ; i--) {
		find_articul_low_result[i] = i + 1;

		AdjacentListGraphicVertex *vertex = graphic -> vertex_list + find_articul_visit_result[i];
		ArcNode *arc_node = vertex -> arc_list;
		while (arc_node) {
			int is_child = 1;
			int adjacent_vertex_index  = arc_node -> vertex_index;
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

			arc_node = arc_node -> next;
		}
	}
}
void find_articul_make_mark(AdjacentListGraphic graphic) {
	int i = 0, j = 0;
	int vertex_count = graphic -> vertex_count;

	for (i = 0; i < vertex_count ; i++) {
		find_articul_mark[i] = 0;

		AdjacentListGraphicVertex *vertex = graphic -> vertex_list + find_articul_visit_result[i];
		ArcNode *arc_node = vertex -> arc_list;
		while (arc_node) {
			int is_child = 1;
			int adjacent_vertex_index  = arc_node -> vertex_index;
			int adjacent_vertex_position = 0;
			for (j = 0; j < vertex_count; j++) {
				if (adjacent_vertex_index == find_articul_visit_result[j]) {
					is_child = j > i;
					adjacent_vertex_position = j;
					break;
				}
			}

			if (!is_child) {
				arc_node = arc_node -> next;
				continue;
			}
			
			if (find_articul_low_result[adjacent_vertex_position] >= i + 1) {
				find_articul_mark[i] = 1;
				break;
			}

			arc_node = arc_node -> next;
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
