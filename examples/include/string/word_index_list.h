/*
 * string.h
 *
 *  Created on: 2009-7-15
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_STRING_WORD_INDEX_LIST_H_
#define DATA_STRUCTURE_IN_C_STRING_WORD_INDEX_LIST_H_

#include "include/common.h"

#define MAX_INDEX_WORD_COUNT 100

//�����ַ���Ϊ�Ѵ洢
#define	String char*

//�������������
typedef struct BookNumberListNode {
	int book_number;
	struct BookNumberListNode *next;

} BookNumberListNode, *BookNumberList;

//����������
typedef struct {
	String word;
	BookNumberList book_number_list;
} WordIndexListItem;

//�����������
typedef struct {
	int length;
	WordIndexListItem* items[MAX_INDEX_WORD_COUNT];
} WordIndexListHead, *WordIndexList;

//��ʼ��
//�����������
Status Initial(WordIndexList *list);

//����
//���ٴ��������ͷ�����ռ�õ��ڴ�
Status Destory(WordIndexList *list);

//����
//���ݹؼ���������ı��
//������
//	word_index_list:	��������Ĵ�������
//	word:				�����ؼ���
//	book_number:		���
Status Index(WordIndexList list, int book_number, String word);

//����
//���ݹؼ����ڸ����Ĵ��������в������
//���ҽ������int�������ʽ���������û���ҵ��κ�ƥ��ļ�¼������NULL
//������
//	word_index_list:	Ҫ��ѯ�Ĵ�������
//	word:				���ҵĹؼ���
int* Search(WordIndexList list, String word);

#endif /* DATA_STRUCTURE_IN_C_STRING_WORD_INDEX_LIST_H_ */
