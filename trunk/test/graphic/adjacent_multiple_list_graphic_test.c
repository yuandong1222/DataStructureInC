/*
 * adjacent_multiple_list_graphic_test.c
 *
 *  Created on: 2009-10-19
 *      Author: yuandong
 */

#include <stdlib.h>

#include "CUnit/Basic.h"
#include "CUnit/Console.h"
#include "CUnit/Automated.h"
#include "CUnit/TestDB.h"

#include "include/graphic/adjacent_multiple_list_graphic.h"
#include "include/graphic/undirected_graphic.h"

void assert_graphic_equal_action(GRAPHIC_TYPE actual, Graphic* expected) {
	CU_ASSERT_PTR_NOT_NULL(actual);
	if(actual == NULL)
		return;

	int i = 0, vertex_count = 0, arc_count = 0;
	for (i = 0; i < MAX_VERTEX_SIZE; i++) {
		if((actual -> vertex_list)[i].is_empty == TRUE)
			continue;

		vertex_count++;

		ArcNode *arc_node = (actual -> vertex_list)[i].arc_list;
		while (arc_node != NULL) {
			arc_count++;
			arc_node = arc_node -> start_vertex_index == i ? 
				arc_node -> start_link_next : arc_node -> end_link_next;
		}
	}

	arc_count /= 2;

	CU_ASSERT_EQUAL(actual -> vertex_count, vertex_count);
	CU_ASSERT_EQUAL(actual -> arc_count, arc_count);
	CU_ASSERT_EQUAL(actual -> vertex_count, expected -> vertex_length);
	CU_ASSERT_EQUAL(actual -> arc_count, expected -> arc_length);

	for (i = 0; i < expected -> vertex_length; i++) {
		ElementType value = *(expected -> vertex_list + i);
		int index = get_vertex_index_by_value(actual, value);
		CU_ASSERT_TRUE(index >= 0);	
	}

	ArcNode *arc_node = NULL;
	for (i = 0; i < expected -> arc_length; i++) {
		Arc	*arc = expected -> arc_list + i;
		int start_vertex_index = get_vertex_index_by_value(actual, arc -> start_vertex);
		int end_vertex_index = get_vertex_index_by_value(actual, arc -> end_vertex);
		
		CU_ASSERT_NOT_EQUAL(start_vertex_index, -1);
		CU_ASSERT_NOT_EQUAL(end_vertex_index, -1);
		if (start_vertex_index == -1 || end_vertex_index == -1)
			continue;

		arc_node = get_arc_node(actual, start_vertex_index, end_vertex_index); 
		CU_ASSERT_PTR_NOT_NULL(arc_node);
		if (arc_node != NULL) 
			CU_ASSERT_EQUAL(arc_node -> weight, arc -> weight);
	}
}
void assert_vertex_equal(VERTEX_TYPE *vertex, ElementType value) {
	CU_ASSERT_PTR_NOT_NULL(vertex);
	if(vertex == NULL)
		return;

	CU_ASSERT_EQUAL(vertex -> value, value);
}

#include "test/graphic/undirected_graphic_test.c"
void test_Initial_Ajacent_Multiple_List_Graphic(void) {
	GRAPHIC_TYPE graphic = NULL;
	Initial(&graphic);

	if (graphic == NULL)
		return;

	CU_ASSERT_PTR_NOT_NULL(graphic -> vertex_list);
	if (graphic -> vertex_list == NULL)
		return;

	int i = 0;
	for (i = 0; i < MAX_VERTEX_SIZE; i++) {
		CU_ASSERT_EQUAL((graphic -> vertex_list)[i].is_empty, TRUE);
		CU_ASSERT_EQUAL((graphic -> vertex_list)[i].arc_list, NULL);
	}

	CU_ASSERT_EQUAL(graphic -> vertex_count, 0);
	CU_ASSERT_EQUAL(graphic -> arc_count, 0);
}

int main(void) {
	CU_pSuite pSuite = buildUndirectedGraphicTestSuite();
	CU_ADD_TEST(pSuite, test_Initial_Ajacent_Multiple_List_Graphic);
	return runTestSuite();
}
