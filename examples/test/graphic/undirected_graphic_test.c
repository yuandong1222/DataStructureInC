/*
 * undirected_graphic_test.c
 *
 *  Created on: 2009-9-20
 *      Author: yuandong
 */

#include <stdlib.h>

#include "include/graphic/undirected_graphic.h"

#include "include/CUnit/Basic.h"
#include "include/CUnit/Console.h"
#include "include/CUnit/Automated.h"
#include "include/CUnit/TestDB.h"

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
	assert_vertex_equal(adjacent_vertex, 1);

	vertex = GetVertex(graphic, 3);
	adjacent_vertex = FirstAdjacentVertex(graphic, vertex);
	assert_vertex_equal(adjacent_vertex, 1);
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
	assert_vertex_equal(next_adjacent_vertex, 3);
}
void test_InsertArc(void) {
	GRAPHIC_TYPE graphic = get_test_graphic("1:2|12,3|13; 2:3|23; 3; 4;");
	if (graphic == NULL)
		return;
	Status status = ERROR;
	VERTEX_TYPE *start_vertex = NULL, *end_vertex = NULL;

	start_vertex = GetVertex(graphic, 1);
	end_vertex = GetVertex(graphic, 4);
	status = InsertArc(&graphic, start_vertex, end_vertex, 14);
	CU_ASSERT_EQUAL(status, OK);
	assert_graphic_equal(graphic, "1:2|12,3|13,4|14; 2:3|23; 3; 4;");

	start_vertex = GetVertex(graphic, 3);
	end_vertex = GetVertex(graphic, 4);
	status = InsertArc(&graphic, start_vertex, end_vertex, 34);
	CU_ASSERT_EQUAL(status, OK);
	assert_graphic_equal(graphic, "1:2|12,3|13,4|14; 2:3|23; 3:4|34; 4;");

	start_vertex = GetVertex(graphic, 4);
	end_vertex = GetVertex(graphic, 3);
	status = InsertArc(&graphic, start_vertex, end_vertex, 43);
	CU_ASSERT_EQUAL(status, OK);
	assert_graphic_equal(graphic, "1:2|12,3|13,4|14; 2:3|23; 3:4|43; 4;");
}
void test_DeleteArc(void) {
	GRAPHIC_TYPE graphic = get_test_graphic("1:2|12,3|13; 2:3|23; 3:4|34; 4;");
	if (graphic == NULL)
		return;
	Status status = ERROR;
	VERTEX_TYPE *start_vertex = NULL, *end_vertex = NULL;

	start_vertex = GetVertex(graphic, 4);
	end_vertex = GetVertex(graphic, 3);
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
	int expert_result_b[] = { 1, 2, 13, 10, 12, 3, 6, 4, 5, 7, 8, 11, 9 };
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
	CU_ASSERT_EQUAL(status, OK)
	int expert_result_a[] = { 1, 2, 3, 4 };
	assert_visit_result(expert_result_a, 4);

	graphic
			= get_test_graphic(
					"1:2|12,3|13,6|16,12|112; 2:13|213; 3; 4:5|45; 5; 6; 7:8|78,9|79,11|711; 8:11|811; 9; 10:12|1012,13|1013; 11; 12:13|1213; 13;");
	visit_result = (ElementType*) malloc(sizeof(ElementType) * 13);
	visit_result_index = 0;
	status = BreadthFirstTraverse(graphic, &visit);
	CU_ASSERT_EQUAL(status, OK)
	int expert_result_b[] = { 1, 2, 3, 6, 12, 13, 10, 4, 5, 7, 8, 9, 11 };
	assert_visit_result(expert_result_b, 13);
}
void test_Degree(void) {
	GRAPHIC_TYPE
			graphic =
					get_test_graphic(
							"1:2|12,3|13,6|16,12|112; 2:13|213; 3; 4:5|45; 5; 6; 7:8|78,9|79,11|711; 8:11|811; 9; 10:12|1012,13|1013; 11; 12:13|1213; 13;");
	if (graphic == NULL)
		return;

	VERTEX_TYPE *vertex = NULL;
	int degree = 0;

	vertex = GetVertex(graphic, 1);
	degree = Degree(graphic, vertex);
	CU_ASSERT_EQUAL(degree, 4);

	vertex = GetVertex(graphic, 8);
	degree = Degree(graphic, vertex);
	CU_ASSERT_EQUAL(degree, 2);

	vertex = GetVertex(graphic, 13);
	degree = Degree(graphic, vertex);
	CU_ASSERT_EQUAL(degree, 3);
}
//Status MiniSpanTree_Prim(GRAPHIC_TYPE graphic, GRAPHIC_TYPE* result);
void test_MiniSpanTree_Prim(void) {
	GRAPHIC_TYPE graphic = get_test_graphic(
			"1:2|6,3|1,4|5; 2:3|5,5|3; 3:4|5,5|6,6|4; 4:6|2; 5:6|6; 6;");
	if (graphic == NULL)
		return;
	GRAPHIC_TYPE result = NULL;
	Status status = ERROR;

	status = MiniSpanTree_Prim(graphic, &result);
	assert_graphic_equal(result, "1:3|1; 2:3|5,5|3; 3:6|4; 4:6|2; 5; 6;");
}
//Status MiniSpanTree_Kruskal(GRAPHIC_TYPE graphic, GRAPHIC_TYPE* result);
void test_MiniSpanTree_Kruskal(void) {
	GRAPHIC_TYPE graphic = get_test_graphic(
			"1:2|6,3|1,4|5; 2:3|5,5|3; 3:4|5,5|6,6|4; 4:6|2; 5:6|6; 6;");
	if (graphic == NULL)
		return;
	GRAPHIC_TYPE result = NULL;
	Status status = ERROR;

	status = MiniSpanTree_Kruskal(graphic, &result);
	assert_graphic_equal(result, "1:3|1; 2:3|5,5|3; 3:6|4; 4:6|2; 5; 6;");
}
//Status FindArticul(GRAPHIC_TYPE graphic, ElementType** result,
//		int* result_length);
void test_FindArticul(void) {
	GRAPHIC_TYPE
			graphic =
					get_test_graphic(
							"1:2|12,3|13,6|16,12|112; 2:13|213,3|23,4|24,7|27,8|28; 3; 4:5|45; 5; 6; 7:8|78,9|79,11|711; 8:11|811; 9; 10:12|1012,13|1013; 11; 12:13|1213; 13;");
	if (graphic == NULL)
		return;
	ElementType* result = NULL;
	int result_length = 0;
	Status status = ERROR;

	status = FindArticul(graphic, &result, &result_length);
	CU_ASSERT_EQUAL(status, OK);
	CU_ASSERT_EQUAL(result_length, 4);
	if (result != NULL) {
		CU_ASSERT_EQUAL(result[0], 1);
		CU_ASSERT_EQUAL(result[1], 2);
		CU_ASSERT_EQUAL(result[2], 4);
		CU_ASSERT_EQUAL(result[3], 7);
	}
}

CU_pSuite buildUndirectedGraphicTestSuite() {

	CU_pSuite pSuite = buildGraphicTestSuite();
	CU_ADD_TEST(pSuite, test_FirstAdjacentVertex);
	CU_ADD_TEST(pSuite, test_NextAdjacentVertex);
	CU_ADD_TEST(pSuite, test_InsertArc);
	CU_ADD_TEST(pSuite, test_DeleteArc);
	CU_ADD_TEST(pSuite, test_DepthFirstTraverse);
	CU_ADD_TEST(pSuite, test_BreadthFirstTraverse);
	CU_ADD_TEST(pSuite, test_Degree);
	CU_ADD_TEST(pSuite, test_MiniSpanTree_Prim);
	CU_ADD_TEST(pSuite, test_MiniSpanTree_Kruskal);
	CU_ADD_TEST(pSuite, test_FindArticul);

	return pSuite;
}
