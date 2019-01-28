#pragma once
#pragma once

#include "DoublyIterator.h" 
/**
*	@brief	DoublyNodeType ����ü
*/
template <class T>
struct DoublyNodeType
{	//Node�� ����ü
	/**
	*	@brief	�⺻������
	*	@post	��尡 �ʱ�ȭ�ȴ�.
	*/
	DoublyNodeType() :prev(nullptr), next(nullptr) {};

	/**
	*	@brief	����� ���������
	*	@post	�Է¹��� ���� ��尡 deepcopy�ȴ�,
	*/
	DoublyNodeType(const DoublyNodeType<T>& node);
	///������
	T data;
	///������ ����Ű�� ������
	DoublyNodeType *prev;
	///������ ����Ű�� ������
	DoublyNodeType *next;

	/**
	*	@brief	���Կ����� �����ε�
	*	@post	�Է¹��� ���� ��尡 deepcopy�ȴ�.
	*	@return	this�����Ͱ� ��ȯ�ȴ�.
	*/
	DoublyNodeType<T>& operator=(const DoublyNodeType<T>& node);
};

/**
*	@brief	DoublyLinkedList Ŭ����.
*/
template <class T>
class DoublyLinkedList
{
	friend class DoublyIterator<T>;	//private����� ����ϱ����� ������ ����
public:
	/**
	*	@brief	�⺻������
	*/
	DoublyLinkedList();

	DoublyLinkedList(const DoublyLinkedList<T>& list);

	/**
	*	@brief	�⺻ �Ҹ���
	*/
	~DoublyLinkedList();

	/**
	*	@brief	�� item�� ������ �� �ִ��� ��ȯ�� �ִ� �Լ�
	*	@pre	����
	*	@post	����
	*	@return	������ �޸𸮰� �ִٸ� true, ���ٸ� false
	*/
	bool IsFull();

	/**
	*	@brief	Initialize list to empty state.
	*	@pre	None
	*	@post	List is empty.
	*/
	void MakeEmpty();

	/**
	*	@brief	Get number of elements in the list.
	*	@pre	None.
	*	@post	Function value = number of elements in list.
	*	@return	Number of elements in this list.
	*/
	int GetLength() const;

	/**
	*	@brief	Add item into this list.
	*	@pre	List is not full. item is not in list.
	*	@post	Item is inserted in this list.
	*	@return	1 if this function works well, otherwise 0.
	*/
	void Add(T item);

	/**
	*	@brief	����Ʈ���� id�� ��ġ�ϴ� �������� ������
	*	@pre	item���� �Է¹��� item�� operator== �� �����ε� �Ǿ��־�� �Ѵ�.
	*	@post	����Ʈ���� ���ڷ� ���� item�� id�� ��ġ�ϴ� ��带 ã�Ƽ� ����(�Ҵ�����)�Ѵ�.
	*/
	void Delete(T item);

	/**
	*	@brief	����Ʈ���� id�� ��ġ�ϴ� �������� ������
	*	@pre	item���� �Է¹��� item�� operator== �� �����ε� �Ǿ��־�� �Ѵ�.
	*	@post	����Ʈ���� �Է¹��� item���� private key(id)�� �̿��� ������ �������� ã�� �ش� node�� �����Ѵ�.
	*/
	void Replace(T item);

	/**
	*	@brief	�Է¹��� item�� ���� private key(id)�� �̿��� ���̵� ã��
	*	@pre	item���� �Է¹��� item�� operator== �� �����ε� �Ǿ��־�� �Ѵ�.
	*	@post	�Է¹��� item�� private key(id)�� ��ġ�ϴ� �������� ã�´�.
	*	@return	ã���� 1,��ã���� 0�� ��ȯ
	*/
	int Get(T &item);


	/**
	*	@brief	����Ʈ���� id�� ��ġ�ϴ� �������� ������
	*	@pre	item���� �Է¹��� item�� operator== �� �����ε� �Ǿ��־�� �Ѵ�.
	*	@post	����Ʈ���� ���ڷ� ���� �ε����� ��ġ�ϴ� ��带 ã�Ƽ� ����(�Ҵ�����)�Ѵ�.
	*/
	void DoublyLinkedList<T>::DeletebyIndex(int index);

	/**
	*	@brief	�������� �˻��ϴ� �Լ�
	*	@return	item�� ã���� item�� ������, ��ã���� NULL�� ��ȯ.
	*/
	T* SearchItem(const T& item);

	/**
	*	@brief	����Ʈ�� ��ī�����ִ� ���������
	*	@post	�Է¹��� ����Ʈ�� ��ī���Ѵ�.
	*	@return	this�����Ͱ� ��ȯ�ȴ�.
	*/
	DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& list);

private:
	///����Ʈ�� ó���� ����Ŵ
	DoublyNodeType<T> *m_pFirst;
	///����Ʈ�� �������� ����Ŵ
	DoublyNodeType<T> *m_pLast;
	///����Ʈ�� ����ִ� ����� ��
	int m_nLength;
};


//�⺻������
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList()
{
	m_nLength = 0;
	m_pFirst = NULL;
	m_pLast = NULL;
	return;
}

//���������
template<class T>
inline DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& list)
{
	m_nLength = 0;
	m_pFirst = nullptr;
	DoublyIterator<T> itor(list);
	for (; itor.NotNull(); ++itor)
	{
		Add(*itor);
	}
	return;
}

//�⺻ �Ҹ���
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	MakeEmpty();	//����Ʈ�� �ʱ�ȭ����(�Ҵ�����)
	return;
}

//�� item�� ������ �� �ִ��� ��ȯ�� �ִ� �Լ�
template<class T>
inline bool DoublyLinkedList<T>::IsFull()
{
	DoublyNodeType<T> *location;	//�ӽ� node��ü
	try		//���� �ڵ鸵�� �Ѵ�.
	{
		location = new DoublyNodeType<T>;	//�ӽ� node��ü�� Node�� �����Ҵ�
		delete location;	//�����Ҵ��� Node ����
		return false;	//������ ��ȯ (���� ���� �ʾҴ�)
	}
	castch(bad_alloc exception)	//allocation ���� exception�� ���
	{
		return true;	//���� ��ȯ (���� á��)
	}
}

//����Ʈ�� �ʱ�ȭ����
template<class T>
void DoublyLinkedList<T>::MakeEmpty()
{
	DoublyNodeType<T> *pItem;		//Node�ּҸ� ������ �ӽ�������
	DoublyIterator<T> itor(*this);	//�ݺ��ڼ���

	while (itor.NotNull())	//�ݺ��ڰ� �������� �Ѿ������ �ݺ�
	{
		pItem = itor.m_pCurPointer;	//�ӽú����� �ݺ����� ���� �����͸� ����
		itor.Next();	//�ݺ��ڸ� ��������
		delete pItem;	//�ӽ� �����ͷ� ������ ����
	}

	m_pFirst = m_pLast = NULL;	//ó��,���� NULL��
	m_nLength = 0;	//������ 0����
	return;
}

//node�� ������ ��ȯ�� �ִ� �Լ�
template<class T>
int DoublyLinkedList<T>::GetLength() const
{
	return m_nLength;	//node�� ������ ��ȯ
}

//node�� �߰��ϴ� �Լ�
template<class T>
void DoublyLinkedList<T>::Add(T item)
{
	DoublyNodeType<T> *newNode = new DoublyNodeType<T>;	//������ node�� �����Ҵ�
	newNode->data = item;	//������ Node�� �Է¹��� �������� �Ҵ�
	newNode->next = NULL;

	if (m_pFirst == NULL) // ���� ������
	{
		m_pFirst = m_pLast = newNode;
		m_nLength++;
		return;
	}

	newNode->prev = m_pLast;
	m_pLast->next = newNode;
	m_pLast = newNode;
	
	m_nLength++;	//���� ����
	return;
}


//�Է¹��� �ε����� ������ �����ϴ� �Լ�
template<class T>
void DoublyLinkedList<T>::DeletebyIndex(int index)
{
	if (index > m_nLength)
		return;

	DoublyIterator<T> iter(*this);	//�ݺ��� ����
	for (int i = 0; i < index; i++)	// �ε������� �ݺ�
		iter.Next();	//���� ����

	if (iter.m_pCurPointer == m_pFirst)	//���� �����Ϸ��°� ó���̸�
		m_pFirst = iter.m_pCurPointer->next;	//ó���� �����ɷ� ����
	if (iter.m_pCurPointer == m_pLast)	//���� �����Ϸ��°� �������̸�
		m_pLast = iter.m_pCurPointer->prev;		//�������� �����ɷ� ����

	if (iter.m_pCurPointer->prev != NULL)	//�տ� ��尡 �ִٸ�
		iter.m_pCurPointer->prev->next = iter.m_pCurPointer->next;	//�ճ���� next�� �������� next�� ����
	if (iter.m_pCurPointer->next != NULL)	//���� �ڿ� �ִ� ��尡 �ƴ϶��
		iter.m_pCurPointer->next->prev = iter.m_pCurPointer->prev;	//�޳���� prev�� �������� prev�� ����

	delete iter.m_pCurPointer;	//���� ��� ����

	m_nLength--;	//���� ����
}

//�Է¹��� item�� �����ϴ� �Լ�.
template<class T>
void DoublyLinkedList<T>::Delete(T item)
{
	DoublyIterator<T> iter(*this);	//�ݺ��� ����
	while (iter.NotNull())	//Null�� �ƴϸ� �ݺ�
	{
		if (iter.GetCurrentNode().data == item)	//���� ��� �����Ͷ� item�̶� ���ٸ�
		{
			if (iter.m_pCurPointer == m_pFirst)	//���� �����Ϸ��°� ó���̸�
				m_pFirst = iter.m_pCurPointer->next;	//ó���� �����ɷ� ����
			if (iter.m_pCurPointer == m_pLast)	//���� �����Ϸ��°� �������̸�
				m_pLast = iter.m_pCurPointer->prev;		//�������� �����ɷ� ����

			if (iter.m_pCurPointer->prev != NULL)	//�տ� ��尡 �ִٸ�
				iter.m_pCurPointer->prev->next = iter.m_pCurPointer->next;	//�ճ���� next�� �������� next�� ����
			if (iter.m_pCurPointer->next != NULL)	//���� �ڿ� �ִ� ��尡 �ƴ϶��
				iter.m_pCurPointer->next->prev = iter.m_pCurPointer->prev;	//�޳���� prev�� �������� prev�� ����

			delete iter.m_pCurPointer;	//���� ��� ����
			m_nLength--;	//���� ����
			return;
		}
		iter.Next();	//���� ����
	}
	return;
}

//private key(id)�� ��ġ�ϴ� node�� ã�Ƽ� ������
template<class T>
void DoublyLinkedList<T>::Replace(T item)
{
	if (Get(item))	//�ش� (id�� ����) �������� ����Ʈ�� �����Ѵٸ�
	{
		Delete(item);	//id�� ��ġ�ϴ� �������� �����ϰ�
		Add(item);	//���� �Է¹��� �������� �߰���
	}
	return;
}

//private key(id)�� ��ġ�ϴ� node�� �ִ��� Ȯ���ϴ� �Լ�.
template<class T>
int DoublyLinkedList<T>::Get(T & item)
{
	DoublyIterator<T> iter(*this);	//�ݺ��� ����
	while (iter.NotNull())	//Null�� �ɶ����� �ݺ�
	{
		if (iter.GetCurrentNode().data == item)	//����node�� �������� item�� private key�� ��ġ�ϸ�
			return 1;	//���� ��ȯ
		iter.Next();	//�ݺ��ڸ� �������� �Ѱ� ��� �ݺ�
	}
	return 0;	//��ã�� ������ ��ȯ
}
//�������� �˻��ϴ� �Լ�
template<class T>
inline T * DoublyLinkedList<T>::SearchItem(const T & item)
{
	DoublyNodeType<T>* currentNode = m_pFirst;	//�����带 ó������ ����
	while (currentNode != NULL)	//����Ʈ������ �ݺ�
	{
		if (currentNode->data == item)	//�Է¹��������۰� ���ٸ�
			return &currentNode->data;	//���� ������ �����͸� ��ȯ
		currentNode = currentNode->next;
	}
	return NULL;
}
//���Կ����� �����ε�
template<class T>
inline DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& list)
{
	m_nLength = 0;
	m_pFirst = nullptr;
	DoublyIterator<T> itor(list);
	for (; itor.NotNull(); ++itor)
	{
		Add(*itor);
	}
	return *this;
}

//���������
template<class T>
inline DoublyNodeType<T>::DoublyNodeType(const DoublyNodeType<T>& node)
{
	data = node.data;	//�����͸� �����س���
	DoublyNodeType<T>* currentNode1;
	DoublyNodeType<T>* currentNode2;

	if (node.next == NULL)	//��(������)����̸�
	{
		next = NULL;	//�ؽ�Ʈ�� NULL
		prev = NULL;
	}
	else
	{
		currentNode2 = new DoublyNodeType<T>;	//�� ��带����
		next = currentNode2;	//next�� ���θ��� ���� ���Ը���
		currentNode2->data = node.next->data;	//���θ��� ����� �����͸� �Է¹��� ����� ���� �����ͷ� ����
		currentNode2->prev = this;
		currentNode1 = node.next->next;	//�ٸ� ��忡 �ٴ��� ���� ����

		while (currentNode1 != NULL)	//�ٴ�����尡 �������϶����� �ݺ�
		{
			currentNode2->next = new DoublyNodeType<T>;	//����带 ����
			currentNode2->next->prev = currentNode2;
			currentNode2 = currentNode2->next;	//���� ���� �̵��Ѵ�
			currentNode2->data = currentNode1->data;	//�̵��� ����� �����͸� �����Ѵ�
			currentNode1 = currentNode1->next;	//�ٴ�����嵵 �̵��Ѵ�.
		}
		currentNode2->next = NULL;	//���� ��带 NULL�� �����Ѵ�.
	}

}

//���Կ����� �����ε�
template<class T>
inline DoublyNodeType<T>& DoublyNodeType<T>::operator=(const DoublyNodeType<T>& node)
{
	data = node.data;	//�����͸� �����س���
	DoublyNodeType<T>* currentNode1;
	DoublyNodeType<T>* currentNode2;

	if (node.next == NULL)	//��(������)����̸�
	{
		next = NULL;	//�ؽ�Ʈ�� NULL
		prev = NULL;
	}
	else
	{
		currentNode2 = new DoublyNodeType<T>;	//�� ��带����
		next = currentNode2;	//next�� ���θ��� ���� ���Ը���
		currentNode2->data = node.next->data;	//���θ��� ����� �����͸� �Է¹��� ����� ���� �����ͷ� ����
		currentNode2->prev = this;
		currentNode1 = node.next->next;	//�ٸ� ��忡 �ٴ��� ���� ����

		while (currentNode1 != NULL)	//�ٴ�����尡 �������϶����� �ݺ�
		{
			currentNode2->next = new DoublyNodeType<T>;	//����带 ����
			currentNode2->next->prev = currentNode2;
			currentNode2 = currentNode2->next;	//���� ���� �̵��Ѵ�
			currentNode2->data = currentNode1->data;	//�̵��� ����� �����͸� �����Ѵ�
			currentNode1 = currentNode1->next;	//�ٴ�����嵵 �̵��Ѵ�.
		}
		currentNode2->next = NULL;	//���� ��带 NULL�� �����Ѵ�.
	}
	return *this;
}
