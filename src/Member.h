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


	// Keyboard�� id set
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


	// �ؽ�Ʈ ���� ���� �̺�Ʈ
	void textcolor(int color);

	/**
	*	@brief	�� ȸ���� ID���� ��Ҹ� ���Ѵ�.
	*	@pre	�� ȸ���� ID���� �����Ǿ��ִ�.
	*	@param	���� ȸ��
	*	@return	this�� ID�� Prod�� ID���� Ŭ�� 1�� �����Ѵ�. �ƴϸ� 0�� �����Ѵ�.
	*/
	bool operator >(Member cust) { return (ID > cust.ID); }
	bool operator <(Member cust) { return (ID < cust.ID); }


	// ���� ģ�� ����� ���÷��� �Ѵ�
	void DisplayFriendList();

	/**
	*	@brief	�� ȸ���� ID���� ��Ҹ� ���Ѵ�.
	*	@pre	�� ȸ���� ID���� �����Ǿ��ִ�.
	*	@param	cust	���� ȸ��
	*	@return	this�� ID�� Prod�� ID�� ���� �� 1�� �����Ѵ�. �ƴϸ� 0�� �����Ѵ�.
	*/
	bool operator ==(Member cust) { return (ID == cust.ID); }

	/**
	*	@brief	MemberŬ������ ���۷����� !=�� ȸ�� ���� ���̵� ���ϴ� ������ �����Ѵ�..
	*	@pre	ȸ���� ������ �־���Ѵ�.
	*	@return	ȸ���� ���̵� �ٸ��� ���� �����Ѵ�.
	*/
	bool operator !=(Member cust) { return (ID != cust.ID); }

	/**
	*	@brief	MemberŬ������ ���۷����� <<�� ȸ�� ���� ����ϴ� ������ �����Ѵ�.
	*	@pre	ȸ���� ������ �־���Ѵ�.
	*	@return	ȸ���� ���������� ����ϴ� ���� �����Ѵ�.
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


	// ģ����Ͽ� �Ķ���ͷ� �Ѿ�� ģ���� add
	void addFriend(Friend fd)
	{
		friendList.Add(fd);
	}

	// �Ķ���ͷ� �Ѿ�� ģ���� ã�� �� ������ �� else false.
	bool findFriend(Friend fd)
	{
		if (friendList.Get(fd))
			return true;
		else
			return false;
	}

	// ģ�� ����� get �ϴ� �Լ�
	SortedLinkedList<Friend>* getFriendlist() { return &friendList; }


private:
	string ID;			// student ID.
	string PW;			// student PW.
	string Name;		// student name.
	
	string Address;		// student address.
	string Number;		// ��ȭ��ȣ 
	string Birth;		// �������

	SortedLinkedList<Friend> friendList; // ģ�� ���
};