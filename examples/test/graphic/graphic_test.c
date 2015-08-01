/*
 * graphic_test.c
 *
 *  Created on: 2009-9-20
 *      Author: yuandong
 */

#include <stdlib.h>

#include "include/graphic/graphic.h"

#include "CUnit/Basic.h"
#include "CUnit/Console.h"
#include "CUnit/Automated.h"
#include "CUnit/TestDB.h"

int get_number(char* string, int start_index, int end_index) {
	int value = 0;
	int i = string[start_index] == '-' ? start_index + 1 : start_index;
	for (i = i; i <= end_index; i++) {
		value = value * 10 + string[i] - '0';
	}
	return string[start_index] == '-' ? value * -1 : value;
}
Graphic* get_graphic_from_definition(char* definition) {
	int index = 0, vertex_count = 0, arc_count = 0;

	while (definition[index] != '\0') {
		if (definition[index] == ';')
			vertex_count++;

		if (definition[index] == '|')
			arc_count++;

		index++;
	}

	Graphic *graphic = (Graphic*) malloc(sizeof(Graphic));
	graphic -> vertex_length = vertex_count;
	graphic -> arc_length = arc_count;
	graphic -> vertex_list = vertex_count == 0 ? NULL : (ElementType*) malloc(
			sizeof(ElementType) * vertex_count);
	graphic -> arc_list = arc_count == 0 ? NULL : (Arc*) malloc(sizeof(Arc)
			* arc_count);

	int vertex_index = 0, arc_index = 0;
	int i = 0, value = 0, is_arc = 0;
	while (definition[i] != '\0') {

		if ((definition[i] >= '0' && definition[i] <= '9') || definition[i]
				== '-') {
			int number_start = i, number_end = i + 1;
			while (definition[number_end] >= '0' && definition[number_end]
					<= '9')
				number_end++;
			value = get_number(definition, number_start, number_end - 1);
			i = number_end;
		}

		if (definition[i] == ':') {
			(graphic -> vertex_list)[vertex_index] = value;
			is_arc = 1;
		}
		if (definition[i] == ';') {
			if (is_arc)
				(graphic -> arc_list)[arc_index++].weight = value;
			else
				(graphic -> vertex_list)[vertex_index] = value;

			vertex_index++;
			is_arc = 0;
		}
		if (definition[i] == '|') {
			(graphic -> arc_list)[arc_index].start_vertex
					= (graphic -> vertex_list)[vertex_index];
			(graphic -> arc_list)[arc_index].end_vertex = value;
		}
		if (definition[i] == ',') {
			(graphic -> arc_list)[arc_index++].weight = value;
		}

		if (definition[i] == '\0')
			break;
		i++;
	}

	return graphic;
}

GRAPHIC_TYPE get_test_graphic(char* definition) {
	GRAPHIC_TYPE graphic;
	Status status;

	status = Initial(&graphic);
	CU_ASSERT_EQUAL(status, OK);
	if (status != OK)
		return NULL;

	if (definition == NULL || definition == "")
		return graphic;

	Graphic *g = get_graphic_from_definition(definition);
	status = Create(&graphic, g);

	free(g -> vertex_list);
	free(g -> arc_list);
	free(g);

	CU_ASSERT_EQUAL(status, OK);
	if (status != OK)
		return NULL;

	return graphic;
}
void assert_graphic_equal(GRAPHIC_TYPE graphic, char* definition) {
	Graphic *g = get_graphic_from_definition(definition);
	assert_graphic_equal_action(graphic, g);

	free(g -> vertex_list);
	free(g -> arc_list);
	free(g);
}

void test_Initial(void) {
	GRAPHIC_TYPE graphic = NULL;
	Status status = Initial(&graphic);

	CU_ASSERT_EQUAL(status, OK);
	CU_ASSERT_PTR_NOT_NULL(graphic);
}
void test_Destory(void) {
	GRAPHIC_TYPE graphic = get_test_graphic("1;");
	if (graphic == NULL)
		return;

	Status status = Destory(&graphic);

	CU_ASSERT_EQUAL(status, OK);
	CU_ASSERT_PTR_NULL(graphic);
}
void test_Create(void) {
	GRAPHIC_TYPE graphic = NULL;

	graphic = get_test_graphic("");
	assert_graphic_equal(graphic, "");

	graphic = get_test_graphic("1;");
	assert_graphic_equal(graphic, "1;");

	graphic = get_test_graphic("1;2;3;");
	assert_graphic_equal(graphic, "1;2;3;");

	graphic = get_test_graphic("1:2|12,3|13; 2:3|23; 3;");
	assert_graphic_equal(graphic, "1:2|12,3|13; 2:3|23; 3;");

	graphic
			= get_test_graphic(
					"1:2|12,3|13,6|16,12|112; 2:13|213; 3; 4:5|45; 5; 6; 7:8|78,9|79,11|711; 8:11|811; 9; 10:12|1012,13|1013; 11; 12:13|1213; 13;");
	assert_graphic_equal(
			graphic,
			"1:2|12,3|13,6|16,12|112; 2:13|213; 3; 4:5|45; 5; 6; 7:8|78,9|79,11|711; 8:11|811; 9; 10:12|1012,13|1013; 11; 12:13|1213; 13;");
}
void test_GetVertex(void) {
	GRAPHIC_TYPE graphic = get_test_graphic("1:2|12,3|13; 2:3|23; 3;");
	if (graphic == NULL)
		return;

	VERTEX_TYPE *vertex = NULL;

	vertex = GetVertex(graphic, 1);
	assert_vertex_equal(vertex, 1);

	vertex = GetVertex(graphic, 2);
	assert_vertex_equal(vertex, 2);

	vertex = GetVertex(graphic, 3);
	assert_vertex_equal(vertex, 3);
}
void test_Value(void) {
	GRAPHIC_TYPE graphic = get_test_graphic("1:2|12,3|13; 2:3|23; 3;");
	if (graphic == NULL)
		return;

	VERTEX_TYPE *vertex = NULL;
	ElementType value = 0;

	vertex = GetVertex(graphic, 1);
	value = Value(graphic, vertex);
	CU_ASSERT_EQUAL(value, 1);

	vertex = GetVertex(graphic, 2);
	value = Value(graphic, vertex);
	CU_ASSERT_EQUAL(value, 2);

	value = Value(graphic, NULL);
	CU_ASSERT_EQUAL(value, 0);
}
void test_Assign(void) {
	GRAPHIC_TYPE graphic = get_test_graphic("1:2|12,3|13; 2:3|23; 3;");
	if (graphic == NULL)
		return;

	VERTEX_TYPE *vertex = NULL;
	Status status = ERROR;

	vertex = GetVertex(graphic, 1);
	status = Assign(&graphic, vertex, 101);
	CU_ASSERT_EQUAL(status, OK);

	vertex = GetVertex(graphic, 2);
	status = Assign(&graphic, vertex, 102);
	CU_ASSERT_EQUAL(status, OK);

	vertex = GetVertex(graphic, 3);
	status = Assign(&graphic, vertex, 103);
	CU_ASSERT_EQUAL(status, OK);

	assert_graphic_equal(graphic, "101:102|12,103|13; 102:103|23; 103;");
}
void test_InsertVertex(void) {
	GRAPHIC_TYPE graphic = get_test_graphic("1:2|12,3|13; 2:3|23; 3;");
	if (graphic == NULL)
		return;

	VERTEX_TYPE *vertex = NULL;
	Status status = InsertVertex(&graphic, 4, &vertex);
	CU_ASSERT_EQUAL(status, OK);
	assert_vertex_equal(vertex, 4);
	assert_graphic_equal(graphic, "1:2|12,3|13; 2:3|23; 3; 4;");
}
void test_DeleteVertex(void) {
	GRAPHIC_TYPE graphic = get_test_graphic("1:2|12,3|13; 2:3|23; 3;");
	if (graphic == NULL)
		return;

	VERTEX_TYPE *vertex = NULL;
	Status status = ERROR;

	vertex = GetVertex(graphic, 3);
	status = DeleteVertex(&graphic, &vertex);
	CU_ASSERT_EQUAL(status, OK);
	CU_ASSERT_PTR_NULL(vertex);
	assert_graphic_equal(graphic, "1:2|12; 2;");

	vertex = GetVertex(graphic, 1);
	status = DeleteVertex(&graphic, &vertex);
	CU_ASSERT_EQUAL(status, OK);
	CU_ASSERT_PTR_NULL(vertex);
	assert_graphic_equal(graphic, "2;");

	vertex = GetVertex(graphic, 2);
	status = DeleteVertex(&graphic, &vertex);
	CU_ASSERT_EQUAL(status, OK);
	CU_ASSERT_PTR_NULL(vertex);
	assert_graphic_equal(graphic, "");
}

CU_pSuite buildGraphicTestSuite() {
	CU_initialize_registry();

	CU_pSuite pSuite = CU_add_suite("Graphic Test Suite", NULL, NULL);
	CU_ADD_TEST(pSuite, test_Initial);
	CU_ADD_TEST(pSuite, test_Destory);
	CU_ADD_TEST(pSuite, test_Create);
	CU_ADD_TEST(pSuite, test_GetVertex);
	CU_ADD_TEST(pSuite, test_Value);
	CU_ADD_TEST(pSuite, test_Assign);
	CU_ADD_TEST(pSuite, test_InsertVertex);
	CU_ADD_TEST(pSuite, test_DeleteVertex);

	return pSuite;
}
int runTestSuite() {
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

	CU_cleanup_registry();
	return CU_get_error();
}
