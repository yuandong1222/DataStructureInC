/*
 * polynomial.h
 *
 *  Created on: 2009-5-12
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_LIST_POLYNOMIAL_H_
#define DATA_STRUCTURE_IN_C_LIST_POLYNOMIAL_H_

#include "include/common.h"

//定义项
typedef struct Term {
	float coefficient;
	int exponent;
	struct Term *next;
} Term;

//定义头结点、多项式
typedef struct PolynomialHead {
	Term *head;
} PolynomialHead, *Polynomial;

//初始化
//操作结果：构造多项式，并将polynomial指向该多项式
//参数
//	polynomial：	用于保存新构造的多项式的指针
Status InitialPolynomial(Polynomial *polynomial);

//构造
//操作结果：构造一个仅包含一项的多项式，并将polynomial指向该多项式
//参数
//	polynomial：		用于保存新构造的多项式的指针
//	coefficient：	系数
//	exponent：		指数
Status
		CreatePolynomial(Polynomial *polynomial, float coefficient,
				int exponent);

//销毁
//操作结果：销毁polynomial指向的多项式
//参数
//	polynomial：	要销毁的多项式
Status DestroyPolynomial(Polynomial *polynomial);

//求项的数目
//操作结果：返回polynomial指向的多项式中项的数目
//参数
//	polynomial：	要求项数目的多项式
int PolynomialLength(Polynomial polynomial);

//加法运算
//操作结果：完成多项式相加运算，即：Pa = Pa + Pb，并销毁Pb
//参数
//	a：	加数和返回结果
//	b：	加数
Status AddPolynomial(Polynomial *a, Polynomial *b);

//减法运算
//操作结果：完成多项式相减运算，即：Pa = Pa - Pb，并销毁Pb
//参数
//	a：	被减数和返回结果
//	b：	减数
Status SubstractPolynomial(Polynomial *a, Polynomial *b);

//乘法运算
//操作结果：完成多项式相乘运算，即：Pa = Pa * Pb，并销毁Pb
//参数
//	a：	乘数和返回结果
//	b：	乘数
Status MultiplyPolynomial(Polynomial *a, Polynomial *b);

#endif /* DATA_STRUCTURE_IN_C_LIST_POLYNOMIAL_H_ */
