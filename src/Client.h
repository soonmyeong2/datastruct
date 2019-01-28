#pragma once
#include "App.h"
#include "Member.h"
#include "DoublyLinkedList.h"
#include "ChattingRoom.h"
#include <conio.h>
#include <atlstr.h>  
#include <Windows.h>
#include <fstream>
#pragma warning(disable:4996)

#define LIGHTGRAY 7
#define GREEN 2
#define RED 4
#define pause system("pause")
#define cls system("cls")

class Client
{
public:
	// �⺻ ������
	Client() {}

	// �⺻ �Ҹ���
	~Client() {}

	// ä�ù� ����� ���÷����ϰ� ����Ű �ڵ鷯�� �̿��Ͽ� ä�ù濡 ������ ���� ��
	void cursorControl();

	// ��ǥ ����
	void gotoxy(int x, int y);
	
	// Ŀ�� �����
	void hidingCursor();

	// ctrl + c ���ִ� �Լ� str�� �����Ѵ�.
	void CopyStrToClipboard(CString str);

	// Ŭ���̾�Ʈ�� �Ѱ� �޴�. ����� Ű ���� ���� �ش� �Լ� �ߵ�
	void ClientMenu();

	// Ŭ���̾�Ʈ�� �޴� ���÷���
	int ClientCommand();

	// �Ķ���ͷ� �Ѿ�� ���� ä�� ��� �� �÷��� �ϸ� room ä���� ��� ����� �Ѱ��Ѵ�.
	void DisplayChat(ChattingRoom& room);

	// ������ ȸ�� Ż�� ��û�ϴ� �Լ�
	bool secession();
	
	// ������ ȸ�� ���� ��û�ϴ� �Լ�
	void changeInfo();

	// ģ�������� ��� �׸��� ���÷���
	void FriendManagement();

	// ģ�� ��û �� ����� ������ ��û�ϴ� �Լ�
	void addFriend();

	// ģ�� ���ã�� ��û�� ������ ��û�ϴ� �Լ�
	void C_setFavorites();

	// ģ�� ���� ��û�� ������ ��û�ϴ� �Լ�
	void blockFriend();

	// ģ�� ���� ��û�� ������ ��û�ϴ� �Լ�
	void deleteFriend();

	// �� ģ�� ��Ͽ��� ģ���� �˻��� �ϴ� �Լ�
	void findFriend();

	// Ŭ���̾�Ʈ�� �α��� ������ set�ϴ� �Լ�
	void setCurruntUser(Member* c_user) { curruntUser = c_user; }

	// ä�ÿ� ���������� ����ڰ� �Է� �޴� �޴� ���÷���
	void chattingManagement();

	// ���ο� ä�ù� ������ ������ ��û�ϴ� �Լ�
	void createChattingRoom();

	// Ŭ���̾�Ʈ�� �ӽ� ä�� ��Ͽ� ����
	void EntrytoChatroom();

	// �Ķ������ ä�ù濡 �޼����� �ִ� �Լ�
	void addCattingList(ChattingRoom room) { curTempChattList.Add(room); }
	
	// �ؽ�Ʈ ���� ���� �̺�Ʈ �Լ�
	void textcolor(int color);

	// �ӽ� ä�ù��� get�ϴ� �Լ�
	DoublyLinkedList<ChattingRoom>* gettempChat() { return &curTempChattList; }

private:
	int m_command; // ����� ���� ����

	DoublyLinkedList<ChattingRoom> curTempChattList; // �������� �޾ƿ� currentUser�� �ӽ� ä�� ����Ʈ
	Member* curruntUser; // ���� Ŭ���̾�Ʈ�� �α��� ����� ����
};