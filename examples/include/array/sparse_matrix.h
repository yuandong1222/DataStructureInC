/*
 * sparse_matrix.h
 *
 *  Created on: 2009-7-25
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_ARRAY_SPARSE_MATRIX_H_
#define DATA_STRUCTURE_IN_C_ARRAY_SPARSE_MATRIX_H_

//��ʼ��
//���ݸ�������������������ϡ�����
//������
//	matrix:			���ڷ��ؾ����ָ��
//	row_length:		���������
//	column_length:	���������
Status Initial(SPARSE_MATRIX_TYPE *matrix, int row_length, int column_length);

//����
//���پ���
//������
//	array:	Ҫ���ٵľ���
Status Destory(SPARSE_MATRIX_TYPE *matrix);

//��ֵ
//�Ը����±��Ԫ�ظ�ֵ
//������
//	matrix:			Ҫ�����ľ���
//	row_index:		���±�
//	column_index:	���±�
//	element:		Ԫ��ֵ
Status Assign(SPARSE_MATRIX_TYPE matrix, int row_index, int column_index,
		ElementType element);

//ȡֵ
//ȡ�ø����±��Ԫ��ֵ
//������
//	matrix:			Ҫ�����ľ���
//	element:		Ԫ��ֵ
//	row_index:		���±�
//	column_index:	���±�
Status Value(SPARSE_MATRIX_TYPE matrix, ElementType *element, int row_index,
		int column_index);

//����
//���ƾ���
//������
//	matrix:				Ҫ���Ƶľ���
//	matrix_duplication:	���صĸ���
Status Copy(SPARSE_MATRIX_TYPE matrix, SPARSE_MATRIX_TYPE *matrix_duplication);

//����ӷ�
//����������ĺ͡�����a��b�����������������Ӧ��ȡ�
//������
//	a:		����a
//	b:		����b
//	sum:	a��b�ĺ�
Status Add(SPARSE_MATRIX_TYPE a, SPARSE_MATRIX_TYPE b, SPARSE_MATRIX_TYPE *sum);

//�������
//����������Ĳ����a��b�����������������Ӧ��ȡ�
//������
//	a:		������
//	b:		����
//	sub:	a��b�Ĳ�
Status Subtract(SPARSE_MATRIX_TYPE a, SPARSE_MATRIX_TYPE b,
		SPARSE_MATRIX_TYPE *sub);

//����˷�
//����������ĳ˻���Ҫ��a����������b��������a����������b��������
//������
//	a:			����a
//	b:			����b
//	product:	a��b�ĳ˻�
Status Multiply(SPARSE_MATRIX_TYPE a, SPARSE_MATRIX_TYPE b,
		SPARSE_MATRIX_TYPE *product);

//ת��
//������ת��
//������
//	matrix:				Ҫת�õľ���
//	matrix_transposed:	���صĽ��
Status Transpose(SPARSE_MATRIX_TYPE matrix,
		SPARSE_MATRIX_TYPE *matrix_transposed);

#endif /* DATA_STRUCTURE_IN_C_ARRAY_SPARSE_MATRIX_H_ */
