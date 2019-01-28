#include "Client.h"

// Ŭ���̾�Ʈ ��û�� ���� �Լ� ����
void Client::ClientMenu()
{
	while (1)
	{
		m_command = ClientCommand();
		switch (m_command)
		{
		case 1:
			chattingManagement(); // ä��
			break; 
		case 2:
			FriendManagement(); // ģ��
			break;
		case 3:
			changeInfo(); // ��������
			break;
		case 4:
			if (secession()) // Ż��
				return;
			break;
		case 0: // ����
			cls;
			return;
		default:
			cout << "\tIllegal selection...\n";
			break;
		}
	}
}

// �������� �޴� ���
int Client::ClientCommand()
{
	int command;

	cout << endl << endl;
	cout << "                             [" << curruntUser->getName() << " ��]\n";
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

// Ż�� �Լ�
bool Client::secession()
{
	int command;
	cout << "\tReally leave ? ( 1.Y / 2.N )\n\t -> ";
	cin >> command;

	if (command == 1)
	{
		App::getServer()->secession(curruntUser); // ������ ��û
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

// ������ ������ ����
void Client::changeInfo()
{
	cls;
	App::getServer()->changeInfo(curruntUser); // ������ ���� ���� ��û
	cls;
}

// ģ�� ���� �Ŵ���
void Client::FriendManagement()
{
	while (1)
	{
		cls;

		cout << endl << endl;
		cout << "                                    [" << curruntUser->getName() << " ��]\n";
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
			addFriend(); // ģ�� �߰�
			break;
		case 2: // ģ�� ���
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
				deleteFriend(); // ģ�� ����
				break;
			case 2:
				blockFriend(); // ģ�� ����
				break;
			case 3:
				findFriend(); // ģ�� ã��
				break;
			case 4:
				C_setFavorites(); // ģ�� ���ã��
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

// ģ�� �߰� ��û
void Client::addFriend()
{
	cls;
	App::getServer()->addFriendMenu(curruntUser); // ������ ��û
	cls;
}

// ģ�� �� ��û
void Client::blockFriend()
{
	App::getServer()->blockFriend(curruntUser); // ������ ��û
}

// ģ�� ���� ��û
void Client::deleteFriend()
{
	App::getServer()->deleteFriend(curruntUser); 
}

// ģ�� ã��
void Client::findFriend()
{
	string name;
	Friend temp;
	bool found = false;

	cout << "\t Name : ";
	cin >> name;
	
	curruntUser->getFriendlist()->ResetList();
	for (int i = 0; i < curruntUser->getFriendlist()->GetLength(); i++) // ģ�� ��� ���鼭
	{
		curruntUser->getFriendlist()->GetNextItem(temp); // 

		if (name == temp.GetFriendName()) //�̸� ���ٸ� ���
		{
			cout << "\t " << name << endl;
			found = true;
		}
	}
	cout << endl;
	if (!found) // �� ã����
	{
		cout << "\t not find..\n";
	}
}

// �ܼ� ���� ��ȯ �̺�Ʈ �ڵ鷯
void Client::textcolor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// ä�� ����� �Ѱ�
void Client::chattingManagement()
{
	while (1)
	{
		cls;

		cout << endl << endl;
		cout << "                                    [" << curruntUser->getName() << " ��]\n";
		cout << "\n\t 1. Create Chattingroom\n";
		cout << "\t 2. Entry to Chattingroom\n";
		cout << "\t 0 : Back" << endl;
		cout << endl << "\t -> ";
		cin >> m_command;
		cout << endl;

		switch (m_command)
		{
		case 1:
			createChattingRoom(); // ä�ù� ����
			break;
		case 2:
			cursorControl(); // ä�ù� ����
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

// ä�ù� ����
void Client::createChattingRoom()
{
	cls;
	App::getServer()->createChatRoom(curruntUser, this); 
}

// ä�ù� ����
void Client::EntrytoChatroom()
{
	cls;

	curTempChattList.MakeEmpty();

	cout << endl << endl;
	cout << "\n\t----- ChattingRoom List ----- \n" << endl;
	
	App::getServer()->DisplayChatroom(curruntUser, this);
	DoublyIterator<ChattingRoom> iter(curTempChattList);	//��¿� �ݺ���
	while (!iter.IsNull()) // ���ͷ������� ���� ���� NULL�� �ƴҶ�����
	{
		cout << iter.GetCurrentNode().data; // ä�ù� ��� ���
		++iter;
	}
	cout << "\n\t 0.Back\n";
}

// ��ǥ �̵� �̺�Ʈ �ڵ鷯
void Client::gotoxy(int x, int y)
{
	COORD cur;
	cur.X = x;
	cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
}

// Ŀ�� ����� �̺�Ʈ �ڵ鷯
void Client::hidingCursor()
{
	CONSOLE_CURSOR_INFO CurInfo;
	CurInfo.dwSize = 1;
	CurInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

// ä�� �� ��� �� ����
void Client::cursorControl()
{
	int menuPos = 5; // ����
	int menuNum = 2; // �¿�
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
		DoublyIterator<ChattingRoom> iter(curTempChattList);	// �ݺ��� ����
		while (!iter.IsNull())
		{
			cout << "\t" << iter.GetCurrentNode().data; // ä�ù� �̸� ���
			++iter;
		}
		if (curTempChattList.GetLength() == 0) // ä�ù��� ���ٸ�
		{
			cout << "\t No Chat Rooms\n";
			pause;
			cls;
			return;
		}
		cout << "\n\t\t Back\n";


		gotoxy(9, menuPos); // 9, menupos�� �ٷ� Ŀ�� ��ġ �ű��
		puts("->"); // ȭ��ǥ ����


		int a;
		a = _getch();

		switch (a)
		{
		case 72: // ��
			menuPos--;
			if (menuPos < 5)
				menuPos = 5;
			if (menuPos == size + 6)
				menuPos--;
			break;
		case 80: // �Ʒ�
			menuPos++;
			if (menuPos == size + 6)
				menuPos++;
			if (menuPos > size + 7)
				menuPos = size + 7;
			break;
		case 13: // ����
		{
			menuNum = menuPos; // �ǾƷ� (=back)
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
					DoublyIterator<ChattingRoom> iter(curTempChattList);	//��¿� �ݺ���
					for (int i=0;i<menuPos-5;i++)
						iter++;
					DisplayChat(iter.GetCurrentNode().data); // ä�� ��� ��� �Լ�
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

	int menuPos = 5; // ����
	int menuNum = 2; // �¿�
	while (1)
	{
		int size = room.getMessageList()->GetLength();
		hidingCursor();

		cls;

		cout << endl << endl;
		cout << "\n         Participant : " << room.getChattingRoomName() << endl << endl;
		cout << "\t     search \n\n";
		
		DoublyIterator<Message> iter(*room.getMessageList());	//��¿� �ݺ���


		Friend at;
		bool check = true;
		
		while (!iter.IsNull() && check)
		{

			at.SetFriendID(iter.GetCurrentNode().data.getSentID()); // �� ģ������߿��� 
			if (NULL != curruntUser->getFriendlist()->Getitem(at))
			{
				if (at.GetFriendID() != curruntUser->getID())
					check = curruntUser->getFriendlist()->Getitem(at)->data.GetInterception(); // ����ģ���̸�
			}
			if(check) // ����ģ���� �ƴϸ�
				cout << iter.GetCurrentNode().data;
			else // ����ģ����� ������ ó��
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
		case 72: // ��
			menuPos--;
			if (menuPos < -6)
				menuPos = -6;
			if (menuPos == -5)
				menuPos--;
			if (menuPos == size -4)
				menuPos--;
			break;
		case 80: // �Ʒ�
			menuPos++;
			if (menuPos == -5)
				menuPos++;
			if (menuPos == size -4)
				menuPos++;
			if (menuPos > size-3)
				menuPos = size-3;
			break;
		case 13: // ����
		{
			menuNum = menuPos;

			if (menuPos == -6) // ��ġ
			{
				gotoxy(1, menuPos + 11);
				cout << "\t     Search : ";
				string aa;
				cin >> aa;

				cls;

				cout << endl << endl;
				cout << "\n         Participant : " << room.getChattingRoomName() << endl << endl;
				cout << "\t     search \n\n";
				DoublyIterator<Message> iter2(*room.getMessageList());	//��¿� �ݺ���
				while (!iter2.IsNull()) // �޼�������Ʈ�� ����������
				{
					if (iter2.GetCurrentNode().data.getContent().find(aa) != string::npos) { // ��Ʈ������ aa�� ã�� �� ������
						textcolor(GREEN); // �׸����� ��ȯ
						cout << iter2.GetCurrentNode().data; // ���
						textcolor(LIGHTGRAY); // ���� ����
					}
					else
					{
						cout << iter2.GetCurrentNode().data; // ��ã���� �׳� ���
					}
					iter2++;
				}
				cout << "\n\t     send (0. Back) ";
				pause;

				
			}
			else if (menuPos == size -3) // �ǾƷ�
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
				ofstream ofs("sendmessage.txt"); // sentmessage�� ��û���� ����
				ofs << room.getChattingRoomName() << "\t" << curruntUser->getID() << "\t" << curruntUser->getName() << "\n";

				ofs << content << "\n"; // ����

				room.getUserList()->ResetList();
				for (int i = 0; i < room.getUserList()->GetLength(); i++) // ä�ù� ���� ���
				{
					room.getUserList()->GetNextItem(f_temp);
					ofs << f_temp.GetFriendID() << "\t";
				}
				ofs.close();
				App::getServer()->sentToMessage(); // ������ �޼��� �ѷ��޶�� ��û
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
				if (pp == 1) // �޼��� ����
				{
					room.getMessageList()->DeletebyIndex(menuPos + 4);

					ofstream ofs("delmessage.txt"); // delmessage�� �Ű��� ������ ���� ��û
					ofs << room.getChattingRoomName() << "\t" << curruntUser->getID() << "\t" << menuPos + 4 << "\n";	
					ofs.close();
					App::getServer()->deleteMessage(); // ������ �޼��� ���� ��û
					menuPos--;
					break;
				}
				else if (pp == 2) // �޼��� ����
				{
					DoublyIterator<Message> iter(*room.getMessageList());	//��¿� �ݺ���
					for (int i = 0; i<menuPos + 4; i++)
						iter++;
					string a = iter.GetCurrentNode().data.getContent();
					CString cs(a.c_str()); 
					CopyStrToClipboard(cs); // �޼��� ����
				}
				else if (pp == 3) // �޼��� ����
				{
					bool flag = true;
					DoublyIterator<Message> it(*room.getMessageList());	//��¿� �ݺ���
					for (int i = 0; i < menuPos + 4; i++)
						it++;
					int menuNum=5;
					int menuPos=5;

					Message temp;
					temp.setSentID(curruntUser->getID());
					temp.setSentName(curruntUser->getName());
					temp.setContent(it.GetCurrentNode().data.getContent());


					
						while(flag) // ���Ϲ��� Ż�� �ϱ����� �÷��� (���� = ������ ä�ù濡 ����)
						{
							curTempChattList.MakeEmpty();
						cls;
						App::getServer()->DisplayChatroom(curruntUser, this);
						int size = curTempChattList.GetLength() - 1;

						hidingCursor();
						cout << "\t Using EnterKey." << endl;
						cout << endl;
						cout << "\n\t----- ChattingRoom List ----- \n" << endl;
						DoublyIterator<ChattingRoom> iter(curTempChattList);	//��¿� �ݺ���
						while (!iter.IsNull())
						{
							cout << "\t" << iter.GetCurrentNode().data; // ���� �� ä�ù� ��� ���
							++iter;
						}
						cout << "\n\t\t Back\n";


						gotoxy(9, menuPos);
						puts("->");


						int b;
						b = _getch();

						switch (b)
						{
						case 72: // ��
							menuPos--;
							if (menuPos < 5)
								menuPos = 5;
							if (menuPos == size + 6)
								menuPos--;
							break;
						case 80: // �Ʒ�
							menuPos++;
							if (menuPos == size + 6)
								menuPos++;
							if (menuPos > size + 7)
								menuPos = size + 7;
							break;
						case 13: // ����
						{
							menuNum = menuPos;
							if (menuPos > 2 && menuPos != size + 7) // ä�ù� ������ ��ȿ�ϴٸ�
							{
								DoublyIterator<ChattingRoom> iter(curTempChattList);	//��¿� �ݺ���
								for (int i = 0; i<menuPos - 5; i++)
									iter++;

								bool flag2 = true;
								if (iter.GetCurrentNode().data.getChattingRoomName() == room.getChattingRoomName())
								{// �̹� ���� �ִ� ä�ù��� ���.
									cout << "Inside room";
									pause;
									flag2 = false;
								}

								if (flag2) // �������� ä�ù��� �ƴϸ�
								{
									Friend f_temp;
									ofstream ofs("sendmessage.txt"); // sendmessage�� �Ű��� ������ ��û
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
									App::getServer()->sentToMessage(); // ������ ��û
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

// ctrl + c �Լ�
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

// ģ�� ���ã�⸦ ������ ��û
void Client::C_setFavorites()
{
	App::getServer()->setFavorites(curruntUser);
}