/*
 * polynomial_test.c
 *
 *  Created on: 2009-5-14
 *      Author: yuandong
 */

#include <stdlib.h>

#include "include/list/polynomial.h"

#include "include/CUnit/Basic.h"
#include "include/CUnit/Console.h"
#include "include/CUnit/Automated.h"

void assertTerm(Polynomial polynomial, int position, float coefficient,
		int exponent, BOOLEAN isLast) {
	Term *term = polynomial -> head;
	int index = 1;
	while (index < position && term != NULL) {
		index++;
		term = term -> next;
	}

	CU_ASSERT_PTR_NOT_NULL(term);
	if (term == NULL)
		return;

	CU_ASSERT_EQUAL(term -> coefficient, coefficient);
	CU_ASSERT_EQUAL(term -> exponent, exponent);

	if (isLast) {
		CU_ASSERT_PTR_NULL(term -> next);
	} else {
		CU_ASSERT_PTR_NOT_NULL(term -> next);
	}
}

//3x5 + 10x2 + x
Polynomial getTestPolynomial_a() {
	Polynomial polynomial = (Polynomial) malloc(sizeof(PolynomialHead));

	polynomial -> head = (Term*) malloc(sizeof(Term));
	polynomial -> head -> coefficient = 3;
	polynomial -> head -> exponent = 5;

	polynomial -> head -> next = (Term*) malloc(sizeof(Term));
	polynomial -> head -> next -> coefficient = 10;
	polynomial -> head -> next -> exponent = 2;

	polynomial -> head -> next -> next = (Term*) malloc(sizeof(Term));
	polynomial -> head -> next -> next -> coefficient = 1;
	polynomial -> head -> next -> next -> exponent = 1;

	polynomial -> head -> next -> next -> next = NULL;

	return polynomial;
}
//3x5 + 3x3 + 12
Polynomial getTestPolynomial_b() {
	Polynomial polynomial = (Polynomial) malloc(sizeof(PolynomialHead));

	polynomial -> head = (Term*) malloc(sizeof(Term));
	polynomial -> head -> coefficient = 3;
	polynomial -> head -> exponent = 5;

	polynomial -> head -> next = (Term*) malloc(sizeof(Term));
	polynomial -> head -> next -> coefficient = 3;
	polynomial -> head -> next -> exponent = 3;

	polynomial -> head -> next -> next = (Term*) malloc(sizeof(Term));
	polynomial -> head -> next -> next -> coefficient = 12;
	polynomial -> head -> next -> next -> exponent = 0;

	polynomial -> head -> next -> next -> next = NULL;

	return polynomial;
}

void test_InitialPolynomial(void) {
	Polynomial polynomial = NULL;
	Status result;

	result = InitialPolynomial(&polynomial);

	CU_ASSERT_EQUAL(result, OK);
	CU_ASSERT_PTR_NOT_NULL(polynomial);
	if (polynomial != NULL)
		CU_ASSERT_PTR_NULL(polynomial -> head);
}
void test_CreatePolynomial(void) {
	Polynomial polynomial = NULL;
	Status result;

	result = CreatePolynomial(&polynomial, 45.4, 130);

	CU_ASSERT_EQUAL(result, OK);
	CU_ASSERT_PTR_NOT_NULL(polynomial);
	if (polynomial == NULL)
		return;

	assertTerm(polynomial, 1, 45.4, 130, TRUE);
}

void test_DestoryPolynomial(void) {
	Polynomial polynomial = getTestPolynomial_a();
	Status result;

	result = DestroyPolynomial(&polynomial);

	CU_ASSERT_EQUAL(result, OK);
	CU_ASSERT_PTR_NULL(polynomial);
}

void test_PloynomialLength(void) {
	Polynomial polynomial = getTestPolynomial_a();

	CU_ASSERT_EQUAL(PolynomialLength(polynomial), 3);
}

void test_AddPolynomial(void) {
	Polynomial a = getTestPolynomial_a(), b = getTestPolynomial_b();
	Status result;

	result = AddPolynomial(&a, &b);

	CU_ASSERT_EQUAL(result, OK);
	CU_ASSERT_PTR_NULL(b);

	//(3x5 + 10x2 + x) + (3x5 + 3x3 + 12) = 6x5 + 3x3 + 10x2 + x + 12
	assertTerm(a, 1, 6, 5, FALSE);
	assertTerm(a, 2, 3, 3, FALSE);
	assertTerm(a, 3, 10, 2, FALSE);
	assertTerm(a, 4, 1, 1, FALSE);
	assertTerm(a, 5, 12, 0, TRUE);
}

void test_SubstractPloynomial(void) {
	Polynomial a = getTestPolynomial_a(), b = getTestPolynomial_b();
	Status result;

	result = SubstractPolynomial(&a, &b);

	CU_ASSERT_EQUAL(result, OK);
	CU_ASSERT_PTR_NULL(b);

	//(3x5 + 10x2 + x) - (3x5 + 3x3 + 12) =  -3x3 + 10x2 + x + (-12)
	assertTerm(a, 1, -3, 3, FALSE);
	assertTerm(a, 2, 10, 2, FALSE);
	assertTerm(a, 3, 1, 1, FALSE);
	assertTerm(a, 4, -12, 0, TRUE);
}

void test_MupltiplyPolynomial(void) {
	Polynomial a = getTestPolynomial_a(), b = getTestPolynomial_b();
	Status result;

	result = MultiplyPolynomial(&a, &b);

	CU_ASSERT_EQUAL(result, OK);
	CU_ASSERT_PTR_NULL(b);

	//(3x5 + 10x2 + x) * (3x5 + 3x3 + 12) = 9x10 + 9x8 + 3x6 + 96x5 + 3x4 + 120x2 + 12x
	assertTerm(a, 1, 9, 10, FALSE);
	assertTerm(a, 2, 9, 8, FALSE);
	assertTerm(a, 3, 30, 7, FALSE);
	assertTerm(a, 4, 3, 6, FALSE);
	assertTerm(a, 5, 66, 5, FALSE);
	assertTerm(a, 6, 3, 4, FALSE);
	assertTerm(a, 7, 120, 2, FALSE);
	assertTerm(a, 8, 12, 1, TRUE);
}

int main(void) {

	CU_initialize_registry();

	CU_pSuite pSuite = CU_add_suite("Polynomial Test Suite", NULL, NULL);
	CU_ADD_TEST(pSuite, test_InitialPolynomial);
	CU_ADD_TEST(pSuite, test_CreatePolynomial);
	CU_ADD_TEST(pSuite, test_DestoryPolynomial);
	CU_ADD_TEST(pSuite, test_PloynomialLength);
	CU_ADD_TEST(pSuite, test_AddPolynomial);
	CU_ADD_TEST(pSuite, test_SubstractPloynomial);
	CU_ADD_TEST(pSuite, test_MupltiplyPolynomial);

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

	CU_cleanup_registry();
	return CU_get_error();
}
