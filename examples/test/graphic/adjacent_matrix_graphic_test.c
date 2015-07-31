/*
 * adjacent_matrix_graphic_test.c
 *
 *  Created on: 2009-9-20
 *      Author: yuandong
 */

#include <stdlib.h>

#include "include/CUnit/Basic.h"
#include "include/CUnit/Console.h"
#include "include/CUnit/Automated.h"
#include "include/CUnit/TestDB.h"

#include "include/graphic/adjacent_matrix_graphic.h"
#include "include/graphic/directed_graphic.h"

void assert_graphic_equal_action(GRAPHIC_TYPE actual, Graphic* expected) {
	CU_ASSERT_PTR_NOT_NULL(actual);
	if(actual == NULL)
		return;

	int i = 0, j = 0, vertex_count = 0, arc_count = 0;
	for (i = 0; i < MAX_VERTEX_SIZE; i++) {
		if((actual -> vertex_list)[i].is_empty == FALSE)
			vertex_count++;
		for (j = 0; j < MAX_VERTEX_SIZE; j++) {
			if((actual -> arc_list)[i][j] != -1)
				arc_count++;
		}
	}

	CU_ASSERT_EQUAL(actual -> vertex_count, vertex_count);
	CU_ASSERT_EQUAL(actual -> arc_count, arc_count);
	CU_ASSERT_EQUAL(actual -> vertex_count, expected -> vertex_length);
	CU_ASSERT_EQUAL(actual -> arc_count, expected -> arc_length);

	for (i = 0; i < expected -> vertex_length; i++) {
		ElementType value = *(expected -> vertex_list + i);
		int index = get_vertex_index_by_value(actual, value);
		CU_ASSERT_TRUE(index >= 0);	
	}

	for (i = 0; i < expected -> arc_length; i++) {
		Arc	*arc = expected -> arc_list + i;
		int start_vertex_index = get_vertex_index_by_value(actual, arc -> start_vertex);
		int end_vertex_index = get_vertex_index_by_value(actual, arc -> end_vertex);
		
		CU_ASSERT_EQUAL((actual -> arc_list)[start_vertex_index][end_vertex_index], arc -> weight);
	}
}
void assert_vertex_equal(VERTEX_TYPE *vertex, ElementType value) {
	CU_ASSERT_PTR_NOT_NULL(vertex);
	if(vertex == NULL)
		return;

	CU_ASSERT_EQUAL(vertex -> value, value);
}

#include "test/graphic/directed_graphic_test.c"

void test_Initial_Ajacent_Matrix_Graphic(void) {
	GRAPHIC_TYPE graphic = NULL;
	Initial(&graphic);

	if (graphic == NULL)
		return;

	int i = 0, j = 0;
	for (i = 0; i < MAX_VERTEX_SIZE; i++) {
		CU_ASSERT_EQUAL((graphic -> vertex_list)[i].is_empty, TRUE);
		for (j = 0; j < MAX_VERTEX_SIZE; j++) {
			CU_ASSERT_EQUAL((graphic -> arc_list)[i][j], -1);
		}
	}

	CU_ASSERT_EQUAL(graphic -> vertex_count, 0);
	CU_ASSERT_EQUAL(graphic -> arc_count, 0);
}

int main(void) {
	CU_pSuite pSuite = buildDirectedGraphicTestSuite();
	CU_ADD_TEST(pSuite, test_Initial_Ajacent_Matrix_Graphic);
	return runTestSuite();
}
