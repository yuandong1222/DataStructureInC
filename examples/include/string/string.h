/*
 * string.h
 *
 *  Created on: 2009-6-3
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_STRING_STRING_H_
#define DATA_STRUCTURE_IN_C_STRING_STRING_H_

#include "include/common.h"

//赋值
//生成一个其值等于chars的字符串string
Status Assign(STRING_TYPE *string, char chars[]);

//复制
//复制string生成一个新的字符串new
Status Copy(STRING_TYPE *new, STRING_TYPE string);

//判空
//判断字符串string是否为空（长度为零），是的话返回TRUE，否则返回FALSE
BOOLEAN Empty(STRING_TYPE string);

//比较
//若a > b，则返回1；若a = b，则返回0；若a < b，则返回-1；
int Compare(STRING_TYPE a, STRING_TYPE b);

//求长度
//返回string中字符的个数，称为串的长度
int Length(STRING_TYPE string);

//清空
//将string清为空串
Status Clear(STRING_TYPE string);

//连接
//用result返回a和b连接而成的新串
Status Concat(STRING_TYPE *result, STRING_TYPE a, STRING_TYPE b);

//子串
//用result返回串string的第position个字符起长度为length的子串，其中1 <= position <= Length(string)且0 <= length <= Length(string) - position + 1
Status SubString(STRING_TYPE *result, STRING_TYPE string, int position, int length);

//定位
//若主串string中存在和子串match相同的子串，则返回它在主串string第position个字符之后第一次出现的位置；否则函数返回0
int Index(STRING_TYPE string, STRING_TYPE match, int position);

//替换
//用replacement替换主串string中出现的所有与match相等的不重叠的子串
Status Replace(STRING_TYPE *string, STRING_TYPE match, STRING_TYPE replacement);

//插入
//在串string的第position个字符之前插入串s，其中1 <= position < Length(string)
Status Insert(STRING_TYPE *string, int position, STRING_TYPE s);

//删除
//从串string中删除第position个字符起长度为length的子串
Status Delete(STRING_TYPE *string, int position, int length);

//销毁
//销毁串string
Status Destroy(STRING_TYPE *string);

#endif /* DATA_STRUCTURE_IN_C_STRING_STRING_H_ */
