#pragma once
#include "stdafx.h"
#include <iomanip>
#include <iostream>
#include<vector> 
using namespace std;

enum RBTColor { RED, BLACK };


class RBTNode {
public:
	RBTColor color;    // 颜色
	int key;            // 键值
	RBTNode *left;    // 左孩子
	RBTNode *right;    // 右孩子
	RBTNode *parent; // 父结点

	RBTNode(int value, RBTColor c, RBTNode *p, RBTNode *l, RBTNode *r) :
		key(value), color(c), parent(), left(l), right(r) {}
};


class RBTree {
private:
	RBTNode * mRoot;    // 根结点

public:
	RBTree();

	// (递归实现)查找"红黑树"中键值为key的节点
	bool  search(int key);

	// 找结点(x)的后继结点。即，查找"红黑树中数据值大于该结点"的"最小结点"。
	RBTNode * successor(RBTNode *x);
	// 找结点(x)的前驱结点。即，查找"红黑树中数据值小于该结点"的"最大结点"。
	RBTNode* predecessor(RBTNode *x);

	// 将结点(key为节点键值)插入到红黑树中
	void insert(int key);
	RBTNode* getmininum(RBTNode* tree);
	int  minimum();
	RBTNode* getmax(RBTNode* tree);
	int  maximum();
private:
	// (递归实现)查找"红黑树x"中键值为key的节点
	RBTNode * search(RBTNode* x, int key);

	// 左旋
	void leftRotate(RBTNode* &root, RBTNode* x);
	// 右旋
	void rightRotate(RBTNode* &root, RBTNode* y);
	// 插入函数
	void insert(RBTNode* &root, RBTNode* node);
	// 插入修正函数
	void insertFixUp(RBTNode* &root, RBTNode* node);


#define rb_parent(r)   ((r)->parent)
#define rb_color(r) ((r)->color)
#define rb_is_red(r)   ((r)->color==RED)
#define rb_is_black(r)  ((r)->color==BLACK)
#define rb_set_black(r)  do { (r)->color = BLACK; } while (0)
#define rb_set_red(r)  do { (r)->color = RED; } while (0)
#define rb_set_parent(r,p)  do { (r)->parent = (p); } while (0)
#define rb_set_color(r,c)  do { (r)->color = (c); } while (0)
};

