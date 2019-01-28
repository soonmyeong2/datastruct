#pragma once
#include "Stack.h"

template <class T> class RedBlackTree;
template <class T> class RedBlackNode;

/**
*	@brief	RBIterator Ŭ����.
*/
template <class Type>
class RBIterator
{
public:
	/**
	*	@brief	iterator�� �����ϴ� Ʈ���� �Է¹޴� ������
	*	@pre	�Է¹��� Ʈ���� �ʱ�ȭ �ǰų�, �ùٸ� Ʈ������ �Ѵ�.
	*	@post	list�� current�� Ʈ���� ������ ����ȴ�.
	*/
	RBIterator(RedBlackTree<Type> &list) :_list(&list), _current(list.root) {}

	/**
	*	@brief	�⺻�Ҹ���
	*/
	~RBIterator() { }

	/**
	*	@brief	���� ����� �ڷᰡ ������� Ȯ���ϴ� �Լ�
	*	@pre	iterator�� ���õǾ� �־�� �Ѵ�.
	*	@post
	*	@return
	*/
	bool IsNull();

	/**
	*	@brief	�������� �Ѿ�� �������� �����ڿ����ε�
	*	@pre	iterator�� �Ҵ��� �Ǿ� �־���Ѵ�.
	*	@post	DFS�� ���� ���� �Ѿ��
	*	@return	���� ����� ���۷����� ��ȯ�ȴ�.
	*/
	RBIterator<Type>& operator++();

	/**
	*	@brief	�������� �Ѿ�� �������� �����ڿ����ε�
	*	@pre	iterator�� �Ҵ��� �Ǿ� �־���Ѵ�.
	*	@post	DFS�� ���� ���� �Ѿ��
	*	@return	this����� ���簡 ��ȯ�ȴ�
	*/
	RBIterator<Type> operator++(int);

	/**
	*	@brief	���� ����� ���۷����� ��ȯ��
	*	@pre	itearator�� BST�Ҵ��� �Ǿ� �־���Ѵ�.
	*	@return	�������� ���۷����� ��ȯ�Ѵ�.
	*/
	Type& operator*();
private:
	///Ʈ�� ����Ʈ
	RedBlackTree<Type>* _list;
	///������������
	RedBlackNode<Type>* _current;
	///��ȸ�� ���� ����
	Stack<RedBlackNode<Type>*> stack;
};

///���������Ͱ� nullptr���� ��ȯ�ϴ� �Լ�
template<class Type>
inline bool RBIterator<Type>::IsNull()
{
	return (_current == nullptr);
}

///�������� �Ѿ���� ���� ������ �����ε�
template<class Type>
inline RBIterator<Type>& RBIterator<Type>::operator++()
{
	//Stack�� �̿��� DFS
	while (_current != nullptr)	//���簡 nullptr�϶����� �ݺ�
	{
		stack.Push(_current);	//���縦 ���ÿ� �߰�
		_current = _current->left;	//������ �������� �̵�(���� �ǾƷ��� �̵�)
	}
	_current = stack.Pop();	//���ÿ��� �ϳ� ������ ����� �ٲ�
	_current = _current->right;	//�������� �̵�
	return *this;
}

///������ �Ѿ���� ���� ������ �����ε�
template<class Type>
inline RBIterator<Type> RBIterator<Type>::operator++(int)
{
	RBIterator temporaryItem = *this;
	while (current != nullptr)
	{
		stack.Push(_current);
		_current = _current->left;
	}
	_current = stack.Pop();
	_current = _current->right();
	return temporaryItem;	//�ӽð�ü�� ��ȯ�Ѵ�.
}

///�������� ������ ���۷����� ��ȯ�ϴ� �����ڿ����ε�
template<class Type>
inline Type & RBIterator<Type>::operator*()
{
	return (_current->data);
}
