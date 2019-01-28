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
	// 기본 생성자
	Client() {}

	// 기본 소멸자
	~Client() {}

	// 채팅방 목록을 디스플레이하고 방향키 핸들러를 이용하여 채팅방에 입장을 시켜 줌
	void cursorControl();

	// 좌표 설정
	void gotoxy(int x, int y);
	
	// 커서 숨기기
	void hidingCursor();

	// ctrl + c 해주는 함수 str을 복사한다.
	void CopyStrToClipboard(CString str);

	// 클라이언트의 총괄 메뉴. 사용자 키 값에 따라 해당 함수 발동
	void ClientMenu();

	// 클라이언트의 메뉴 디스플레이
	int ClientCommand();

	// 파라미터로 넘어온 방의 채팅 목록 디스 플레이 하며 room 채팅의 모든 기능을 총괄한다.
	void DisplayChat(ChattingRoom& room);

	// 서버로 회원 탈퇴 요청하는 함수
	bool secession();
	
	// 서버로 회원 정보 요청하는 함수
	void changeInfo();

	// 친구관리의 모든 항목을 디스플레이
	void FriendManagement();

	// 친구 신청 한 결과를 서버로 요청하는 함수
	void addFriend();

	// 친구 즐겨찾기 신청을 서버에 요청하는 함수
	void C_setFavorites();

	// 친구 차단 신청을 서버에 요청하는 함수
	void blockFriend();

	// 친구 삭제 신청을 서버에 요청하는 함수
	void deleteFriend();

	// 내 친구 목록에서 친구를 검색을 하는 함수
	void findFriend();

	// 클라이언트의 로그인 유저를 set하는 함수
	void setCurruntUser(Member* c_user) { curruntUser = c_user; }

	// 채팅에 입장했을때 사용자가 입력 메뉴 받는 디스플레이
	void chattingManagement();

	// 새로운 채팅방 생성을 서버에 요청하는 함수
	void createChattingRoom();

	// 클라이언트의 임시 채팅 목록에 입장
	void EntrytoChatroom();

	// 파라미터의 채팅방에 메세지를 넣는 함수
	void addCattingList(ChattingRoom room) { curTempChattList.Add(room); }
	
	// 텍스트 생상 변경 이벤트 함수
	void textcolor(int color);

	// 임시 채팅방을 get하는 함수
	DoublyLinkedList<ChattingRoom>* gettempChat() { return &curTempChattList; }

private:
	int m_command; // 사용자 선택 변수

	DoublyLinkedList<ChattingRoom> curTempChattList; // 서버에서 받아온 currentUser의 임시 채팅 리스트
	Member* curruntUser; // 현재 클라이언트의 로그인 사용자 정보
};