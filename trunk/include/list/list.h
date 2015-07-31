/*
 * list.inc
 *
 *  Created on: 2009-4-10
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_LIST_H_
#define DATA_STRUCTURE_IN_C_LIST_H_

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

//ȡ��Ԫ��
//��ʼ����: ���Ա�list�Ѵ��ڣ�1<=position<=ListLength(L)
//����position��Ԫ�ش���ʱ,��ֵ����element������OK,���򷵻�ERROR
//����
//	list:		Ҫ���ҵ����Ա�
//	position:	Ҫȡ�õ�Ԫ�ص�λ��
//	element:	ȡ�õ�Ԫ��
Status GetElement(LIST_TYPE list, int position, ElementType *element);

//��λ
//��ʼ����: ���Ա�list�Ѵ���,compare()������Ԫ���ж�����(����ΪTRUE,����ΪFALSE)
//�������: ����list�е�һ����element�����ϵcompare()������Ԫ�ص�λ��������������Ԫ�ز�����,�򷵻�ֵΪ0
//����
//	list:		Ҫ���ҵ����Ա�
//	element:	Ҫ���ҵ�Ԫ��
//	compare:	�Ƚ�Ԫ���Ƿ���ȵĺ���
int LocateElement(LIST_TYPE list, ElementType element, Status(*compare)(
		ElementType, ElementType));

//ǰ��
//��ʼ����: ���Ա�list�Ѵ���
//�������: ��currentElement��L������Ԫ��,�Ҳ��ǵ�һ��,����priorElement��������ǰ��,����OK;�������ʧ��,priorElement�޶���,����INFEASIBLE
//����
//	list:			Ҫ���ҵ����Ա�
//	currentElement:	Ҫ���ҵ�λ��
//	nextElement:	����Ԫ�ص�ǰ��
Status PriorElement(LIST_TYPE list, ElementType currentElement,
		ElementType *priorElement);

//���
//��ʼ���������Ա�list�Ѵ���
//�����������currentElement��list������Ԫ�أ��Ҳ������һ��������nextElement�������ĺ�̣�����OK;�������ʧ�ܣ�nextElement�޶��壬����INFEASIBLE
//����
//	list:			Ҫ���ҵ����Ա�
//	currentElement:	Ҫ���ҵ�λ��
//	nextElement:	����Ԫ�صĺ��
Status NextElement(LIST_TYPE list, ElementType currentElement,
		ElementType *nextElement);

//����Ԫ��
//��ʼ���������Ա�list�Ѵ��ڣ�1<=position<=ListLength(L)+1
//�����������list�е�position��λ��֮ǰ�����µ�����Ԫ��element��list�ĳ��ȼ�1
//����
//	list:		Ҫ��������Ա�
//	position:	Ҫ�����λ��
//	element:	Ҫ�����Ԫ�ص�ֵ
Status ListInsert(LIST_TYPE list, int position, ElementType element);

//ɾ��Ԫ��
//��ʼ���������Ա�list�Ѵ��ڣ�1<=position<=ListLength(L)
//���������ɾ��list�ĵ�position������Ԫ�أ�����deletedElement������ֵ��L�ĳ��ȼ�1
//����
//	list:			Ҫɾ��Ԫ�ص����Ա�
//	position:		Ҫɾ����Ԫ�ص�λ��
//	deletedElement:	��ɾ����Ԫ�ص�ֵ
Status ListDelete(LIST_TYPE list, int position, ElementType *deletedElement);

//����
//��ʼ���������Ա�list�Ѵ���
//������������ζ�list��ÿ������Ԫ�ص��ú���visit()��һ��visit()ʧ�ܣ������ʧ��,visit()���βμ�'*'��������ͨ������visit()�ı�Ԫ�ص�ֵ
//����
//	list:	Ҫ���������Ա�
//	visit:	��ÿ��Ԫ����Ҫִ�еĺ���
Status ListTraverse(LIST_TYPE list, Status(*visit)(ElementType*));

//�ϲ�
//��ʼ���������Ա�a��b�����ڣ���a��b�����ź�˳��
//����������ϲ�a��b�������Ա����������a�У����ͷ�b
//����
//	a:	���Ա�a
//	b:	���Ա�b
Status ListMerge(LIST_TYPE *a, LIST_TYPE *b);

#endif /* DATA_STRUCTURE_IN_C_LIST_H_ */
