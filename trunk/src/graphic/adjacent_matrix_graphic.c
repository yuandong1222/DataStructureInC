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
}

Status Initial(GRAPHIC_TYPE* graphic) {
}

Status Destory(GRAPHIC_TYPE* graphic) {
}

Status Create(GRAPHIC_TYPE* graphic, Graphic* definition) {
}

VERTEX_TYPE* GetVertex(GRAPHIC_TYPE graphic, ElementType value) {
}

ElementType Value(GRAPHIC_TYPE graphic, VERTEX_TYPE* vertex) {
}

Status Assign(GRAPHIC_TYPE* graphic, VERTEX_TYPE* vertex, ElementType value) {
}

VERTEX_TYPE* FirstAdjacentVertex(GRAPHIC_TYPE graphic, VERTEX_TYPE* vertex) {
}

VERTEX_TYPE* NextAdjacentVertex(GRAPHIC_TYPE graphic, VERTEX_TYPE* vertex,
		VERTEX_TYPE* adjacent_vertex) {
}

Status InsertVertex(GRAPHIC_TYPE* graphic, ElementType value, VERTEX_TYPE** vertex) {
}

Status DeleteVertex(GRAPHIC_TYPE* graphic, VERTEX_TYPE** vertex) {
}

Status InsertArc(GRAPHIC_TYPE* graphic, VERTEX_TYPE* start_vertex,
		VERTEX_TYPE* end_vertex, int weight) {
}

Status DeleteArc(GRAPHIC_TYPE* graphic, VERTEX_TYPE* start_vertex,
		VERTEX_TYPE* end_vertex) {
}

BOOLEAN is_marked(GRAPHIC_TYPE graphic, int* traverse_mark, int vertex_index) {
}

void mark(int* traverse_mark, int vertex_index) {
}

int get_min_value_vertex_index(GRAPHIC_TYPE graphic, int* traverse_mark) {
}

Status DepthFirstTravese_Action(GRAPHIC_TYPE graphic, int* traverse_mark,
		int vertex_index, Status(*visit)(ElementType*)) {
}

Status DepthFirstTraverse(GRAPHIC_TYPE graphic, Status(*visit)(ElementType*)) {
}

Status BreadthFirstTravese_Action(GRAPHIC_TYPE graphic, int* traverse_mark,
		int *mark_index, int *mark_length, Status(*visit)(ElementType*)) {
}

Status BreadthFirstTraverse(GRAPHIC_TYPE graphic, Status(*visit)(ElementType*)) {
}

int InDegree(GRAPHIC_TYPE graphic, VERTEX_TYPE* vertex) {
}

int OutDegree(GRAPHIC_TYPE graphic, VERTEX_TYPE* vertex) {
}

int un_mark_in_degree(GRAPHIC_TYPE graphic, int* traverse_mark, int vertex_index) {
}

int get_min_value_vertex_index_with_no_in_degree(GRAPHIC_TYPE graphic, int* traverse_mark) {
}

Status TopologicalSort(GRAPHIC_TYPE graphic, ElementType** result) {
}

void calculate_topological_sort_result_index(GRAPHIC_TYPE graphic,int* topological_sort_result_index) {
}

void calculate_vertex_earliest_start_time(
		GRAPHIC_TYPE graphic,
		int* topological_sort_result_index,
		int* vertex_earliest_start_time) {
}
void calculate_vertex_latest_start_time(
		GRAPHIC_TYPE graphic,
		int* topological_sort_result_index,
		int* vertex_latest_start_time) {
}
void result_insert_arc(
		GRAPHIC_TYPE* graphic,
		VERTEX_TYPE* start_vertex,
		VERTEX_TYPE* end_vertex,
		int arc_weight) {
}

void calculate_critical_path_result(
		GRAPHIC_TYPE graphic,
		int* topological_sort_result_index,
		int* vertex_earliest_start_time,
		int* vertex_latest_start_time,
		GRAPHIC_TYPE* result) {
}

Status CriticalPath(GRAPHIC_TYPE graphic, GRAPHIC_TYPE* result) {
}

void shortest_path_initial_path(int vertex_count, int* path) {
}

void shortest_path_calculate_path(GRAPHIC_TYPE graphic, VERTEX_TYPE* start_vertex, int* path) {
}

void shortext_path_build_result(GRAPHIC_TYPE graphic, 
		VERTEX_TYPE *vertex, 
		int* path, 
		ShortestPathResultNode** result) {
}

Status ShortestPath(GRAPHIC_TYPE graphic, VERTEX_TYPE *vertex,
		ShortestPathResultNode** result) {
}

