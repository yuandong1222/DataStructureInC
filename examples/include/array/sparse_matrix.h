/*
 * sparse_matrix.h
 *
 *  Created on: 2009-7-25
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_ARRAY_SPARSE_MATRIX_H_
#define DATA_STRUCTURE_IN_C_ARRAY_SPARSE_MATRIX_H_

//初始化
//根据给定的行数和列数构造稀疏矩阵
//参数：
//	matrix:			用于返回矩阵的指针
//	row_length:		矩阵的行数
//	column_length:	矩阵的列数
Status Initial(SPARSE_MATRIX_TYPE *matrix, int row_length, int column_length);

//销毁
//销毁矩阵
//参数：
//	array:	要销毁的矩阵
Status Destory(SPARSE_MATRIX_TYPE *matrix);

//赋值
//对给定下标的元素赋值
//参数：
//	matrix:			要操作的矩阵
//	row_index:		行下标
//	column_index:	列下标
//	element:		元素值
Status Assign(SPARSE_MATRIX_TYPE matrix, int row_index, int column_index,
		ElementType element);

//取值
//取得给定下标的元素值
//参数：
//	matrix:			要操作的矩阵
//	element:		元素值
//	row_index:		行下标
//	column_index:	列下标
Status Value(SPARSE_MATRIX_TYPE matrix, ElementType *element, int row_index,
		int column_index);

//复制
//复制矩阵
//参数：
//	matrix:				要复制的矩阵
//	matrix_duplication:	返回的副本
Status Copy(SPARSE_MATRIX_TYPE matrix, SPARSE_MATRIX_TYPE *matrix_duplication);

//矩阵加法
//求两个矩阵的和。矩阵a和b的行数和列数必须对应相等。
//参数：
//	a:		矩阵a
//	b:		矩阵b
//	sum:	a和b的和
Status Add(SPARSE_MATRIX_TYPE a, SPARSE_MATRIX_TYPE b, SPARSE_MATRIX_TYPE *sum);

//矩阵减法
//求两个矩阵的差。矩阵a和b的行数和列数必须对应相等。
//参数：
//	a:		被减数
//	b:		减数
//	sub:	a和b的差
Status Subtract(SPARSE_MATRIX_TYPE a, SPARSE_MATRIX_TYPE b,
		SPARSE_MATRIX_TYPE *sub);

//矩阵乘法
//求两个矩阵的乘积。要求a的行数等于b的列数，a的列数等于b的行数。
//参数：
//	a:			矩阵a
//	b:			矩阵b
//	product:	a和b的乘积
Status Multiply(SPARSE_MATRIX_TYPE a, SPARSE_MATRIX_TYPE b,
		SPARSE_MATRIX_TYPE *product);

//转置
//求矩阵的转置
//参数：
//	matrix:				要转置的矩阵
//	matrix_transposed:	返回的结果
Status Transpose(SPARSE_MATRIX_TYPE matrix,
		SPARSE_MATRIX_TYPE *matrix_transposed);

#endif /* DATA_STRUCTURE_IN_C_ARRAY_SPARSE_MATRIX_H_ */
