/*
 * string_test.c
 *
 *  Created on: 2009-4-10
 *      Author: yuandong
 */

#include <stdlib.h>

#include "include/string/string.h"

#include "CUnit/Basic.h"
#include "CUnit/Console.h"
#include "CUnit/Automated.h"
#include "CUnit/TestDB.h"

#define EMPTY_STRING_CHARS	""
#define TEST_STRING_CHARS	"yuandong"
#define TEST_STRING_LENGTH	8

STRING_TYPE getString(char* chars) {
	STRING_TYPE temp = NULL;
	CU_ASSERT_EQUAL(Assign(&temp, chars), OK);
	return temp;

}
STRING_TYPE getTestString() {
	return getString(TEST_STRING_CHARS);
}
STRING_TYPE getEmptyString() {
	return getString(EMPTY_STRING_CHARS);
}

void test_Copy(void) {
	STRING_TYPE string = getTestString(), copied = NULL;

	CU_ASSERT_EQUAL(Copy(&copied, string), OK);

	CU_ASSERT_EQUAL(Compare(string, copied), 0);
	CU_ASSERT_NOT_EQUAL(Compare(copied, getEmptyString()), 0);
}
void test_Empty(void) {
	CU_ASSERT_TRUE(Empty(getEmptyString()));
	CU_ASSERT_FALSE(Empty(getTestString()));
}

void test_Compare(void) {
	STRING_TYPE a = getString("a");
	STRING_TYPE b = getString("ab");
	STRING_TYPE c = getString("b");
	STRING_TYPE d = getString("a");

	CU_ASSERT_EQUAL(Compare(a, a), 0);
	CU_ASSERT_EQUAL(Compare(a, b), -1);
	CU_ASSERT_EQUAL(Compare(a, c), -1);

	CU_ASSERT_EQUAL(Compare(b, a), 1);
	CU_ASSERT_EQUAL(Compare(b, b), 0);
	CU_ASSERT_EQUAL(Compare(b, c), -1);

	CU_ASSERT_EQUAL(Compare(c, a), 1);
	CU_ASSERT_EQUAL(Compare(c, b), 1);
	CU_ASSERT_EQUAL(Compare(c, c), 0);

	CU_ASSERT_EQUAL(Compare(a, d), 0);

	CU_ASSERT_EQUAL(Compare(a, NULL), 1);
	CU_ASSERT_EQUAL(Compare(NULL, a), -1);

	CU_ASSERT_EQUAL(Compare(a, getEmptyString()), 1);
	CU_ASSERT_EQUAL(Compare(getEmptyString(), a), -1);
}
void test_Length(void) {
	CU_ASSERT_EQUAL(Length(getTestString()), TEST_STRING_LENGTH);
	CU_ASSERT_EQUAL(Length(getEmptyString()), 0);
	CU_ASSERT_EQUAL(NULL, 0);
}
void test_Clear(void) {
	STRING_TYPE string = getTestString();

	CU_ASSERT_EQUAL(Clear(string), OK);
	CU_ASSERT_TRUE(Empty(string));

	CU_ASSERT_EQUAL(Clear(NULL), ERROR);
}
void test_Concat(void) {
	STRING_TYPE temp = NULL;

	CU_ASSERT_EQUAL(Concat(&temp, getString("abc"), getString("de")), OK);
	CU_ASSERT_EQUAL(Compare(temp, getString("abcde")), 0);

	CU_ASSERT_EQUAL(Concat(&temp, getString("abc"), getEmptyString()), OK);
	CU_ASSERT_EQUAL(Compare(temp, getString("abc")), 0);
}
void test_SubString(void) {
	STRING_TYPE a = getString("abcde"), temp = NULL;

	CU_ASSERT_EQUAL(SubString(&temp, a, 1, 3), OK);
	CU_ASSERT_EQUAL(Compare(temp, getString("abc")), 0);

	CU_ASSERT_EQUAL(SubString(&temp, a, 4, 2), OK);
	CU_ASSERT_EQUAL(Compare(temp, getString("de")), 0);

	CU_ASSERT_EQUAL(SubString(&temp, a, 4, 0), OK);
	CU_ASSERT_EQUAL(Compare(temp, getEmptyString()), 0);

	CU_ASSERT_EQUAL(SubString(&temp, a, 0, 1), ERROR);
	CU_ASSERT_EQUAL(SubString(&temp, a, 1, 10), ERROR);
	CU_ASSERT_EQUAL(SubString(&temp, a, 10, 1), ERROR);
}
void test_Index(void) {
	STRING_TYPE a = getString("abc");
	STRING_TYPE b = getString("de");
	STRING_TYPE c = getString("abcdeabc");

	CU_ASSERT_EQUAL(Index(c, a, 1), 1);
	CU_ASSERT_EQUAL(Index(c, a, 2), 6);
	CU_ASSERT_EQUAL(Index(c, a, 6), 6);
	CU_ASSERT_EQUAL(Index(c, a, 7), 0);

	CU_ASSERT_EQUAL(Index(c, b, 1), 4);
	CU_ASSERT_EQUAL(Index(c, b, 5), 0);

	CU_ASSERT_EQUAL(Index(c, getEmptyString(), 5), 5);

	STRING_TYPE d = getString("acabaabaabcacaabc");
	STRING_TYPE e = getString("abaabcac");
	CU_ASSERT_EQUAL(Index(d, e, 1), 6);

	STRING_TYPE f = getString("aaabaaaab");
	STRING_TYPE g = getString("aaaab");
	CU_ASSERT_EQUAL(Index(f, g, 1), 5);
}
void test_Replace(void) {
	STRING_TYPE a = getString("abc");
	STRING_TYPE b = getString("de");
	STRING_TYPE c = getString("abcdeabc");

	//replace a by b
	c = getString("abcdeabc");
	CU_ASSERT_EQUAL(Replace(&c, a, b), OK);
	CU_ASSERT_EQUAL(Compare(c, getString("dedede")), 0);

	//replace a by empty
	c = getString("abcdeabc");
	CU_ASSERT_EQUAL(Replace(&c, a, getEmptyString()), OK);
	CU_ASSERT_EQUAL(Compare(c, getString("de")), 0);
}
void test_Insert(void) {
	STRING_TYPE a = getString("abc");
	STRING_TYPE b = getString("de");

	b = getString("de");
	CU_ASSERT_EQUAL(Insert(&b, 1, a), OK);
	CU_ASSERT_EQUAL(Compare(b, getString("abcde")), 0);

	b = getString("de");
	CU_ASSERT_EQUAL(Insert(&b, 2, a), OK);
	CU_ASSERT_EQUAL(Compare(b, getString("dabce")), 0);

	b = getString("de");
	CU_ASSERT_EQUAL(Insert(&b, 2, getEmptyString()), OK);
	CU_ASSERT_EQUAL(Compare(b, getString("de")), 0);

	b = getString("de");
	CU_ASSERT_EQUAL(Insert(&b, 3, a), OK);
	CU_ASSERT_EQUAL(Compare(b, getString("deabc")), 0);

	CU_ASSERT_EQUAL(Insert(&b, 0, a), ERROR);
}
void test_Delete(void) {
	STRING_TYPE a = NULL;

	a = getString("abcde");
	CU_ASSERT_EQUAL(Delete(&a, 1, 1), OK);
	CU_ASSERT_EQUAL(Compare(a, getString("bcde")), 0);

	a = getString("abcde");
	CU_ASSERT_EQUAL(Delete(&a, 1, 2), OK);
	CU_ASSERT_EQUAL(Compare(a, getString("cde")), 0);

	a = getString("abcde");
	CU_ASSERT_EQUAL(Delete(&a, 1, 5), OK);
	CU_ASSERT_EQUAL(Compare(a, getString("")), 0);

	a = getString("abcde");
	CU_ASSERT_EQUAL(Delete(&a, 1, 10), OK);
	CU_ASSERT_EQUAL(Compare(a, getString("")), 0);

	a = getString("abcde");
	CU_ASSERT_EQUAL(Delete(&a, 3, 2), OK);
	CU_ASSERT_EQUAL(Compare(a, getString("abe")), 0);

	a = getString("abcde");
	CU_ASSERT_EQUAL(Delete(&a, 3, 5), OK);
	CU_ASSERT_EQUAL(Compare(a, getString("ab")), 0);
}
void test_Destroy(void) {
	STRING_TYPE a = getString("abcde");
	CU_ASSERT_EQUAL(Destroy(&a), OK);
	CU_ASSERT_PTR_NULL(a);
}
CU_pSuite buildTestSuite() {
	CU_initialize_registry();

	CU_pSuite pSuite = CU_add_suite("String Test Suite", NULL, NULL);
	CU_ADD_TEST(pSuite, test_Copy);
	CU_ADD_TEST(pSuite, test_Empty);
	CU_ADD_TEST(pSuite, test_Compare);
	CU_ADD_TEST(pSuite, test_Length);
	CU_ADD_TEST(pSuite, test_Clear);
	CU_ADD_TEST(pSuite, test_Concat);
	CU_ADD_TEST(pSuite, test_SubString);
	CU_ADD_TEST(pSuite, test_Index);
	CU_ADD_TEST(pSuite, test_Replace);
	CU_ADD_TEST(pSuite, test_Insert);
	CU_ADD_TEST(pSuite, test_Delete);
	CU_ADD_TEST(pSuite, test_Destroy);

	return pSuite;
}

int runTestSuite() {
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

	CU_cleanup_registry();
	return CU_get_error();
}
