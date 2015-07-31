/*
 * binary_tree.h
 *
 *  Created on: 2009-8-23
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_TREE_BINARY_TREE_H_
#define DATA_STRUCTURE_IN_C_TREE_BINARY_TREE_H_

#include "include/common.h"
#include "include/tree/binary_tree_position.h"

enum LeftOrRight {
	Left, Right
};

//��ʼ��
//��ʼ��������
//������
//	tree:	Ҫ��ʼ���Ķ�����
Status Initial(BINARY_TREE_TYPE* tree);

//����
//���ٶ�����
//������
//	tree:	Ҫ���ٵĶ�����
Status Destory(BINARY_TREE_TYPE* tree);

//����
//���ݸ������ַ�����ʾ������Ӧ�Ķ�����
//������
//	tree:		�����Ķ�����
//	definition:	���������ַ�����ʾ
Status Create(BINARY_TREE_TYPE* tree, char* definition);

//���
//��������������нڵ�
//������
//	tree:	Ҫ��յĶ�����
Status Clear(BINARY_TREE_TYPE* tree);

//�п�
//�ж��������Ƿ�Ϊ����
//������
//	tree:	Ҫ�пյĶ�����
Status Empty(BINARY_TREE_TYPE tree);

//�����
//������������
//������
//	tree:	Ҫ����ȵĶ�����
Status Depth(BINARY_TREE_TYPE tree);

//ȡ���ڵ�
//���ض������ĸ��ڵ㣬����ǿ����������ؿ�
//������
//	tree:	Ҫȡ���ڵ�Ķ�����
BINARY_TREE_NODE* Root(BINARY_TREE_TYPE tree);

//ȡֵ
//ȡ�ö������ϵ�ĳһ���ڵ��ֵ�������λ���ϵĽ�㲻�����򷵻�0
//������
//	tree:		Ҫȡֵ�Ķ�����
//	position:	Ҫȡֵ�Ľڵ��λ�ã���������������
ElementType Value(BINARY_TREE_TYPE tree, Position position);

//��ֵ
//����������ָ��λ�õĽڵ㸳ֵ�����ָ���ڵ�ĸ��ڵ㲻���ڣ�������ERROR
//������
//	tree:		Ҫ��ֵ�Ķ�����
//	position:	Ҫ��ֵ�Ľڵ��λ�ã���������������
//	value:		�ڵ��ֵ
Status Assign(BINARY_TREE_TYPE* tree, Position position, ElementType value);

//ȡ���ڵ�
//ȡһ���ڵ�ĸ��ڵ㣬����ýڵ�Ϊ���ڵ㣬�丸�ڵ�Ϊ��
//������
//	tree:	���漰�Ķ�����
//	node:	Ҫ�󸸽ڵ�Ľڵ�
BINARY_TREE_NODE* Parent(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node);

//ȡ������
//ȡһ���ڵ��������������ýڵ�û�����������򷵻ؿ�
//������
//	tree:	���漰�Ķ�����
//	node:	Ҫ���������Ľڵ�
BINARY_TREE_NODE* LeftChild(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node);

//ȡ������
//ȡһ���ڵ��������������ýڵ�û�����������򷵻ؿ�
//������
//	tree:	���漰�Ķ�����
//	node:	Ҫ���������Ľڵ�
BINARY_TREE_NODE* RightChild(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node);

//ȡ���ֵ�����
//ȡһ���ڵ�����ֵ�����������ýڵ�û�����ֵ��������򷵻ؿ�
//������
//	tree:	���漰�Ķ�����
//	node:	Ҫ�����ֵ������Ľڵ�
BINARY_TREE_NODE* LeftSibling(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node);

//ȡ���ֵ�����
//ȡһ���ڵ�����ֵ�����������ýڵ�û�����ֵ��������򷵻ؿ�
//������
//	tree:	���漰�Ķ�����
//	node:	Ҫ�����ֵ������Ľڵ�
BINARY_TREE_NODE* RightSibling(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node);

//�����ӽڵ�
//����left_or_right����value��Ϊparent����������������������ýڵ������λ���������������򷵻�Error��
//������
//	tree:			�漰�Ķ�����
//	parent:			���ڵ�
//	left_or_right:	ָ�������������Ϊ����������Ϊ������
//	value:			Ҫ�����������ֵ
Status InsertChild(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* parent,
		enum LeftOrRight left_or_right, ElementType value);

//ɾ������
//����left_or_rightɾ��parent������������������
//������
//	tree:			�漰�Ķ�����
//	parent:			���ڵ�
//	left_or_right:	ָ��ɾ������������������
Status DeleteChild(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node,
		enum LeftOrRight left_or_right);

//�������������
//�������������tree����ÿһ���ڵ����visitһ�Σ�һ��visitʧ�ܣ��򷵻ز���ʧ��
//������
//	tree:	Ҫ�����Ķ�����
//	visit:	�����Ĳ�������
Status PreOrderTraverse(BINARY_TREE_TYPE tree, Status(*visit)(ElementType*));

//�������������
//�������������tree����ÿһ���ڵ����visitһ�Σ�һ��visitʧ�ܣ��򷵻ز���ʧ��
//������
//	tree:	Ҫ�����Ķ�����
//	visit:	�����Ĳ�������
Status InOrderTraverse(BINARY_TREE_TYPE tree, Status(*visit)(ElementType*));

//�������������
//�������������tree����ÿһ���ڵ����visitһ�Σ�һ��visitʧ�ܣ��򷵻ز���ʧ��
//������
//	tree:	Ҫ�����Ķ�����
//	visit:	�����Ĳ�������
Status PostOrderTraverse(BINARY_TREE_TYPE tree, Status(*visit)(ElementType*));

//�������������
//�������������tree����ÿһ���ڵ����visitһ�Σ�һ��visitʧ�ܣ��򷵻ز���ʧ��
//������
//	tree:	Ҫ�����Ķ�����
//	visit:	�����Ĳ�������
Status LevelOrderTraverse(BINARY_TREE_TYPE tree, Status(*visit)(ElementType*));

#endif /* DATA_STRUCTURE_IN_C_TREE_BINARY_TREE_H_ */
