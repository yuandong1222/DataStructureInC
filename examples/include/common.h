/*
 * common.h
 *
 *  Created on: 2009-4-10
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_COMMON_H_
#define DATA_STRUCTURE_IN_C_COMMON_H_

#define BOOLEAN		int
#define TRUE  		1
#define FALSE 		0

//Status是函数的返回类型，其值是函数结果状态代码
typedef int Status;

//函数结果状态代码
#define OK			1
#define ERROR		0
#define INFEASIBLE	-1

#ifndef OVERFLOW
#define OVERFLOW	-2
#endif

#endif /* COMMON_H_ */
