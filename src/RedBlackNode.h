#ifndef RBNODE_H
#define RBNODE_H
#include "RBIterator.h"

template <class T>
class RedBlackNode
{
	friend class RBIterator<T>;

	// ������ �޸� ������ üũ �ϱ� ���� ���� ����
	// ���������� �Ҵ�, ������ �Ͼ ��� alloc_cnt_��
	// 0�� ���� �����ؾ� �Ѵ�. 
#ifdef _DEBUG
public:
	static int alloc_cnt_;
#endif

public:
	// ��� �Ӽ� ����ü
	// red-black Ʈ���� ���� �÷��� ���ͳ�,�ͽ��ͳ� �Ӽ��� ������.
	typedef struct _NODEATTR
	{
		unsigned red : 1;			// red�� ��� 1, black�̸� 0
		unsigned internal:1;	// internal�� ��� 1, external�̸� 0
	} NODEATTR, *PNODEATTR;

	NODEATTR	attr_;			// ��� �Ӽ�
	T			v_;				// ����� ��

	RedBlackNode<T>	*parent_;		// �θ� ���
	RedBlackNode<T>	*left_;			// ���� �ڽ� ���
	RedBlackNode<T>	*right_;		// ������ �ڽ� ���

public:
	RedBlackNode(RedBlackNode<T> *p = NULL,
		RedBlackNode<T> *l = NULL,
		RedBlackNode<T> *r = NULL,
		bool red = false,
		bool internal = false)
	{
		attr_.red = red;
		attr_.internal = internal;
		left_ = l;
		right_ = r;
		parent_ = p;

#ifdef _DEBUG
		++alloc_cnt_;
#endif
	}

	~RedBlackNode()
	{
#ifdef _DEBUG
		--alloc_cnt_;
#endif
	}

	// ���� ����� ���� ����, ��ȯ�ϴ� �Լ�.
	void value(T v) { v_ = v; }
	T value() { return v_; }

	// ��带 red, black���� �����Ű�� �Լ�.
	void red() { attr_.red = 1; }
	void black() { attr_.red = 0; }

	// ��带 internal, external�� �����Ű�� �Լ�.
	void internal() { attr_.internal = 1; }
	void external() { attr_.internal = 0; }

	// ��尡 red���� �Ǻ��ϴ� �Լ�.
	bool is_red()
	{
		if (attr_.red)
			return true;

		return false;
	}

	// ��尡 black���� �Ǻ��ϴ� �Լ�.
	bool is_black() { return !is_red(); }

	// ��尡 external���� �Ǻ��ϴ� �Լ�.
	bool is_external() { return !is_internal(); }

	// ��尡 internal���� �Ǻ��ϴ� �Լ�.
	bool is_internal()
	{
		if (attr_.internal)
			return true;
		return false;
	}

	// ���� parent, left, right child�� ��ȯ�ϴ� �Լ�.
	RedBlackNode<T> *parent() { return parent_; }
	RedBlackNode<T> *left() { return left_; }
	RedBlackNode<T> *right() { return right_; }

	// ���� parent, left, right child�� �����ϴ� �Լ�.
	// left, right ������ parent������ �ڵ����� �����ȴ�.
	void left(RedBlackNode<T> *l) { left_ = l; if (l) l->parent_ = this; }
	void right(RedBlackNode<T> *r) { right_ = r;  if (r) r->parent_ = this; }
	void parent(RedBlackNode<T> *p) { parent_ = p; }

	// ���� ��带 ã�� �Լ�.
	// ���� ��尡 �������� ������ NULL ��ȯ
	RedBlackNode<T> *sibling()
	{
		if (parent_ == NULL)
			return NULL;

		if (parent_->left() == this)
			return parent_->right();

		return parent_->left();
	}
};

#ifdef _DEBUG
template <class T>
int RedBlackNode<T>::alloc_cnt_ = 0;
#endif
#endif

