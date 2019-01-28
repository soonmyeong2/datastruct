#ifndef RBNODE_H
#define RBNODE_H
#include "RBIterator.h"

template <class T>
class RedBlackNode
{
	friend class RBIterator<T>;

	// 디버깅시 메모리 누수를 체크 하기 위한 정적 변수
	// 정상적으로 할당, 삭제가 일어난 경우 alloc_cnt_는
	// 0의 값을 유지해야 한다. 
#ifdef _DEBUG
public:
	static int alloc_cnt_;
#endif

public:
	// 노드 속성 구조체
	// red-black 트리의 노드는 컬러와 인터널,익스터널 속성을 가진다.
	typedef struct _NODEATTR
	{
		unsigned red : 1;			// red인 경우 1, black이면 0
		unsigned internal:1;	// internal인 경우 1, external이면 0
	} NODEATTR, *PNODEATTR;

	NODEATTR	attr_;			// 노드 속성
	T			v_;				// 저장된 값

	RedBlackNode<T>	*parent_;		// 부모 노드
	RedBlackNode<T>	*left_;			// 왼쪽 자식 노드
	RedBlackNode<T>	*right_;		// 오른쪽 자식 노드

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

	// 각각 저장된 값을 설정, 반환하는 함수.
	void value(T v) { v_ = v; }
	T value() { return v_; }

	// 노드를 red, black으로 변경시키는 함수.
	void red() { attr_.red = 1; }
	void black() { attr_.red = 0; }

	// 노드를 internal, external로 변경시키는 함수.
	void internal() { attr_.internal = 1; }
	void external() { attr_.internal = 0; }

	// 노드가 red인지 판별하는 함수.
	bool is_red()
	{
		if (attr_.red)
			return true;

		return false;
	}

	// 노드가 black인지 판별하는 함수.
	bool is_black() { return !is_red(); }

	// 노드가 external인지 판별하는 함수.
	bool is_external() { return !is_internal(); }

	// 노드가 internal인지 판별하는 함수.
	bool is_internal()
	{
		if (attr_.internal)
			return true;
		return false;
	}

	// 각각 parent, left, right child를 반환하는 함수.
	RedBlackNode<T> *parent() { return parent_; }
	RedBlackNode<T> *left() { return left_; }
	RedBlackNode<T> *right() { return right_; }

	// 각각 parent, left, right child를 설정하는 함수.
	// left, right 설정시 parent정보는 자동으로 설정된다.
	void left(RedBlackNode<T> *l) { left_ = l; if (l) l->parent_ = this; }
	void right(RedBlackNode<T> *r) { right_ = r;  if (r) r->parent_ = this; }
	void parent(RedBlackNode<T> *p) { parent_ = p; }

	// 형제 노드를 찾는 함수.
	// 형제 노드가 존재하지 않으면 NULL 반환
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

