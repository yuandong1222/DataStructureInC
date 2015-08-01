/*
 * link_string_test.c
 *
 *  Created on: 2009-4-10
 *      Author: yuandong
 */
#include <stdlib.h>

#include "CUnit/Basic.h"
#include "CUnit/Console.h"
#include "CUnit/Automated.h"
#include "CUnit/TestDB.h"

#include "include/string/link_string.h"
#include "include/string/string.h"

void test_Assign(void) {
	STRING_TYPE temp = NULL;
	Status result;

	result = Assign(&temp, "abcde");

	CU_ASSERT_EQUAL(result, OK);
	if (result != OK)
		return;

	CU_ASSERT_PTR_NOT_NULL(temp);
	if (temp == NULL)
		return;

	CU_ASSERT_EQUAL(temp -> length, 5);

	CU_ASSERT_PTR_NOT_NULL(temp -> head);
	if (temp -> head == NULL)
		return;

	CU_ASSERT_PTR_NOT_NULL(temp -> tail);
	if (temp -> tail == NULL)
		return;

	CU_ASSERT_EQUAL(temp -> head -> next, temp -> tail);
	CU_ASSERT_EQUAL(temp -> tail -> next, NULL);

	CU_ASSERT_EQUAL((temp -> head -> data)[0], 'a');
	CU_ASSERT_EQUAL((temp -> head -> data)[1], 'b');
	CU_ASSERT_EQUAL((temp -> head -> data)[2], 'c');
	CU_ASSERT_EQUAL((temp -> head -> data)[3], 'd');
	CU_ASSERT_EQUAL((temp -> tail -> data)[0], 'e');
	CU_ASSERT_EQUAL((temp -> tail -> data)[1], BLANK);
	CU_ASSERT_EQUAL((temp -> tail -> data)[2], BLANK);
	CU_ASSERT_EQUAL((temp -> tail -> data)[3], BLANK);
}
void test_Zip(void) {
	STRING_TYPE temp = NULL;
	Status result;

	result = Assign(&temp, "abcde");
	CU_ASSERT_EQUAL(result, OK);
	if (result != OK)
		return;

	(temp -> head -> data)[0] = 'a';
	(temp -> head -> data)[1] = BLANK;
	(temp -> head -> data)[2] = 'b';
	(temp -> head -> data)[3] = BLANK;
	(temp -> tail -> data)[0] = 'c';
	(temp -> tail -> data)[1] = 'd';
	(temp -> tail -> data)[2] = BLANK;
	(temp -> tail -> data)[3] = BLANK;
	temp -> length = 4;

	result = Zip(&temp);
	CU_ASSERT_EQUAL(result, OK);
	if (result != OK)
		return;

	CU_ASSERT_EQUAL(temp -> head, temp -> tail);
	CU_ASSERT_EQUAL(temp -> length, 4);

	CU_ASSERT_EQUAL((temp -> head -> data)[0], 'a');
	CU_ASSERT_EQUAL((temp -> head -> data)[1], 'b');
	CU_ASSERT_EQUAL((temp -> head -> data)[2], 'c');
	CU_ASSERT_EQUAL((temp -> head -> data)[3], 'd');

	//2
	result = Assign(&temp, "abcde");
	CU_ASSERT_EQUAL(result, OK);
	if (result != OK)
		return;

	(temp -> head -> data)[0] = 'a';
	(temp -> head -> data)[1] = BLANK;
	(temp -> head -> data)[2] = 'b';
	(temp -> head -> data)[3] = BLANK;
	(temp -> tail -> data)[0] = 'c';
	(temp -> tail -> data)[1] = 'd';
	(temp -> tail -> data)[2] = BLANK;
	(temp -> tail -> data)[3] = 'e';

	result = Zip(&temp);
	CU_ASSERT_EQUAL(result, OK);
	if (result != OK)
		return;

	CU_ASSERT_EQUAL((temp -> head -> data)[0], 'a');
	CU_ASSERT_EQUAL((temp -> head -> data)[1], 'b');
	CU_ASSERT_EQUAL((temp -> head -> data)[2], 'c');
	CU_ASSERT_EQUAL((temp -> head -> data)[3], 'd');
	CU_ASSERT_EQUAL((temp -> tail -> data)[0], 'e');
	CU_ASSERT_EQUAL((temp -> tail -> data)[1], BLANK);
	CU_ASSERT_EQUAL((temp -> tail -> data)[2], BLANK);
	CU_ASSERT_EQUAL((temp -> tail -> data)[3], BLANK);

}

#include "test/string/string_test.c"
int main(void) {

	CU_pSuite suite = buildTestSuite();
	CU_ADD_TEST(suite, test_Assign);
	CU_ADD_TEST(suite, test_Zip);

	return runTestSuite();
}
