/*
 * tree.h
 *
 *  Created on: 2009-9-3
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_TREE_TREE_H_
#define DATA_STRUCTURE_IN_C_TREE_TREE_H_

#include "include/common.h"

//��ʼ��
//��ʼ����
//������
//	tree:	Ҫ��ʼ������
Status Initial(TREE_TYPE* tree);

//����
//������
//������
//	tree:	Ҫ���ٵ���
Status Destory(TREE_TYPE* tree);

//����
//���ݸ������ַ�����ʾ������Ӧ����
//������
//	tree:		��������
//	definition:	�����ַ�����ʾ
Status Create(TREE_TYPE* tree, char* definition);

//���
//����������нڵ�
//������
//	tree:	Ҫ��յ���
Status Clear(TREE_TYPE* tree);

//�п�
//�ж����Ƿ�Ϊ����
//������
//	tree:	Ҫ�пյ���
Status Empty(TREE_TYPE tree);

//�����
//���������
//������
//	tree:	Ҫ����ȵ���
int Depth(TREE_TYPE tree);

//ȡ���ڵ�
//�������ĸ��ڵ㣬����ǿ����������ؿ�
//������
//	tree:	Ҫȡ���ڵ����
TREE_NODE* Root(TREE_TYPE tree);

//ȡֵ
//ȡ�����ϵ�ĳһ���ڵ��ֵ������ý�㲻�����򷵻�0
//������
//	tree:	Ҫȡֵ����
//	node:	Ҫȡֵ�Ľڵ�
ElementType Value(TREE_TYPE tree, TREE_NODE *node);

//��ֵ
//������ָ��λ�õĽڵ㸳ֵ�����ָ���ڵ㲻���ڣ�������ERROR
//������
//	tree:	Ҫ��ֵ����
//	node:	Ҫ��ֵ�Ľڵ㣬����������
//	value:	�ڵ��ֵ
Status Assign(TREE_TYPE* tree, TREE_NODE *node, ElementType value);

//ȡ���ڵ�
//ȡһ���ڵ�ĸ��ڵ㣬����ýڵ�Ϊ���ڵ㣬�丸�ڵ�Ϊ��
//������
//	tree:	���漰����
//	node:	Ҫ�󸸽ڵ�Ľڵ�
TREE_NODE* Parent(TREE_TYPE tree, TREE_NODE* node);

//ȡ������
//ȡһ���ڵ��������������ýڵ�û�����������򷵻ؿ�
//������
//	tree:	���漰����
//	node:	Ҫ���������Ľڵ�
TREE_NODE* LeftChild(TREE_TYPE tree, TREE_NODE* node);

//ȡ���ֵ�����
//ȡһ���ڵ�����ֵ�����������ýڵ�û�����ֵ��������򷵻ؿ�
//������
//	tree:	���漰����
//	node:	Ҫ�����ֵ������Ľڵ�
TREE_NODE* RightSibling(TREE_TYPE tree, TREE_NODE* node);

//�����ӽڵ�
//����value��Ϊparent�ĵ�position��������
//������
//	tree:		�漰����
//	parent:		���ڵ�
//	position:	ָ��������ӽ���λ��
//	value:		Ҫ������ӽ���ֵ
Status InsertChild(TREE_TYPE tree, TREE_NODE* parent, int position,
		ElementType value);

//ɾ������
//ɾ��parent�ĵ�position��������
//������
//	tree:		�漰����
//	parent:		���ڵ�
//	position:	ָ��ɾ����������λ��
Status DeleteChild(TREE_TYPE tree, TREE_NODE* node, int position);

//������
//������tree����ÿһ���ڵ����visitһ�Σ�һ��visitʧ�ܣ��򷵻ز���ʧ��
//������
//	tree:	Ҫ��������
//	visit:	�����Ĳ�������
Status Traverse(TREE_TYPE tree, Status(*visit)(ElementType*));

#endif /* DATA_STRUCTURE_IN_C_TREE_BINARY_TREE_H_ */
