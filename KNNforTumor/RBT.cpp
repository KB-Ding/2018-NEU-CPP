/**
* C++ ����: �����
*
* @author skywang
* @date 2013/11/07
*/

#include "stdafx.h"
#include "RBT.h"


/*
* ���캯��
*/

RBTree::RBTree() :mRoot(NULL)
{
	mRoot = NULL;
}


/*
* (�ݹ�ʵ��)����"�����x"�м�ֵΪkey�Ľڵ�
*/

RBTNode* RBTree::search(RBTNode* x, int  key)
{
	if (x == NULL || x->key == key)
		return x;

	if (key < x->key)
		return search(x->left, key);
	else
		return search(x->right, key);
}


bool RBTree::search(int key)
{
	if (NULL == search(mRoot, key)) {
		return false;
	}
	else {
		return true;
	}
}


/*
* ������С��㣺����treeΪ�����ĺ��������С��㡣
*/

RBTNode* RBTree::getmininum(RBTNode* tree)
{
	if (tree == NULL)
		return NULL;

	while (tree->left != NULL)
		tree = tree->left;
	return tree;
}


int  RBTree::minimum() {
	RBTNode *p = getmininum(mRoot);
	if (p != NULL)
		return p->key;
	else {
		return NULL;
	}
}

/*
* ��������㣺����treeΪ�����ĺ����������㡣
*/

RBTNode* RBTree::getmax(RBTNode* tree)
{
	if (tree == NULL)
		return NULL;

	while (tree->right != NULL)
		tree = tree->right;
	return tree;
}


int RBTree::maximum()
{
	RBTNode *p = getmax(mRoot);
	if (p != NULL)
		return p->key;
	else {
		return NULL;
	}
}

/*
* �ҽ��(x)�ĺ�̽�㡣��������"�����������ֵ���ڸý��"��"��С���"��
*/

RBTNode* RBTree::successor(RBTNode *x)
{
	// ���x�����Һ��ӣ���"x�ĺ�̽��"Ϊ "�����Һ���Ϊ������������С���"��
	if (x->right != NULL)
		return getmininum(x->right);

	// ���xû���Һ��ӡ���x���������ֿ��ܣ�
	// (01) x��"һ������"����"x�ĺ�̽��"Ϊ "���ĸ����"��
	// (02) x��"�����������Һ���"�������"x����͵ĸ���㣬���Ҹø����Ҫ��������"���ҵ������"��͵ĸ����"����"x�ĺ�̽��"��
	RBTNode* y = x->parent;
	while ((y != NULL) && (x == y->right))//�˳�������x == y->leftʱ
	{
		x = y;
		y = y->parent;
	}
	return y;
}

/*
* �ҽ��(x)��ǰ����㡣��������"�����������ֵС�ڸý��"��"�����"��
*/

RBTNode* RBTree::predecessor(RBTNode *x)
{
	// ���x�������ӣ���"x��ǰ�����"Ϊ "��������Ϊ���������������"��
	if (x->left != NULL)
		return getmax(x->left);

	// ���xû�����ӡ���x���������ֿ��ܣ�
	// (01) x��"һ���Һ���"����"x��ǰ�����"Ϊ "���ĸ����"��
	// (01) x��"���������Һ���"�������"x����͵ĸ���㣬���Ҹø����Ҫ�����Һ���"���ҵ������"��͵ĸ����"����"x��ǰ�����"��
	RBTNode* y = x->parent;
	while ((y != NULL) && (x == y->left))//�˳�������x == y->rightʱ
	{
		x = y;
		y = y->parent;
	}

	return y;
}

/*
* �Ժ�����Ľڵ�(x)��������ת
*
* ����ʾ��ͼ(�Խڵ�x��������)��
*      px											 px
*     /												/
*    x											  y
*   /  \      --(����)-->           / \                #
*  lx   y                          x  ry
*     /   \                       /  \
*    ly   ry                     lx  ly
*
*
*/

void RBTree::leftRotate(RBTNode* &root, RBTNode* x)
{
	// ����x���Һ���Ϊy
	RBTNode* y = x->right;

	// �� ��y�����ӡ� ��Ϊ ��x���Һ��ӡ���
	// ���y�����ӷǿգ��� ��x�� ��Ϊ ��y�����ӵĸ��ס�
	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;

	// �� ��x�ĸ��ס� ��Ϊ ��y�ĸ��ס�
	y->parent = x->parent;

	if (x->parent == NULL)
	{
		root = y;            // ��� ��x�ĸ��ס� �ǿսڵ㣬��y��Ϊ���ڵ�
	}
	else
	{
		if (x->parent->left == x)
			x->parent->left = y;    // ��� x�������ڵ�����ӣ���y��Ϊ��x�ĸ��ڵ�����ӡ�
		else
			x->parent->right = y;    // ��� x�������ڵ�����ӣ���y��Ϊ��x�ĸ��ڵ�����ӡ�
	}

	// �� ��x�� ��Ϊ ��y�����ӡ�
	y->left = x;
	// �� ��x�ĸ��ڵ㡱 ��Ϊ ��y��
	x->parent = y;
}

/*
* �Ժ�����Ľڵ�(y)��������ת
*
* ����ʾ��ͼ(�Խڵ�y��������)��
*            py                               py
*           /                                /
*          y                                x
*         /  \      --(����)-->            /  \                     #
*        x   ry                           lx   y
*       / \                                   / \                   #
*      lx  rx                                rx  ry
*
*/

void RBTree::rightRotate(RBTNode* &root, RBTNode* y)
{
	// ����x�ǵ�ǰ�ڵ�����ӡ�
	RBTNode *x = y->left;

	// �� ��x���Һ��ӡ� ��Ϊ ��y�����ӡ���
	// ���"x���Һ���"��Ϊ�յĻ����� ��y�� ��Ϊ ��x���Һ��ӵĸ��ס�
	y->left = x->right;
	if (x->right != NULL)
		x->right->parent = y;

	// �� ��y�ĸ��ס� ��Ϊ ��x�ĸ��ס�
	x->parent = y->parent;

	if (y->parent == NULL)
	{
		root = x;            // ��� ��y�ĸ��ס� �ǿսڵ㣬��x��Ϊ���ڵ�
	}
	else
	{
		if (y == y->parent->right)
			y->parent->right = x;    // ��� y�������ڵ���Һ��ӣ���x��Ϊ��y�ĸ��ڵ���Һ��ӡ�
		else
			y->parent->left = x;    // (y�������ڵ������) ��x��Ϊ��x�ĸ��ڵ�����ӡ�
	}

	// �� ��y�� ��Ϊ ��x���Һ��ӡ�
	x->right = y;

	// �� ��y�ĸ��ڵ㡱 ��Ϊ ��x��
	y->parent = x;
}

/*
* �����������������
*
* ���������в���ڵ�֮��(ʧȥƽ��)���ٵ��øú�����
* Ŀ���ǽ������������һ�ź������
*
* ����˵����
*     root ������ĸ�
*     node ����Ľ��        // ��Ӧ���㷨���ۡ��е�z
*/

void RBTree::insertFixUp(RBTNode* &root, RBTNode* node)
{
	RBTNode *parent, *gparent;

	// �������ڵ���ڣ����Ҹ��ڵ����ɫ�Ǻ�ɫ��
	while ((parent = rb_parent(node)) && rb_is_red(parent))
	{
		gparent = rb_parent(parent);

		//�������ڵ㡱�ǡ��游�ڵ�����ӡ�
		if (parent == gparent->left)
		{
			// Case 1����������ڵ��Ǻ�ɫ
			{
				RBTNode *uncle = gparent->right;
				if (uncle && rb_is_red(uncle))
				{
					rb_set_black(uncle);
					rb_set_black(parent);
					rb_set_red(gparent);
					node = gparent;
					continue;
				}
			}

			// Case 2�����������Ǻ�ɫ���ҵ�ǰ�ڵ����Һ���
			if (parent->right == node)
			{
				RBTNode *tmp;
				leftRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			// Case 3�����������Ǻ�ɫ���ҵ�ǰ�ڵ������ӡ�
			rb_set_black(parent);
			rb_set_red(gparent);
			rightRotate(root, gparent);
		}
		else//����z�ĸ��ڵ㡱�ǡ�z���游�ڵ���Һ��ӡ�
		{
			// Case 1����������ڵ��Ǻ�ɫ
			{
				RBTNode *uncle = gparent->left;
				if (uncle && rb_is_red(uncle))
				{
					rb_set_black(uncle);
					rb_set_black(parent);
					rb_set_red(gparent);
					node = gparent;
					continue;
				}
			}

			// Case 2�����������Ǻ�ɫ���ҵ�ǰ�ڵ�������
			if (parent->left == node)
			{
				RBTNode *tmp;
				rightRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			// Case 3�����������Ǻ�ɫ���ҵ�ǰ�ڵ����Һ��ӡ�
			rb_set_black(parent);
			rb_set_red(gparent);
			leftRotate(root, gparent);
		}
	}

	// �����ڵ���Ϊ��ɫ
	rb_set_black(root);
}

/*
* �������뵽�������
*
* ����˵����
*     root ������ĸ����
*     node ����Ľ��        // ��Ӧ���㷨���ۡ��е�node
*/

void RBTree::insert(RBTNode* &root, RBTNode* node)
{
	RBTNode *y = NULL;
	RBTNode *x = root;

	// 1. �����������һ�Ŷ�������������ڵ���ӵ�����������С�
	while (x != NULL)
	{
		y = x;
		if (node->key < x->key)
			x = x->left;
		else
			x = x->right;
	}

	node->parent = y;
	if (y != NULL)
	{
		if (node->key < y->key)
			y->left = node;
		else
			y->right = node;
	}
	else
		root = node;

	// 2. ���ýڵ����ɫΪ��ɫ
	node->color = RED;

	// 3. ������������Ϊһ�Ŷ��������
	insertFixUp(root, node);
}

/*
* �����(keyΪ�ڵ��ֵ)���뵽�������
*
* ����˵����
*     tree ������ĸ����
*     key ������ļ�ֵ
*/

void RBTree::insert(int key)
{
	RBTNode *z = NULL;

	// ����½����ʧ�ܣ��򷵻ء�
	if ((z = new RBTNode(key, BLACK, NULL, NULL, NULL)) == NULL)
		return;

	insert(mRoot, z);
}


