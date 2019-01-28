#pragma once
#include <iostream>
#include <fstream>
using namespace std;

#include "RedBlackTree.h"
#include "Member.h"
#include "Message.h"
#include "HASH.h"
#include "ChattingRoom.h"
#include "SortedLinkedList.h"
#include "Client.h"

class Client; // ������� ���� ���� ����� Ŭ���� ����

#define pause system("pause")
#define cls system("cls")

class App
{
private:

	/**
	*	@brief	�⺻ ������. load_File()�Լ��� .txt ������ �о�´�.
	*	@details private�� ���� �Ұ��ϰ� ���� �� 1���� ��ü�� �����ϰ� �Ѵ�.
	*/
	App() { load_File(); }

public:


	/**
	*	@brief	�⺻ �Ҹ���.
	*/
	~App() {}

	/**
	*	@brief	AppŬ������ ������ �����ϴ� �Լ�
	*	@pre	None.
	*	@post	����ڿ��� Ű���� �Է¹޾� �� �ش��ϴ� �Լ��� ��������ش�.
	*/
	void Run();

	/**
	*	@brief	����ڿ��� Ű ���� �Է¹޾� Ű ���� �����Ѵ�.
	*	@pre	None.
	*	@post	����ڿ��� �Լ� ����� ���÷��� ���� �� �ʿ��� ����� Ű ���� �Է¹޴´�.
	*	@return	����� �Է°��� ��ȯ�Ѵ�.
	*/
	int GetCommand();
	
	/**
	*	@brief	����ڿ��� ID, PW�� �Է¹޾� ��ġ�ϴ� ������ ������ Ŭ���̾�Ʈ Ŭ���� �����Ҵ��Ͽ� ����
	*	@pre	None.
	*	@post	��������Ʈ�� ����� �־�� �Ѵ�.
	*	@return	�α��� ������ 1. else false
	*/
	bool Login();

	// ����ڿ��� Ű ���� �Է¹޾� ��������Ʈ�� �߰��Ѵ� (= ȸ������)
	void Join();

	// Ŭ���̾�Ʈ���� ��û�� ȸ��Ż������ ��������ش�. ��������Ʈ���� ���ŵǸ� �����Ҵ� �� Ŭ���̾�Ʈ�� �޸����� �ȴ�.
	void secession(Member* deleteMember);

	// Ŭ���̾�Ʈ���� ��û�� ȸ�� �����û ���� ������
	void changeInfo(Member* Member);

	// Ŭ���̾�Ʈ���� ��û�� ģ�� ���� �޴��� ���� ������
	void addFriendMenu(Member* mb);

	// Ŭ���̾�Ʈ���� ��û�� ģ�� �߰� ��û�� ���� ������
	bool addFriend(Member* mb);

	// �̸����� ��������Ʈ���� ��ġ�ϴ� ȸ���� ����Ѵ�.
	void findSearchbyName(RedBlackNode<Member>* node, string name);

	// .txt ������ �о��
	void load_File();

	// Ŭ���̾�Ʈ���� �޼��� ����, ���� �ߴ� ��� �α׸� ���÷��� ����
	void printServerLog();

	// Ŭ���̾�Ʈ���� ��û�� ģ�� ���ã�� �޴��� ���� ������ 
	void setFavorites(Member *mb);

	// sendmessage.txt�� �о� �ش� ��ġ�ϴ� ä�ù濡 ���� ��
	void sentToMessage();

	// delete.txt�� �о� �ش� ��ġ�ϴ� ä�ù濡�� �޼����� ���� ����
	void deleteMessage();

	// Ŭ���̾�Ʈ�� ��õ ģ������� ���÷��� ����
	void recommandMember(Member* mb);

	// Ŭ���̾�Ʈ�� ģ�� ���� ��û�޴��� ���� ������
	void blockFriend(Member* mb);

	// Ŭ���̾�Ʈ���� ģ�� ���� ��û�� ���� ������
	void deleteFriend(Member* mb);

	// Ŭ���̾�Ʈ���� ä�ù��� ���� ��û�ϸ� ä�� ���� ��� ���� ������
	void createChatRoom(Member* mb, Client* cn);

	// ���� ������ ä�ù� ����� ���÷��� ����(== Ŭ���̾�Ʈ�� ä�� �� ����)
	void DisplayChatroom(Member* mb, Client* cur);

	// �ؽ� ���̺��� �ؽ� ���
	int hash_function(string temp);

	// �����ϰ� �����ϴ� ���� ��ȯ �� �� �ִ� �Լ�
	static App* getServer(); 

private:
	int m_Command; // ���� ���ÿ� ����

	RedBlackTree<Member> userList; // ���� ���
	HASH<ChattingRoom> chattingList; // ä�ù� ��� 
	SortedLinkedList<Member> recommendationList; // ��õģ�� ���
	
	static App* server; // ������ ���� �ν��Ͻ�
};