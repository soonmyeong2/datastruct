#include <iostream>
using namespace std;

#define MAX_HASH 100000 // �ؽ� ���̺� ũ�� ���� 

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

	// ���� �ؽ� ���̺��� NULL�� �ƴ� ��� ���� ���
	void PrintAllHashData();

	// �ؽ����̺��� key �ε����� item ����
	void AddHashData(int key, T item);

	// �ؽ����̺��� key �ε����� item�� ����
	void DeleteHashData(int key, T item);

	// �ؽ����̺��� kye �ε����� item�� ã���� ��� ��ȯ ��ã���� NULL
	Node<T>* FindHashData(int key, T item);

	// �ؽ����̺��� key �ε��� �����Ͽ� ��� ��ȯ ��ã���� NULL
	Node<T>* operator[](int kye);

private:
	Node<T>* hashTable[MAX_HASH]; // �ؽ����̺�
};


template <typename T>
HASH<T>::HASH()
{
}

template <typename T>
HASH<T>::~HASH()
{
	//delete[] *hashTable;  // �޸� ����
}

template <typename T>
void HASH<T>::AddHashData(int key, T item)
{
	Node<T> *node = new Node<T>;	//���ο� ��� ����
	node->data = item;
	node->hash_Next = NULL;

	if (hashTable[key] == NULL) // ���� �ؽ� Ű ���� NULL�̶��
		hashTable[key] = node; // ù ���� set
	else // �̹� �����ϸ�
	{	
		node->hash_Next = hashTable[key]; // node�� �ؽ� ���̺��� ù��° ���ҷ� ���ϰ�
		hashTable[key] = node; // ���̺��� �����͸� �Ķ���� ���� ���� 
	}
}

template <typename T>
void HASH<T>::DeleteHashData(int key, T item)
{
	if (hashTable[key] == NULL) // ã�°� �������� ���� ���
		return;
		
	Node<T>* delNode = NULL;

	if (hashTable[key]->data == item) // �ؽ����̺� ���� �ٷ� ã�� ���� ���ٸ�
	{
		delNode = hashTable[key];     // delnode�� ���ϰ�
		hashTable[key] = hashTable[key]->hash_Next; // �� �ڸ� ���� ��带 �Ѱ� �����Ѵ�
	}
	else //  �ؽ����̺� ���� ���ٸ�
	{
		Node<T>* node = hashTable[key]; 
		Node<T>* next = node->hash_Next;
		while (next) // ��ũ�帮��Ʈ�� Ž���ϸ鼭 delete
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
	if (hashTable[key] == NULL) // ã������ ���� ���ٸ�
		return NULL;

	if (hashTable[key]->data == item) // ã������ ���� �ؽ����̺� ���� �ִٸ�
		return hashTable[key]; 
	else // ��ũ�帮��Ʈ�� ����Ǿ� ������
	{ 
		Node<T>* node = hashTable[key];  
		while (node->hash_Next)  // ���� �ؽð��� Ž��
		{
			if (node->hash_Next->data == item)  // ���ٸ�
			{
				return node->hash_Next; // ��� ����
			}
			node = node->hash_Next;
		}
	}
	return NULL; // ���� ���
}

template <typename T>
void HASH<T>::PrintAllHashData()
{
	cout << "###Print All Hash Data###" << endl;
	for (int i = 0; i < MAX_HASH; i++)
	{
		if (hashTable[i] != NULL)  // �ؽ� ���̺� �ΰ��� �ƴϸ� ���
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
	if (hashTable[kye] == NULL) // ã������ ���� ���ٸ�
		return NULL;
	else // ã������ ���� �ؽ����̺� ���� �ִٸ�
		return hashTable[kye];
}