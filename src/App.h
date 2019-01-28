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

class Client; // 교차헤더 방지 위해 명시적 클래스 선언

#define pause system("pause")
#define cls system("cls")

class App
{
private:

	/**
	*	@brief	기본 생성자. load_File()함수로 .txt 파일을 읽어온다.
	*	@details private로 생성 불가하게 막아 단 1개의 개체만 유지하게 한다.
	*/
	App() { load_File(); }

public:


	/**
	*	@brief	기본 소멸자.
	*/
	~App() {}

	/**
	*	@brief	App클래스의 시작을 실행하는 함수
	*	@pre	None.
	*	@post	사용자에게 키값을 입력받아 각 해당하는 함수를 실행시켜준다.
	*/
	void Run();

	/**
	*	@brief	사용자에게 키 값을 입력받아 키 값을 리턴한다.
	*	@pre	None.
	*	@post	사용자에게 함수 기능을 디스플레이 해준 후 필요한 기능의 키 값을 입력받는다.
	*	@return	사용자 입력값을 반환한다.
	*/
	int GetCommand();
	
	/**
	*	@brief	사용자에게 ID, PW를 입력받아 일치하는 정보가 있으면 클라이언트 클래스 동적할당하여 실행
	*	@pre	None.
	*	@post	유저리스트에 멤버가 있어야 한다.
	*	@return	로그인 성공시 1. else false
	*/
	bool Login();

	// 사용자에게 키 값을 입력받아 유저리스트에 추가한다 (= 회원가입)
	void Join();

	// 클라이언트에서 요청한 회원탈퇴기능을 실행시켜준다. 유저리스트에서 제거되며 동적할당 된 클라이언트는 메모리해제 된다.
	void secession(Member* deleteMember);

	// 클라이언트에서 요청한 회원 변경요청 실행 시켜줌
	void changeInfo(Member* Member);

	// 클라이언트에서 요청한 친구 관리 메뉴를 실행 시켜줌
	void addFriendMenu(Member* mb);

	// 클라이언트에서 요청한 친구 추가 요청을 실행 시켜줌
	bool addFriend(Member* mb);

	// 이름으로 유저리스트에서 일치하는 회원을 출력한다.
	void findSearchbyName(RedBlackNode<Member>* node, string name);

	// .txt 파일을 읽어옴
	void load_File();

	// 클라이언트에서 메세지 전송, 삭제 했던 모든 로그를 디스플레이 해줌
	void printServerLog();

	// 클라이언트에서 요청한 친구 즐겨찾기 메뉴를 실행 시켜줌 
	void setFavorites(Member *mb);

	// sendmessage.txt를 읽어 해당 일치하는 채팅방에 전송 함
	void sentToMessage();

	// delete.txt를 읽어 해당 일치하는 채팅방에서 메세지를 삭제 해줌
	void deleteMessage();

	// 클라이언트의 추천 친구목록을 디스플레이 해줌
	void recommandMember(Member* mb);

	// 클라이언트의 친구 차단 요청메뉴를 실행 시켜줌
	void blockFriend(Member* mb);

	// 클라이언트에서 친구 삭제 요청을 실행 시켜줌
	void deleteFriend(Member* mb);

	// 클라이언트에서 채팅방을 새로 요청하면 채팅 개설 목록 실행 시켜줌
	void createChatRoom(Member* mb, Client* cn);

	// 현재 유저의 채팅방 목록을 디스플레이 해줌(== 클라이언트의 채팅 방 갱신)
	void DisplayChatroom(Member* mb, Client* cur);

	// 해시 테이블의 해시 펑션
	int hash_function(string temp);

	// 유일하게 존재하는 앱을 소환 할 수 있는 함수
	static App* getServer(); 

private:
	int m_Command; // 유저 선택용 변수

	RedBlackTree<Member> userList; // 유저 목록
	HASH<ChattingRoom> chattingList; // 채팅방 목록 
	SortedLinkedList<Member> recommendationList; // 추천친구 목록
	
	static App* server; // 유일한 서버 인스턴스
};