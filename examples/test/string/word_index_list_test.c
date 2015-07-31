/*
 * string_test.c
 *
 *  Created on: 2009-4-10
 *      Author: yuandong
 */

#include <stdlib.h>

#include "include/string/word_index_list.h"

#include "include/CUnit/Basic.h"
#include "include/CUnit/Console.h"
#include "include/CUnit/Automated.h"
#include "include/CUnit/TestDB.h"

/*
 * Test Data:
 * 01: love book manage
 * 02: work water
 * 03: word index list
 * 04: string list test
 * 05: love string
 * 06: help window
 * 07: help project
 * 08: help run
 * 09: window project run
 * 10: edit file
 *
 * So the word index list should be like this:
 * book:	1
 * edit:	10
 * file:	10
 * help:	6, 7, 8
 * index:	3
 * list:	3, 4
 * love:	1, 5
 * manage:	1
 * project:	7, 9
 * run:		8, 9
 * string:	4, 5
 * test:	4
 * water:	2
 * window:	6, 9
 * word:	3
 * work:	2
 */
WordIndexList getTestWordIndexList() {
	WordIndexList list = NULL;
	Status status = 0;

	status = Initial(&list);
	if (status != OK)
		return NULL;

	Index(list, 1, "love");
	Index(list, 1, "book");
	Index(list, 1, "manage");
	Index(list, 2, "work");
	Index(list, 2, "water");
	Index(list, 3, "word");
	Index(list, 3, "index");
	Index(list, 3, "list");
	Index(list, 4, "string");
	Index(list, 4, "list");
	Index(list, 4, "test");
	Index(list, 5, "love");
	Index(list, 5, "string");
	Index(list, 6, "help");
	Index(list, 6, "window");
	Index(list, 7, "help");
	Index(list, 7, "project");
	Index(list, 8, "help");
	Index(list, 8, "run");
	Index(list, 9, "window");
	Index(list, 9, "project");
	Index(list, 9, "run");
	Index(list, 10, "edit");
	status = Index(list, 10, "file");

	if (status != OK)
		return NULL;

	return list;
}
int compare(String a, String b) {

	if (a == NULL)
		return b == NULL ? 0 : -1;
	if (b == NULL)
		return a == NULL ? 0 : 1;

	char *pointer_a = a, *pointer_b = b;
	while (*pointer_a != '\0' && *pointer_b != '\0') {
		if (*pointer_a > *pointer_b)
			return 1;
		else if (*pointer_a < *pointer_b)
			return -1;

		pointer_a++;
		pointer_b++;
	}

	if (*pointer_a > *pointer_b)
		return 1;
	if (*pointer_a < *pointer_b)
		return -1;
	return 0;
}

void test_Initial(void) {
	WordIndexList list = NULL;
	Status status = 0;

	status = Initial(&list);
	CU_ASSERT_EQUAL(status, OK);
	CU_ASSERT_PTR_NOT_NULL(list);
	if (list == NULL)
		return;

	CU_ASSERT_EQUAL(list -> length, 0);

	int i = 0;
	for (i = 0; i < MAX_INDEX_WORD_COUNT; i++) {
		CU_ASSERT_PTR_NULL((list -> items)[i]);
	}
}

void assertBookNumberListEuqal(BookNumberList book_number_list,
		int* book_number_array) {

	int book_number_array_position = 1, book_number_array_length =
			book_number_array[0];
	BookNumberListNode *book_number_node = book_number_list;

	for (book_number_array_position = 1; book_number_array_position
			<= book_number_array_length; book_number_array_position++) {

		CU_ASSERT_PTR_NOT_NULL(book_number_node);
		if (book_number_node == NULL)
			return;

		CU_ASSERT_EQUAL(book_number_node -> book_number, book_number_array[book_number_array_position]);

		book_number_node = book_number_node -> next;
	}
	CU_ASSERT_PTR_NULL(book_number_node);

}

void assertWordIndexListItem(WordIndexList list, String word, int position,
		int* book_number_array) {
	CU_ASSERT_PTR_NOT_NULL(list);
	if (list == NULL)
		return;

	CU_ASSERT_TRUE(list -> length >= position);
	if (list -> length < position)
		return;

	WordIndexListItem *item = (list -> items)[position - 1];
	CU_ASSERT_PTR_NOT_NULL(item);
	if (item == NULL)
		return;

	String item_word = item -> word;
	CU_ASSERT_EQUAL(compare(item_word, word), 0);

	assertBookNumberListEuqal(item -> book_number_list, book_number_array);
}
void test_Index(void) {
	WordIndexList list = getTestWordIndexList();
	CU_ASSERT_PTR_NOT_NULL(list);
	if (list == NULL)
		return;

	int book_number_array_book[] = { 1, 1 };
	assertWordIndexListItem(list, "book", 1, book_number_array_book);

	int book_number_array_edit[] = { 1, 10 };
	assertWordIndexListItem(list, "edit", 2, book_number_array_edit);

	int book_number_array_file[] = { 1, 10 };
	assertWordIndexListItem(list, "file", 3, book_number_array_file);

	int book_number_array_help[] = { 3, 6, 7, 8 };
	assertWordIndexListItem(list, "help", 4, book_number_array_help);

	int book_number_array_index[] = { 1, 3 };
	assertWordIndexListItem(list, "index", 5, book_number_array_index);

	int book_number_array_list[] = { 2, 3, 4 };
	assertWordIndexListItem(list, "list", 6, book_number_array_list);

	int book_number_array_love[] = { 2, 1, 5 };
	assertWordIndexListItem(list, "love", 7, book_number_array_love);

	int book_number_array_manage[] = { 1, 1 };
	assertWordIndexListItem(list, "manage", 8, book_number_array_manage);

	int book_number_array_project[] = { 2, 7, 9 };
	assertWordIndexListItem(list, "project", 9, book_number_array_project);

	int book_number_array_run[] = { 2, 8, 9 };
	assertWordIndexListItem(list, "run", 10, book_number_array_run);

	int book_number_array_string[] = { 2, 4, 5 };
	assertWordIndexListItem(list, "string", 11, book_number_array_string);

	int book_number_array_test[] = { 1, 4 };
	assertWordIndexListItem(list, "test", 12, book_number_array_test);

	int book_number_array_water[] = { 1, 2 };
	assertWordIndexListItem(list, "water", 13, book_number_array_water);

	int book_number_array_window[] = { 2, 6, 9 };
	assertWordIndexListItem(list, "window", 14, book_number_array_window);

	int book_number_array_word[] = { 1, 3 };
	assertWordIndexListItem(list, "word", 15, book_number_array_word);

	int book_number_array_work[] = { 1, 2 };
	assertWordIndexListItem(list, "work", 16, book_number_array_work);
}

void assertIntArrayEqual(int* a, int* b) {
	if (a == NULL) {
		CU_ASSERT_PTR_NULL(b);
		return;
	}
	if (b == NULL) {
		CU_ASSERT_PTR_NULL(a);
		return;
	}

	int length_a = a[0];
	int length_b = b[0];
	CU_ASSERT_EQUAL(length_a, length_b);
	if (length_a != length_b)
		return;

	int i = 0;
	for (i = 1; i <= length_a; i++) {
		CU_ASSERT_EQUAL(a[i], b[i]);
	}
}
void test_Search(void) {
	WordIndexList list = getTestWordIndexList();
	CU_ASSERT_PTR_NOT_NULL(list);
	if (list == NULL)
		return;

	int book_number_array_book[] = { 1, 1 };
	assertIntArrayEqual(Search(list, "book"), book_number_array_book);

	int book_number_array_edit[] = { 1, 10 };
	assertIntArrayEqual(Search(list, "edit"), book_number_array_edit);

	int book_number_array_file[] = { 1, 10 };
	assertIntArrayEqual(Search(list, "file"), book_number_array_file);

	int book_number_array_help[] = { 3, 6, 7, 8 };
	assertIntArrayEqual(Search(list, "help"), book_number_array_help);

	int book_number_array_index[] = { 1, 3 };
	assertIntArrayEqual(Search(list, "index"), book_number_array_index);

	int book_number_array_list[] = { 2, 3, 4 };
	assertIntArrayEqual(Search(list, "list"), book_number_array_list);

	int book_number_array_love[] = { 2, 1, 5 };
	assertIntArrayEqual(Search(list, "love"), book_number_array_love);

	int book_number_array_manage[] = { 1, 1 };
	assertIntArrayEqual(Search(list, "manage"), book_number_array_manage);

	int book_number_array_project[] = { 2, 7, 9 };
	assertIntArrayEqual(Search(list, "project"), book_number_array_project);

	int book_number_array_run[] = { 2, 8, 9 };
	assertIntArrayEqual(Search(list, "run"), book_number_array_run);

	int book_number_array_string[] = { 2, 4, 5 };
	assertIntArrayEqual(Search(list, "string"), book_number_array_string);

	int book_number_array_test[] = { 1, 4 };
	assertIntArrayEqual(Search(list, "test"), book_number_array_test);

	int book_number_array_water[] = { 1, 2 };
	assertIntArrayEqual(Search(list, "water"), book_number_array_water);

	int book_number_array_window[] = { 2, 6, 9 };
	assertIntArrayEqual(Search(list, "window"), book_number_array_window);

	int book_number_array_word[] = { 1, 3 };
	assertIntArrayEqual(Search(list, "word"), book_number_array_word);

	int book_number_array_work[] = { 1, 2 };
	assertIntArrayEqual(Search(list, "work"), book_number_array_work);

	assertIntArrayEqual(Search(list, "not_has"), NULL);
}

void test_Destory(void) {
	WordIndexList list = NULL;
	Status status = 0;

	status = Initial(&list);
	CU_ASSERT_EQUAL(status, OK);
	CU_ASSERT_PTR_NOT_NULL(list);
	if (list == NULL)
		return;

	status = Destory(&list);
	CU_ASSERT_EQUAL(status, OK);
	CU_ASSERT_PTR_NULL(list);
}

int main(void) {
	CU_initialize_registry();

	CU_pSuite pSuite = CU_add_suite("Word Index List Test Suite", NULL, NULL);
	CU_ADD_TEST(pSuite, test_Initial);
	CU_ADD_TEST(pSuite, test_Index);
	CU_ADD_TEST(pSuite, test_Search);
	CU_ADD_TEST(pSuite, test_Destory);

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

	CU_cleanup_registry();
	return CU_get_error();
}
