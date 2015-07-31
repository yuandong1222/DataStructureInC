/*
 * string.h
 *
 *  Created on: 2009-6-3
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_STRING_STRING_H_
#define DATA_STRUCTURE_IN_C_STRING_STRING_H_

#include "include/common.h"

//��ֵ
//����һ����ֵ����chars���ַ���string
Status Assign(STRING_TYPE *string, char chars[]);

//����
//����string����һ���µ��ַ���new
Status Copy(STRING_TYPE *new, STRING_TYPE string);

//�п�
//�ж��ַ���string�Ƿ�Ϊ�գ�����Ϊ�㣩���ǵĻ�����TRUE�����򷵻�FALSE
BOOLEAN Empty(STRING_TYPE string);

//�Ƚ�
//��a > b���򷵻�1����a = b���򷵻�0����a < b���򷵻�-1��
int Compare(STRING_TYPE a, STRING_TYPE b);

//�󳤶�
//����string���ַ��ĸ�������Ϊ���ĳ���
int Length(STRING_TYPE string);

//���
//��string��Ϊ�մ�
Status Clear(STRING_TYPE string);

//����
//��result����a��b���Ӷ��ɵ��´�
Status Concat(STRING_TYPE *result, STRING_TYPE a, STRING_TYPE b);

//�Ӵ�
//��result���ش�string�ĵ�position���ַ��𳤶�Ϊlength���Ӵ�������1 <= position <= Length(string)��0 <= length <= Length(string) - position + 1
Status SubString(STRING_TYPE *result, STRING_TYPE string, int position, int length);

//��λ
//������string�д��ں��Ӵ�match��ͬ���Ӵ����򷵻���������string��position���ַ�֮���һ�γ��ֵ�λ�ã�����������0
int Index(STRING_TYPE string, STRING_TYPE match, int position);

//�滻
//��replacement�滻����string�г��ֵ�������match��ȵĲ��ص����Ӵ�
Status Replace(STRING_TYPE *string, STRING_TYPE match, STRING_TYPE replacement);

//����
//�ڴ�string�ĵ�position���ַ�֮ǰ���봮s������1 <= position < Length(string)
Status Insert(STRING_TYPE *string, int position, STRING_TYPE s);

//ɾ��
//�Ӵ�string��ɾ����position���ַ��𳤶�Ϊlength���Ӵ�
Status Delete(STRING_TYPE *string, int position, int length);

//����
//���ٴ�string
Status Destroy(STRING_TYPE *string);

#endif /* DATA_STRUCTURE_IN_C_STRING_STRING_H_ */
