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
	*	깊은복사생성자
	*/
	SortedLinkedList(const SortedLinkedList<T>& List); // 깊은 복사생성자
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
	*	@brief	아이템을 넣는다.
	*	@pre	없음
	*	@post	아이템을 정렬하여 넣는다.
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
	*	@pre	없음
	*	@post	해당 찾아서아이템을 지운다.
	*	@return	1 if this function works well, otherwise 0.
	*/
	int Delete(T item);
	/**
	*	@brief	Delete item into this list.
	*	@pre	없음
	*	@post	해당 찾아서 아이템 값을 바꿔준다.
	*	@return	1 if this function works well, otherwise 0.
	*/
	int Replace(T item);
	NodeType<T>* Getitem(T item);
	/**
	*	m_pList 리턴
	*/
	NodeType<T>* First(); // 헤드리턴
						  /**
						  *	=오버로딩
						  */
	void operator=(const SortedLinkedList<T>& sll); // =오버로딩
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
SortedLinkedList<T>::SortedLinkedList(const SortedLinkedList<T>& List) // 깊은 복사생성자 링크드리스트 복사생성자와 동일
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
	//리스트내의 모든 node 제거
	MakeEmpty();
}
// Initialize list to empty state.
template <typename T>
void SortedLinkedList<T>::MakeEmpty()
// Post: List is empty; all items have been deallocated.
{
	// 리스트내의 모든 노드 제거 하고 리스트의 length를 초기화
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
	// 리스트 초기화
	ResetList();
	// 리스트에 추가할 새로운 node 객체와 이전 노드를 가리킬 포인터 선언
	NodeType<T> *node = new NodeType<T>;
	NodeType<T> *pre = nullptr;
	bool bFound = false;
	// node 객체에 입력받은 데이터 설정 및 초기화
	node->data = item;
	node->next = NULL;
	int cnt = 0; // 첫번째 비교일 경우를 위한 변수
				 // list 에 node 가 존재하지 않는 경우
	if (!m_nLength1)
	{
		m_pList = node;
	}
	// list 에 node 가 하나 이상 존재하는 경우
	else
	{
		this->m_pCurPointer = m_pList; //컬포인터를 처음으로 보내줌
		while (1)
		{
			if (cnt == 0) // 첫번째 비교일 경우
			{
				if (m_pCurPointer->data>node->data) //컬포인터의 데이터보다 노드의 데이터가 작다면
				{
					node->next = this->m_pCurPointer;//노드의 넥스트를 컬포인터로 바꿔주고
					m_pList = node;// 처음 피리스트를 노드로 함.
					break;
				}
				else
				{
					if (this->m_pCurPointer->next == NULL) // 만약 데이터가 한개라면
					{
						this->m_pCurPointer->next = node; // 컬포인터의 넥스트를 노드에 연결시킴
						break;
					}
					else // 둘다아닐경우
					{
						pre = this->m_pCurPointer;//이전에 컬포인터저장
						this->m_pCurPointer = this->m_pCurPointer->next; // 컬포인터 한칸뒤로옮김
						cnt++;// 카운트증가
					}
				}
				if (m_pCurPointer->data == node->data)
					return 0;
			}
			else // 첫번째비교가 아닐경우
			{
				if (m_pCurPointer->data>node->data)//컬포인터의 데이터보다 노드의 데이터가 작다면
				{
					node->next = this->m_pCurPointer;//노드의 넥스트를 컬포인터로 바꿔주고
					pre->next = node;//이전의 넥스트를 노드로 연결
					break;
				}
				else
				{
					if (this->m_pCurPointer->next == NULL) // 맨마지막이면
					{
						this->m_pCurPointer->next = node; // 마지막뒤 연결
						break;
					}
					pre = this->m_pCurPointer; // 이전에 컬포인트저장
					this->m_pCurPointer = this->m_pCurPointer->next; // 컬포인트 한칸 옮김
					cnt++; // 안해도 되지만 써줌 카운트증가
				}
				if (m_pCurPointer->data == node->data)
					return 0;
			}
		}
	}
	m_nLength1++; // 길이증가
	return 1;
}
// Retrieve list element whose key matches item's key (if present).
template <typename T>
int SortedLinkedList<T>::Get(T& item)
{
	bool moreToSearch, found;
	ResetList(); // 컬포인트 초기화
	this->m_pCurPointer = m_pList; // 컬포인트 초기화(처음으로)
	found = false;
	moreToSearch = (this->m_pCurPointer != NULL); // 컬포인트가 눌이 아닐경우 참
	while (moreToSearch && !found)
	{
		if (item == this->m_pCurPointer->data) // 아이템의 데이터와 컬포인트 데이터가 같으면
		{
			item = this->m_pCurPointer->data;
			found = true; // 찾음
		}
		else // 아닐경우
		{
			this->m_pCurPointer = this->m_pCurPointer->next; // 컬포인트 한칸 옮김
			moreToSearch = (this->m_pCurPointer != NULL); // 더이상 찾을지 말지 확인
			if (moreToSearch && item<this->m_pCurPointer->data) // 여기서 더이상찾을지 말지를 넣어서 만약 컬포인트가 눌값이여도 애러가 안뜸
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
	// current pointer 초기화
	m_pCurPointer = NULL;
}
// Gets the next element in list.
template <typename T>
void SortedLinkedList<T>::GetNextItem(T& item)
{
	// current pointer 이 NULL이라면 처음 node를 가리킴.
	if (m_pCurPointer == NULL)
	{
		m_pCurPointer = m_pList;
	}
	//current position 을 다음 노드로 이동
	else
	{
		m_pCurPointer = m_pCurPointer->next;
	}
	//item 에 current position 의 info 를 삽입
	item = m_pCurPointer->data;
}
template <typename T>
int SortedLinkedList<T>::Delete(T item)
{
	if (this->Get(item)) // 같은 아이디을 찾는다면
	{
		NodeType<T> *temp = this->m_pCurPointer; // 템프에 같은 아이디 값을 가지고 있는 곳 저장
		if (this->m_nLength1 == 1) // 1개밖에 데이터가 없다면
		{
			this->m_pList = NULL; // 초기화해주고
			this->ResetList(); // 리셋시켜주고
			this->m_nLength1--; // 길이줄이고
			delete temp; // 템프 동적할당 딜리트
			return 1;
		}
		else // 아니라면
		{
			this->ResetList();
			this->m_pCurPointer = this->m_pList; // 컬포인트 처음으로 맞춰주고
			if (temp == this->m_pList) // 만약 첫번째라면
			{
				m_pList = m_pList->next; // 처음을 빼줌
				this->m_nLength1--; // 길이줄이고
				delete temp; // 동적할당제거
				return 1;
			}
			else // 첫번째아니라면
			{
				while (1)// 템프이전으로 컬포인터를 보내줘서 해당 데이터 삭제
				{
					if (this->m_pCurPointer->next == temp)  // 컬포인터의 다음이 템프(제거할데이터)라면 
					{
						if (temp->next == NULL)// 템프가 마지막노드였다면
						{
							this->m_pCurPointer->next = NULL; // 컬포인터의 넥스트를 눌값으로 바꿔주고
							this->m_nLength1--; // 길이줄이고
							delete temp; //동적할당 제거
							return 1;
						}
						else
						{
							this->m_pCurPointer->next = temp->next; //컬포인터의 넥스트를 템프의 넥스트로 바꿔줌
							this->m_nLength1--;// 길이줄이고
							delete temp; // 동적할당 제거
							return 1;
						}
					}
					this->m_pCurPointer = this->m_pCurPointer->next;// 아니라면 컬포인터 한칸 옮겨줌
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
	if (this->Get(temp)) // 아이디가 겹치면
	{
		this->m_pCurPointer->data = item; // 해당아이디에 데이터를 넣어줌
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
void SortedLinkedList<T>::operator=(const SortedLinkedList<T>& sll) // 복사생성자와 동일
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