/*
 * link_string.c
 *
 *  Created on: 2009-5-16
 *      Author: yuandong
 */

#include <stdlib.h>
#include <stdio.h>

#include "include/common.h"
#include "include/string/link_string.h"
#include "include/string/string.h"

#include "include/common.h"

Status Assign(STRING_TYPE *string, char chars[]) {
	*string = (LinkString) malloc(sizeof(LinkStringHead));
	if (*string == NULL)
		return OVERFLOW;

	(*string) -> head = NULL;
	(*string) -> tail = NULL;

	int chars_index = 0;
	int current_chunk_index = 0;
	Chunk *current_chunk = NULL;
	while (chars[chars_index] != '\0') {
		if ((*string) -> head == NULL) {
			(*string) -> head = (Chunk*) malloc(sizeof(Chunk));
			if ((*string) -> head == NULL)
				return OVERFLOW;

			(*string) -> head -> data = (char*) malloc(sizeof(char) * CHUNK_SIZE);
			if ((*string) -> head -> data == NULL)
				return OVERFLOW;

			(*string) -> head -> next = NULL;

			current_chunk = (*string) -> head;
		} else if (current_chunk_index == CHUNK_SIZE) {
			current_chunk -> next = (Chunk*) malloc(sizeof(Chunk));
			if (current_chunk -> next == NULL)
				return OVERFLOW;

			current_chunk -> next -> data = (char*) malloc(sizeof(char) * CHUNK_SIZE);
			if (current_chunk -> next -> data == NULL)
				return OVERFLOW;
			current_chunk -> next -> next = NULL;

			current_chunk = current_chunk -> next;
			current_chunk_index = 0;
		}

		(current_chunk -> data)[current_chunk_index] = chars[chars_index];
		current_chunk_index++;

		chars_index++;
	}
	while (current_chunk != NULL && current_chunk_index < CHUNK_SIZE) {
		(current_chunk -> data)[current_chunk_index] = BLANK;
		current_chunk_index++;
	}
	(*string) -> tail = current_chunk;
	(*string) -> length = chars_index;

	return OK;
}

Status Copy(STRING_TYPE *new, STRING_TYPE string) {

	*new = (LinkString) malloc(sizeof(LinkStringHead));
	if (*new == NULL)
		return OVERFLOW;

	(*new) -> length = string -> length;
	(*new) -> head = NULL;
	(*new) -> tail = NULL;

	Chunk *current_chunk = string -> head, *new_current_chunk = NULL;
	int current_chunk_index = 0;
	while (current_chunk != NULL) {
		if ((*new) -> head == NULL) {
			(*new) -> head = (Chunk*) malloc(sizeof(Chunk));
			if ((*new) -> head == NULL)
				return OVERFLOW;

			new_current_chunk = (*new) -> head;
			new_current_chunk -> next = NULL;
			new_current_chunk -> data = (char*)malloc(sizeof(char) * CHUNK_SIZE);
			if (new_current_chunk -> data == NULL)
				return OVERFLOW;
		}
		if (current_chunk_index == CHUNK_SIZE) {
			current_chunk = current_chunk -> next;
			current_chunk_index = 0;

			if (current_chunk == NULL)
				break;

			new_current_chunk -> next = (Chunk*) malloc(sizeof(Chunk));
			if (new_current_chunk -> next == NULL)
				return OVERFLOW;

			new_current_chunk -> next -> next = NULL;
			new_current_chunk -> next -> data = (char*)malloc(sizeof(char) * CHUNK_SIZE);
			if (new_current_chunk -> data == NULL)
				return OVERFLOW;

			new_current_chunk = new_current_chunk -> next;
		}

		(new_current_chunk -> data)[current_chunk_index]
				= (current_chunk -> data)[current_chunk_index];

		current_chunk_index++;
	}

	(*new) -> tail = new_current_chunk;

	return OK;
}

Status Empty(STRING_TYPE string) {
	return string -> length == 0;
}

int Compare(STRING_TYPE a, STRING_TYPE b) {

	if (a == NULL)
		return b == NULL ? 0 : -1;
	if (b == NULL)
		return a == NULL ? 0 : 1;

	Chunk *current_chunk_a = a -> head, *current_chunk_b = b -> head;
	int current_chunk_index_a = 0, current_chunk_index_b = 0;

	while (TRUE) {
		//get next char for a
		while (current_chunk_a != NULL
				&& (current_chunk_a -> data)[current_chunk_index_a] == BLANK) {
			current_chunk_index_a++;
			if (current_chunk_index_a == CHUNK_SIZE) {
				current_chunk_a = current_chunk_a -> next;
				current_chunk_index_a = 0;
			}
		}
		//get next char for b
		while (current_chunk_b != NULL
				&& (current_chunk_b -> data)[current_chunk_index_b] == BLANK) {
			current_chunk_index_b++;
			if (current_chunk_index_b == CHUNK_SIZE) {
				current_chunk_b = current_chunk_b -> next;
				current_chunk_index_b = 0;
			}
		}
		//if arrive at the end?
		if (current_chunk_a == NULL || current_chunk_b == NULL)
			break;

		//compare
		if ((current_chunk_a -> data)[current_chunk_index_a]
				> (current_chunk_b -> data)[current_chunk_index_b])
			return 1;
		else if ((current_chunk_a -> data)[current_chunk_index_a]
				< (current_chunk_b -> data)[current_chunk_index_b])
			return -1;

		//next
		current_chunk_index_a++;
		if (current_chunk_index_a == CHUNK_SIZE) {
			current_chunk_a = current_chunk_a -> next;
			current_chunk_index_a = 0;
		}
		current_chunk_index_b++;
		if (current_chunk_index_b == CHUNK_SIZE) {
			current_chunk_b = current_chunk_b -> next;
			current_chunk_index_b = 0;
		}
	}

	if (current_chunk_a == NULL && current_chunk_b == NULL)
		return 0;
	if (current_chunk_a == NULL)
		return -1;

	return 1;
}

int Length(STRING_TYPE string) {
	return string -> length;
}

Status Clear(STRING_TYPE string) {
	if (string == NULL)
		return ERROR;

	Chunk *current = string -> head, *next = NULL;
	while (current != NULL) {
		next = current -> next;
		free(current -> data);
		free(current);

		current = next;
	}
	string -> head = NULL;
	string -> tail = NULL;
	string -> length = 0;
	return OK;
}

Status Concat(STRING_TYPE *result, STRING_TYPE a, STRING_TYPE b) {
	LinkString b_copy = NULL;
	Status status;

	status = Copy(result, a);
	if (status != OK)
		return status;

	status = Copy(&b_copy, b);
	if (status != OK)
		return status;

	(*result) -> tail -> next = b_copy -> head;
	(*result) -> tail = b_copy -> tail;
	(*result) -> length += b_copy -> length;

	free(b_copy);
	return OK;
}

Status SubString(STRING_TYPE *result, STRING_TYPE string, int position,
		int length) {
	int stringLength = Length(string);
	if (position < 1 || position > stringLength || length < 0 || length
			> stringLength - position + 1)
		return ERROR;

	int current_chunk_index = 0, index = 0;
	Chunk *current_chunk = string -> head;

	while (current_chunk != NULL && index < position - 1) {
		if ((current_chunk -> data)[current_chunk_index] != BLANK) {
			current_chunk_index++;
			index++;
		} else {
			current_chunk_index++;
		}
		if (current_chunk_index == CHUNK_SIZE) {
			current_chunk = current_chunk -> next;
			current_chunk_index = 0;
		}
	}

	*result = (LinkString) malloc(sizeof(LinkStringHead));
	if (*result == NULL)
		return OVERFLOW;

	(*result) -> length = 0;
	(*result) -> head = NULL;
	(*result) -> tail = NULL;

	int result_length = 0, result_current_chunk_index = 0;
	Chunk *result_current_chunk = NULL;

	while (current_chunk != NULL && result_length < length) {
		if ((*result) -> head == NULL) {
			(*result) -> head = (Chunk*) malloc(sizeof(Chunk));
			if ((*result) -> head == NULL)
				return OVERFLOW;

			result_current_chunk = (*result) -> head;
			result_current_chunk -> next = NULL;
			result_current_chunk -> data = (char*)malloc(sizeof(char) * CHUNK_SIZE);
			if (result_current_chunk -> data == NULL)
				return OVERFLOW;
		}
		if (current_chunk_index == CHUNK_SIZE) {
			current_chunk = current_chunk -> next;
			current_chunk_index = 0;

			if (current_chunk == NULL)
				break;
		}
		if (result_current_chunk_index == CHUNK_SIZE) {
			result_current_chunk -> next = (Chunk*) malloc(sizeof(Chunk));
			if (result_current_chunk -> next == NULL)
				return OVERFLOW;

			result_current_chunk -> next -> next = NULL;
			result_current_chunk -> next -> data = (char*)malloc(sizeof(char) * CHUNK_SIZE);
			if (result_current_chunk -> data == NULL)
				return OVERFLOW;

			result_current_chunk = result_current_chunk -> next;
			result_current_chunk_index = 0;
		}

		if ((current_chunk -> data)[current_chunk_index] != BLANK) {
			(result_current_chunk -> data)[result_current_chunk_index]
					= (current_chunk -> data)[current_chunk_index];

			result_current_chunk_index++;
			result_length++;
		}

		current_chunk_index++;
	}
	while (result_current_chunk != NULL && result_current_chunk_index < CHUNK_SIZE) {
		(result_current_chunk -> data)[result_current_chunk_index] = BLANK;
		result_current_chunk_index++;
	}

	(*result) -> tail = result_current_chunk;
	(*result) -> length = result_length;

	return OK;
}
int Index(STRING_TYPE string, STRING_TYPE match, int position) {
	int index = position;
	while (index <= Length(string) - Length(match) + 1) {
		LinkString s = NULL;
		SubString(&s, string, index, Length(match));

		int result = Compare(match, s);
		Destroy(&s);

		if (result == 0)
			return index;

		index++;
	}
	return 0;
}

Status Zip(STRING_TYPE *string) {
	int current_index = 0, next_index = 0;
	Chunk *current_chunk = (*string) -> head, *next_chunk = (*string) -> head;

	while (next_chunk != NULL) {
		if ((next_chunk -> data)[next_index] != BLANK) {
			if (current_index == CHUNK_SIZE) {
				current_chunk = current_chunk -> next;
				current_index = 0;
			}

			(current_chunk -> data)[current_index]
					= (next_chunk -> data)[next_index];

			current_index++;
		}

		next_index++;
		if (next_index == CHUNK_SIZE) {
			next_chunk = next_chunk -> next;
			next_index = 0;
		}
	}

	while (current_chunk != NULL && current_index < CHUNK_SIZE) {
		(current_chunk -> data)[current_index] = BLANK;
		current_index++;
	}
	(*string) -> tail = current_chunk;

	next_chunk = current_chunk -> next;
	current_chunk -> next = NULL;
	while (next_chunk != NULL) {
		current_chunk = next_chunk -> next;
		free(next_chunk -> data);
		free(next_chunk);
		next_chunk = current_chunk;
	}

	return OK;
}

Status Replace(STRING_TYPE *string, STRING_TYPE match, STRING_TYPE replacement) {
	if (Empty(*string))
		return ERROR;

	int index = 1;

	do {
		index = Index(*string, match, index);
		if (index != 0) {
			Delete(string, index, Length(match));
			Insert(string, index, replacement);
			index += Length(replacement);
		}
	} while (index != 0);

	return OK;
}

Status Insert(STRING_TYPE *string, int position, STRING_TYPE s) {
	if (position < 1 || position > Length(*string) + 1)
		return ERROR;
	if (Length(s) == 0)
		return OK;

	LinkString s_duplication;
	Status status;

	status = Copy(&s_duplication, s);
	if (status != OK)
		return OK;

	int string_index = 0, count = 0;
	Chunk *string_chunk = (*string) -> head;
	while (count < position - 1) {
		if (string_index == CHUNK_SIZE) {
			string_chunk = string_chunk -> next;
			string_index = 0;
		}

		if ((string_chunk -> data)[string_index] != BLANK) {
			count++;
		}
		string_index++;
	}
	if (string_index != CHUNK_SIZE) {
		Chunk *chunk = (Chunk*) malloc(sizeof(Chunk));
		if (chunk == NULL)
			return OVERFLOW;

		chunk -> data = (char*)malloc(sizeof(char) * CHUNK_SIZE);
		if (chunk -> data == NULL)
			return OVERFLOW;

		chunk -> next = string_chunk -> next;

		int chunk_index = 0;
		while (chunk_index < string_index) {
			(chunk -> data)[chunk_index] = BLANK;
			chunk_index++;
		}
		while (chunk_index < CHUNK_SIZE) {
			(chunk -> data)[chunk_index] = (string_chunk -> data)[chunk_index];
			chunk_index++;
		}

		while (string_index < CHUNK_SIZE) {
			(string_chunk -> data)[string_index] = BLANK;
			string_index++;
		}

		string_chunk -> next = chunk;
	}

	s_duplication -> tail -> next = string_chunk -> next;
	string_chunk -> next = s_duplication -> head;
	(*string) -> length = (*string) -> length + s_duplication -> length;

	free(s_duplication);
	return OK;
}

Status Delete(STRING_TYPE *string, int position, int length) {
	if (position < 1)
		return ERROR;

	int index = 0, count = 0;
	Chunk *chunk = (*string) -> head;
	while (chunk != NULL && count < position - 1) {
		if ((chunk -> data)[index] != BLANK) {
			count++;
		}
		index++;
		if (index == CHUNK_SIZE) {
			chunk = chunk -> next;
			index = 0;
		}
	}
	int deleted_count = 0;
	while (chunk != NULL && deleted_count < length) {
		if ((chunk -> data)[index] != BLANK) {
			(chunk -> data)[index] = BLANK;
			deleted_count++;
		}
		index++;
		if (index == CHUNK_SIZE) {
			chunk = chunk -> next;
			index = 0;
		}
	}
	(*string) -> length = (*string) -> length - deleted_count;
	return OK;
}

Status Destroy(STRING_TYPE *string) {
	Clear(*string);
	free(*string);
	*string = NULL;

	return OK;
}
