/**
* 红黑树
*
*
*
*/

#include "stdafx.h"
#include "RBT.h"


/*
* 构造函数
*/

RBTree::RBTree() :mRoot(NULL)
{
	mRoot = NULL;
}


/*
* (递归实现)查找"红黑树x"中键值为key的节点
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
* 查找最小结点：返回tree为根结点的红黑树的最小结点。
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
* 查找最大结点：返回tree为根结点的红黑树的最大结点。
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
* 找结点(x)的后继结点。即，查找"红黑树中数据值大于该结点"的"最小结点"。
*/

RBTNode* RBTree::successor(RBTNode *x)
{
	// 如果x存在右孩子，则"x的后继结点"为 "以其右孩子为根的子树的最小结点"。
	if (x->right != NULL)
		return getmininum(x->right);

	// 如果x没有右孩子。则x有以下两种可能：
	// (01) x是"一个左孩子"，则"x的后继结点"为 "它的父结点"。
	// (02) x是"左子树的最右孩子"，则查找"x的最低的父结点，并且该父结点要具有左孩子"，找到的这个"最低的父结点"就是"x的后继结点"。
	RBTNode* y = x->parent;
	while ((y != NULL) && (x == y->right))//退出条件：x == y->left时
	{
		x = y;
		y = y->parent;
	}
	return y;
}

/*
* 找结点(x)的前驱结点。即，查找"红黑树中数据值小于该结点"的"最大结点"。
*/

RBTNode* RBTree::predecessor(RBTNode *x)
{
	// 如果x存在左孩子，则"x的前驱结点"为 "以其左孩子为根的子树的最大结点"。
	if (x->left != NULL)
		return getmax(x->left);

	// 如果x没有左孩子。则x有以下两种可能：
	// (01) x是"一个右孩子"，则"x的前驱结点"为 "它的父结点"。
	// (01) x是"左子树最右孩子"，则查找"x的最低的父结点，并且该父结点要具有右孩子"，找到的这个"最低的父结点"就是"x的前驱结点"。
	RBTNode* y = x->parent;
	while ((y != NULL) && (x == y->left))//退出条件：x == y->right时
	{
		x = y;
		y = y->parent;
	}

	return y;
}

/*
* 对红黑树的节点(x)进行左旋转
*
* 左旋示意图(对节点x进行左旋)：
*      px											 px
*     /												/
*    x											  y
*   /  \      --(左旋)-->           / \                #
*  lx   y                          x  ry
*     /   \                       /  \
*    ly   ry                     lx  ly
*
*
*/

void RBTree::leftRotate(RBTNode* &root, RBTNode* x)
{
	// 设置x的右孩子为y
	RBTNode* y = x->right;

	// 将 “y的左孩子” 设为 “x的右孩子”；
	// 如果y的左孩子非空，将 “x” 设为 “y的左孩子的父亲”
	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;

	// 将 “x的父亲” 设为 “y的父亲”
	y->parent = x->parent;

	if (x->parent == NULL)
	{
		root = y;            // 如果 “x的父亲” 是空节点，则将y设为根节点
	}
	else
	{
		if (x->parent->left == x)
			x->parent->left = y;    // 如果 x是它父节点的左孩子，则将y设为“x的父节点的左孩子”
		else
			x->parent->right = y;    // 如果 x是它父节点的左孩子，则将y设为“x的父节点的左孩子”
	}

	// 将 “x” 设为 “y的左孩子”
	y->left = x;
	// 将 “x的父节点” 设为 “y”
	x->parent = y;
}

/*
* 对红黑树的节点(y)进行右旋转
*
* 右旋示意图(对节点y进行左旋)：
*            py                               py
*           /                                /
*          y                                x
*         /  \      --(右旋)-->            /  \                     #
*        x   ry                           lx   y
*       / \                                   / \                   #
*      lx  rx                                rx  ry
*
*/

void RBTree::rightRotate(RBTNode* &root, RBTNode* y)
{
	// 设置x是当前节点的左孩子。
	RBTNode *x = y->left;

	// 将 “x的右孩子” 设为 “y的左孩子”；
	// 如果"x的右孩子"不为空的话，将 “y” 设为 “x的右孩子的父亲”
	y->left = x->right;
	if (x->right != NULL)
		x->right->parent = y;

	// 将 “y的父亲” 设为 “x的父亲”
	x->parent = y->parent;

	if (y->parent == NULL)
	{
		root = x;            // 如果 “y的父亲” 是空节点，则将x设为根节点
	}
	else
	{
		if (y == y->parent->right)
			y->parent->right = x;    // 如果 y是它父节点的右孩子，则将x设为“y的父节点的右孩子”
		else
			y->parent->left = x;    // (y是它父节点的左孩子) 将x设为“x的父节点的左孩子”
	}

	// 将 “y” 设为 “x的右孩子”
	x->right = y;

	// 将 “y的父节点” 设为 “x”
	y->parent = x;
}

/*
* 红黑树插入修正函数
*
* 在向红黑树中插入节点之后(失去平衡)，再调用该函数；
* 目的是将它重新塑造成一颗红黑树。
*
* 参数说明：
*     root 红黑树的根
*     node 插入的结点        // 对应《算法导论》中的z
*/

void RBTree::insertFixUp(RBTNode* &root, RBTNode* node)
{
	RBTNode *parent, *gparent;

	// 若“父节点存在，并且父节点的颜色是红色”
	while ((parent = rb_parent(node)) && rb_is_red(parent))
	{
		gparent = rb_parent(parent);

		//若“父节点”是“祖父节点的左孩子”
		if (parent == gparent->left)
		{
			// Case 1条件：叔叔节点是红色
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

			// Case 2条件：叔叔是黑色，且当前节点是右孩子
			if (parent->right == node)
			{
				RBTNode *tmp;
				leftRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			// Case 3条件：叔叔是黑色，且当前节点是左孩子。
			rb_set_black(parent);
			rb_set_red(gparent);
			rightRotate(root, gparent);
		}
		else//若“z的父节点”是“z的祖父节点的右孩子”
		{
			// Case 1条件：叔叔节点是红色
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

			// Case 2条件：叔叔是黑色，且当前节点是左孩子
			if (parent->left == node)
			{
				RBTNode *tmp;
				rightRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			// Case 3条件：叔叔是黑色，且当前节点是右孩子。
			rb_set_black(parent);
			rb_set_red(gparent);
			leftRotate(root, gparent);
		}
	}

	// 将根节点设为黑色
	rb_set_black(root);
}

/*
* 将结点插入到红黑树中
*
* 参数说明：
*     root 红黑树的根结点
*     node 插入的结点        // 对应《算法导论》中的node
*/

void RBTree::insert(RBTNode* &root, RBTNode* node)
{
	RBTNode *y = NULL;
	RBTNode *x = root;

	// 1. 将红黑树当作一颗二叉查找树，将节点添加到二叉查找树中。
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

	// 2. 设置节点的颜色为红色
	node->color = RED;

	// 3. 将它重新修正为一颗二叉查找树
	insertFixUp(root, node);
}

/*
* 将结点(key为节点键值)插入到红黑树中
*
* 参数说明：
*     tree 红黑树的根结点
*     key 插入结点的键值
*/

void RBTree::insert(int key)
{
	RBTNode *z = NULL;

	// 如果新建结点失败，则返回。
	if ((z = new RBTNode(key, BLACK, NULL, NULL, NULL)) == NULL)
		return;

	insert(mRoot, z);
}


