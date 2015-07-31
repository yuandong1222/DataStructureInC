/*
 * word_index_list.c
 *
 *  Created on: 2009-7-15
 *      Author: yuandong
 */

#include <stdlib.h>
#include <stdio.h>

#include "include/common.h"
#include "include/string/word_index_list.h"

Status Initial(WordIndexList *word_index_list) {
	*word_index_list = (WordIndexList) malloc(sizeof(WordIndexListHead));
	if (*word_index_list == NULL)
		return OVERFLOW;

	(*word_index_list) -> length = 0;
	int i = 0;
	for (i = 0; i < MAX_INDEX_WORD_COUNT; i++) {
		((*word_index_list) -> items)[i] = NULL;
	}

	return OK;
}

int stringLength(String string) {
	if (string == NULL)
		return 0;

	char* s = string;
	while (*s != '\0')
		s++;

	return s - string;
}
int stringCompare(String a, String b) {

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
Status stringCopy(String *new, String string) {
	(*new) = (char*) malloc(sizeof(char) * (stringLength(string) + 1));
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

//find the index of the word, if not found, return -1
int getWordIndexItemIndex(WordIndexList list, String word) {
	int i = 0;
	for (i = 0; i < list -> length; i++) {
		if (stringCompare(word, (list -> items)[i] -> word) == 0)
			return i;
	}
	return -1;
}
//insert word into the list
//if success, the item will be the word index item
Status insertWord(WordIndexList list, String word, WordIndexListItem **item) {
	Status status;

	//max?
	if (list -> length == MAX_INDEX_WORD_COUNT)
		return OVERFLOW;

	//new item
	*item = (WordIndexListItem*) malloc(sizeof(WordIndexListItem));
	if (*item == NULL)
		return OVERFLOW;

	//copy string to item
	status = stringCopy(&((*item) -> word), word);
	if (status != OK)
		return status;

	//set the number list of the item to NULL
	(*item) -> book_number_list = NULL;

	//find index to insert
	int i = 0, index_to_insert = 0;
	for (i = 0; i < list -> length; i++)
		if (stringCompare(word, (list -> items)[i] -> word) < 0)
			break;
	index_to_insert = i;

	//move items after the index
	for (i = list -> length; i > index_to_insert; i--)
		(list -> items)[i] = (list -> items)[i - 1];

	//insert
	(list -> items)[index_to_insert] = *item;

	//increase list length
	(list -> length)++;

	return OK;
}
//return whether the book number in the list or not
BOOLEAN isBookNumberInList(BookNumberList list, int book_number) {
	BookNumberListNode *node = list;
	while (node != NULL) {
		if (node -> book_number == book_number)
			return TRUE;

		node = node -> next;
	}
	return FALSE;
}
//append the book number to list
Status appendBookNumberToList(BookNumberList *list, int book_number) {

	if (*list == NULL) {
		*list = (BookNumberListNode*) malloc(sizeof(BookNumberListNode));
		if (*list == NULL)
			return OVERFLOW;

		(*list) -> book_number = book_number;
		(*list) -> next = NULL;

		return OK;
	}

	BookNumberListNode *node = *list;
	while (node -> next != NULL)
		node = node -> next;

	node -> next = (BookNumberListNode*) malloc(sizeof(BookNumberListNode));
	if (node -> next == NULL)
		return OVERFLOW;

	node -> next -> book_number = book_number;
	node -> next -> next = NULL;

	return OK;
}

Status Index(WordIndexList list, int book_number, String word) {
	WordIndexListItem *item = NULL;
	Status status;

	int word_index_item_index = getWordIndexItemIndex(list, word);
	if (word_index_item_index > 0) {
		item = (list -> items)[word_index_item_index];
	} else {
		status = insertWord(list, word, &item);
		if (status != OK)
			return status;
	}

	if (isBookNumberInList(item -> book_number_list, book_number))
		return OK;

	status = appendBookNumberToList(&(item -> book_number_list), book_number);
	if (status != OK)
		return status;

	return OK;
}

int* getIntArrayFromBookNumberList(BookNumberList list) {
	BookNumberListNode *node = list;
	int length = 0;
	while (node != NULL) {
		length++;
		node = node -> next;
	}

	int *array = (int*) malloc(sizeof(int) * (length + 1));
	if (array == NULL)
		return NULL;

	array[0] = length;
	node = list;
	int index = 1;
	while (node != NULL) {
		array[index] = node -> book_number;
		node = node -> next;
		index++;
	}

	return array;
}

int* Search(WordIndexList list, String word) {
	int word_index_item_index = getWordIndexItemIndex(list, word);
	if (word_index_item_index < 0)
		return NULL;

	return getIntArrayFromBookNumberList(
			(list -> items)[word_index_item_index] -> book_number_list);
}

void freeWordIndexListItem(WordIndexListItem *item) {
	free(item -> word);

	BookNumberListNode *node = item -> book_number_list, *temp = NULL;
	while (node != NULL) {
		temp = node -> next;
		free(node);
		node = temp;
	}
}
Status Destory(WordIndexList *list) {
	int i = 0;
	for (i = 0; i < (*list) -> length; i++) {
		freeWordIndexListItem(((*list) -> items)[i]);
		free(((*list) -> items)[i]);
		((*list) -> items)[i] = NULL;
	}

	free(*list);
	*list = NULL;

	return OK;
}
