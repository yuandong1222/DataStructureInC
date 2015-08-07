/*
 * orghogonal_list_graphic.c
 *
 *  Created on: 2009-10-19
 *      Author: yuandong
 */

#include <stdlib.h>
#include <stdio.h>

#include "include/common.h"
#include "include/graphic/orthogonal_list_graphic.h"
#include "include/graphic/directed_graphic.h"

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
	OrthogonalListGraphicVertex *start_vertex = graphic -> vertex_list + start_vertex_index;
	ArcNode *arc_node = start_vertex -> start_link_list;
	while (arc_node != NULL && arc_node -> end_vertex_index != end_vertex_index) {
		arc_node = (ArcNode*)(arc_node -> start_link_next);
	}
	return arc_node;
}


Status Initial(GRAPHIC_TYPE* graphic) {

	*graphic = (GRAPHIC_TYPE)malloc(sizeof(OrthogonalListGraphicHead));
	(*graphic) -> vertex_list = (OrthogonalListGraphicVertex*)malloc(sizeof(OrthogonalListGraphicVertex) * MAX_VERTEX_SIZE);
	(*graphic) -> vertex_count = 0;
	(*graphic) -> arc_count = 0;

	int i = 0;
	for (i = 0; i < MAX_VERTEX_SIZE; i++) {
		((*graphic) -> vertex_list)[i].is_empty = TRUE;
		((*graphic) -> vertex_list)[i].start_link_list = NULL;
		((*graphic) -> vertex_list)[i].end_link_list = NULL;
	}

	return OK;
}

Status Destory(GRAPHIC_TYPE* graphic) {
	int i = 0;
	ArcNode *node = NULL, *next_node = NULL;

	for (i = 0; i < MAX_VERTEX_SIZE; i++) {
		node = ((*graphic) -> vertex_list + i) -> start_link_list;
		while (node != NULL) {
			next_node = (ArcNode*)(node -> start_link_next);
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
	for (i = 0; i < definition -> arc_length; i++) {
		Arc	*arc = definition -> arc_list + i;
		int start_vertex_index = get_vertex_index_by_value(*graphic, arc -> start_vertex);
		int end_vertex_index = get_vertex_index_by_value(*graphic, arc -> end_vertex);

		OrthogonalListGraphicVertex *start_vertex = (*graphic) -> vertex_list + start_vertex_index;
		OrthogonalListGraphicVertex *end_vertex = (*graphic) -> vertex_list + end_vertex_index;

		arc_node = (ArcNode*)malloc(sizeof(ArcNode));
		arc_node -> start_vertex_index = start_vertex_index;
		arc_node -> end_vertex_index = end_vertex_index;
		arc_node -> start_link_next = start_vertex -> start_link_list;
		arc_node -> end_link_next = end_vertex -> end_link_list;
		arc_node -> weight = arc -> weight;
		
		start_vertex -> start_link_list = arc_node;
		end_vertex -> end_link_list = arc_node;
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
	OrthogonalListGraphicVertex *result = NULL;
	ArcNode *arc_node = vertex -> start_link_list;
	while (arc_node != NULL) {
		OrthogonalListGraphicVertex *v = graphic -> vertex_list + arc_node -> end_vertex_index;

		if (adjacent_vertex != NULL && v -> value <= adjacent_vertex -> value) {
			arc_node = arc_node -> start_link_next;
			continue;
		}

		if (result == NULL || v -> value < result -> value)
			result = v;

		arc_node = arc_node -> start_link_next;
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
void remove_arc_node(OrthogonalListGraphic graphic, ArcNode* arc_node) {
	ArcNode *node = NULL;
	OrthogonalListGraphicVertex *start_vertex = graphic -> vertex_list + arc_node -> start_vertex_index;
	OrthogonalListGraphicVertex *end_vertex = graphic -> vertex_list + arc_node -> end_vertex_index;

	if (start_vertex -> start_link_list == arc_node) {
		start_vertex -> start_link_list = arc_node -> start_link_next;
	} else {
		node = start_vertex -> start_link_list;
		while (node != NULL && node -> start_link_next != NULL && node -> start_link_next != arc_node)
			node = node -> start_link_next;
		if (node -> start_link_next == arc_node)
			node -> start_link_next = arc_node -> start_link_next;
	}
	if (end_vertex -> end_link_list == arc_node) {
		end_vertex -> end_link_list = arc_node -> end_link_next;
	} else {
		node = end_vertex -> end_link_list;
		while (node != NULL && node -> end_link_next != NULL && node -> end_link_next != arc_node)
			node = node -> end_link_next;
		if (node -> end_link_next == arc_node)
			node -> end_link_next = arc_node -> end_link_next;
	}
	free(arc_node);
}

Status DeleteVertex(GRAPHIC_TYPE* graphic, VERTEX_TYPE** vertex) {
	ArcNode *arc_node = NULL, *next_arc_node = NULL;

    arc_node = (*vertex) -> start_link_list;
	while (arc_node != NULL) {
		next_arc_node = arc_node -> start_link_next;
		remove_arc_node(*graphic, arc_node);
		arc_node = next_arc_node;
		(*graphic) -> arc_count--;
	}
    arc_node = (*vertex) -> end_link_list;
	while (arc_node != NULL) {
		next_arc_node = arc_node -> end_link_next;
		remove_arc_node(*graphic, arc_node);
		arc_node = next_arc_node;
		(*graphic) -> arc_count--;
	}

	(*vertex) -> is_empty = TRUE;
	(*vertex) -> start_link_list = NULL;
	(*vertex) -> end_link_list = NULL;
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
	arc_node -> start_link_next = start_vertex -> start_link_list;
	arc_node -> end_link_next = end_vertex -> end_link_list;
	arc_node -> weight = weight;
	
	start_vertex -> start_link_list = arc_node;
	end_vertex -> end_link_list = arc_node;

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

int InDegree(GRAPHIC_TYPE graphic, VERTEX_TYPE* vertex) {
	ArcNode *arc_node = vertex -> end_link_list;
	int count = 0;

	while (arc_node) {
		count++;
		arc_node = arc_node -> end_link_next;
	}

	return count;
}

int OutDegree(GRAPHIC_TYPE graphic, VERTEX_TYPE* vertex) {
	ArcNode *arc_node = vertex -> start_link_list;
	int count = 0;

	while (arc_node) {
		count++;
		arc_node = arc_node -> start_link_next;
	}

	return count;
}

int un_mark_in_degree(GRAPHIC_TYPE graphic, int* traverse_mark, int vertex_index) {
	OrthogonalListGraphicVertex *vertex = graphic -> vertex_list + vertex_index;
	ArcNode *arc_node = vertex -> end_link_list;
	int in_degree = 0;

	while (arc_node) {
		if (!is_marked(graphic, traverse_mark, arc_node -> start_vertex_index)) {
			in_degree++;
		}
		arc_node = arc_node -> end_link_next;
	}
	return in_degree;
}

int get_min_value_vertex_index_with_no_in_degree(GRAPHIC_TYPE graphic, int* traverse_mark) {
	int i = 0;
	VERTEX_TYPE *min_vertex = NULL;

	for (i = 0; i < MAX_VERTEX_SIZE; i++) {
		VERTEX_TYPE *vertex = graphic -> vertex_list + i;
		if (vertex -> is_empty)
			continue;

		if (is_marked(graphic, traverse_mark, i)) {
			continue;
		}

		if(un_mark_in_degree(graphic, traverse_mark, i) > 0 ) {
			continue;
		}

		if (min_vertex == NULL || min_vertex -> value > vertex -> value) {
			min_vertex = vertex;
		}
	}

	return min_vertex == NULL ? -1 : min_vertex - graphic -> vertex_list;
}

Status TopologicalSort(GRAPHIC_TYPE graphic, ElementType** result) {
	int *traverse_mark = (int*)malloc(sizeof(int) * graphic -> vertex_count);
	int i = 0;
	for (i = 0; i < graphic -> vertex_count; i++)
		traverse_mark[i] = -1;

	int min_vertex_index = get_min_value_vertex_index_with_no_in_degree(graphic, traverse_mark);
	int mark_length = 0;
	while (min_vertex_index != -1) {
		traverse_mark[mark_length++] = min_vertex_index;
		min_vertex_index = get_min_value_vertex_index_with_no_in_degree(graphic, traverse_mark);
	}

	*result = (ElementType*)malloc(sizeof(ElementType) * graphic -> vertex_count);
	for (i = 0; i < graphic -> vertex_count; i++) {
		(*result)[i] = (graphic -> vertex_list)[traverse_mark[i]].value;
	}

	free(traverse_mark);
	return OK;
}

void calculate_topological_sort_result_index(GRAPHIC_TYPE graphic,int* topological_sort_result_index) {
	ElementType *topological_sort_result;
	TopologicalSort(graphic, &topological_sort_result);

	int i = 0;
	for (i = 0; i < graphic -> vertex_count; i++) {
		int vertex_value = topological_sort_result[i];
		OrthogonalListGraphicVertex	*vertex = GetVertex(graphic, vertex_value);
		topological_sort_result_index[i] = vertex - graphic -> vertex_list;
	}

	free(topological_sort_result);
}

void calculate_vertex_earliest_start_time(
		GRAPHIC_TYPE graphic,
		int* topological_sort_result_index,
		int* vertex_earliest_start_time) {

	int i = 0, j = 0;
	vertex_earliest_start_time[0] = 0;
	for (i = 1; i < graphic -> vertex_count; i++) {
		for (j = 0; j < i; j++) {
			int start_vertex_index = topological_sort_result_index[j];
			int end_vertex_index = topological_sort_result_index[i];

			ArcNode *arc_node = get_arc_node(graphic, start_vertex_index, end_vertex_index);
			if (arc_node == NULL) {
				continue;
			}

			if (vertex_earliest_start_time[j] + arc_node -> weight > vertex_earliest_start_time[i]) {
				vertex_earliest_start_time[i] = vertex_earliest_start_time[j] + arc_node -> weight;
			}
		}
	}
}
void calculate_vertex_latest_start_time(
		GRAPHIC_TYPE graphic,
		int* topological_sort_result_index,
		int* vertex_latest_start_time) {

	int i = 0, j = 0;
	for (i = graphic -> vertex_count - 2; i >= 0; i--) {
		for (j = graphic -> vertex_count - 1; j > i; j--) {
			int start_vertex_index = topological_sort_result_index[i];
			int end_vertex_index = topological_sort_result_index[j];

			ArcNode *arc_node = get_arc_node(graphic, start_vertex_index, end_vertex_index);
			if (arc_node == NULL) {
				continue;
			}

			if (vertex_latest_start_time[i] == -1 || vertex_latest_start_time[j] - arc_node -> weight < vertex_latest_start_time[i]) {
				vertex_latest_start_time[i] = vertex_latest_start_time[j] - arc_node -> weight;
			}
		}
	}
}
void result_insert_arc(
		GRAPHIC_TYPE* graphic,
		VERTEX_TYPE* start_vertex,
		VERTEX_TYPE* end_vertex,
		int arc_weight) {
	VERTEX_TYPE* graphic_start_vertex = GetVertex(*graphic, start_vertex -> value);
	if (graphic_start_vertex == NULL) {
		InsertVertex(graphic, start_vertex -> value, &graphic_start_vertex);
	}
	VERTEX_TYPE* graphic_end_vertex = GetVertex(*graphic, end_vertex -> value);
	if (graphic_end_vertex == NULL) {
		InsertVertex(graphic, end_vertex -> value, &graphic_end_vertex);
	}
	InsertArc(graphic, graphic_start_vertex, graphic_end_vertex, arc_weight);
}

void calculate_critical_path_result(
		GRAPHIC_TYPE graphic,
		int* topological_sort_result_index,
		int* vertex_earliest_start_time,
		int* vertex_latest_start_time,
		GRAPHIC_TYPE* result) {

	int i = 0, j = 0;
	for (i = 0; i < MAX_VERTEX_SIZE; i++) {
		OrthogonalListGraphicVertex *start_vertex = graphic -> vertex_list + i;
		if (start_vertex -> is_empty) {
			continue;
		}

		for (j = 0; j < MAX_VERTEX_SIZE; j++) {
			OrthogonalListGraphicVertex *end_vertex = graphic -> vertex_list + j;
			if (end_vertex -> is_empty) {
				continue;
			}

			ArcNode *arc_node = get_arc_node(graphic, i, j);
			if (arc_node == NULL) {
				continue;
			}

			int m = 0, earliest_start_time = 0, latest_start_time = 0;
			for (m = 0; m < graphic -> vertex_count; m++) {
				if (topological_sort_result_index[m] == i) {
					earliest_start_time = vertex_earliest_start_time[m];
				}
				if (topological_sort_result_index[m] == j) {
					latest_start_time = vertex_latest_start_time[m] - arc_node -> weight;
				}
			}

			if (earliest_start_time == latest_start_time) {
				result_insert_arc(result, start_vertex, end_vertex, arc_node -> weight);
			}
		}
	}
}

Status CriticalPath(GRAPHIC_TYPE graphic, GRAPHIC_TYPE* result) {

	int i = 0;
	int vertex_count = graphic -> vertex_count;
	int *topological_sort_result_index = (int*)malloc(sizeof(int) * vertex_count),
		*vertex_earliest_start_time = (int*)malloc(sizeof(int) * vertex_count),
		*vertex_latest_start_time   = (int*)malloc(sizeof(int) * vertex_count);

	//initial
	for (i = 0; i < vertex_count; i++) {
		vertex_earliest_start_time[i] = -1;
		vertex_latest_start_time[i] = -1;
	}

	calculate_topological_sort_result_index(graphic, topological_sort_result_index);
	calculate_vertex_earliest_start_time(graphic, topological_sort_result_index, vertex_earliest_start_time);

	vertex_latest_start_time[vertex_count - 1] = vertex_earliest_start_time[vertex_count - 1];
	calculate_vertex_latest_start_time(graphic, topological_sort_result_index, vertex_latest_start_time);

	Initial(result);
	calculate_critical_path_result(graphic, topological_sort_result_index, vertex_earliest_start_time, vertex_latest_start_time, result);

	free(topological_sort_result_index);
	free(vertex_earliest_start_time);
	free(vertex_latest_start_time);

	return OK;
}

void shortest_path_initial_path(int vertex_count, int* path) {
	int i = 0, j = 0;
	for (i = 0; i < vertex_count; i++) {
		for (j = 0; j < vertex_count; j++) {
			path[i * vertex_count + j] = -1;
		}
	}
}

void shortest_path_calculate_path(GRAPHIC_TYPE graphic, VERTEX_TYPE* start_vertex, int* path) {
	int vertex_count = graphic -> vertex_count, i = 0, j = 0, m = 0;
	int start_vertex_index = start_vertex - graphic -> vertex_list;

	int* min_path_weight_dimension = (int*)malloc(sizeof(int) * vertex_count);
	int* finish = (int*)malloc(sizeof(int) * vertex_count);
	for (i = 0; i < vertex_count; i++) {
		min_path_weight_dimension[i] = -1;
		finish[i] = FALSE;
	}

	min_path_weight_dimension[start_vertex_index] = 0;
	finish[start_vertex_index] = TRUE;

	int current_vertex_index = start_vertex_index;
	int current_vertex_path_weight = 0;
	for (i = 0; i < vertex_count; i++) {
		for (j = 0; j < vertex_count; j++) {
			if (finish[j] == TRUE) {
				continue;
			}

			ArcNode *arc_node = get_arc_node(graphic, current_vertex_index, j);
			if (arc_node == NULL) {
				continue;
			}

			if (min_path_weight_dimension[j] == -1
					|| current_vertex_path_weight + arc_node -> weight < min_path_weight_dimension[j]) {
				min_path_weight_dimension[j] = current_vertex_path_weight + arc_node -> weight;
				//copy path
				for (m = 0; m < i; m++) {
					path[j * vertex_count + m] = path[current_vertex_index * vertex_count + m];
				}
				path[j * vertex_count + m] = j;
			}
		}

		current_vertex_path_weight = -1;
		current_vertex_index = -1;
		for (j = 0; j < vertex_count; j++) {
			if (finish[j] == TRUE) {
				continue;
			}
			if (current_vertex_path_weight == -1) {
				current_vertex_path_weight = min_path_weight_dimension[j];
				current_vertex_index = j;
				continue;
			}
			if (min_path_weight_dimension[j] == -1) {
				continue;
			}
			if (min_path_weight_dimension[j] < current_vertex_path_weight) {
				current_vertex_path_weight = min_path_weight_dimension[j];
				current_vertex_index = j;
			}
		}
                if (current_vertex_index != -1) {
		        finish[current_vertex_index] = TRUE;
                }
	}
	free(min_path_weight_dimension);
	free(finish);
}

void shortext_path_build_result(GRAPHIC_TYPE graphic, 
		VERTEX_TYPE *vertex, 
		int* path, 
		ShortestPathResultNode** result) {
	int i = 0, j = 0, count = 0;
	int vertex_count = graphic -> vertex_count;
	int vertex_index = vertex - graphic -> vertex_list;
	*result = (ShortestPathResultNode*)malloc(sizeof(ShortestPathResultNode) * vertex_count - 1);

	for (i = 0; i < vertex_count; i++) {
		if (i == vertex_index) {
			continue;
		}

		(*result + count) -> end_vertex = (OrthogonalListGraphicVertex*)malloc(sizeof(OrthogonalListGraphicVertex));
		(*result + count) -> end_vertex -> is_empty = FALSE;
		(*result + count) -> end_vertex -> value = (graphic -> vertex_list)[i].value;

		OrthogonalListGraphic *result_graphic = &((*result + count) -> graphic);
		Initial(result_graphic);

		int start_vertex_index = vertex_index;
		for (j = 0; j < vertex_count; j++) {
			int end_vertex_index = path[i * vertex_count + j];
			if (end_vertex_index == -1) {
				continue;
			}

			OrthogonalListGraphicVertex *start_vertex = graphic -> vertex_list + start_vertex_index;
			OrthogonalListGraphicVertex *end_vertex = graphic -> vertex_list + end_vertex_index;
			int arc_weight = get_arc_node(graphic, start_vertex_index, end_vertex_index) -> weight;
			result_insert_arc(result_graphic, start_vertex, end_vertex, arc_weight);

			start_vertex_index = end_vertex_index;
		}
		if (start_vertex_index == vertex_index) {
			Destory(result_graphic);
		}

		count++;
	}
}

Status ShortestPath(GRAPHIC_TYPE graphic, VERTEX_TYPE *vertex,
		ShortestPathResultNode** result) {
	int vertex_count = graphic -> vertex_count;
	int *path = (int*)malloc(sizeof(int) * vertex_count * vertex_count);

	shortest_path_initial_path(vertex_count, path);
	shortest_path_calculate_path(graphic, vertex, path);
	shortext_path_build_result(graphic, vertex, path, result);

	free(path);
	return OK;
}

