/*
 * heap_string.c
 *
 *  Created on: 2009-5-16
 *      Author: yuandong
 */

#include <stdlib.h>
#include <stdio.h>

#include "include/common.h"
#include "include/string/sequence_string.h"
#include "include/string/string.h"

Status Assign(STRING_TYPE *string, char chars[]) {
	(*string) = (char*) malloc(sizeof(char) * (Length(chars) + 1));
	if ((*string) == NULL)
		return OVERFLOW;

	int index = 0;
	while (*(chars + index) != '\0') {
		*((*string) + index) = *(chars + index);
		index++;
	}
	*((*string) + index) = '\0';
	return OK;
}

Status Copy(STRING_TYPE *new, STRING_TYPE string) {
	(*new) = (char*) malloc(sizeof(char) * (Length(string) + 1));
	if ((*new) == NULL)
		return OVERFLOW;

	int index = 0;
	while (*(string + index) != '\0') {
		*((*new) + index) = *(string + index);
		index++;
	}
	*((*new) + index) = '\0';
	return OK;
}

Status Empty(STRING_TYPE string) {
	return string == NULL || *string == '\0';
}

int Compare(STRING_TYPE a, STRING_TYPE b) {

	if (a == NULL)
		return b == NULL ? 0 : -1;
	if (b == NULL)
		return a == NULL ? 0 : 1;

	char *pointer_a = a, *pointer_b = b;
	while (*pointer_a != '\0' && *pointer_b != '\0') {
		if (*pointer_a > *pointer_b)
			return 1;
		else if (*pointer_a < *pointer_b)
			return -1;

		pointer_a++;
		pointer_b++;
	}

	if (*pointer_a > *pointer_b)
		return 1;
	if (*pointer_a < *pointer_b)
		return -1;
	return 0;
}

int Length(STRING_TYPE string) {
	if (string == NULL)
		return 0;

	char* s = string;
	while (*s != '\0')
		s++;

	return s - string;
}

Status Clear(STRING_TYPE string) {
	if (string == NULL)
		return ERROR;

	*string = '\0';
	return OK;
}

Status Concat(STRING_TYPE *result, STRING_TYPE a, STRING_TYPE b) {
	int length_a = Length(a);
	int length_b = Length(b);
	int length_result = length_a + length_b;

	*result = (char*) malloc(sizeof(char) * (length_result + 1));
	if (*result == NULL)
		return OVERFLOW;

	char *pointer_a = a, *pointer_b = b, *pointer_result = *result;
	while (*pointer_a != '\0') {
		*pointer_result = *pointer_a;
		pointer_a++;
		pointer_result++;
	}
	while (*pointer_b != '\0') {
		*pointer_result = *pointer_b;
		pointer_b++;
		pointer_result++;
	}

	*pointer_result = '\0';

	return OK;
}

Status SubString(STRING_TYPE *result, STRING_TYPE string, int position,
		int length) {
	//ÆäÖÐ1 <= position <= Length(string)ÇÒ0 <= length <= Length(string) - position + 1
	int stringLength = Length(string);
	if (position < 1 || position > stringLength || length < 0 || length
			> stringLength - position + 1)
		return ERROR;

	*result = (char*) malloc(sizeof(char) * (length + 1));
	if (*result == NULL)
		return OVERFLOW;

	char *pointer = *result;
	while (pointer - *result < length) {
		*pointer = *(string + position - 1 + (pointer - *result));
		pointer++;
	}

	*pointer = '\0';
	return OK;
}

int* getMatchNext(STRING_TYPE match) {
	if (Empty(match))
		return NULL;

	int length = Length(match);
	int* next = (int*) malloc(sizeof(int) * length);
	int i = 0, j = -1;

	next[0] = -1;
	while (i < length) {
		if (j == -1 || match[i] == match[j]) {
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
	int string_index = position - 1;
	int match_index = 0;

	while (string[string_index] != '\0') {
		if (next[match_index] == -1 || string[string_index]
				== match[match_index]) {
			string_index++;
			match_index++;
			if (match[match_index] == '\0')
				return string_index - match_index + 1;
		} else {
			match_index = next[match_index];
		}
	}
	return 0;
}

Status Replace(STRING_TYPE *string, STRING_TYPE match, STRING_TYPE replacement) {
	if (Empty(match))
		return ERROR;

	int string_length = Length(*string);
	int match_length = Length(match);
	int replacement_length = Length(replacement);

	int max_match_count = string_length / match_length + 1;
	int* match_array = (int*) malloc(sizeof(int) * max_match_count);
	if (match_array == NULL)
		return OVERFLOW;

	int match_array_index = 0;
	int match_index = Index(*string, match, 1);

	while (match_index != 0) {
		match_array[match_array_index] = match_index;
		match_index = Index(*string, match, match_index + 1);
		match_array_index++;
	}

	int match_count = match_array_index;
	int result_length = string_length + ((replacement_length - match_length)
			* match_count);

	char* result = (char*) malloc(sizeof(char) * (result_length + 1));
	if (result == NULL) {
		free(match_array);
		return OVERFLOW;
	}

	match_array_index = 0;
	int result_index = 0;
	int string_index = 0;
	int replacement_index = 0;
	while (match_array_index < match_count) {
		while (string_index < match_array[match_array_index] - 1) {
			result[result_index] = (*string)[string_index];
			result_index++;
			string_index++;
		}
		string_index += match_length;

		while (replacement_index < replacement_length) {
			result[result_index] = replacement[replacement_index];
			result_index++;
			replacement_index++;
		}
		replacement_index = 0;

		match_array_index++;
	}
	result[result_index] = '\0';

	free(*string);
	*string = result;

	return OK;
}

Status Insert(STRING_TYPE *string, int position, STRING_TYPE s) {
	int length_s = Length(s);
	int length_string = Length(*string);
	int length = length_s + length_string;

	if (position < 1 || position > length_string + 1)
		return ERROR;

	char *result = (char*) malloc(sizeof(char) * (length + 1));
	if (result == NULL)
		return OVERFLOW;

	char *pointer_result = result, *pointer_s = s, *pointer_string = *string;
	while (pointer_string - *string < position - 1) {
		*pointer_result = *pointer_string;
		pointer_result++;
		pointer_string++;
	}
	while (*pointer_s != '\0') {
		*pointer_result = *pointer_s;
		pointer_result++;
		pointer_s++;
	}
	while (*pointer_string != '\0') {
		*pointer_result = *pointer_string;
		pointer_result++;
		pointer_string++;
	}

	*pointer_result = '\0';
	free(*string);
	*string = result;
	return OK;
}

Status Delete(STRING_TYPE *string, int position, int length) {
	if (position < 1 || length < 0)
		return ERROR;

	int string_length = Length(*string);
	if (position > string_length)
		return OK;

	if (position + length > string_length)
		length = string_length - position + 1;

	int newLength = string_length - length;
	char* newString = (char*) malloc(sizeof(char) * (newLength + 1));
	if (newString == NULL)
		return OVERFLOW;

	int index = 0;
	while (*(*string + index) != '\0' && index < position - 1) {
		*(newString + index) = *(*string + index);
		index++;
	}
	while (*(index + *string + length) != '\0') {
		*(newString + index) = *(index + *string + length);
		index++;
	}
	*(newString + index) = '\0';

	free(*string);
	*string = newString;

	return OK;
}

Status Destroy(STRING_TYPE *string) {
	free(*string);
	*string = NULL;
	return OK;
}
