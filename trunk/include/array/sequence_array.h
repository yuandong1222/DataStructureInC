/*
 * sequence_array.h
 *
 *  Created on: 2009-7-19
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_ARRAY_SEQUENCE_ARRAY_H_
#define DATA_STRUCTURE_IN_C_ARRAY_SEQUENCE_ARRAY_H_

#define ElementType int

#include "include/common.h"

typedef struct {
	int dimension;
	ElementType *base;
	int *bounds;
	int *constants;

} SequenceArrayHead, *SequenceArray;

//初始化
//根据给定的维度和每个维度的维界构造数组
//参数：
//	array:		用于返回数组的指针
//	dimension:	数组的维度
//	...:		各维度的维界
Status Initial(SequenceArray* array, int dimension, ...);

//销毁
//销毁数组
//参数：
//	array:		要销毁的数组
Status Destory(SequenceArray* array);

//赋值
//对给定下标的元素赋值
//参数：
//	array:		要操作的数组
//	element:	元素值
//	...:		下标
Status Assign(SequenceArray array, ElementType element, int dimension, ...);

//取值
//取得给定下标的元素值
//参数：
//	array:		要操作的数组
//	element:	元素值
//	...:		下标
Status Value(SequenceArray array, ElementType *element, int dimension, ...);

#endif /* DATA_STRUCTURE_IN_C_ARRAY_SEQUENCE_ARRAY_H_ */
