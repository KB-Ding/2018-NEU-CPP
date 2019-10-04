#pragma once
#include "stdafx.h"
#include <iomanip>
#include <iostream>
#include<vector> 
using namespace std;

enum RBTColor { RED, BLACK };


class RBTNode {
public:
	RBTColor color;    // ��ɫ
	int key;            // ��ֵ
	RBTNode *left;    // ����
	RBTNode *right;    // �Һ���
	RBTNode *parent; // �����

	RBTNode(int value, RBTColor c, RBTNode *p, RBTNode *l, RBTNode *r) :
		key(value), color(c), parent(), left(l), right(r) {}
};


class RBTree {
private:
	RBTNode * mRoot;    // �����

public:
	RBTree();

	// (�ݹ�ʵ��)����"�����"�м�ֵΪkey�Ľڵ�
	bool  search(int key);

	// �ҽ��(x)�ĺ�̽�㡣��������"�����������ֵ���ڸý��"��"��С���"��
	RBTNode * successor(RBTNode *x);
	// �ҽ��(x)��ǰ����㡣��������"�����������ֵС�ڸý��"��"�����"��
	RBTNode* predecessor(RBTNode *x);

	// �����(keyΪ�ڵ��ֵ)���뵽�������
	void insert(int key);
	RBTNode* getmininum(RBTNode* tree);
	int  minimum();
	RBTNode* getmax(RBTNode* tree);
	int  maximum();
private:
	// (�ݹ�ʵ��)����"�����x"�м�ֵΪkey�Ľڵ�
	RBTNode * search(RBTNode* x, int key);

	// ����
	void leftRotate(RBTNode* &root, RBTNode* x);
	// ����
	void rightRotate(RBTNode* &root, RBTNode* y);
	// ���뺯��
	void insert(RBTNode* &root, RBTNode* node);
	// ������������
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

