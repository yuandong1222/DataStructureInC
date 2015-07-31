/*
 * polynomial.h
 *
 *  Created on: 2009-5-12
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_LIST_POLYNOMIAL_H_
#define DATA_STRUCTURE_IN_C_LIST_POLYNOMIAL_H_

#include "include/common.h"

//������
typedef struct Term {
	float coefficient;
	int exponent;
	struct Term *next;
} Term;

//����ͷ��㡢����ʽ
typedef struct PolynomialHead {
	Term *head;
} PolynomialHead, *Polynomial;

//��ʼ��
//����������������ʽ������polynomialָ��ö���ʽ
//����
//	polynomial��	���ڱ����¹���Ķ���ʽ��ָ��
Status InitialPolynomial(Polynomial *polynomial);

//����
//�������������һ��������һ��Ķ���ʽ������polynomialָ��ö���ʽ
//����
//	polynomial��		���ڱ����¹���Ķ���ʽ��ָ��
//	coefficient��	ϵ��
//	exponent��		ָ��
Status
		CreatePolynomial(Polynomial *polynomial, float coefficient,
				int exponent);

//����
//�������������polynomialָ��Ķ���ʽ
//����
//	polynomial��	Ҫ���ٵĶ���ʽ
Status DestroyPolynomial(Polynomial *polynomial);

//�������Ŀ
//�������������polynomialָ��Ķ���ʽ�������Ŀ
//����
//	polynomial��	Ҫ������Ŀ�Ķ���ʽ
int PolynomialLength(Polynomial polynomial);

//�ӷ�����
//�����������ɶ���ʽ������㣬����Pa = Pa + Pb��������Pb
//����
//	a��	�����ͷ��ؽ��
//	b��	����
Status AddPolynomial(Polynomial *a, Polynomial *b);

//��������
//�����������ɶ���ʽ������㣬����Pa = Pa - Pb��������Pb
//����
//	a��	�������ͷ��ؽ��
//	b��	����
Status SubstractPolynomial(Polynomial *a, Polynomial *b);

//�˷�����
//�����������ɶ���ʽ������㣬����Pa = Pa * Pb��������Pb
//����
//	a��	�����ͷ��ؽ��
//	b��	����
Status MultiplyPolynomial(Polynomial *a, Polynomial *b);

#endif /* DATA_STRUCTURE_IN_C_LIST_POLYNOMIAL_H_ */
