/*
 * sequence_string.c
 *
 *  Created on: 2009-5-16
 *      Author: yuandong
 */

#include <stdlib.h>
#include <stdio.h>

#include "include/common.h"
#include "include/string/sequence_string.h"
#include "include/string/string.h"

#include "include/common.h"

Status Assign(STRING_TYPE *string, char chars[]) {
	(*string) = (char*) malloc(sizeof(char) * (MAX_LENGTH + 1));
	if ((*string) == NULL)
		return OVERFLOW;

	int index = 0;
	while (*(chars + index) != '\0') {
		*((*string) + index + 1) = *(chars + index);
		index++;
	}
	**string = index;
	return OK;
}

Status Copy(STRING_TYPE *new, STRING_TYPE string) {
	(*new) = (char*) malloc(sizeof(char) * (MAX_LENGTH + 1));
	if ((*new) == NULL)
		return OVERFLOW;

	int index = 0;
	while (index <= string[0]) {
		*((*new) + index) = *(string + index);
		index++;
	}
	return OK;
}

BOOLEAN Empty(STRING_TYPE string) {
	return string == NULL || *string == 0;
}

int Compare(STRING_TYPE a, STRING_TYPE b) {

	if (a == NULL)
		return b == NULL ? 0 : -1;
	if (b == NULL)
		return a == NULL ? 0 : 1;

	char *pointer_a = a + 1, *pointer_b = b + 1;
	while (pointer_a - (a + 1) < a[0] && pointer_b - (b + 1) < b[0]) {
		if (*pointer_a > *pointer_b)
			return 1;
		else if (*pointer_a < *pointer_b)
			return -1;

		pointer_a++;
		pointer_b++;
	}
	if (pointer_a - (a + 1) == a[0] && pointer_b - (b + 1) != b[0])
		return -1;
	if (pointer_a - (a + 1) != a[0] && pointer_b - (b + 1) == b[0])
		return 1;

	return 0;
}

int Length(STRING_TYPE string) {
	if (string == NULL)
		return 0;

	return string[0];
}

Status Clear(STRING_TYPE string) {
	if (string == NULL)
		return ERROR;

	*string = 0;

	return OK;
}

Status Concat(STRING_TYPE *result, STRING_TYPE a, STRING_TYPE b) {
	(*result) = (STRING_TYPE) malloc(sizeof(char) * (MAX_LENGTH + 1));
	if (*result == NULL)
		return OVERFLOW;

	char *index_a = a + 1, *index_b = b + 1, *index_result = *result + 1;

	while (index_a - (a + 1) < a[0] && index_result - ((*result) + 1)
			< MAX_LENGTH) {
		*index_result = *index_a;
		index_a++;
		index_result++;
	}
	while (index_b - (b + 1) < b[0] && index_result - ((*result) + 1)
			< MAX_LENGTH) {
		*index_result = *index_b;
		index_b++;
		index_result++;
	}
	**result = index_result - (*result + 1);

	return OK;
}

Status SubString(STRING_TYPE *result, STRING_TYPE string, int position,
		int length) {
	//ÆäÖÐ1 <= position <= Length(string)ÇÒ0 <= length <= Length(string) - position + 1
	int stringLength = Length(string);
	if (position < 1 || position > stringLength || length < 0 || length
			> stringLength - position + 1)
		return ERROR;

	(*result) = (STRING_TYPE) malloc(sizeof(char) * (MAX_LENGTH + 1));
	if (*result == NULL)
		return OVERFLOW;

	int index = position;
	while (index < position + length) {
		(*result)[index - position + 1] = string[index];
		index++;
	}

	*(*result) = length;
	return OK;
}

int* getMatchNext(STRING_TYPE match) {
	if (Empty(match))
		return NULL;

	int length = Length(match);
	int* next = (int*) malloc(sizeof(int) * (length + 1));
	int i = 1, j = 0;

	next[1] = 0;
	while (i < length) {
		if (j == 0 || match[i] == match[j]) {
			j++;
			i++;
			if (match[i] == match[j])
				next[i] = next[j];
			else
				next[i] = j;
		} else {
			j = next[j];
		}
	}

	return next;
}
int Index(STRING_TYPE string, STRING_TYPE match, int position) {
	if (Empty(match))
		return position;

	int* next = getMatchNext(match);
	int string_index = position;
	int match_index = 1;

	while (string_index <= string[0]) {
		if (next[match_index] == 0 || string[string_index]
				== match[match_index]) {
			string_index++;
			match_index++;
			if (match_index == match[0] + 1)
				return string_index - match_index + 1;
		} else {
			match_index = next[match_index];
		}
	}
	return 0;
}
Status Replace(STRING_TYPE *string, STRING_TYPE match, STRING_TYPE replacement) {
	if (Empty(match))
		return OK;

	char *result = (char*) malloc(sizeof(char) * (MAX_LENGTH + 1));
	if (result == NULL)
		return OVERFLOW;

	int matched_index = Index(*string, match, 1);
	int result_index = 1, string_index = 1, replacement_index = 1;
	while (matched_index != 0) {
		while (string_index < matched_index) {
			result[result_index] = (*string)[string_index];

			string_index++;
			result_index++;

			if (result_index == MAX_LENGTH)
				break;
		}
		if (result_index == MAX_LENGTH)
			break;

		string_index += match[0];

		replacement_index = 1;
		while (replacement_index <= replacement[0]) {
			result[result_index] = replacement[replacement_index];

			replacement_index++;
			result_index++;

			if (result_index == MAX_LENGTH)
				break;
		}
		if (result_index == MAX_LENGTH)
			break;

		matched_index = Index(*string, match, matched_index + 1);
	}

	result[0] = result_index - 1;

	free(*string);
	*string = result;

	return OK;
}

Status Insert(STRING_TYPE *string, int position, STRING_TYPE s) {
	int s_length = Length(s);
	int string_length = Length(*string);

	if (position < 1 || position > string_length + 1)
		return ERROR;

	if (s_length + string_length > MAX_LENGTH)
		return OVERFLOW;

	int index = 0;
	while (index < string_length - position + 1) {
		*(*string + string_length + s_length - index) = *(*string
				+ string_length - index);
		index++;
	}

	index = 0;
	while (index < s_length) {
		*(*string + position + index) = *(s + index + 1);
		index++;
	}

	**string = s_length + string_length;

	return OK;
}

Status Delete(STRING_TYPE *string, int position, int length) {
	if (position < 1)
		return ERROR;

	char *index = (*string) + 1;
	while (index - (*string) - 1 < **string && index - (*string) < position)
		index++;
	while (index - (*string) - 1 + length < **string) {
		*index = *(index + length);
		index++;
	}
	**string = index - (*string) - 1;
	return OK;
}

Status Destroy(STRING_TYPE *string) {
	free(*string);
	*string = NULL;
	return OK;
}
