/*
 * generalized_list.h
 *
 *  Created on: 2009-8-10
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_ARRAY_GENERALIZED_LIST_H_
#define DATA_STRUCTURE_IN_C_ARRAY_GENERALIZED_LIST_H_

//��ʼ��
//��ʼ�������
//������
//	list:	���ڷ��ع�����ָ��
Status Initial(GENERALIZED_LIST_TYPE* list);

//����
//���������
//������
//	list	���ڷ��ع�����ָ��
//	string:	�������ַ�����ʾ��ʽ
Status Create(GENERALIZED_LIST_TYPE* list, char* string);

//����
//���ٹ����
//������
//	list:	Ҫ���ٵĹ����
Status Destory(GENERALIZED_LIST_TYPE* list);

//����
//������
//	list:			Ҫ���ƵĹ����
//	duplication:	���Ƴ��Ĺ����
Status Copy(GENERALIZED_LIST_TYPE list, GENERALIZED_LIST_TYPE* duplication);

//����
//������ĳ��ȣ���Ԫ�صĸ���
//������
//	list:	Ҫ�󳤶ȵĹ����
int Length(GENERALIZED_LIST_TYPE list);

//���
//����������
//������
//	list:	Ҫ����ȵĹ����
int Depth(GENERALIZED_LIST_TYPE list);

//�п�
//�ж�list�Ƿ�Ϊ�ձ�
//������
//	list:	Ҫ�пյĹ����
BOOLEAN Empty(GENERALIZED_LIST_TYPE list);

//ȡͷԪ��
//ȡ������ͷԪ�أ���������Ϊ�ձ����ؿ�
//������
//	list:	ҪȡͷԪ�صĹ����
GENERALIZED_LIST_TYPE GetHead(GENERALIZED_LIST_TYPE list);

//ȡβԪ��
//ȡ������βԪ�أ���������Ϊ�ձ����ؿ�
//������
//	list:	ҪȡβԪ�صĹ����
GENERALIZED_LIST_TYPE GetTail(GENERALIZED_LIST_TYPE list);

//��ͷ����
//����Ԫ��element��Ϊlist�ĵ�һԪ��
//������
//	list:		Ҫ����Ԫ�صĹ����
//	element:	Ҫ�����Ԫ��
Status InsertFirst(GENERALIZED_LIST_TYPE* list, GENERALIZED_LIST_TYPE* element);

//��ͷɾ��
//ɾ��list�ĵ�һ��Ԫ�أ�����element����
//������
//	list:		Ҫɾ��Ԫ�صĹ����
//	element:	����ɾ����Ԫ��
Status DeleteFirst(GENERALIZED_LIST_TYPE* list, GENERALIZED_LIST_TYPE* element);

//����
//ʹ��visit������������������нڵ�
//����:
//	list:	Ҫ�����Ĺ����
//	visit:	��������
Status Traverse(GENERALIZED_LIST_TYPE* list, Status(*visit)(ElementType*));

#endif /* DATA_STRUCTURE_IN_C_ARRAY_GENERALIZED_LIST_H_ */
