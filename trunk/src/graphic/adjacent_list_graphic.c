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
}

ArcNode* get_arc_node(GRAPHIC_TYPE graphic, int start_vertex_index, int end_vertex_index) {
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

VERTEX_TYPE* NextAdjacentVertex(GRAPHIC_TYPE graphic, VERTEX_TYPE* vertex, VERTEX_TYPE* adjacent_vertex) {
}

Status InsertVertex(GRAPHIC_TYPE* graphic, ElementType value, VERTEX_TYPE** vertex) {
}

void remove_arc_node(AdjacentListGraphicVertex* vertex, int vertex_index) {
}

Status DeleteVertex(GRAPHIC_TYPE* graphic, VERTEX_TYPE** vertex) {
}

Status InsertArc(GRAPHIC_TYPE* graphic, VERTEX_TYPE* start_vertex, VERTEX_TYPE* end_vertex, int weight) {
}

Status DeleteArc(GRAPHIC_TYPE* graphic, VERTEX_TYPE* start_vertex, VERTEX_TYPE* end_vertex) {
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

int Degree(GRAPHIC_TYPE graphic, VERTEX_TYPE* vertex) {
}
void result_insert_arc(
		AdjacentListGraphic graphic,
		int start_vertex_index,
		int end_vertex_index,
		int weight,
		AdjacentListGraphic* result) {
}

void mini_span_tree_prim_calculate_min_weight_arc(
		AdjacentListGraphic graphic,
		int* mark,
		int* start_vertex_index,
		int* end_vertex_index,
		int* weight) {
}

Status MiniSpanTree_Prim(GRAPHIC_TYPE graphic, GRAPHIC_TYPE* result) {
}

void mini_span_tree_kruskal_mark(int* mark, int vertex_count, int start_vertex_index, int end_vertex_index) {
}
BOOLEAN mini_span_tree_kruskal_is_connected(int* mark, int vertex_count, int start_vertex_index, int end_vertex_index) {
}
void mini_span_tree_kruskal_calculate_min_weight_arc(
		AdjacentListGraphic graphic,
		int* mark,
		int* start_vertex_index,
		int* end_vertex_index,
		int* weight) {
}
Status MiniSpanTree_Kruskal(GRAPHIC_TYPE graphic, GRAPHIC_TYPE* result) {
}

int* find_articul_visit_result;
int* find_articul_low_result;
int* find_articul_mark;

int find_articul_visit_result_index;
Status find_articul_visit_function(ElementType* element) {
}
void find_articul_calculate_visit_result(AdjacentListGraphic graphic) {
}
void find_articul_calculate_low_result(AdjacentListGraphic graphic) {
}
void find_articul_make_mark(AdjacentListGraphic graphic) {
}
void find_articul_build_result(GRAPHIC_TYPE graphic, ElementType** result, int* result_length) {
}
Status FindArticul(GRAPHIC_TYPE graphic, ElementType** result, int* result_length) {
}
