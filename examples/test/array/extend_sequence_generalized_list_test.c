/*
 * extend_sequence_generalized_list_test.c
 *
 *  Created on: 2009-8-12
 *      Author: yuandong
 */

#include <stdlib.h>

#include "CUnit/Basic.h"
#include "CUnit/Console.h"
#include "CUnit/Automated.h"
#include "CUnit/TestDB.h"

#include "include/array/extend_sequence_generalized_list.h"

void assertEqual_Action(GENERALIZED_LIST_TYPE list, char* string,
		int start_index, int end_index) {
	if (start_index + 1 == end_index && string[start_index] == '('
			&& string[end_index] == ')') {
		CU_ASSERT_PTR_NULL(list);
		return;
	}

	Node *node = list;
	int i = start_index + 1;
	while (i < end_index) {

		CU_ASSERT_PTR_NOT_NULL(node);
		if (node == NULL)
			return;

		char c = string[i];
		//跳过空白
		if (c == ' ') {
			i++;
		}
		//元素
		if (c >= '0' && c <= '9') {
			int number_start = i, number_end = i + 1;
			while (string[number_end] != ',' && string[number_end] != ' '
					&& string[number_end] != ')')
				number_end++;
			int value = get_number(string, number_start, number_end - 1);

			//判等

			CU_ASSERT_EQUAL(node -> tag, Atom);
			CU_ASSERT_EQUAL(node -> value, value);

			//next
			i = number_end + 1;
			node = node -> next;
		}
		//子表
		if (c == '(') {
			CU_ASSERT_EQUAL(node -> tag, List);
			if (node -> tag != List)
				return;

			int generation = 0;
			int next_start_index = i;
			int next_end_index = i + 1;

			while (next_end_index < end_index) {
				if (string[next_end_index] == '(')
					generation++;

				if (string[next_end_index] == ')') {
					if (generation == 0)
						break;
					else
						generation--;
				}

				next_end_index++;
			}

			//判等
			assertEqual_Action(node -> head, string, next_start_index,
					next_end_index);

			//next
			i = next_end_index + 2;
			node = node -> next;
		}
	}

}

void assertEqual(GENERALIZED_LIST_TYPE list, char* string) {
	assertEqual_Action(list, string, 0, get_string_length(string) - 1);
}

#include "test/array/generalized_list_test.c"
int main(void) {
	buildTestSuite();

	return runTestSuite();
}
