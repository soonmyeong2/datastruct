#pragma once
#include <iostream>
using namespace std;

#include "DoublyLinkedList.h"
/**
*	Message information class.
*/
class Message
{
public:

	/**
	*	default constructor.
	*/
	Message()
	{
		sender.SetFriendID("-1");
		m_content = "";
	}

	/**
	*	default constructor.
	*/
	~Message() {}

	/**
	*	@brief	Set to id.
	*	@pre	none.
	*	@post	toid is set.
	*	@param	toid	message toid.
	*/
	void setSentID(string ID) { sender.SetFriendID(ID); }

	/**
	*	@brief	Set to name.
	*	@pre	none.
	*	@post	toid is set.
	*	@param	toid	message toid.
	*/
	void setSentName(string name) { sender.SetFriendName(name); }

	/**
	*	@brief	Set content.
	*	@pre	none.
	*	@post	content is set.
	*	@param	content	message content.
	*/
	void setContent(string content) { m_content = content; }

	/**
	*	@brief	Get to id.
	*	@pre	toid is set.
	*	@post	none.
	*	@return	toid.
	*/
	string getSentID() { return sender.GetFriendID(); }

	/**
	*	@brief	Get to content.
	*	@pre	content is set.
	*	@post	none.
	*	@return	content.
	*/
	string getContent() { return m_content; }

	// ���� ���� �̸��� get
	string getSenderName() { return sender.GetFriendName(); }
	
	/**
	*	@pre	= ������ �����ε� �޼����� �������ش�(��������ڿ� ��� ����)..
	*	@post	������ �־�� �Ѵ�.
	*	@return ������ 1
	*/
	/*void operator = (const Message& message) {
		this->reicever = message.reicever;
		this->senderName = message.senderName;
		this->sender = message.sender;
		this->m_content = message.m_content;
	}*/

	// �޼��� ������ ����ϴ� << ������ �����ε�
	friend ostream& operator<<(ostream& os, Message& dt) {
		os << " \t    " << dt.getSenderName() << "\t " << dt.m_content << endl;
		return os;
	}

private:
	Friend sender;		// ���� ��
	string m_content;   // ����
};