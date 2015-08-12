# Data Structure In C 

All codes for the teaching material DataStructure writen by Weimin Yan.

## 1. Usage

### 1.0 prepare

1. git clone https://github.com/yuandong1222/DataStructureInC

### 1.1 run examples

1. cd DataStructureInC/examples
2. edit makefile to choose a test to run
3. make

### 1.2 write and test your your own impl

1. cd DataStructureInC/trunk
2. edit makefile to choose a test to impl
3. impl your code in src dir
3. make

## 2. Data Structures

### 2.1 List
* SequenceList
* StaticLinkList
* LinkList
* DoubleLinkList
* CircularLinkList
* LinkListWithHead
* Polynomial
	
### 2.2 Stack
* SequenceStack
* LinkStack
	
### 2.3 Queue
* LinkQueue
* SequenceQueue
	
### 2.4 String
* SequenceString
* HeapString
* LinkString
* WordIndexList
	
### 2.5 Array & GeneralizedList
* SequenceArray
* TripletSparseMatrix
* CrossSparseMatrix
* HeadTailGeneralizedList
* ExtendSequenceGeneralizedList
	
### 2.6 Tree
* SequenceBinaryTree
* LinkBinaryTree
* ThreadBinaryTree
* ParentTree
* ChildTree
* ChildSildeTree
	
### 2.7 Graph
* AdjacentMatrixGraphic
* AdjacentListGraphic
* OrthogonalListGraphic
* AdjacentMultipleListGraphic
* Related Algorithm：
  * Directed Graph：
    * Strongly Connected Components
    * Topological Sort of Directed Acyclic Graph
    * Key Path of Directed Acyclic Graph
  * Undirected Graph：
    * Key Node
    * Minimal Spanning Tree
    * Shortest Path

## 3. Directory

** /examples **

Unit tests and impl codes.

** /trunk **

Only the tests and method define without impl codes.
