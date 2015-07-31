/*
 * link_stack.c
 *
 *  Created on: 2009-5-16
 *      Author: yuandong
 */

#include <stdlib.h>
#include <stdio.h>

#include "include/common.h"
#include "include/stack/link_stack.h"
#include "include/stack/stack.h"

Status InitialStack(STACK_TYPE *stack) {
}

Status DestroyStack(STACK_TYPE *stack) {
}

Status ClearStack(STACK_TYPE stack) {
}

BOOLEAN StackEmpty(STACK_TYPE stack) {
}

int StackLength(STACK_TYPE stack) {
}

Status GetTop(STACK_TYPE stack, ElementType *element) {
}

Status Push(STACK_TYPE stack, ElementType element) {
}

Status Pop(STACK_TYPE stack, ElementType *element) {
}

Status Traverse(STACK_TYPE stack, Status(*visit)(ElementType *element)) {
}
