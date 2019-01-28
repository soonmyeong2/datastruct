#include <iostream>
using namespace std;

#define MAX_HASH 100000 // 해시 테이블 크기 설정 

template <typename T>
struct Node
{
	T data;
	Node* hash_Next;
};

template <typename T>
class HASH
{
public:
	HASH();
	~HASH();

	// 현재 해시 테이블에서 NULL이 아닌 모든 값을 출력
	void PrintAllHashData();

	// 해시테이블의 key 인덱스에 item 삽입
	void AddHashData(int key, T item);

	// 해시테이블의 key 인덱스에 item을 삭제
	void DeleteHashData(int key, T item);

	// 해시테이블의 kye 인덱스에 item을 찾으면 노드 반환 못찾으면 NULL
	Node<T>* FindHashData(int key, T item);

	// 해시테이블의 key 인덱스 접근하여 노드 반환 못찾으면 NULL
	Node<T>* operator[](int kye);

private:
	Node<T>* hashTable[MAX_HASH]; // 해시테이블
};


template <typename T>
HASH<T>::HASH()
{
}

template <typename T>
HASH<T>::~HASH()
{
	//delete[] *hashTable;  // 메모리 해제
}

template <typename T>
void HASH<T>::AddHashData(int key, T item)
{
	Node<T> *node = new Node<T>;	//새로운 노드 생성
	node->data = item;
	node->hash_Next = NULL;

	if (hashTable[key] == NULL) // 만약 해시 키 값이 NULL이라면
		hashTable[key] = node; // 첫 노드로 set
	else // 이미 존재하면
	{	
		node->hash_Next = hashTable[key]; // node를 해시 테이블의 첫번째 원소로 셋하고
		hashTable[key] = node; // 테이블의 포인터를 파라미터 노드로 변경 
	}
}

template <typename T>
void HASH<T>::DeleteHashData(int key, T item)
{
	if (hashTable[key] == NULL) // 찾는게 존재하지 않을 경우
		return;
		
	Node<T>* delNode = NULL;

	if (hashTable[key]->data == item) // 해시테이블에 값이 바로 찾는 값과 같다면
	{
		delNode = hashTable[key];     // delnode를 셋하고
		hashTable[key] = hashTable[key]->hash_Next; // 앞 뒤를 삭제 노드를 넘겨 연결한다
	}
	else //  해시테이블 위에 없다면
	{
		Node<T>* node = hashTable[key]; 
		Node<T>* next = node->hash_Next;
		while (next) // 링크드리스트를 탐색하면서 delete
		{
			if (next->data == item)
			{
				node->hash_Next = next->hash_Next;
				delNode = next;
				break;
			}
			node = next;
			next = node->hash_Next;
		}
	}
	delete delNode;
}

template <typename T>
Node<T>* HASH<T>::FindHashData(int key, T item)
{
	if (hashTable[key] == NULL) // 찾으려는 값이 없다면
		return NULL;

	if (hashTable[key]->data == item) // 찾으려는 값이 해시테이블 위에 있다면
		return hashTable[key]; 
	else // 링크드리스트와 연결되어 있으면
	{ 
		Node<T>* node = hashTable[key];  
		while (node->hash_Next)  // 다음 해시값을 탐색
		{
			if (node->hash_Next->data == item)  // 같다면
			{
				return node->hash_Next; // 노드 리턴
			}
			node = node->hash_Next;
		}
	}
	return NULL; // 없을 경우
}

template <typename T>
void HASH<T>::PrintAllHashData()
{
	cout << "###Print All Hash Data###" << endl;
	for (int i = 0; i < MAX_HASH; i++)
	{
		if (hashTable[i] != NULL)  // 해시 테이블에 널값이 아니면 출력
		{
			cout << "idx:" << i << endl;

			Node<T>* node = hashTable[i];

			while (node->hash_Next != NULL)
			{
				cout << node->data << " ";
				node = node->hash_Next;
			}
			cout << node->data << endl;
		}
	}
	cout << endl << endl;;
}

template <typename T>
Node<T>* HASH<T>::operator[](int kye)
{
	if (hashTable[kye] == NULL) // 찾으려는 값이 없다면
		return NULL;
	else // 찾으려는 값이 해시테이블 위에 있다면
		return hashTable[kye];
}