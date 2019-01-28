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

	// 보낸 이의 이름을 get
	string getSenderName() { return sender.GetFriendName(); }
	
	/**
	*	@pre	= 연산자 오버로딩 메세지를 복사해준다(복사생성자와 기능 같음)..
	*	@post	내용이 있어야 한다.
	*	@return 성립시 1
	*/
	/*void operator = (const Message& message) {
		this->reicever = message.reicever;
		this->senderName = message.senderName;
		this->sender = message.sender;
		this->m_content = message.m_content;
	}*/

	// 메세지 내용을 출력하는 << 연산자 오버로딩
	friend ostream& operator<<(ostream& os, Message& dt) {
		os << " \t    " << dt.getSenderName() << "\t " << dt.m_content << endl;
		return os;
	}

private:
	Friend sender;		// 보낸 이
	string m_content;   // 내용
};