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

//初始化
//初始化二叉树
//参数：
//	tree:	要初始化的二叉树
Status Initial(BINARY_TREE_TYPE* tree);

//销毁
//销毁二叉树
//参数：
//	tree:	要销毁的二叉树
Status Destory(BINARY_TREE_TYPE* tree);

//构造
//根据给出的字符串表示构造相应的二叉树
//参数：
//	tree:		构造后的二叉树
//	definition:	二叉树的字符串表示
Status Create(BINARY_TREE_TYPE* tree, char* definition);

//清空
//清楚二叉树的所有节点
//参数：
//	tree:	要清空的二叉树
Status Clear(BINARY_TREE_TYPE* tree);

//判空
//判定二叉树是否为空树
//参数：
//	tree:	要判空的二叉树
Status Empty(BINARY_TREE_TYPE tree);

//求深度
//求二叉树的深度
//参数：
//	tree:	要求深度的二叉树
Status Depth(BINARY_TREE_TYPE tree);

//取根节点
//返回二叉树的根节点，如果是空树，而返回空
//参数：
//	tree:	要取根节点的二叉树
BINARY_TREE_NODE* Root(BINARY_TREE_TYPE tree);

//取值
//取得二叉树上的某一个节点的值，如果该位置上的结点不存在则返回0
//参数：
//	tree:		要取值的二叉树
//	position:	要取值的节点的位置，按满二叉树计算
ElementType Value(BINARY_TREE_TYPE tree, Position position);

//赋值
//给二叉树上指定位置的节点赋值，如果指定节点的父节点不存在，而返回ERROR
//参数：
//	tree:		要赋值的二叉树
//	position:	要赋值的节点的位置，按满二叉树计算
//	value:		节点的值
Status Assign(BINARY_TREE_TYPE* tree, Position position, ElementType value);

//取父节点
//取一个节点的父节点，如果该节点为根节点，其父节点为空
//参数：
//	tree:	所涉及的二叉树
//	node:	要求父节点的节点
BINARY_TREE_NODE* Parent(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node);

//取左子树
//取一个节点的左子树，如果该节点没有左子树，则返回空
//参数：
//	tree:	所涉及的二叉树
//	node:	要求左子树的节点
BINARY_TREE_NODE* LeftChild(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node);

//取右子树
//取一个节点的右子树，如果该节点没有右子树，则返回空
//参数：
//	tree:	所涉及的二叉树
//	node:	要求左子树的节点
BINARY_TREE_NODE* RightChild(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node);

//取左兄弟子树
//取一个节点的左兄弟子树，如果该节点没有左兄弟子树，则返回空
//参数：
//	tree:	所涉及的二叉树
//	node:	要求左兄弟子树的节点
BINARY_TREE_NODE* LeftSibling(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node);

//取右兄弟子树
//取一个节点的右兄弟子树，如果该节点没有右兄弟子树，则返回空
//参数：
//	tree:	所涉及的二叉树
//	node:	要求左兄弟子树的节点
BINARY_TREE_NODE* RightSibling(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node);

//插入子节点
//根据left_or_right插入value作为parent的左子树或右子树，如果该节点在这个位置上已有子树，则返回Error。
//参数：
//	tree:			涉及的二叉树
//	parent:			父节点
//	left_or_right:	指定插入的子树是为左子树还是为右子树
//	value:			要插入的子树的值
Status InsertChild(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* parent,
		enum LeftOrRight left_or_right, ElementType value);

//删除子树
//根据left_or_right删除parent的左子树或右子树。
//参数：
//	tree:			涉及的二叉树
//	parent:			父节点
//	left_or_right:	指定删除左子树还是右子树
Status DeleteChild(BINARY_TREE_TYPE tree, BINARY_TREE_NODE* node,
		enum LeftOrRight left_or_right);

//先序遍历二叉树
//先序遍历二叉树tree，对每一个节点调用visit一次，一旦visit失败，则返回操作失败
//参数：
//	tree:	要遍历的二叉树
//	visit:	遍历的操作函数
Status PreOrderTraverse(BINARY_TREE_TYPE tree, Status(*visit)(ElementType*));

//中序遍历二叉树
//中序遍历二叉树tree，对每一个节点调用visit一次，一旦visit失败，则返回操作失败
//参数：
//	tree:	要遍历的二叉树
//	visit:	遍历的操作函数
Status InOrderTraverse(BINARY_TREE_TYPE tree, Status(*visit)(ElementType*));

//后序遍历二叉树
//后序遍历二叉树tree，对每一个节点调用visit一次，一旦visit失败，则返回操作失败
//参数：
//	tree:	要遍历的二叉树
//	visit:	遍历的操作函数
Status PostOrderTraverse(BINARY_TREE_TYPE tree, Status(*visit)(ElementType*));

//层序遍历二叉树
//层序遍历二叉树tree，对每一个节点调用visit一次，一旦visit失败，则返回操作失败
//参数：
//	tree:	要遍历的二叉树
//	visit:	遍历的操作函数
Status LevelOrderTraverse(BINARY_TREE_TYPE tree, Status(*visit)(ElementType*));

#endif /* DATA_STRUCTURE_IN_C_TREE_BINARY_TREE_H_ */
