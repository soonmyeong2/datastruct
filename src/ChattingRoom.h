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
	// 기본 생성자
	ChattingRoom() {}

	// 기본 소멸자
	~ChattingRoom() {}


	// 채팅 방 목록 출력을 위한 << 연산자 오버로딩
	friend ostream& operator<<(ostream& os, const ChattingRoom& dt) {
		os << "\t" << dt.chttingRoomName << endl;
		return os;
	}

	// == 연산자 오버로딩, 채팅방 이름이 같으면 참
	bool operator ==(ChattingRoom cust) { return (chttingRoomName == cust.chttingRoomName); }

	// 채팅방 이름을 set하는 함수
	void setChttingRoomName(string name) { chttingRoomName = name; }

	// 채팅방 이름을 get하는 함수
	string getChattingRoomName() { return chttingRoomName; }

	// 채팅방의 메세지 목록을 get하는 함수
	DoublyLinkedList<Message>* getMessageList() { return &messageList; }

	// 채팅방의 유저 목록을 get하는 함수
	SortedLinkedList<Friend>* getUserList() { return &userList; }

private:
	string chttingRoomName; // 채팅방 이륾

	DoublyLinkedList<Message> messageList; // 채팅 내용
	SortedLinkedList<Friend> userList; // 참여자
};