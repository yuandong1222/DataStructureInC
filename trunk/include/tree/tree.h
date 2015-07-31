/*
 * tree.h
 *
 *  Created on: 2009-9-3
 *      Author: yuandong
 */

#ifndef DATA_STRUCTURE_IN_C_TREE_TREE_H_
#define DATA_STRUCTURE_IN_C_TREE_TREE_H_

#include "include/common.h"

//初始化
//初始化树
//参数：
//	tree:	要初始化的树
Status Initial(TREE_TYPE* tree);

//销毁
//销毁树
//参数：
//	tree:	要销毁的树
Status Destory(TREE_TYPE* tree);

//构造
//根据给出的字符串表示构造相应的树
//参数：
//	tree:		构造后的树
//	definition:	树的字符串表示
Status Create(TREE_TYPE* tree, char* definition);

//清空
//清楚树的所有节点
//参数：
//	tree:	要清空的树
Status Clear(TREE_TYPE* tree);

//判空
//判定树是否为空树
//参数：
//	tree:	要判空的树
Status Empty(TREE_TYPE tree);

//求深度
//求树的深度
//参数：
//	tree:	要求深度的树
int Depth(TREE_TYPE tree);

//取根节点
//返回树的根节点，如果是空树，而返回空
//参数：
//	tree:	要取根节点的树
TREE_NODE* Root(TREE_TYPE tree);

//取值
//取得树上的某一个节点的值，如果该结点不存在则返回0
//参数：
//	tree:	要取值的树
//	node:	要取值的节点
ElementType Value(TREE_TYPE tree, TREE_NODE *node);

//赋值
//给树上指定位置的节点赋值，如果指定节点不存在，而返回ERROR
//参数：
//	tree:	要赋值的树
//	node:	要赋值的节点，按满树计算
//	value:	节点的值
Status Assign(TREE_TYPE* tree, TREE_NODE *node, ElementType value);

//取父节点
//取一个节点的父节点，如果该节点为根节点，其父节点为空
//参数：
//	tree:	所涉及的树
//	node:	要求父节点的节点
TREE_NODE* Parent(TREE_TYPE tree, TREE_NODE* node);

//取左子树
//取一个节点的左子树，如果该节点没有左子树，则返回空
//参数：
//	tree:	所涉及的树
//	node:	要求左子树的节点
TREE_NODE* LeftChild(TREE_TYPE tree, TREE_NODE* node);

//取右兄弟子树
//取一个节点的右兄弟子树，如果该节点没有右兄弟子树，则返回空
//参数：
//	tree:	所涉及的树
//	node:	要求左兄弟子树的节点
TREE_NODE* RightSibling(TREE_TYPE tree, TREE_NODE* node);

//插入子节点
//插入value作为parent的第position棵子树。
//参数：
//	tree:		涉及的树
//	parent:		父节点
//	position:	指定插入的子结点的位置
//	value:		要插入的子结点的值
Status InsertChild(TREE_TYPE tree, TREE_NODE* parent, int position,
		ElementType value);

//删除子树
//删除parent的第position棵子树。
//参数：
//	tree:		涉及的树
//	parent:		父节点
//	position:	指定删除的子树的位置
Status DeleteChild(TREE_TYPE tree, TREE_NODE* node, int position);

//遍历树
//遍历树tree，对每一个节点调用visit一次，一旦visit失败，则返回操作失败
//参数：
//	tree:	要遍历的树
//	visit:	遍历的操作函数
Status Traverse(TREE_TYPE tree, Status(*visit)(ElementType*));

#endif /* DATA_STRUCTURE_IN_C_TREE_BINARY_TREE_H_ */
