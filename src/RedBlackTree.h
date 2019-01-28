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

	// 멤버 변수
private:
	RBNode	*root_;
	// 내부적으로 사용되는 함수

protected:

	// v값을 가지는 노드를 찾아서 리턴한다.
	RBNode *_search(T v);

	// n으로 부터 LEFT MOST INTERNAL 노드를 찾아서 리턴한다.
	RBNode *_search_lmi(RBNode *n);

	// 노드 n을 삭제한다.
	void _erase(RBNode *n);

	// 더블 레드시의 리컬러링을 수행한다.
	bool _recoloring_drp(RBNode *n);

	// 더블 블랙시의 리컬러링을 수행한다.
	bool _recoloring_dbp(RBNode *n);

	// 노드 n부터 n, n부모, n부모의 부모 노드에 대한
	// 트라이노드 리스트럭쳐링을 수행한다.
	RBNode *_trirest(RBNode *n);

	// 더블 레드 문제를 해결한다.
	void _solve_dbp(RBNode *n);

	// 더블 블랙 문제를 해결한다.
	void _solve_drp(RBNode *n);

	// 루트를 설정한다. n의 부모는 NULL로 설정된다.
	void _set_root(RBNode *n) { root_ = n; if (n) { n->parent(NULL); } }


	// n부터 시작해서 dfs순으로 모든 노드를 제거한다.
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

	// n노드 부터 시작해서 가장 긴 노드의 높이를 구한다.
	int _height(RBNode *n)
	{
		if (n == NULL)
			return 0;

		return MAX(_height(n->left()) + 1, _height(n->right()) + 1);
	}


	// 외부 인터페이스 함수
public:


	// 루트 노드를 반환한다.
	RBNode *root() { return root_; }

	// 생성자 및 소멸자
	RedBlackTree();
	virtual ~RedBlackTree();

	// value값을 추가한다.
	int insert(T value);

	// value값을 삭제한다.
	void erase(T value);

	// value값이 존재하는지 검색한다.
	bool search(T& value);

	// 높이를 반환한다.
	int height() { return _height(root()); }

	
	// 모든 item을 complete binary tree 형태로 배열에 저장한다.
	void items(PRBARITEM items)
	{
		int size = int(pow(2, height()));
		
		for (int i = 0; i<size; ++i)
			items[i].used = false;
		
		_fill_items(items, root(), 1);
	}

	// 모든 노드를 제거한다.
	void clear()
	{
		_clear(root());
		_set_root(NULL);
	}

	/**
	*	@brief	트리에서 해당 아이템을 찾는다.
	*	@pre	트리가 비었다면, 초기화가 되어있어야 한다.
	*	@return	해당 아이템을 찾으면 true,못찾으면 false를 리턴
	*/
	bool Retrieve(const T & item, T*& found);	// retrieve item in tree

};

// v값을 가지는 노드를 찾는다.
template <class T>
RedBlackNode<T> *RedBlackTree<T>::_search(T v)
{
	RBNode	*cur = root();
	
	// external노드이거나 v값을 찾을때까지 반복한다.
	while (cur != NULL && cur->value() != v && cur->is_internal())
	{
		// v가 현재 노드 값보다 작으면 왼쪽으로 탐색한다.
		if (v < cur->value())
			cur = cur->left();

		// v가 현재 노드 값보다 크면 오른쪽으로 탐색한다.
		else if (v > cur->value())
			cur = cur->right();
	}

	return cur;
}

// n노드 부터의 LEFT MOST INTERNAL 노드를 찾는다.
template <class T>
RedBlackNode<T> *RedBlackTree<T>::_search_lmi(RBNode *n)
{
	RBNode *cur = n;

	// left가 internal인 동안 반복한다.
	while (cur != NULL &&
		cur->is_internal() &&
		cur->left()->is_internal())
	{
		cur = cur->left();
	}

	return cur;
}


// 생성자
template <class T>
RedBlackTree<T>::RedBlackTree()
{
	_set_root(NULL);
}

// 소멸자
template <class T>
RedBlackTree<T>::~RedBlackTree()
{
	clear();
}

// 더블레드시의 리컬러링을 수행한다.
// 루트로 확장 가능한 경우 true를, 그렇지 않은 경우 false를 리턴한다.
template <class T>
bool RedBlackTree<T>::_recoloring_drp(RBNode *n)
{
	RBNode *p;

	ASSERT(n != NULL);
	ASSERT(n->parent() != NULL);

	p = n->parent();

	// 부모 노드의 자식 둘을 black으로 칠한다.
	p->left()->black();
	p->right()->black();

	// 부모가 root가 아닌 경우 red로 칠한다.
	// root로 확장 가능하므로 true를 리턴한다.
	if (p != root())
	{
		p->red();
		return true;
	}

	return false;
}

// 더블 블랙시의 리컬러링을 수행한다.
// 더블 블랙 문제가 확장될 수 있는 경우 true를, 
// 그렇지 않으면 false를 리턴한다.
template <class T>
bool RedBlackTree<T>::_recoloring_dbp(RBNode *n)
{
	RBNode *sn, *pn;

	ASSERT(n != NULL);
	ASSERT(n->parent() != NULL);

	pn = n->parent();
	sn = n->sibling();

	// 자신의 노드를 블랙으로 칠한다.
	n->black();

	// 형제 노드를 레드로 칠한다.
	sn->red();

	// 부모가 red인 경우 black으로 변경한다.
	// 이 경우 더 이상 더블 블랙이 전파되지 않는다.
	if (pn->is_red())
	{
		pn->black();
		return false;
	}

	// 부모가 루트가 아닌 경우 더블 블랙이 전파될 수 있다.
	return pn != root();
}

// n, n부모, n부모부모 노드로 리스트럭쳐링을 수행한다.
// 리스트럭쳐링 완료 후의 중간 노드를 반환한다.
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

	// 다음과 같은 두 단계에 걸쳐서 트라이노드 리스트럭쳐링을 한다.
	// 
	// 1. 세 노드의 링크 기준을 판별하여, 적절하게 
	// 2. 세 노드중 부모노드가 된 mid의 부모를 연결한다.

	// 1단계:
	// 트라이 노드 리스트럭쳐링에는 총 네가지 경우가 있다.

	if (ppn->left() == pn)
	{

		if (pn->left() == n)
		{
			// 1번 경우
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
			// 2번 경우
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
			// 3번 경우
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
			// 4번 경우
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

	// 2단계:
	// 이 단계에서는 mid를 기준으로 아래와 같은 형태로
	// 리스트럭쳐링이 완료되었다.
	//
	//       mid
	//      /   \
	//    left   right
	//
	// 남은 작업은 pp의 부모노드의 링크를 mid로 연결 시켜주는 것이다.

	if (pppn)
	{
		// ppp로 부모가 넘어온 경우
		// ppp의 자식 링크로 mid를 가리키도록 설정한다.
		if (pppn->right() == ppn)
			pppn->right(mid);
		else
			pppn->left(mid);
	}
	else
	{
		// ppp가 없는 경우 pp가 루트 였으므로
		// mid를 루트로 변경해 준다.
		_set_root(mid);
	}

	return mid;
}

// 노드 n에서 발생한 더블 레드 문제를 해결한다.
template <class T>
void RedBlackTree<T>::_solve_drp(RBNode *n)
{
	RBNode *pn;
	RBNode *mid;

	ASSERT(n->is_red());

	// 더블 레드인지 확인한다.
	pn = n->parent();
	if (pn && pn->is_red() && pn->sibling())
	{
		// 부모의 형제가 블랙인 경우
		// 트라이 노드 리스트럭쳐링을 수행한다.
		if (pn->sibling()->is_black())
		{
			mid = _trirest(n);

			// 새로운 mid노드가 red인 경우
			// 색깔을 변경한다.
			if (mid->is_red())
			{
				mid->black();
				mid->left()->red();
				mid->right()->red();
			}
		}

		// 형제가 레드인 경우 리컬러링을 수행한다.
		else if (pn->sibling()->is_red())
		{
			// 리컬러링을 수행한 후, 전파되면 _solve_drp를 재귀호출 하여
			// 문제를 해결한다.
			if (_recoloring_drp(pn) && pn->parent()->parent()->is_red())
				_solve_drp(pn->parent());
		}
	}
}

// 노드 n에서 발생한 더블 블랙 문제를 해결한다.
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

	// 형제 노드가 블랙인 경우
	if (sn->is_black())
	{
		// 형제 노드의 모든 자식이 블랙이면 리컬러링을 수행한다.
		if (sn->left()->is_black() && sn->right()->is_black())
		{
			if (_recoloring_dbp(n))
				_solve_dbp(n->parent());
		}

		// 형제 노드의 왼쪽 자식이 red이면
		// 왼쪽 자식을 기준으로 트라이노드 리스트럭쳐링을 수행한다.
		else
		{
			bool red;

			if (sn->left()->is_red())
			{
				red = sn->left()->parent()->parent()->is_red();
				mid = _trirest(sn->left());

			}

			// 오른족 자식을 기준으로 트라이노드 리스트럭쳐링을 수행한다.
			else
			{
				red = sn->right()->parent()->parent()->is_red();
				mid = _trirest(sn->right());
			}

			// mid는 원래 trirest 수행전에 최상단 부모의 색상으로 칠한다.
			if (red)
				mid->red();
			else
				mid->black();

			// mid의 left와 right는 black으로 칠한다.
			mid->left()->black();
			mid->right()->black();

		}
	}

	// 형제 노드가 레드인 경우 adjustment를 수행한다.
	else
	{
		// 형제를 블랙으로
		// 부모를 레드로 색칠한다.
		sn->black();
		pn->red();

		// 세 노드를 리스트럭쳐링 한다.
		if (pn->left() == n)
			_trirest(sn->right());
		else
			_trirest(sn->left());

		// n의 새로운 형제가 블랙인 경우
		// 다시 더블 블랙 문제를 푼다.
		if (n->sibling()->is_black())
			_solve_dbp(n);
	}

}

// 트리에 v값을 가지는 노드를 추가한다.
template <class T>
int RedBlackTree<T>::insert(T v)
{
	RBNode	*n;

	// v값을 가지는 노드를 찾는다.
	n = _search(v);

	// n이 NULL인 경우 루트를 삽입한다.
	if (n == NULL)
	{
		// 루트를 추가한다.
		n = new RBNode(NULL, NULL, NULL, false, true);
		n->value(v);
		
		// 루트에 익스터널 노드를 추가한다.
		n->left(new RBNode);
		n->right(new RBNode);

		_set_root(n);

		return 1;
	}

	// n이 익스터널 노드인 경우
	else if (n->is_external())
	{
		// 해당 노드를 인터널, 레드, 값을 v로 변경한다.
		n->internal();
		n->red();
		n->value(v);

		// n에 새로운 익스터널 노드 두개를 추가한다.
		n->left(new RBNode);
		n->right(new RBNode);

		// 더블 레드 문제가 생긴 경우 해결한다.
		_solve_drp(n);

		return 1;
	}

	return 0;
}

// 노드 n을 삭제한다.
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

	// n의 left와 right가 모두 인터널 노드인 경우
	if (n->left()->is_internal() && n->right()->is_internal())
	{
		// 오른쪽 서브트리의 LEFT MOST INTERNAL노드를 찾는다.
		lmi = _search_lmi(n->right());

		// LMI노드를 삭제한후, n의 값을 LMI값으로 바꾼다.
		tmp = lmi->value();
		_erase(lmi);
		n->value(tmp);
		return;
	}

	// 삭제된 후, 원래 노드와 결합될 r노드를 찾는다.
	// r노드 외의 자식은 삭제한다.
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

	// 부모가 NULL인 경우
	if (pn == NULL)
	{
		// rn이 익스터널 노드이면 모두 제거한후, 
		// 루트를 NULL로 만든다.
		if (rn->is_external())
		{
			_set_root(NULL);
			delete rn;
		}

		// rn이 인터널 노드인 경우 rn을 루트로 설정하고
		// rn을 블랙으로 설정한다.
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
		// 부모와 rn을 연결한다.
		if (pn->left() == n)
			pn->left(rn);
		else
			pn->right(rn);

		// 더블 블랙 체크
		if (rn && rn->is_black() && n->is_black())
			_solve_dbp(rn);

		// 더블 블랙이 아닌 경우 rn을 블랙으로 변경한다.
		else
			rn->black();
	}

	// 노드 삭제
	delete n;
}

// 트리에서 v값을 가지는 노드를 삭제한다.
template <class T>
void RedBlackTree<T>::erase(T v)
{
	_erase(_search(v));
}

// 트리에서 v값을 가지는 노드를 찾는다.
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

//트리에서 해당 아이템을 찾는 함수
template<class T>
bool RedBlackTree<T>::Retrieve(const T & item, T*& found)
{//비재귀적 방법을 통해 속도를 올림.
	RBNode *currentNode = root();
	while (1)
	{
		if (currentNode == NULL)	//현재 노드가 비었다면
			return false;	//못찾음
		if (currentNode->v_ == item)	//일치하는 노드를 찾앗다면
		{
			found = &(currentNode->v_);	//레퍼런스를 넘김
			return true;	//찾음
		}
		else if (currentNode->v_ > item)	//오른쪽이 더 크다면
			currentNode = currentNode->left_;	//왼쪽으로 이동
		else if (currentNode->v_ < item)	//왼쪽이 더 크다면
			currentNode = currentNode->right_;	//오른쪽으로 이동
	}
}
#endif