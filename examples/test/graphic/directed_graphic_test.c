/*
 * directed_graphic_test.c
 *
 *  Created on: 2009-9-20
 *      Author: yuandong
 */

#include <stdlib.h>

#include "CUnit/Basic.h"
#include "CUnit/Console.h"
#include "CUnit/Automated.h"
#include "CUnit/TestDB.h"

#include "include/graphic/directed_graphic.h"
#include "test/graphic/graphic_test.c"

void test_FirstAdjacentVertex(void) {
	GRAPHIC_TYPE graphic = get_test_graphic("1:2|12,3|13; 2:3|23; 3;");
	if (graphic == NULL)
		return;

	VERTEX_TYPE *vertex = NULL, *adjacent_vertex = NULL;

	vertex = GetVertex(graphic, 1);
	adjacent_vertex = FirstAdjacentVertex(graphic, vertex);
	assert_vertex_equal(adjacent_vertex, 2);

	vertex = GetVertex(graphic, 2);
	adjacent_vertex = FirstAdjacentVertex(graphic, vertex);
	assert_vertex_equal(adjacent_vertex, 3);

	vertex = GetVertex(graphic, 3);
	adjacent_vertex = FirstAdjacentVertex(graphic, vertex);
	CU_ASSERT_PTR_NULL(adjacent_vertex);
}
void test_NextAdjacentVertex(void) {
	GRAPHIC_TYPE graphic = get_test_graphic("1:2|12,3|13; 2:3|23; 3;");
	if (graphic == NULL)
		return;

	VERTEX_TYPE *vertex = NULL, *adjacent_vertex = NULL, *next_adjacent_vertex =
			NULL;

	vertex = GetVertex(graphic, 1);
	adjacent_vertex = FirstAdjacentVertex(graphic, vertex);
	next_adjacent_vertex = NextAdjacentVertex(graphic, vertex, adjacent_vertex);
	assert_vertex_equal(next_adjacent_vertex, 3);

	vertex = GetVertex(graphic, 2);
	adjacent_vertex = FirstAdjacentVertex(graphic, vertex);
	next_adjacent_vertex = NextAdjacentVertex(graphic, vertex, adjacent_vertex);
	CU_ASSERT_PTR_NULL(next_adjacent_vertex);
}
void test_InsertArc(void) {
	GRAPHIC_TYPE graphic = get_test_graphic("1:2|12,3|13; 2:3|23; 3; 4;");
	if (graphic == NULL)
		return;
	Status status = ERROR;
	VERTEX_TYPE *start_vertex = NULL, *end_vertex = NULL;

	start_vertex = GetVertex(graphic, 3);
	end_vertex = GetVertex(graphic, 4);
	status = InsertArc(&graphic, start_vertex, end_vertex, 34);
	CU_ASSERT_EQUAL(status, OK);
	assert_graphic_equal(graphic, "1:2|12,3|13; 2:3|23; 3:4|34; 4;");

	start_vertex = GetVertex(graphic, 4);
	end_vertex = GetVertex(graphic, 3);
	status = InsertArc(&graphic, start_vertex, end_vertex, 43);
	CU_ASSERT_EQUAL(status, OK);
	assert_graphic_equal(graphic, "1:2|12,3|13; 2:3|23; 3:4|34; 4:3|43;");

	start_vertex = GetVertex(graphic, 4);
	end_vertex = GetVertex(graphic, 3);
	status = InsertArc(&graphic, start_vertex, end_vertex, 143);
	CU_ASSERT_EQUAL(status, OK);
	assert_graphic_equal(graphic, "1:2|12,3|13; 2:3|23; 3:4|34; 4:3|143;");
}
void test_DeleteArc(void) {
	GRAPHIC_TYPE graphic = get_test_graphic(
			"1:2|12,3|13; 2:3|23; 3:4|34; 4:3|43;");
	if (graphic == NULL)
		return;
	Status status = ERROR;
	VERTEX_TYPE *start_vertex = NULL, *end_vertex = NULL;

	start_vertex = GetVertex(graphic, 4);
	end_vertex = GetVertex(graphic, 3);
	status = DeleteArc(&graphic, start_vertex, end_vertex);
	CU_ASSERT_EQUAL(status, OK);
	assert_graphic_equal(graphic, "1:2|12,3|13; 2:3|23; 3:4|34; 4;");

	start_vertex = GetVertex(graphic, 3);
	end_vertex = GetVertex(graphic, 4);
	status = DeleteArc(&graphic, start_vertex, end_vertex);
	CU_ASSERT_EQUAL(status, OK);
	assert_graphic_equal(graphic, "1:2|12,3|13; 2:3|23; 3; 4;");

	start_vertex = GetVertex(graphic, 1);
	end_vertex = GetVertex(graphic, 3);
	status = DeleteArc(&graphic, start_vertex, end_vertex);
	CU_ASSERT_EQUAL(status, OK);
	assert_graphic_equal(graphic, "1:2|12; 2:3|23; 3; 4;");
}

ElementType *visit_result = NULL;
int visit_result_index = 0;
Status visit(ElementType* value) {
	visit_result[visit_result_index++] = *value;
	return OK;
}
void assert_visit_result(ElementType *expect_result, int length) {
	CU_ASSERT_EQUAL(length, visit_result_index);

	int i = 0;
	for (i = 0; i < length; i++) {
		CU_ASSERT_EQUAL(visit_result[i], expect_result[i]);
	}
}
void test_DepthFirstTraverse(void) {
	GRAPHIC_TYPE graphic = get_test_graphic("1:2|12,3|13; 2:3|23; 3; 4;");
	if (graphic == NULL)
		return;
	Status status = ERROR;

	graphic = get_test_graphic("1:2|12,3|13; 2:3|23; 3; 4;");
	visit_result = (ElementType*) malloc(sizeof(ElementType) * 4);
	visit_result_index = 0;
	status = DepthFirstTraverse(graphic, &visit);
	CU_ASSERT_EQUAL(status, OK)
	int expert_result_a[] = { 1, 2, 3, 4 };
	assert_visit_result(expert_result_a, 4);

	graphic
			= get_test_graphic(
					"1:2|12,3|13,6|16,12|112; 2:13|213; 3; 4:5|45; 5; 6; 7:8|78,9|79,11|711; 8:11|811; 9; 10:12|1012,13|1013; 11; 12:13|1213; 13;");
	visit_result = (ElementType*) malloc(sizeof(ElementType) * 13);
	visit_result_index = 0;
	status = DepthFirstTraverse(graphic, &visit);
	CU_ASSERT_EQUAL(status, OK)
	int expert_result_b[] = { 1, 2, 13, 3, 6, 12, 4, 5, 7, 8, 11, 9, 10 };
	assert_visit_result(expert_result_b, 13);
}
void test_BreadthFirstTraverse(void) {
	GRAPHIC_TYPE graphic = get_test_graphic("1:2|12,3|13; 2:3|23; 3; 4;");
	if (graphic == NULL)
		return;
	Status status = ERROR;

	graphic = get_test_graphic("1:2|12,3|13; 2:3|23; 3; 4;");
	visit_result = (ElementType*) malloc(sizeof(ElementType) * 4);
	visit_result_index = 0;
	status = BreadthFirstTraverse(graphic, &visit);
	CU_ASSERT_EQUAL(status, OK);
	int expert_result_a[] = { 1, 2, 3, 4 };
	assert_visit_result(expert_result_a, 4);

	graphic
			= get_test_graphic(
					"1:2|12,3|13,6|16,12|112; 2:13|213; 3; 4:5|45; 5; 6; 7:8|78,9|79,11|711; 8:11|811; 9; 10:12|1012,13|1013; 11; 12:13|1213; 13;");
	visit_result = (ElementType*) malloc(sizeof(ElementType) * 13);
	visit_result_index = 0;
	status = BreadthFirstTraverse(graphic, &visit);
	CU_ASSERT_EQUAL(status, OK);
	int expert_result_b[] = { 1, 2, 3, 6, 12, 13, 4, 5, 7, 8, 9, 11, 10 };
	assert_visit_result(expert_result_b, 13);
}
void test_InDegree(void) {
	GRAPHIC_TYPE
			graphic =
					get_test_graphic(
							"1:2|12,3|13,6|16,12|112; 2:13|213; 3; 4:5|45; 5; 6; 7:8|78,9|79,11|711; 8:11|811; 9; 10:12|1012,13|1013; 11; 12:13|1213; 13;");
	if (graphic == NULL)
		return;

	VERTEX_TYPE *vertex = NULL;
	int in_degree = 0;

	vertex = GetVertex(graphic, 1);
	in_degree = InDegree(graphic, vertex);
	CU_ASSERT_EQUAL(in_degree, 0);

	vertex = GetVertex(graphic, 8);
	in_degree = InDegree(graphic, vertex);
	CU_ASSERT_EQUAL(in_degree, 1);

	vertex = GetVertex(graphic, 13);
	in_degree = InDegree(graphic, vertex);
	CU_ASSERT_EQUAL(in_degree, 3);
}
void test_OutDegree(void) {
	GRAPHIC_TYPE
			graphic =
					get_test_graphic(
							"1:2|12,3|13,6|16,12|112; 2:13|213; 3; 4:5|45; 5; 6; 7:8|78,9|79,11|711; 8:11|811; 9; 10:12|1012,13|1013; 11; 12:13|1213; 13;");
	if (graphic == NULL)
		return;

	VERTEX_TYPE *vertex = NULL;
	int in_degree = 0;

	vertex = GetVertex(graphic, 1);
	in_degree = OutDegree(graphic, vertex);
	CU_ASSERT_EQUAL(in_degree, 4);

	vertex = GetVertex(graphic, 8);
	in_degree = OutDegree(graphic, vertex);
	CU_ASSERT_EQUAL(in_degree, 1);

	vertex = GetVertex(graphic, 10);
	in_degree = OutDegree(graphic, vertex);
	CU_ASSERT_EQUAL(in_degree, 2);
}
//Status TopologicalSort(GRAPHIC_TYPE graphic, ElementType* result);
void test_TopologicalSort(void) {
	GRAPHIC_TYPE graphic = get_test_graphic("1:2|12,3|13; 2:3|23; 3; 4;");
	if (graphic == NULL)
		return;
	Status status = ERROR;

	graphic = get_test_graphic(
			"1:2|12,3|13,4|14; 2; 3:2|32,5|35; 4:5|45; 5; 6:4|64,5|65;");
	status = TopologicalSort(graphic, &visit_result);
	CU_ASSERT_EQUAL(status, OK)
	int expert_result_a[] = { 1, 3, 2, 6, 4, 5 };
	visit_result_index = 6;
	assert_visit_result(expert_result_a, 6);

	graphic
			= get_test_graphic(
					"1:4|14,2|12,3|13,12|112; 2:3|23; 3:5|35,7|37,8|38; 4:5|45; 5:7|57; 6:8|68; 7; 8; 9:12|912,10|910,11|911; 10:12|1012; 11:6|116; 12;");
	status = TopologicalSort(graphic, &visit_result);
	CU_ASSERT_EQUAL(status, OK)
	int expert_result_b[] = { 1, 2, 3, 4, 5, 7, 9, 10, 11, 6, 8, 12 };
	visit_result_index = 12;
	assert_visit_result(expert_result_b, 12);
}
//Status CriticalPath(GRAPHIC_TYPE graphic, GRAPHIC* result);
void test_CriticalPath(void) {
	GRAPHIC_TYPE graphic = get_test_graphic("1:2|12,3|13; 2:3|23; 3; 4;");
	if (graphic == NULL)
		return;
	Status status = ERROR;
	GRAPHIC_TYPE result = NULL;

	graphic
			= get_test_graphic(
					"1:2|6,3|4,4|5; 2:5|1; 3:5|1; 4:6|2; 5:7|9,8|7; 6:8|4; 7:9|2; 8:9|4; 9;");
	status = CriticalPath(graphic, &result);
	CU_ASSERT_EQUAL(status, OK)
	assert_graphic_equal(result, "1:2|6; 2:5|1; 5:7|9,8|7; 7:9|2; 8:9|4; 9;");

	graphic = get_test_graphic(
			"1:2|3,3|2; 2:4|2,5|3; 3:4|4,6|3; 4:6|2; 5:6|1; 6;");
	status = CriticalPath(graphic, &result);
	CU_ASSERT_EQUAL(status, OK)
	assert_graphic_equal(result, "1:3|2; 3:4|4; 4:6|2; 6;");
}
void test_ShortestPath(void) {
	GRAPHIC_TYPE graphic = get_test_graphic(
			"0:2|10,4|30,5|100; 1:2|5; 2:3|50; 3:5|10; 4:3|20,5|60; 5;");
	if (graphic == NULL)
		return;
	Status status = ERROR;
	ShortestPathResultNode *result = NULL;
	VERTEX_TYPE *vertex = NULL;

	vertex = GetVertex(graphic, 0);
	status = ShortestPath(graphic, vertex, &result);

	//asert result equal
	CU_ASSERT_EQUAL(status, OK);
	CU_ASSERT_PTR_NOT_NULL(result);
	if (result == NULL)
		return;

	int i = 0, vertex_array[5];
	for (i = 0; i < 5; i++) {
		vertex_array[i] = 0;
	}
	for (i = 0; i < 5; i++) {
		ShortestPathResultNode *shortest_path_result_vertex = result + i;
		VERTEX_TYPE *end_vertex = shortest_path_result_vertex -> end_vertex;
		ElementType end_vertex_value = Value(graphic, end_vertex);
		GRAPHIC_TYPE end_vertex_graphic = shortest_path_result_vertex -> graphic;

		vertex_array[end_vertex_value - 1] = 1;
		switch (end_vertex_value) {
		case 1:
			CU_ASSERT_PTR_NULL(end_vertex_graphic)
			break;
		case 2:
			assert_graphic_equal(end_vertex_graphic, "0:2|10; 2;");
			break;
		case 3:
			assert_graphic_equal(end_vertex_graphic, "0:4|30; 3; 4:3|20;");
			break;
		case 4:
			assert_graphic_equal(end_vertex_graphic, "0:4|30; 4;");
			break;
		case 5:
			assert_graphic_equal(end_vertex_graphic,
					"0:4|30; 3:5|10; 4:3|20; 5;");
			break;
		}
	}
	for (i = 0; i < 5; i++) {
		CU_ASSERT_EQUAL(vertex_array[i], 1);
	}
}

CU_pSuite buildDirectedGraphicTestSuite() {

	CU_pSuite pSuite = buildGraphicTestSuite();
	CU_ADD_TEST(pSuite, test_FirstAdjacentVertex);
	CU_ADD_TEST(pSuite, test_NextAdjacentVertex);
	CU_ADD_TEST(pSuite, test_InsertArc);
	CU_ADD_TEST(pSuite, test_DeleteArc);
	CU_ADD_TEST(pSuite, test_DepthFirstTraverse);
	CU_ADD_TEST(pSuite, test_BreadthFirstTraverse);
	CU_ADD_TEST(pSuite, test_InDegree);
	CU_ADD_TEST(pSuite, test_OutDegree);
	CU_ADD_TEST(pSuite, test_TopologicalSort);
	CU_ADD_TEST(pSuite, test_CriticalPath);
	CU_ADD_TEST(pSuite, test_ShortestPath);

	return pSuite;
}
