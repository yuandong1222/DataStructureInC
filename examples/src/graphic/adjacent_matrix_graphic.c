/*
 * adjacent_matrix_graphic.c
 *
 *  Created on: 2009-9-20
 *      Author: yuandong
 */

#include <stdlib.h>
#include <stdio.h>

#include "include/common.h"
#include "include/graphic/adjacent_matrix_graphic.h"
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

Status Initial(GRAPHIC_TYPE* graphic) {
	*graphic = (GRAPHIC_TYPE) malloc(sizeof(AdjacentMatrixGraphicHead));
	(*graphic) -> vertex_count = 0;
	(*graphic) -> arc_count = 0;

	int i = 0, j = 0;
	for (i = 0; i < MAX_VERTEX_SIZE; i++) {
		((*graphic) -> vertex_list)[i].is_empty = TRUE;
		for (j = 0; j < MAX_VERTEX_SIZE; j++) {
			((*graphic) -> arc_list)[i][j] = -1;
		}
	}
	return OK;
}

Status Destory(GRAPHIC_TYPE* graphic) {
	free(*graphic);
	*graphic = NULL;
	return OK;
}

Status Create(GRAPHIC_TYPE* graphic, Graphic* definition) {
	int i = 0;
	for (i = 0; i < definition -> vertex_length; i++) {
		((*graphic) -> vertex_list)[i].value = (definition -> vertex_list)[i];
		((*graphic) -> vertex_list)[i].is_empty = FALSE;
	}
	(*graphic) -> vertex_count = definition -> vertex_length;

	for (i = 0; i < definition -> arc_length; i++) {
		Arc	*arc = definition -> arc_list + i;
		int start_vertex_index = get_vertex_index_by_value(*graphic, arc -> start_vertex);
		int end_vertex_index = get_vertex_index_by_value(*graphic, arc -> end_vertex);

		((*graphic) -> arc_list)[start_vertex_index][end_vertex_index] = arc -> weight;
	}
	(*graphic) -> arc_count = definition -> arc_length;

	return OK;
}

VERTEX_TYPE* GetVertex(GRAPHIC_TYPE graphic, ElementType value) {
	int index = get_vertex_index_by_value(graphic, value);
	return index == -1 ? NULL : graphic -> vertex_list + index;
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

VERTEX_TYPE* NextAdjacentVertex(GRAPHIC_TYPE graphic, VERTEX_TYPE* vertex,
		VERTEX_TYPE* adjacent_vertex) {
	int vertex_index = vertex - graphic -> vertex_list;
	int i = 0;
	VERTEX_TYPE *result = NULL, *temp = NULL;

	for (i = 0; i < MAX_VERTEX_SIZE; i++) {
		if ((graphic -> arc_list)[vertex_index][i] == -1)
			continue;

		temp = graphic -> vertex_list + i;
		if(result == NULL || result -> value > temp -> value)
			if (adjacent_vertex == NULL || adjacent_vertex -> value < temp -> value)
				result = temp;
	}
	return result;
}

Status InsertVertex(GRAPHIC_TYPE* graphic, ElementType value, VERTEX_TYPE** vertex) {
	int i = 0;
	for (i = 0; i < MAX_VERTEX_SIZE; i++) {
		VERTEX_TYPE *temp = (*graphic) -> vertex_list + i;
		if(temp -> is_empty) {
			temp -> is_empty = FALSE;
			temp -> value = value;
			*vertex = temp;

			(*graphic) -> vertex_count++;
			return OK;
		}
	}
	return ERROR;
}

Status DeleteVertex(GRAPHIC_TYPE* graphic, VERTEX_TYPE** vertex) {
	int i = 0;
	int vertex_index = *vertex - (*graphic) -> vertex_list;
	for (i = 0; i < MAX_VERTEX_SIZE; i++) {
		if(((*graphic) -> arc_list)[vertex_index][i] != -1) {
			((*graphic) -> arc_list)[vertex_index][i] = -1;
			(*graphic) -> arc_count--;
		}
		if(((*graphic) -> arc_list)[i][vertex_index] != -1) {
			((*graphic) -> arc_list)[i][vertex_index] = -1;
			(*graphic) -> arc_count--;
		}
	}
	(*vertex) -> is_empty = TRUE;
	(*graphic) -> vertex_count--;

	*vertex = NULL;
	return OK;
}

Status InsertArc(GRAPHIC_TYPE* graphic, VERTEX_TYPE* start_vertex,
		VERTEX_TYPE* end_vertex, int weight) {
	int start_vertex_index = start_vertex - (*graphic) -> vertex_list;
	int end_vertex_index = end_vertex - (*graphic) -> vertex_list;

	if (((*graphic) -> arc_list)[start_vertex_index][end_vertex_index] == -1) {
		(*graphic) -> arc_count++;
	}
	((*graphic) -> arc_list)[start_vertex_index][end_vertex_index] = weight;

	return OK;
}

Status DeleteArc(GRAPHIC_TYPE* graphic, VERTEX_TYPE* start_vertex,
		VERTEX_TYPE* end_vertex) {
	int start_vertex_index = start_vertex - (*graphic) -> vertex_list;
	int end_vertex_index = end_vertex - (*graphic) -> vertex_list;

	if (((*graphic) -> arc_list)[start_vertex_index][end_vertex_index] == -1) {
		return OK;
	}

	((*graphic) -> arc_list)[start_vertex_index][end_vertex_index] = -1;
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

int InDegree(GRAPHIC_TYPE graphic, VERTEX_TYPE* vertex) {
	int in_degree = 0, i = 0;
	int vertex_index = vertex - graphic -> vertex_list;

	for (i = 0; i < MAX_VERTEX_SIZE; i++) {
		if ((graphic -> arc_list)[i][vertex_index] != -1) {
			in_degree++;
		}
	}
	return in_degree;
}

int OutDegree(GRAPHIC_TYPE graphic, VERTEX_TYPE* vertex) {
	int out_degree = 0, i = 0;
	int vertex_index = vertex - graphic -> vertex_list;

	for (i = 0; i < MAX_VERTEX_SIZE; i++) {
		if ((graphic -> arc_list)[vertex_index][i] != -1) {
			out_degree++;
		}
	}
	return out_degree;
}

int un_mark_in_degree(GRAPHIC_TYPE graphic, int* traverse_mark, int vertex_index) {
	int in_degree = 0, i = 0;

	for (i = 0; i < MAX_VERTEX_SIZE; i++) {
		if ((graphic -> arc_list)[i][vertex_index] != -1 && !is_marked(graphic, traverse_mark, i)) {
			in_degree++;
		}
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
		AdjacentMatrixGraphicVertex *vertex = GetVertex(graphic, vertex_value);
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

			int arc_weight = (graphic -> arc_list)[start_vertex_index][end_vertex_index];
			if (arc_weight == -1) {
				continue;
			}

			if (vertex_earliest_start_time[j] + arc_weight > vertex_earliest_start_time[i]) {
				vertex_earliest_start_time[i] = vertex_earliest_start_time[j] + arc_weight;
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

			int arc_weight = (graphic -> arc_list)[start_vertex_index][end_vertex_index];
			if (arc_weight == -1) {
				continue;
			}

			if (vertex_latest_start_time[i] == -1 || vertex_latest_start_time[j] - arc_weight < vertex_latest_start_time[i]) {
				vertex_latest_start_time[i] = vertex_latest_start_time[j] - arc_weight;
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
		AdjacentMatrixGraphicVertex *start_vertex = graphic -> vertex_list + i;
		if (start_vertex -> is_empty) {
			continue;
		}

		for (j = 0; j < MAX_VERTEX_SIZE; j++) {
			AdjacentMatrixGraphicVertex *end_vertex = graphic -> vertex_list + j;
			if (end_vertex -> is_empty) {
				continue;
			}

			int arc_weight = (graphic -> arc_list)[i][j];
			if (arc_weight == -1) {
				continue;
			}

			int m = 0, earliest_start_time = 0, latest_start_time = 0;
			for (m = 0; m < graphic -> vertex_count; m++) {
				if (topological_sort_result_index[m] == i) {
					earliest_start_time = vertex_earliest_start_time[m];
				}
				if (topological_sort_result_index[m] == j) {
					latest_start_time = vertex_latest_start_time[m] - arc_weight;
				}
			}

			if (earliest_start_time == latest_start_time) {
				result_insert_arc(result, start_vertex, end_vertex, arc_weight);
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

			int arc_weight = (graphic -> arc_list)[current_vertex_index][j];
			if (arc_weight == -1) {
				continue;
			}

			if (min_path_weight_dimension[j] == -1
					|| current_vertex_path_weight + arc_weight < min_path_weight_dimension[j]) {
				min_path_weight_dimension[j] = current_vertex_path_weight + arc_weight;
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
	free (min_path_weight_dimension);
	free (finish);
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

		(*result + count) -> end_vertex = (AdjacentMatrixGraphicVertex*)malloc(sizeof(AdjacentMatrixGraphicVertex));
		(*result + count) -> end_vertex -> is_empty = FALSE;
		(*result + count) -> end_vertex -> value = (graphic -> vertex_list)[i].value;

		AdjacentMatrixGraphic *result_graphic = &((*result + count) -> graphic);
		Initial(result_graphic);

		int start_vertex_index = vertex_index;
		for (j = 0; j < vertex_count; j++) {
			int end_vertex_index = path[i * vertex_count + j];
			if (end_vertex_index == -1) {
				continue;
			}

			AdjacentMatrixGraphicVertex *start_vertex = graphic -> vertex_list + start_vertex_index;
			AdjacentMatrixGraphicVertex *end_vertex = graphic -> vertex_list + end_vertex_index;
			int arc_weight = (graphic -> arc_list)[start_vertex_index][end_vertex_index];
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

