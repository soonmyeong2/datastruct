#pragma once
#include "Message.h"
#include "DoublyLinkedList.h"
#include <iostream>
#include <fstream>
#include "SortedLinkedList.h"
using namespace std;

class ChattingRoom
{
public:
	// �⺻ ������
	ChattingRoom() {}

	// �⺻ �Ҹ���
	~ChattingRoom() {}


	// ä�� �� ��� ����� ���� << ������ �����ε�
	friend ostream& operator<<(ostream& os, const ChattingRoom& dt) {
		os << "\t" << dt.chttingRoomName << endl;
		return os;
	}

	// == ������ �����ε�, ä�ù� �̸��� ������ ��
	bool operator ==(ChattingRoom cust) { return (chttingRoomName == cust.chttingRoomName); }

	// ä�ù� �̸��� set�ϴ� �Լ�
	void setChttingRoomName(string name) { chttingRoomName = name; }

	// ä�ù� �̸��� get�ϴ� �Լ�
	string getChattingRoomName() { return chttingRoomName; }

	// ä�ù��� �޼��� ����� get�ϴ� �Լ�
	DoublyLinkedList<Message>* getMessageList() { return &messageList; }

	// ä�ù��� ���� ����� get�ϴ� �Լ�
	SortedLinkedList<Friend>* getUserList() { return &userList; }

private:
	string chttingRoomName; // ä�ù� �̐a

	DoublyLinkedList<Message> messageList; // ä�� ����
	SortedLinkedList<Friend> userList; // ������
};