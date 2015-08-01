/*
 * heap_string_test.c
 *
 *  Created on: 2009-4-10
 *      Author: yuandong
 */
#include <stdlib.h>

#include "CUnit/Basic.h"
#include "CUnit/Console.h"
#include "CUnit/Automated.h"
#include "CUnit/TestDB.h"

#include "include/string/heap_string.h"
#include "include/string/string.h"

void test_Assign(void) {
	STRING_TYPE temp = NULL;
	Status result;

	result = Assign(&temp, "abc");

	CU_ASSERT_EQUAL(result, OK);
	if(result != OK)
		return;

	CU_ASSERT_PTR_NOT_NULL(temp);
	if(temp == NULL)
		return;

	CU_ASSERT_EQUAL(temp[0], 'a');
	CU_ASSERT_EQUAL(temp[1], 'b');
	CU_ASSERT_EQUAL(temp[2], 'c');
	CU_ASSERT_EQUAL(temp[3], '\0');
}

#include "test/string/string_test.c"
int main(void) {

	CU_pSuite suite = buildTestSuite();
	CU_ADD_TEST(suite, test_Assign);

	return runTestSuite();
}
