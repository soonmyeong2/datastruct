#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

#include "Friend.h"
#include "SortedLinkedList.h"

#define LIGHTGRAY 7
#define RED 4

class Member
{
public:

	Member() 
	{
		ID = "";
		PW = "";
		Address = "";
	}

	~Member() {}


	// Keyboard로 id set
	void setIDbyKB()
	{
		cout << "\t ID : ";
		cin >> ID;
	}

	void setPWbyKB()
	{
		cout << "\t PW : ";
		cin >> PW;
	}

	void setNamebyKB()
	{
		cout << "\t Name : ";
		cin >> Name;
	}

	void setAreabyKB()
	{
		cout << "\t Address : ";
		cin >> Address;
	}

	void setUserbyKB()
	{
		setIDbyKB();
		setPWbyKB();
		setNamebyKB();
		setAreabyKB();
	}


	// ---------- SET ------------ //
	void setID(string m_ID) { ID = m_ID; }
	void setPW(string m_PW) { PW = m_PW; }
	void setName(string m_name) { Name = m_name; }
	void setArea(string m_area) { Address = m_area; }


	// ---------- GET ------------ //
	string getID() { return ID; }
	string getPW() { return PW; }
	string getName() { return Name; }
	string getArea() { return Address; }


	// 텍스트 색상 변경 이벤트
	void textcolor(int color);

	/**
	*	@brief	두 회원의 ID값의 대소를 비교한다.
	*	@pre	두 회원의 ID값이 설정되어있다.
	*	@param	비교할 회원
	*	@return	this의 ID가 Prod의 ID보다 클때 1을 리턴한다. 아니면 0을 리턴한다.
	*/
	bool operator >(Member cust) { return (ID > cust.ID); }
	bool operator <(Member cust) { return (ID < cust.ID); }


	// 나의 친구 목록을 디스플레이 한다
	void DisplayFriendList();

	/**
	*	@brief	두 회원의 ID값의 대소를 비교한다.
	*	@pre	두 회원의 ID값이 설정되어있다.
	*	@param	cust	비교할 회원
	*	@return	this의 ID가 Prod의 ID와 같을 때 1을 리턴한다. 아니면 0을 리턴한다.
	*/
	bool operator ==(Member cust) { return (ID == cust.ID); }

	/**
	*	@brief	Member클래스의 오퍼레이터 !=를 회원 정보 아이디 비교하는 것으로 정의한다..
	*	@pre	회원의 정보가 있어야한다.
	*	@return	회원의 아이디가 다르면 참을 리턴한다.
	*/
	bool operator !=(Member cust) { return (ID != cust.ID); }

	/**
	*	@brief	Member클래스의 오퍼레이터 <<를 회원 정보 출력하는 것으로 정의한다.
	*	@pre	회원의 정보가 있어야한다.
	*	@return	회원의 개인정보를 출력하는 것을 리턴한다.
	*/
	friend ostream& operator<<(ostream& os, const Member& dt)
	{
		os << "\t -------------------\n"
			<< "\t  ID      :  " << dt.ID << endl		
			<< "\t  Name    :  " << dt.Name << endl
			<< "\t  Address :  " << dt.Address << endl
			<< "\t -------------------\n";
		return os;
	}


	// 친구목록에 파라미터로 넘어온 친구를 add
	void addFriend(Friend fd)
	{
		friendList.Add(fd);
	}

	// 파라미터로 넘어온 친구를 찾을 수 있으면 참 else false.
	bool findFriend(Friend fd)
	{
		if (friendList.Get(fd))
			return true;
		else
			return false;
	}

	// 친구 목록을 get 하는 함수
	SortedLinkedList<Friend>* getFriendlist() { return &friendList; }


private:
	string ID;			// student ID.
	string PW;			// student PW.
	string Name;		// student name.
	
	string Address;		// student address.
	string Number;		// 전화번호 
	string Birth;		// 생년월일

	SortedLinkedList<Friend> friendList; // 친구 목록
};