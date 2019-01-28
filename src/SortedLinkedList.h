#pragma once
template <typename T>
struct NodeType
{
	T data;	///< A data for each node.
	NodeType* next;	///< A node pointer to point succeed node.
};
/**
*	Simple sorted list class for managing items.
*/
template <typename T>
class SortedLinkedList
{
public:
	/**
	*	default constructor.
	*/
	SortedLinkedList();
	/**
	*	�������������
	*/
	SortedLinkedList(const SortedLinkedList<T>& List); // ���� ���������
													   /**
													   *	destructor.
													   */
	~SortedLinkedList();
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
	*	@brief	�������� �ִ´�.
	*	@pre	����
	*	@post	�������� �����Ͽ� �ִ´�.
	*	@return	1 if this function works well, otherwise 0.
	*/
	int Add(T item);
	/**
	*	@brief	Retrieve list element whose key matches item's key (if present).
	*	@pre	Key member of item is initialized.
	*	@post	If there is an element whose key matches with item's key then the element's record is copied to the item.
	*	@return	1 if any element's primary key matches with item's, otherwise 0.
	*/
	int Get(T& item);
	/**
	*	@brief	Initialize current pointer for an iteration through the list.
	*	@pre	None.
	*	@post	current pointer is prior to list. current pointer has been initialized.
	*/
	void ResetList();
	/**
	*	@brief	Get the next element in list.
	*	@pre	current pointer is defined. Element at current pointer is not last in list.
	*	@post	current pointer is updated to next position. item is a copy of element at current pointer.
	*/
	void GetNextItem(T& item);
	/**
	*	@brief	Delete item into this list.
	*	@pre	����
	*	@post	�ش� ã�Ƽ��������� �����.
	*	@return	1 if this function works well, otherwise 0.
	*/
	int Delete(T item);
	/**
	*	@brief	Delete item into this list.
	*	@pre	����
	*	@post	�ش� ã�Ƽ� ������ ���� �ٲ��ش�.
	*	@return	1 if this function works well, otherwise 0.
	*/
	int Replace(T item);
	NodeType<T>* Getitem(T item);
	/**
	*	m_pList ����
	*/
	NodeType<T>* First(); // ��帮��
						  /**
						  *	=�����ε�
						  */
	void operator=(const SortedLinkedList<T>& sll); // =�����ε�
private:
	NodeType<T>* m_pList;	///< Pointer for pointing a first node.
	NodeType<T>* m_pCurPointer;	///< Node pointer for pointing current node to use iteration.
	int m_nLength1;	///< Number of node in the list.
};
// Class constructor
template <typename T>
SortedLinkedList<T>::SortedLinkedList()
{
	m_nLength1 = 0;
	m_pList = NULL;
	m_pCurPointer = NULL;
}
template <typename T>
SortedLinkedList<T>::SortedLinkedList(const SortedLinkedList<T>& List) // ���� ��������� ��ũ�帮��Ʈ ��������ڿ� ����
{
	NodeType<T>* copy;
	if (List.m_pList == NULL)
	{
		this->m_pList = NULL;
		this->m_nLength1 = List.m_nLength1;
	}
	else
	{
		copy = new NodeType<T>;
		NodeType<T>* temp;
		temp = List.m_pList;
		this->m_pList = copy;
		copy->data = temp->data;
		temp = temp->next;
		while (temp != NULL)
		{
			copy->next = new NodeType<T>;
			copy = copy->next;
			copy->next = NULL;
			copy->data = temp->data;
			temp = temp->next;
		}
		copy->next = NULL;
		this->m_nLength1 = List.m_nLength1;
	}
}
// Class destructor
template <typename T>
SortedLinkedList<T>::~SortedLinkedList()
{
	//����Ʈ���� ��� node ����
	MakeEmpty();
}
// Initialize list to empty state.
template <typename T>
void SortedLinkedList<T>::MakeEmpty()
// Post: List is empty; all items have been deallocated.
{
	// ����Ʈ���� ��� ��� ���� �ϰ� ����Ʈ�� length�� �ʱ�ȭ
	NodeType<T>* tempPtr;
	while (m_pList != NULL)
	{
		tempPtr = m_pList;
		m_pList = m_pList->next;
		delete tempPtr;
	}
	m_nLength1 = 0;
}
// Get number of elements in the list.
template <typename T>
int SortedLinkedList<T>::GetLength() const
{
	return m_nLength1;
}
// Add item into this list.
template <typename T>
int SortedLinkedList<T>::Add(T item)
{
	// ����Ʈ �ʱ�ȭ
	ResetList();
	// ����Ʈ�� �߰��� ���ο� node ��ü�� ���� ��带 ����ų ������ ����
	NodeType<T> *node = new NodeType<T>;
	NodeType<T> *pre = nullptr;
	bool bFound = false;
	// node ��ü�� �Է¹��� ������ ���� �� �ʱ�ȭ
	node->data = item;
	node->next = NULL;
	int cnt = 0; // ù��° ���� ��츦 ���� ����
				 // list �� node �� �������� �ʴ� ���
	if (!m_nLength1)
	{
		m_pList = node;
	}
	// list �� node �� �ϳ� �̻� �����ϴ� ���
	else
	{
		this->m_pCurPointer = m_pList; //�������͸� ó������ ������
		while (1)
		{
			if (cnt == 0) // ù��° ���� ���
			{
				if (m_pCurPointer->data>node->data) //���������� �����ͺ��� ����� �����Ͱ� �۴ٸ�
				{
					node->next = this->m_pCurPointer;//����� �ؽ�Ʈ�� �������ͷ� �ٲ��ְ�
					m_pList = node;// ó�� �Ǹ���Ʈ�� ���� ��.
					break;
				}
				else
				{
					if (this->m_pCurPointer->next == NULL) // ���� �����Ͱ� �Ѱ����
					{
						this->m_pCurPointer->next = node; // ���������� �ؽ�Ʈ�� ��忡 �����Ŵ
						break;
					}
					else // �ѴپƴҰ��
					{
						pre = this->m_pCurPointer;//������ ������������
						this->m_pCurPointer = this->m_pCurPointer->next; // �������� ��ĭ�ڷοű�
						cnt++;// ī��Ʈ����
					}
				}
				if (m_pCurPointer->data == node->data)
					return 0;
			}
			else // ù��°�񱳰� �ƴҰ��
			{
				if (m_pCurPointer->data>node->data)//���������� �����ͺ��� ����� �����Ͱ� �۴ٸ�
				{
					node->next = this->m_pCurPointer;//����� �ؽ�Ʈ�� �������ͷ� �ٲ��ְ�
					pre->next = node;//������ �ؽ�Ʈ�� ���� ����
					break;
				}
				else
				{
					if (this->m_pCurPointer->next == NULL) // �Ǹ������̸�
					{
						this->m_pCurPointer->next = node; // �������� ����
						break;
					}
					pre = this->m_pCurPointer; // ������ ������Ʈ����
					this->m_pCurPointer = this->m_pCurPointer->next; // ������Ʈ ��ĭ �ű�
					cnt++; // ���ص� ������ ���� ī��Ʈ����
				}
				if (m_pCurPointer->data == node->data)
					return 0;
			}
		}
	}
	m_nLength1++; // ��������
	return 1;
}
// Retrieve list element whose key matches item's key (if present).
template <typename T>
int SortedLinkedList<T>::Get(T& item)
{
	bool moreToSearch, found;
	ResetList(); // ������Ʈ �ʱ�ȭ
	this->m_pCurPointer = m_pList; // ������Ʈ �ʱ�ȭ(ó������)
	found = false;
	moreToSearch = (this->m_pCurPointer != NULL); // ������Ʈ�� ���� �ƴҰ�� ��
	while (moreToSearch && !found)
	{
		if (item == this->m_pCurPointer->data) // �������� �����Ϳ� ������Ʈ �����Ͱ� ������
		{
			item = this->m_pCurPointer->data;
			found = true; // ã��
		}
		else // �ƴҰ��
		{
			this->m_pCurPointer = this->m_pCurPointer->next; // ������Ʈ ��ĭ �ű�
			moreToSearch = (this->m_pCurPointer != NULL); // ���̻� ã���� ���� Ȯ��
			if (moreToSearch && item<this->m_pCurPointer->data) // ���⼭ ���̻�ã���� ������ �־ ���� ������Ʈ�� �����̿��� �ַ��� �ȶ�
			{
				break;
			}
		}
	}
	if (found)
		return 1;
	else
		return 0;
}
// Initializes current pointer for an iteration through the list.
template <typename T>
void SortedLinkedList<T>::ResetList()
{
	// current pointer �ʱ�ȭ
	m_pCurPointer = NULL;
}
// Gets the next element in list.
template <typename T>
void SortedLinkedList<T>::GetNextItem(T& item)
{
	// current pointer �� NULL�̶�� ó�� node�� ����Ŵ.
	if (m_pCurPointer == NULL)
	{
		m_pCurPointer = m_pList;
	}
	//current position �� ���� ���� �̵�
	else
	{
		m_pCurPointer = m_pCurPointer->next;
	}
	//item �� current position �� info �� ����
	item = m_pCurPointer->data;
}
template <typename T>
int SortedLinkedList<T>::Delete(T item)
{
	if (this->Get(item)) // ���� ���̵��� ã�´ٸ�
	{
		NodeType<T> *temp = this->m_pCurPointer; // ������ ���� ���̵� ���� ������ �ִ� �� ����
		if (this->m_nLength1 == 1) // 1���ۿ� �����Ͱ� ���ٸ�
		{
			this->m_pList = NULL; // �ʱ�ȭ���ְ�
			this->ResetList(); // ���½����ְ�
			this->m_nLength1--; // �������̰�
			delete temp; // ���� �����Ҵ� ����Ʈ
			return 1;
		}
		else // �ƴ϶��
		{
			this->ResetList();
			this->m_pCurPointer = this->m_pList; // ������Ʈ ó������ �����ְ�
			if (temp == this->m_pList) // ���� ù��°���
			{
				m_pList = m_pList->next; // ó���� ����
				this->m_nLength1--; // �������̰�
				delete temp; // �����Ҵ�����
				return 1;
			}
			else // ù��°�ƴ϶��
			{
				while (1)// ������������ �������͸� �����༭ �ش� ������ ����
				{
					if (this->m_pCurPointer->next == temp)  // ���������� ������ ����(�����ҵ�����)��� 
					{
						if (temp->next == NULL)// ������ ��������忴�ٸ�
						{
							this->m_pCurPointer->next = NULL; // ���������� �ؽ�Ʈ�� �������� �ٲ��ְ�
							this->m_nLength1--; // �������̰�
							delete temp; //�����Ҵ� ����
							return 1;
						}
						else
						{
							this->m_pCurPointer->next = temp->next; //���������� �ؽ�Ʈ�� ������ �ؽ�Ʈ�� �ٲ���
							this->m_nLength1--;// �������̰�
							delete temp; // �����Ҵ� ����
							return 1;
						}
					}
					this->m_pCurPointer = this->m_pCurPointer->next;// �ƴ϶�� �������� ��ĭ �Ű���
				}
			}
		}
	}
	else
	{
		return 0;
	}
}
template <typename T>
int SortedLinkedList<T>::Replace(T item)
{
	T temp;
	temp = item;
	if (this->Get(temp)) // ���̵� ��ġ��
	{
		this->m_pCurPointer->data = item; // �ش���̵� �����͸� �־���
		return 1;
	}
	else
	{
		return 0;
	}
}
template <typename T>
NodeType<T>* SortedLinkedList<T>::First()
{
	return this->m_pList;
}
template <typename T>
void SortedLinkedList<T>::operator=(const SortedLinkedList<T>& sll) // ��������ڿ� ����
{
	NodeType<T>* copy;
	if (sll.m_pList == NULL)
	{
		this->m_pList = NULL;
		this->m_nLength1 = sll.m_nLength1;
	}
	else
	{
		copy = new NodeType<T>;
		NodeType<T>* temp;
		temp = sll.m_pList;
		this->m_pList = copy;
		copy->data = temp->data;
		temp = temp->next;
		while (temp != NULL)
		{
			copy->next = new NodeType<T>;
			copy = copy->next;
			copy->next = NULL;
			copy->data = temp->data;
			temp = temp->next;
		}
		copy->next = NULL;
		this->m_nLength1 = sll.m_nLength1;
	}
}
template <typename T>
NodeType<T>* SortedLinkedList<T>::Getitem(T item)
{
	bool moreToSearch, found;
	NodeType<T>* location;
	location = m_pList;
	found = false;
	moreToSearch = (location != NULL);
	while (moreToSearch && !found)
	{
		if (item == location->data)
		{
			found = true;
		}
		else
		{
			location = location->next;
			moreToSearch = (location != NULL);
		}
	}
	if (found)
		return location;
	else
		return NULL;
}