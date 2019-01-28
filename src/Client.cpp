#include "Client.h"

// 클라이언트 요청에 따른 함수 실행
void Client::ClientMenu()
{
	while (1)
	{
		m_command = ClientCommand();
		switch (m_command)
		{
		case 1:
			chattingManagement(); // 채팅
			break; 
		case 2:
			FriendManagement(); // 친구
			break;
		case 3:
			changeInfo(); // 개인정보
			break;
		case 4:
			if (secession()) // 탈퇴
				return;
			break;
		case 0: // 종료
			cls;
			return;
		default:
			cout << "\tIllegal selection...\n";
			break;
		}
	}
}

// 유저에게 메뉴 출력
int Client::ClientCommand()
{
	int command;

	cout << endl << endl;
	cout << "                             [" << curruntUser->getName() << " 님]\n";
	cout << "\t        KA TALK       \n";
	cout << "\t------------------------ " << endl << endl;
	cout << "\t   1 : Chatting" << endl;
	cout << "\t   2 : management Friend" << endl;
	cout << "\t   3 : Change Info" << endl;
	cout << "\t   4 : leave to KA TALK" << endl;
	cout << "\t   0 : Logout" << endl;
	cout << endl << "\t -> ";
	cin >> command;
	cout << endl;
	
	return command;
}

// 탈퇴 함수
bool Client::secession()
{
	int command;
	cout << "\tReally leave ? ( 1.Y / 2.N )\n\t -> ";
	cin >> command;

	if (command == 1)
	{
		App::getServer()->secession(curruntUser); // 서버에 요청
		cls;
		return true;
	}
	else if (command == 2)
	{
		cls;
	}
	else
	{
		cls;
		cout << "\tIllegal selection...\n";
	}
	return false;
}

// 유저의 정보를 갱신
void Client::changeInfo()
{
	cls;
	App::getServer()->changeInfo(curruntUser); // 서버에 정보 갱신 요청
	cls;
}

// 친구 관리 매니저
void Client::FriendManagement()
{
	while (1)
	{
		cls;

		cout << endl << endl;
		cout << "                                    [" << curruntUser->getName() << " 님]\n";
		cout << "\t       MANAGEMENT  FRIEND       \n";
		cout << "\t---------------------------------- " << endl << endl;
		cout << "\t   1 : Add to friend" << endl;
		cout << "\t   2 : Friend List" << endl;
		cout << "\t   0 : Back" << endl;
		cout << endl << "\t -> ";
		cin >> m_command;
		cout << endl;

		switch (m_command)
		{
		case 1:
			addFriend(); // 친구 추가
			break;
		case 2: // 친구 목록
		{
			cls;
			curruntUser->DisplayFriendList();

			cout << "\n\t 1. Delete friends\n";
			cout << "\t 2. Block friends\n";
			cout << "\t 3. Find fiends\n";
			cout << "\t 4. Favorites\n";
			cout << "\t 0 : Back" << endl;
			cout << endl << "\t -> ";
			cin >> m_command;
		
			switch (m_command)
			{
			case 1:
				deleteFriend(); // 친구 삭제
				break;
			case 2:
				blockFriend(); // 친구 차단
				break;
			case 3:
				findFriend(); // 친구 찾기
				break;
			case 4:
				C_setFavorites(); // 친구 즐겨찾기
				break;
			case 0:
				cls;
				return;
			default:
				break;
			}
			pause;
			cls;
			break;
		}
		break;
		case 0:
			cls;
			return;
		default:
			cout << "\tIllegal selection...\n";
			break;
		}
	}
}

// 친구 추가 요청
void Client::addFriend()
{
	cls;
	App::getServer()->addFriendMenu(curruntUser); // 서버에 요청
	cls;
}

// 친구 블럭 요청
void Client::blockFriend()
{
	App::getServer()->blockFriend(curruntUser); // 서버에 요청
}

// 친구 삭제 요청
void Client::deleteFriend()
{
	App::getServer()->deleteFriend(curruntUser); 
}

// 친구 찾기
void Client::findFriend()
{
	string name;
	Friend temp;
	bool found = false;

	cout << "\t Name : ";
	cin >> name;
	
	curruntUser->getFriendlist()->ResetList();
	for (int i = 0; i < curruntUser->getFriendlist()->GetLength(); i++) // 친구 목록 돌면서
	{
		curruntUser->getFriendlist()->GetNextItem(temp); // 

		if (name == temp.GetFriendName()) //이름 갖다면 출력
		{
			cout << "\t " << name << endl;
			found = true;
		}
	}
	cout << endl;
	if (!found) // 못 찾으면
	{
		cout << "\t not find..\n";
	}
}

// 콘솔 색상 변환 이벤트 핸들러
void Client::textcolor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// 채팅 기능의 총괄
void Client::chattingManagement()
{
	while (1)
	{
		cls;

		cout << endl << endl;
		cout << "                                    [" << curruntUser->getName() << " 님]\n";
		cout << "\n\t 1. Create Chattingroom\n";
		cout << "\t 2. Entry to Chattingroom\n";
		cout << "\t 0 : Back" << endl;
		cout << endl << "\t -> ";
		cin >> m_command;
		cout << endl;

		switch (m_command)
		{
		case 1:
			createChattingRoom(); // 채팅방 생성
			break;
		case 2:
			cursorControl(); // 채팅방 입장
			break;
		case 0:
			cls;
			return;
		default:
			cout << "\tIllegal selection...\n";
			break;
		}
	}
}

// 채팅방 생성
void Client::createChattingRoom()
{
	cls;
	App::getServer()->createChatRoom(curruntUser, this); 
}

// 채팅방 입장
void Client::EntrytoChatroom()
{
	cls;

	curTempChattList.MakeEmpty();

	cout << endl << endl;
	cout << "\n\t----- ChattingRoom List ----- \n" << endl;
	
	App::getServer()->DisplayChatroom(curruntUser, this);
	DoublyIterator<ChattingRoom> iter(curTempChattList);	//출력용 반복자
	while (!iter.IsNull()) // 이터레이터의 다음 값이 NULL이 아닐때까지
	{
		cout << iter.GetCurrentNode().data; // 채팅방 목록 출력
		++iter;
	}
	cout << "\n\t 0.Back\n";
}

// 좌표 이동 이벤트 핸들러
void Client::gotoxy(int x, int y)
{
	COORD cur;
	cur.X = x;
	cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
}

// 커서 숨기는 이벤트 핸들러
void Client::hidingCursor()
{
	CONSOLE_CURSOR_INFO CurInfo;
	CurInfo.dwSize = 1;
	CurInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

// 채팅 방 출력 및 입장
void Client::cursorControl()
{
	int menuPos = 5; // 상하
	int menuNum = 2; // 좌우
	curTempChattList.MakeEmpty();
	while (1)
	{
		App::getServer()->DisplayChatroom(curruntUser, this);
		int size = curTempChattList.GetLength()-1;

		hidingCursor();
		cls;
		cout << "\t Using EnterKey." << endl;
		cout << endl;
		cout << "\n\t----- ChattingRoom List ----- \n" << endl;
		DoublyIterator<ChattingRoom> iter(curTempChattList);	// 반복자 선언
		while (!iter.IsNull())
		{
			cout << "\t" << iter.GetCurrentNode().data; // 채팅방 이름 출력
			++iter;
		}
		if (curTempChattList.GetLength() == 0) // 채팅방이 없다면
		{
			cout << "\t No Chat Rooms\n";
			pause;
			cls;
			return;
		}
		cout << "\n\t\t Back\n";


		gotoxy(9, menuPos); // 9, menupos로 바로 커서 위치 옮기고
		puts("->"); // 화살표 놓기


		int a;
		a = _getch();

		switch (a)
		{
		case 72: // 위
			menuPos--;
			if (menuPos < 5)
				menuPos = 5;
			if (menuPos == size + 6)
				menuPos--;
			break;
		case 80: // 아래
			menuPos++;
			if (menuPos == size + 6)
				menuPos++;
			if (menuPos > size + 7)
				menuPos = size + 7;
			break;
		case 13: // 엔터
		{
			menuNum = menuPos; // 맨아래 (=back)
			if (menuPos == size + 7)
				return;
			if (menuPos > 2)
			{
				gotoxy(1, menuPos);

				cout << "1. In" << endl;
				cout << " 0. Back" << endl;
				cout << " -> ";
				int pp;
				cin >> pp;
				if (pp == 1)
				{
					DoublyIterator<ChattingRoom> iter(curTempChattList);	//출력용 반복자
					for (int i=0;i<menuPos-5;i++)
						iter++;
					DisplayChat(iter.GetCurrentNode().data); // 채팅 목록 출력 함수
				}
				else if (pp == 0)
					break;
			}
		}
		break;
		}
		curTempChattList.MakeEmpty();
	}
}


void Client::DisplayChat(ChattingRoom& room)
{

	int menuPos = 5; // 상하
	int menuNum = 2; // 좌우
	while (1)
	{
		int size = room.getMessageList()->GetLength();
		hidingCursor();

		cls;

		cout << endl << endl;
		cout << "\n         Participant : " << room.getChattingRoomName() << endl << endl;
		cout << "\t     search \n\n";
		
		DoublyIterator<Message> iter(*room.getMessageList());	//출력용 반복자


		Friend at;
		bool check = true;
		
		while (!iter.IsNull() && check)
		{

			at.SetFriendID(iter.GetCurrentNode().data.getSentID()); // 내 친구목록중에서 
			if (NULL != curruntUser->getFriendlist()->Getitem(at))
			{
				if (at.GetFriendID() != curruntUser->getID())
					check = curruntUser->getFriendlist()->Getitem(at)->data.GetInterception(); // 차단친구이면
			}
			if(check) // 차단친구가 아니면
				cout << iter.GetCurrentNode().data;
			else // 차단친구라면 빨간색 처리
			{
				textcolor(RED);
				cout << iter.GetCurrentNode().data;
				textcolor(LIGHTGRAY);
			}
			iter++;
			check = true;
		}
		cout << "\n\t     send (0. Back) ";



		if (menuPos > size - 3)
			menuPos = size - 3;

		gotoxy(9, menuPos+11);
		puts("->");


		int a;
		a = _getch();

		switch (a)
		{
		case 72: // 위
			menuPos--;
			if (menuPos < -6)
				menuPos = -6;
			if (menuPos == -5)
				menuPos--;
			if (menuPos == size -4)
				menuPos--;
			break;
		case 80: // 아래
			menuPos++;
			if (menuPos == -5)
				menuPos++;
			if (menuPos == size -4)
				menuPos++;
			if (menuPos > size-3)
				menuPos = size-3;
			break;
		case 13: // 엔터
		{
			menuNum = menuPos;

			if (menuPos == -6) // 서치
			{
				gotoxy(1, menuPos + 11);
				cout << "\t     Search : ";
				string aa;
				cin >> aa;

				cls;

				cout << endl << endl;
				cout << "\n         Participant : " << room.getChattingRoomName() << endl << endl;
				cout << "\t     search \n\n";
				DoublyIterator<Message> iter2(*room.getMessageList());	//출력용 반복자
				while (!iter2.IsNull()) // 메세지리스트가 끝날때까지
				{
					if (iter2.GetCurrentNode().data.getContent().find(aa) != string::npos) { // 스트링에서 aa를 찾을 수 있으면
						textcolor(GREEN); // 그린으로 변환
						cout << iter2.GetCurrentNode().data; // 출력
						textcolor(LIGHTGRAY); // 색상 리턴
					}
					else
					{
						cout << iter2.GetCurrentNode().data; // 못찾으면 그냥 출력
					}
					iter2++;
				}
				cout << "\n\t     send (0. Back) ";
				pause;

				
			}
			else if (menuPos == size -3) // 맨아래
			{
				string content;
				cout << "\t  content : ";
				cin >> content;

				if (content == "0")
					return;

				Message temp;
				temp.setSentID(curruntUser->getID());
				temp.setSentName(curruntUser->getName());
				temp.setContent(content);

				room.getMessageList()->Add(temp);

				Friend f_temp;
				ofstream ofs("sendmessage.txt"); // sentmessage로 요청사항 서지
				ofs << room.getChattingRoomName() << "\t" << curruntUser->getID() << "\t" << curruntUser->getName() << "\n";

				ofs << content << "\n"; // 내용

				room.getUserList()->ResetList();
				for (int i = 0; i < room.getUserList()->GetLength(); i++) // 채팅방 유저 목록
				{
					room.getUserList()->GetNextItem(f_temp);
					ofs << f_temp.GetFriendID() << "\t";
				}
				ofs.close();
				App::getServer()->sentToMessage(); // 서버에 메세지 뿌려달라고 요청
				menuPos++;
				break;
			}
			else
			{
				gotoxy(1, menuPos+11);

				cout << "1. Del" << endl;
				cout << " 2. Copy" << endl;
				cout << " 3. Send" << endl;
				cout << " 0. Back" << endl;
				cout << " -> ";
				int pp;
				cin >> pp;
				if (pp == 1) // 메세지 삭제
				{
					room.getMessageList()->DeletebyIndex(menuPos + 4);

					ofstream ofs("delmessage.txt"); // delmessage를 매개로 서버에 삭제 요청
					ofs << room.getChattingRoomName() << "\t" << curruntUser->getID() << "\t" << menuPos + 4 << "\n";	
					ofs.close();
					App::getServer()->deleteMessage(); // 서버에 메세지 삭제 요청
					menuPos--;
					break;
				}
				else if (pp == 2) // 메세지 복사
				{
					DoublyIterator<Message> iter(*room.getMessageList());	//출력용 반복자
					for (int i = 0; i<menuPos + 4; i++)
						iter++;
					string a = iter.GetCurrentNode().data.getContent();
					CString cs(a.c_str()); 
					CopyStrToClipboard(cs); // 메세지 복사
				}
				else if (pp == 3) // 메세지 전달
				{
					bool flag = true;
					DoublyIterator<Message> it(*room.getMessageList());	//출력용 반복자
					for (int i = 0; i < menuPos + 4; i++)
						it++;
					int menuNum=5;
					int menuPos=5;

					Message temp;
					temp.setSentID(curruntUser->getID());
					temp.setSentName(curruntUser->getName());
					temp.setContent(it.GetCurrentNode().data.getContent());


					
						while(flag) // 와일문을 탈출 하기위한 플래그 (조건 = 전달할 채팅방에 접근)
						{
							curTempChattList.MakeEmpty();
						cls;
						App::getServer()->DisplayChatroom(curruntUser, this);
						int size = curTempChattList.GetLength() - 1;

						hidingCursor();
						cout << "\t Using EnterKey." << endl;
						cout << endl;
						cout << "\n\t----- ChattingRoom List ----- \n" << endl;
						DoublyIterator<ChattingRoom> iter(curTempChattList);	//출력용 반복자
						while (!iter.IsNull())
						{
							cout << "\t" << iter.GetCurrentNode().data; // 전달 할 채팅방 목록 출력
							++iter;
						}
						cout << "\n\t\t Back\n";


						gotoxy(9, menuPos);
						puts("->");


						int b;
						b = _getch();

						switch (b)
						{
						case 72: // 위
							menuPos--;
							if (menuPos < 5)
								menuPos = 5;
							if (menuPos == size + 6)
								menuPos--;
							break;
						case 80: // 아래
							menuPos++;
							if (menuPos == size + 6)
								menuPos++;
							if (menuPos > size + 7)
								menuPos = size + 7;
							break;
						case 13: // 엔터
						{
							menuNum = menuPos;
							if (menuPos > 2 && menuPos != size + 7) // 채팅방 선택이 유효하다면
							{
								DoublyIterator<ChattingRoom> iter(curTempChattList);	//출력용 반복자
								for (int i = 0; i<menuPos - 5; i++)
									iter++;

								bool flag2 = true;
								if (iter.GetCurrentNode().data.getChattingRoomName() == room.getChattingRoomName())
								{// 이미 들어와 있는 채팅방일 경우.
									cout << "Inside room";
									pause;
									flag2 = false;
								}

								if (flag2) // 입장중인 채팅방이 아니면
								{
									Friend f_temp;
									ofstream ofs("sendmessage.txt"); // sendmessage를 매개로 서버에 요청
									ofs << iter.GetCurrentNode().data.getChattingRoomName() << "\t" << temp.getSentID() << "\t" << temp.getSenderName() << "\n";

									ofs << temp.getContent() << "\n";

									SortedLinkedList<Friend> a(*iter.GetCurrentNode().data.getUserList());
									a.ResetList();
									for (int i = 0; i < iter.GetCurrentNode().data.getUserList()->GetLength(); i++)
									{
										a.GetNextItem(f_temp);
										//iter.GetCurrentNode().data.getUserList()->GetNextItem(f_temp);
										ofs << f_temp.GetFriendID() << "\t";
									}
									ofs.close();
									App::getServer()->sentToMessage(); // 서버에 요청
									cout << "Complete";
									pause;
								}
							}
							flag = false;
						}
						}
					}
				}
				else if (pp == 0)
					break;
			}
		}
		break;
		}
	}

}

// ctrl + c 함수
void Client::CopyStrToClipboard(CString str)
{
	EmptyClipboard();
	CStringA temp(str);
	if (::OpenClipboard(NULL))
	{
		HGLOBAL clipbuffer;
		char * buffer;
		EmptyClipboard();
		clipbuffer = GlobalAlloc(GMEM_DDESHARE, str.GetLength() + 1);
		buffer = (char*)GlobalLock(clipbuffer);
		strcpy(buffer, LPCSTR(temp));
		GlobalUnlock(clipbuffer);
		SetClipboardData(CF_TEXT, buffer);
		CloseClipboard();
	}
}

// 친구 즐겨찾기를 서버에 요청
void Client::C_setFavorites()
{
	App::getServer()->setFavorites(curruntUser);
}