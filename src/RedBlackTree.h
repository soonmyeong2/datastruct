#pragma once

#ifndef RBTREE_H
#define RBTREE_H

#include "RedBlackNode.h"
#include "RBIterator.h"
#include <stdio.h>
#include <assert.h>

#ifndef ASSERT
#ifdef _DEBUG
#define ASSERT assert
#else
#define ASSERT 1 ? (void) 0 : assert 
#endif
#endif

#ifndef MAX
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif

template <class T>
class RedBlackTree
{
	friend class RBIterator<T>;
private:
	typedef RedBlackNode<T>	RBNode;

public:
	typedef struct _RBARITEM
	{
		T		v;
		bool	red;
		bool	internal;
		bool	used;
	} RBARITEM, *PRBARITEM;

	// ��� ����
private:
	RBNode	*root_;
	// ���������� ���Ǵ� �Լ�

protected:

	// v���� ������ ��带 ã�Ƽ� �����Ѵ�.
	RBNode *_search(T v);

	// n���� ���� LEFT MOST INTERNAL ��带 ã�Ƽ� �����Ѵ�.
	RBNode *_search_lmi(RBNode *n);

	// ��� n�� �����Ѵ�.
	void _erase(RBNode *n);

	// ���� ������� ���÷����� �����Ѵ�.
	bool _recoloring_drp(RBNode *n);

	// ���� ������ ���÷����� �����Ѵ�.
	bool _recoloring_dbp(RBNode *n);

	// ��� n���� n, n�θ�, n�θ��� �θ� ��忡 ����
	// Ʈ���̳�� ����Ʈ���ĸ��� �����Ѵ�.
	RBNode *_trirest(RBNode *n);

	// ���� ���� ������ �ذ��Ѵ�.
	void _solve_dbp(RBNode *n);

	// ���� �� ������ �ذ��Ѵ�.
	void _solve_drp(RBNode *n);

	// ��Ʈ�� �����Ѵ�. n�� �θ�� NULL�� �����ȴ�.
	void _set_root(RBNode *n) { root_ = n; if (n) { n->parent(NULL); } }


	// n���� �����ؼ� dfs������ ��� ��带 �����Ѵ�.
	void _clear(RBNode *n)
	{
		if (n != NULL)
		{
			_clear(n->left());
			_clear(n->right());

			delete n;
		}
	}

	// 
	void _fill_items(PRBARITEM ar, RBNode *n, int offset)
	{
		ASSERT(ar != NULL);

		if (n != NULL)
		{
			if (n->is_internal())
				ar[offset].v = n->value();

			ar[offset].red = n->is_red();
			ar[offset].internal = n->is_internal();
			ar[offset].used = true;

			_fill_items(ar, n->left(), offset * 2);
			_fill_items(ar, n->right(), offset * 2 + 1);
		}
	}

	// n��� ���� �����ؼ� ���� �� ����� ���̸� ���Ѵ�.
	int _height(RBNode *n)
	{
		if (n == NULL)
			return 0;

		return MAX(_height(n->left()) + 1, _height(n->right()) + 1);
	}


	// �ܺ� �������̽� �Լ�
public:


	// ��Ʈ ��带 ��ȯ�Ѵ�.
	RBNode *root() { return root_; }

	// ������ �� �Ҹ���
	RedBlackTree();
	virtual ~RedBlackTree();

	// value���� �߰��Ѵ�.
	int insert(T value);

	// value���� �����Ѵ�.
	void erase(T value);

	// value���� �����ϴ��� �˻��Ѵ�.
	bool search(T& value);

	// ���̸� ��ȯ�Ѵ�.
	int height() { return _height(root()); }

	
	// ��� item�� complete binary tree ���·� �迭�� �����Ѵ�.
	void items(PRBARITEM items)
	{
		int size = int(pow(2, height()));
		
		for (int i = 0; i<size; ++i)
			items[i].used = false;
		
		_fill_items(items, root(), 1);
	}

	// ��� ��带 �����Ѵ�.
	void clear()
	{
		_clear(root());
		_set_root(NULL);
	}

	/**
	*	@brief	Ʈ������ �ش� �������� ã�´�.
	*	@pre	Ʈ���� ����ٸ�, �ʱ�ȭ�� �Ǿ��־�� �Ѵ�.
	*	@return	�ش� �������� ã���� true,��ã���� false�� ����
	*/
	bool Retrieve(const T & item, T*& found);	// retrieve item in tree

};

// v���� ������ ��带 ã�´�.
template <class T>
RedBlackNode<T> *RedBlackTree<T>::_search(T v)
{
	RBNode	*cur = root();
	
	// external����̰ų� v���� ã�������� �ݺ��Ѵ�.
	while (cur != NULL && cur->value() != v && cur->is_internal())
	{
		// v�� ���� ��� ������ ������ �������� Ž���Ѵ�.
		if (v < cur->value())
			cur = cur->left();

		// v�� ���� ��� ������ ũ�� ���������� Ž���Ѵ�.
		else if (v > cur->value())
			cur = cur->right();
	}

	return cur;
}

// n��� ������ LEFT MOST INTERNAL ��带 ã�´�.
template <class T>
RedBlackNode<T> *RedBlackTree<T>::_search_lmi(RBNode *n)
{
	RBNode *cur = n;

	// left�� internal�� ���� �ݺ��Ѵ�.
	while (cur != NULL &&
		cur->is_internal() &&
		cur->left()->is_internal())
	{
		cur = cur->left();
	}

	return cur;
}


// ������
template <class T>
RedBlackTree<T>::RedBlackTree()
{
	_set_root(NULL);
}

// �Ҹ���
template <class T>
RedBlackTree<T>::~RedBlackTree()
{
	clear();
}

// ��������� ���÷����� �����Ѵ�.
// ��Ʈ�� Ȯ�� ������ ��� true��, �׷��� ���� ��� false�� �����Ѵ�.
template <class T>
bool RedBlackTree<T>::_recoloring_drp(RBNode *n)
{
	RBNode *p;

	ASSERT(n != NULL);
	ASSERT(n->parent() != NULL);

	p = n->parent();

	// �θ� ����� �ڽ� ���� black���� ĥ�Ѵ�.
	p->left()->black();
	p->right()->black();

	// �θ� root�� �ƴ� ��� red�� ĥ�Ѵ�.
	// root�� Ȯ�� �����ϹǷ� true�� �����Ѵ�.
	if (p != root())
	{
		p->red();
		return true;
	}

	return false;
}

// ���� ������ ���÷����� �����Ѵ�.
// ���� �� ������ Ȯ��� �� �ִ� ��� true��, 
// �׷��� ������ false�� �����Ѵ�.
template <class T>
bool RedBlackTree<T>::_recoloring_dbp(RBNode *n)
{
	RBNode *sn, *pn;

	ASSERT(n != NULL);
	ASSERT(n->parent() != NULL);

	pn = n->parent();
	sn = n->sibling();

	// �ڽ��� ��带 ������ ĥ�Ѵ�.
	n->black();

	// ���� ��带 ����� ĥ�Ѵ�.
	sn->red();

	// �θ� red�� ��� black���� �����Ѵ�.
	// �� ��� �� �̻� ���� ���� ���ĵ��� �ʴ´�.
	if (pn->is_red())
	{
		pn->black();
		return false;
	}

	// �θ� ��Ʈ�� �ƴ� ��� ���� ���� ���ĵ� �� �ִ�.
	return pn != root();
}

// n, n�θ�, n�θ�θ� ���� ����Ʈ���ĸ��� �����Ѵ�.
// ����Ʈ���ĸ� �Ϸ� ���� �߰� ��带 ��ȯ�Ѵ�.
template <class T>
RedBlackNode<T> *RedBlackTree<T>::_trirest(RBNode *n)
{
	RBNode	*l, *r;
	RBNode	*pn, *ppn;
	RBNode	*pppn;
	RBNode	*mid;

	ASSERT(n != NULL);
	ASSERT(n->parent() != NULL);
	ASSERT(n->parent()->parent() != NULL);

	pn = n->parent();
	ppn = pn->parent();
	pppn = ppn->parent();

	// ������ ���� �� �ܰ迡 ���ļ� Ʈ���̳�� ����Ʈ���ĸ��� �Ѵ�.
	// 
	// 1. �� ����� ��ũ ������ �Ǻ��Ͽ�, �����ϰ� 
	// 2. �� ����� �θ��尡 �� mid�� �θ� �����Ѵ�.

	// 1�ܰ�:
	// Ʈ���� ��� ����Ʈ���ĸ����� �� �װ��� ��찡 �ִ�.

	if (ppn->left() == pn)
	{

		if (pn->left() == n)
		{
			// 1�� ���
			//     pp
			//    /
			//   p
			//  /
			// c
			ppn->left(pn->right());
			pn->right(ppn);
			mid = pn;
		}
		else
		{
			// 2�� ���
			//     pp
			//    /
			//   p
			//    \
			//     c

			l = n->left();
			r = n->right();

			n->left(pn);
			n->right(ppn);
			pn->right(l);
			ppn->left(r);
			mid = n;
		}
	}
	else
	{
		if (pn->left() == n)
		{
			// 3�� ���
			// pp
			//  \
			//   p
			//  /
			// c

			l = n->left();
			r = n->right();

			n->left(ppn);
			n->right(pn);
			ppn->right(l);
			pn->left(r);
			mid = n;
		}
		else
		{
			// 4�� ���
			// pp
			//  \
			//   p
			//    \
			//     c

			ppn->right(pn->left());
			pn->left(ppn);
			mid = pn;
		}
	}

	// 2�ܰ�:
	// �� �ܰ迡���� mid�� �������� �Ʒ��� ���� ���·�
	// ����Ʈ���ĸ��� �Ϸ�Ǿ���.
	//
	//       mid
	//      /   \
	//    left   right
	//
	// ���� �۾��� pp�� �θ����� ��ũ�� mid�� ���� �����ִ� ���̴�.

	if (pppn)
	{
		// ppp�� �θ� �Ѿ�� ���
		// ppp�� �ڽ� ��ũ�� mid�� ����Ű���� �����Ѵ�.
		if (pppn->right() == ppn)
			pppn->right(mid);
		else
			pppn->left(mid);
	}
	else
	{
		// ppp�� ���� ��� pp�� ��Ʈ �����Ƿ�
		// mid�� ��Ʈ�� ������ �ش�.
		_set_root(mid);
	}

	return mid;
}

// ��� n���� �߻��� ���� ���� ������ �ذ��Ѵ�.
template <class T>
void RedBlackTree<T>::_solve_drp(RBNode *n)
{
	RBNode *pn;
	RBNode *mid;

	ASSERT(n->is_red());

	// ���� �������� Ȯ���Ѵ�.
	pn = n->parent();
	if (pn && pn->is_red() && pn->sibling())
	{
		// �θ��� ������ ���� ���
		// Ʈ���� ��� ����Ʈ���ĸ��� �����Ѵ�.
		if (pn->sibling()->is_black())
		{
			mid = _trirest(n);

			// ���ο� mid��尡 red�� ���
			// ������ �����Ѵ�.
			if (mid->is_red())
			{
				mid->black();
				mid->left()->red();
				mid->right()->red();
			}
		}

		// ������ ������ ��� ���÷����� �����Ѵ�.
		else if (pn->sibling()->is_red())
		{
			// ���÷����� ������ ��, ���ĵǸ� _solve_drp�� ���ȣ�� �Ͽ�
			// ������ �ذ��Ѵ�.
			if (_recoloring_drp(pn) && pn->parent()->parent()->is_red())
				_solve_drp(pn->parent());
		}
	}
}

// ��� n���� �߻��� ���� �� ������ �ذ��Ѵ�.
template <class T>
void RedBlackTree<T>::_solve_dbp(RBNode *n)
{
	RBNode *pn, *ppn, *mid;
	RBNode *sn;

	if (n == NULL)
		return;

	if (n->parent() == NULL)
		return;

	pn = n->parent();
	ppn = pn->parent();
	sn = n->sibling();

	if (sn == NULL || sn->is_external())
		return;

	// ���� ��尡 ���� ���
	if (sn->is_black())
	{
		// ���� ����� ��� �ڽ��� ���̸� ���÷����� �����Ѵ�.
		if (sn->left()->is_black() && sn->right()->is_black())
		{
			if (_recoloring_dbp(n))
				_solve_dbp(n->parent());
		}

		// ���� ����� ���� �ڽ��� red�̸�
		// ���� �ڽ��� �������� Ʈ���̳�� ����Ʈ���ĸ��� �����Ѵ�.
		else
		{
			bool red;

			if (sn->left()->is_red())
			{
				red = sn->left()->parent()->parent()->is_red();
				mid = _trirest(sn->left());

			}

			// ������ �ڽ��� �������� Ʈ���̳�� ����Ʈ���ĸ��� �����Ѵ�.
			else
			{
				red = sn->right()->parent()->parent()->is_red();
				mid = _trirest(sn->right());
			}

			// mid�� ���� trirest �������� �ֻ�� �θ��� �������� ĥ�Ѵ�.
			if (red)
				mid->red();
			else
				mid->black();

			// mid�� left�� right�� black���� ĥ�Ѵ�.
			mid->left()->black();
			mid->right()->black();

		}
	}

	// ���� ��尡 ������ ��� adjustment�� �����Ѵ�.
	else
	{
		// ������ ������
		// �θ� ����� ��ĥ�Ѵ�.
		sn->black();
		pn->red();

		// �� ��带 ����Ʈ���ĸ� �Ѵ�.
		if (pn->left() == n)
			_trirest(sn->right());
		else
			_trirest(sn->left());

		// n�� ���ο� ������ ���� ���
		// �ٽ� ���� �� ������ Ǭ��.
		if (n->sibling()->is_black())
			_solve_dbp(n);
	}

}

// Ʈ���� v���� ������ ��带 �߰��Ѵ�.
template <class T>
int RedBlackTree<T>::insert(T v)
{
	RBNode	*n;

	// v���� ������ ��带 ã�´�.
	n = _search(v);

	// n�� NULL�� ��� ��Ʈ�� �����Ѵ�.
	if (n == NULL)
	{
		// ��Ʈ�� �߰��Ѵ�.
		n = new RBNode(NULL, NULL, NULL, false, true);
		n->value(v);
		
		// ��Ʈ�� �ͽ��ͳ� ��带 �߰��Ѵ�.
		n->left(new RBNode);
		n->right(new RBNode);

		_set_root(n);

		return 1;
	}

	// n�� �ͽ��ͳ� ����� ���
	else if (n->is_external())
	{
		// �ش� ��带 ���ͳ�, ����, ���� v�� �����Ѵ�.
		n->internal();
		n->red();
		n->value(v);

		// n�� ���ο� �ͽ��ͳ� ��� �ΰ��� �߰��Ѵ�.
		n->left(new RBNode);
		n->right(new RBNode);

		// ���� ���� ������ ���� ��� �ذ��Ѵ�.
		_solve_drp(n);

		return 1;
	}

	return 0;
}

// ��� n�� �����Ѵ�.
template <class T>
void RedBlackTree<T>::_erase(RBNode *n)
{
	RBNode	*pn, *lmi;
	T		tmp;
	RBNode	*rn;
	bool	dbp = false;

	if (n == NULL)
		return;

	if (n->is_external())
		return;

	pn = n->parent();

	// n�� left�� right�� ��� ���ͳ� ����� ���
	if (n->left()->is_internal() && n->right()->is_internal())
	{
		// ������ ����Ʈ���� LEFT MOST INTERNAL��带 ã�´�.
		lmi = _search_lmi(n->right());

		// LMI��带 ��������, n�� ���� LMI������ �ٲ۴�.
		tmp = lmi->value();
		_erase(lmi);
		n->value(tmp);
		return;
	}

	// ������ ��, ���� ���� ���յ� r��带 ã�´�.
	// r��� ���� �ڽ��� �����Ѵ�.
	if (n->left()->is_internal())
	{
		rn = n->left();
		delete n->right();
	}
	else
	{
		rn = n->right();
		delete n->left();
	}

	// �θ� NULL�� ���
	if (pn == NULL)
	{
		// rn�� �ͽ��ͳ� ����̸� ��� ��������, 
		// ��Ʈ�� NULL�� �����.
		if (rn->is_external())
		{
			_set_root(NULL);
			delete rn;
		}

		// rn�� ���ͳ� ����� ��� rn�� ��Ʈ�� �����ϰ�
		// rn�� ������ �����Ѵ�.
		else
		{
			_set_root(rn);

			if (rn->is_black() && n->is_black())
				_solve_dbp(rn);

			rn->black();
		}
	}
	else
	{
		// �θ�� rn�� �����Ѵ�.
		if (pn->left() == n)
			pn->left(rn);
		else
			pn->right(rn);

		// ���� �� üũ
		if (rn && rn->is_black() && n->is_black())
			_solve_dbp(rn);

		// ���� ���� �ƴ� ��� rn�� ������ �����Ѵ�.
		else
			rn->black();
	}

	// ��� ����
	delete n;
}

// Ʈ������ v���� ������ ��带 �����Ѵ�.
template <class T>
void RedBlackTree<T>::erase(T v)
{
	_erase(_search(v));
}

// Ʈ������ v���� ������ ��带 ã�´�.
template <class T>
bool RedBlackTree<T>::search(T& v)
{
	RBNode *node = _search(v);

	if (node && node->is_internal())
	{
		v = node->v_;
		return true;
	}

	return false;
}

//Ʈ������ �ش� �������� ã�� �Լ�
template<class T>
bool RedBlackTree<T>::Retrieve(const T & item, T*& found)
{//������� ����� ���� �ӵ��� �ø�.
	RBNode *currentNode = root();
	while (1)
	{
		if (currentNode == NULL)	//���� ��尡 ����ٸ�
			return false;	//��ã��
		if (currentNode->v_ == item)	//��ġ�ϴ� ��带 ã�Ѵٸ�
		{
			found = &(currentNode->v_);	//���۷����� �ѱ�
			return true;	//ã��
		}
		else if (currentNode->v_ > item)	//�������� �� ũ�ٸ�
			currentNode = currentNode->left_;	//�������� �̵�
		else if (currentNode->v_ < item)	//������ �� ũ�ٸ�
			currentNode = currentNode->right_;	//���������� �̵�
	}
}
#endif