/*
 * head_link_list.h
 *
 *  Created on: 2009-4-10
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_HEAD_LIST_LINK_LIST_H_
#define DATA_STRUCTURE_IN_C_HEAD_LIST_LINK_LIST_H_

#define ElementType int
#define LIST_TYPE HeadLinkList

#include "include/common.h"

//���Ա�ĵ�����洢�ṹ
typedef struct HeadLinkListNode {
	ElementType data;
	struct HeadLinkListNode *next;
} HeadLinkListNode, *Position, *Link;

//��ͷ���������ӱ�ı�ͷ
typedef struct HeadLinkListHeadNode {
	int length;
	HeadLinkListNode *head, *tail;
} HeadLinkListHeadNode, *HeadLinkList;

//����ڵ�
//�����������node����ΪֵΪelement�Ľڵ㣬������OK��������ʧ�ܣ�����ERROR
//����
//	node��		���صĽڵ�
//	element��	�ڵ��ֵ
Status MakeNode(HeadLinkListNode **node, ElementType element);

//�ͷŽڵ�
//����������ͷ�node��ָ��Ľڵ�
//����
//	node��	Ҫ�ͷŵĽڵ�
void FreeNode(HeadLinkListNode **node);

//����һ�����Ա�
//�������������һ���յ����Ա�list
//����
//	list:	Ҫ��������Ա�
Status InitialList(LIST_TYPE *list);

//����һ�����Ա�
//��ʼ���������Ա�list�Ѵ��ڡ�
//����������������Ա�list
//����
//	list:	Ҫ�����ٵ����Ա�
Status DestroyList(LIST_TYPE *list);

//���һ�����Ա�
//��ʼ���������Ա�list�Ѵ��ڡ�
//�����������list����Ϊ�ձ�,���ı�list
//����
//	list:	Ҫ����������Ա�
Status ClearList(LIST_TYPE list);

//�ڵ�һλ����
//��ʼ������list�Ѵ���
//�����������node��ָ��Ľڵ����list�ĵ�һ��λ����
//����
//	list��	Ҫ��������Ա�
//	node��	Ҫ����Ľڵ�
Status InsertFirst(LIST_TYPE list, HeadLinkListNode *node);

//ɾ����һ���ڵ�
//��ʼ������list�Ѵ���
//���������ɾ����һ���ڵ㣬����node���ء�������Ա�Ϊ�գ��򷵻�NULL
//����
//	list��	Ҫɾ���ڵ�����Ա�
//	node��	ɾ���Ľڵ�
Status DeleteFirst(LIST_TYPE list, HeadLinkListNode **node);

//����
//��ʼ������list�Ѵ���
//�����������link��ָ���һ�����������list�����һ�����֮�󣬲��ı�list��βָ��ָ���µ�β���
//����
//	list��	Ҫ���ӽ�������
//	link��	Ҫ���ӵĽ�㣨����
Status Append(LIST_TYPE list, Link link);

//ȥ��
//��ʼ������list�Ѵ���
//���������ɾ��list��β��㲢��node���أ����ı�list��βָ��ָ���µ�β���
//����
//	list��	Ҫȥ����������
//	node��	ȥ���Ľ��
Status Remove(LIST_TYPE list, HeadLinkListNode **node);

//��λ��ǰ����
//��ʼ������list�Ѵ���
//�����������֪positionָ��list�е�һ����㣬��node��ָ��Ľ�������position��ָ���֮ǰ�����޸�positionָ���²���Ľ��
//����
//	list��		Ҫ�����������
//	position��	���λ��
//	node��		Ҫ����Ľ��
Status InsertBefore(LIST_TYPE list, Position *position, HeadLinkListNode *node);

//��λ�ú����
//��ʼ������list�Ѵ���
//�����������֪positionָ��list�е�һ����㣬��node��ָ��Ľ�������position��ָ���֮�󣬲��޸�positionָ���²���Ľ��
//����
//	list��		Ҫ�����������
//	position��	���λ��
//	node��		Ҫ����Ľ��
Status InsertAfter(LIST_TYPE list, Position *position, HeadLinkListNode *node);

//���ý��ֵ
//��ʼ������positionָ��list�е�һ�����
//�����������element����position��ָ�����Ԫ�����ݵ�ֵ
//����
//	position��	Ҫ���µĽ��
//	node��		�½��ֵ
Status SetElement(Position position, ElementType element);

//ȡ�ý��ֵ
//��ʼ������positionָ��list�е�һ�����
//�������������positionָ��Ľ���ֵ
//����
//	position��	Ҫȡ��ֵ�Ľ��
ElementType GetElement(Position position);

//�ж������Ƿ�Ϊ��
//��ʼ���������Ա�list�Ѵ��ڡ�
//�����������listΪ�ձ��򷵻�TRUE�����򷵻�FALSE
//����
//	list:	Ҫ�жϵ����Ա�
BOOLEAN ListEmpty(LIST_TYPE list);

//�����Ա���
//��ʼ���������Ա�list�Ѵ��ڡ�
//�������������list������Ԫ�ظ���
//����
//	list:	Ҫ�󳤶ȵ����Ա�
int ListLength(LIST_TYPE list);

//ȡ�����Ա�ĵ�һ�����
//��ʼ���������Ա�list�Ѵ��ڡ�
//�������������list�е�һ������λ�ã����listΪ�գ�����NULL
//����
//	list:	Ҫȡ�õ�һ���������Ա�
Position GetFirst(LIST_TYPE list);

//ȡ�����Ա�����һ�����
//��ʼ���������Ա�list�Ѵ��ڡ�
//�������������list�����һ������λ�ã����listΪ�գ�����NULL
//����
//	list:	Ҫȡ�����һ���������Ա�
Position GetLast(LIST_TYPE list);

//ǰ��
//��ʼ���������Ա�list�Ѵ��ڡ�positionָ��list�еĽ��
//�������������position��ǰ�������û��ǰ�����ͷ���NULL
//����
//	list:		������Ա�
//	position��	Ҫȡ��ǰ���Ľ��
Position PriorPosition(LIST_TYPE list, Position position);

//���
//��ʼ���������Ա�list�Ѵ��ڡ�positionָ��list�еĽ��
//�������������position�ĺ�̣����û�к�̣��ͷ���NULL
//����
//	list:		������Ա�
//	position��	Ҫȡ�ú�̵Ľ��
Position NextPosition(LIST_TYPE list, Position position);

//��λλ��
//��ʼ����: ���Ա�list�Ѵ���
//�������: ����list��positionIndexλ�õĽ�㣬������OK����positionIndex�Ƿ����򷵻�ERROR
//����
//	list:			Ҫ���ҵ����Ա�
//	positionIndex:	Ҫ���ҵĽ��λ��
//	position:		�ҵ��Ľ��
Status LocatePosition(LIST_TYPE list, int positionIndex, Position *position);

//��λԪ��
//��ʼ����: ���Ա�list�Ѵ���,compare()������Ԫ���ж�����(����ΪTRUE,����ΪFALSE)
//�������: ����list�е�һ����element�����ϵcompare()������Ԫ�ص�λ�á�������������Ԫ�ز�����,�򷵻�ֵΪNULL
//����
//	list:		Ҫ���ҵ����Ա�
//	element:	Ҫ���ҵ�Ԫ��
//	compare:	�Ƚ�Ԫ���Ƿ���ȵĺ���
Position LocateElement(LIST_TYPE list, ElementType element, Status(*compare)(
		ElementType, ElementType));

//����
//��ʼ���������Ա�list�Ѵ���
//������������ζ�list��ÿ������Ԫ�ص��ú���visit()��һ��visit()ʧ�ܣ������ʧ��,visit()���βμ�'*'��������ͨ������visit()�ı�Ԫ�ص�ֵ
//����
//	list:	Ҫ���������Ա�
//	visit:	��ÿ��Ԫ����Ҫִ�еĺ���
Status ListTraverse(LIST_TYPE list, Status(*visit)(ElementType*));

#endif /* DATA_STRUCTURE_IN_C_HEAD_LIST_LINK_LIST_H_ */
