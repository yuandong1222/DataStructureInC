/*
 * polynomial.c
 *
 *  Created on: 2009-5-12
 *      Author: yuandong
 */

#include <stdlib.h>
#include <stdio.h>

#include "include/common.h"
#include "include/list/polynomial.h"

Status InitialPolynomial(Polynomial *polynomial) {
	*polynomial = (Polynomial) malloc(sizeof(PolynomialHead));
	if (polynomial == NULL)
		return OVERFLOW;

	(*polynomial) -> head = NULL;

	return OK;
}

Status CreatePolynomial(Polynomial *polynomial, float coefficient, int exponent) {
	Status result = InitialPolynomial(polynomial);
	if (result != OK)
		return result;

	(*polynomial) -> head = (Term*) malloc(sizeof(Term));
	if ((*polynomial) -> head == NULL)
		return OVERFLOW;

	(*polynomial) -> head -> coefficient = coefficient;
	(*polynomial) -> head -> exponent = exponent;
	(*polynomial) -> head -> next = NULL;

	return OK;
}

Status DestroyPolynomial(Polynomial *polynomial) {
	Term *current = (*polynomial) -> head, *temp = NULL;
	while (current != NULL) {
		temp = current -> next;
		free(current);
		current = temp;
	}
	free(*polynomial);
	*polynomial = NULL;

	return OK;
}

int PolynomialLength(Polynomial polynomial) {
	Term *term = (polynomial) -> head;
	int length = 0;

	while (term != NULL) {
		length++;
		term = term -> next;
	}

	return length;
}

Status appendTerm(Polynomial polynomial, float coefficient, int exponent) {
	if (polynomial -> head == NULL) {
		polynomial -> head = (Term*) malloc(sizeof(Term));
		if (polynomial -> head == NULL)
			return OVERFLOW;

		polynomial -> head -> coefficient = coefficient;
		polynomial -> head -> exponent = exponent;
		polynomial -> head -> next = NULL;
	} else {
		Term *term = polynomial -> head;
		while (term -> next != NULL) {
			term = term -> next;
		}
		term -> next = (Term*) malloc(sizeof(Term));
		if (term -> next == NULL)
			return OVERFLOW;

		term -> next -> coefficient = coefficient;
		term -> next -> exponent = exponent;
		term -> next -> next = NULL;
	}

	return OK;
}
Status AddPolynomial(Polynomial *a, Polynomial *b) {
	Polynomial sum;
	Status result;

	result = InitialPolynomial(&sum);
	if (result != OK)
		return result;

	Term *term_a = (*a) -> head, *term_b = (*b) -> head;
	while (term_a != NULL || term_b != NULL) {
		if (term_a != NULL && term_b != NULL) {
			if (term_a -> exponent == term_b -> exponent) {
				float sum_coefficient = term_a -> coefficient
						+ term_b -> coefficient;
				if (sum_coefficient != 0) {
					result = appendTerm(sum, sum_coefficient,
							term_a -> exponent);
					if (result != OK)
						return result;
				}

				term_a = term_a -> next;
				term_b = term_b -> next;
			} else if (term_a -> exponent > term_b -> exponent) {
				result = appendTerm(sum, term_a -> coefficient,
						term_a -> exponent);
				if (result != OK)
					return result;

				term_a = term_a -> next;

			} else if (term_b -> exponent > term_a -> exponent) {
				result = appendTerm(sum, term_b -> coefficient,
						term_b -> exponent);
				if (result != OK)
					return result;

				term_b = term_b -> next;
			}
		} else if (term_a != NULL) {
			result = appendTerm(sum, term_a -> coefficient, term_a -> exponent);
			if (result != OK)
				return result;

			term_a = term_a -> next;
		} else if (term_b != NULL) {
			result = appendTerm(sum, term_b -> coefficient, term_b -> exponent);
			if (result != OK)
				return result;

			term_b = term_b -> next;
		}
	}

	DestroyPolynomial(a);
	DestroyPolynomial(b);

	*a = sum;

	return OK;
}

Status SubstractPolynomial(Polynomial *a, Polynomial *b) {
	Term *term = (*b) -> head;
	while (term != NULL) {
		term -> coefficient *= -1.0;
		term = term -> next;
	}

	return AddPolynomial(a, b);
}

Status MultiplyPolynomial(Polynomial *a, Polynomial *b) {
	Term *term_a = NULL, *term_b = NULL;
	Polynomial temp = NULL, result = NULL;
	Status status;

	term_b = (*b) -> head;
	while (term_b != NULL) {
		InitialPolynomial(&temp);
		term_a = (*a) -> head;
		while (term_a != NULL) {
			appendTerm(temp, term_a -> coefficient * term_b -> coefficient,
					term_a -> exponent + term_b -> exponent);

			term_a = term_a -> next;
		}
		if (result == NULL)
			result = temp;
		else {
			status = AddPolynomial(&result, &temp);
			if (status != OK)
				return status;
		}

		term_b = term_b -> next;
	}

	DestroyPolynomial(b);
	DestroyPolynomial(a);

	*a = result;

	return OK;
}
