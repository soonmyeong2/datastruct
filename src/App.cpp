#include "App.h"

App* App::server = nullptr; // instance 초기화

//싱글톤 패턴을 위한 함수. 생성자를 숨기고 유일하게 하나의 인스턴스만 만들게 한다.
App* App::getServer()
{
	if (server == nullptr) //  인스턴스가 가르키는 값이 없다면
	{
		App* newServer = new App(); // 새로운 인스턴스 생성
		server = newServer; // 인스턴스는 command;

		return server; // 리턴
	}
	else
	{
		return server; // 가르키는 값이 있다면 기존 인스턴스 반환
	}
}

void App::Run()
{
	while (1)
	{
		m_Command = GetCommand();

		switch (m_Command)
		{
		case 1:
			Login(); // 로그인
			break;
		case 2:
			Join(); // 회원 가입
			break;
		case 3:
			printServerLog(); // 서버가 처리한 요청 출력
			break;
		case 0:
			return;
		default:
			cout << "\tIllegal selection...\n";
			break;
		}
	}
}

// Display command on screen and get a input from keyboard.
int App::GetCommand()
{
	int command;
	cout << endl << endl;
	cout << "\t----- KAKAO TALK ----- \n" << endl;
	cout << "\t   1 : Login" << endl;
	cout << "\t   2 : Join" << endl;
	cout << "\t   3 : Server Log" << endl;
	cout << "\t   0 : Quit" << endl;

	cout << endl << "\t -> ";
	cin >> command;
	cout << endl;

	return command;
}

// 사용자에게 정보를 입력받고 해당 유저의 클라이언트 실행
bool App::Login()
{
	cls;
	cout << "\n\n";
	
	Member m_temp;
	Member *temp;
	m_temp.setIDbyKB();
	m_temp.setPWbyKB();
	
	if (userList.Retrieve(m_temp,temp)) // 아이디로 멤버를 찾을수 있고 
	{
		if (m_temp.getPW() == temp->getPW()) // 비번이 같다면
		{
			Client *m_Clinet = new Client; // 클라이언트 클래스 실행
			m_Clinet->setCurruntUser(temp); // 유저 set하고
			cls;
			m_Clinet->ClientMenu(); // 클라이언트 메뉴 실행
		
			delete m_Clinet; // 클라이언트 종료시 메모리 할당 해제
		}
		else
			cout << "\n\t  Password error..\n";
	}
	else
	{
		cout << "\n\tNo matching member information.." << endl; // 실패시
	}

	return false;
}

// 정보를 입력받아 회원 가입 실행
void App::Join()
{
	cls;

	cout << "\n\n";

	Member newMember;
	newMember.setUserbyKB(); // 새로운 멤버 정보 set

	if (userList.insert(newMember)) // 동일한 ID 존재하지 않다면
		cout << "\n\t Seccess ! \n";
	else
		cout << "\n\t ID Duplication..\n";

	pause;
	cls;
}

// 파라미터로 넘어온 회원 축출 기능
void App::secession(Member* deleteMember)
{
	Member* del;

	userList.Retrieve(*deleteMember, del); // 파라미터로 넘어온 노드를 찾아서
	userList.erase(*del); // 제거해버림
}

// 파라미터로 넘어온 회원 정보 갱신
void App::changeInfo(Member* member)
{
	Member* re_member;

	userList.Retrieve(*member, re_member);
	while (1)
	{
		int command;

		cout << "\n\n\t     INFO \n" << *re_member << "\n\n";

		cout << "\t 1. change name\n";
		cout << "\t 2. change location\n";
		cout << "\t 0. back\n\n\t  -> ";
		cin >> command;

		switch (command)
		{
		case 1:
			re_member->setNamebyKB(); // 이름 변경
			break;
		case 2:
			re_member->setAreabyKB(); // 지역 변경
			break;
		case 0:
			return;
		default:
			cout << "\tIllegal selection...\n";
			break;
		}
		cls;
	}
}

// 파일 읽어오기
void App::load_File()
{
	ifstream ifs("user.txt"); // user.txt를 엽니다
	string  userId, pw, username, area;
	while (!ifs.eof()) // 파일이 끝날때까지
	{
		Member member; // m_List에 들어갈 멤버 객체 하나 선언하고

		ifs >> userId >> pw >> username >> area; // 순서대로 자료를 읽고
		if (ifs.fail()) // 파일읽기에 실패하면 와일문 빠져나간다.
			break;
		member.setID(userId); // 멤버 객체에 정보를 채운다
		member.setPW(pw);
		member.setName(username);
		member.setArea(area);

		userList.insert(member);
	}
	ifs.close(); // 파일 닫기


	////////////////////////////////////////////

	ifstream ifs2("friend.txt"); // friend 파일을 열고
	while (!ifs2.eof()) // 파일이 끝날때까지
	{
		string userId;
		int friendsCnt;
		string F_id, F_name;
		ifs2 >> userId >> friendsCnt; // 유저 아이디, 친구 수를 카운트하고
		if (ifs2.fail()) // 파일이 끝이면 빠져나간다
			break;

		Friend temp; // friendList에 들어갈 객체 생성하고
		Member m_temp; // m_List의 유저 임시 객체
		Member *user;
		m_temp.setID(userId);
		
		for (int i = 0; i < friendsCnt; i++) // 친구 수 만큼 돌리면서
		{
			ifs2 >> F_id >> F_name; // 친구 정보를 읽어오고
			temp.SetFriendID(F_id); // 임시 FriendList에 저장한다
			temp.SetFriendName(F_name);

			userList.Retrieve(m_temp, user);
			user->addFriend(temp);
		}
	}
	ifs2.close();

	////////////////////////////////////

	ifstream ifs3("chatting.txt"); // message 파일 열고

	string chat_name;
	string user_id;
	string user_name;
	string content;
	int chat_num;
	int user_num;
	Friend user_temp;
	ChattingRoom chat_temp;
	Message message_temp;

	while (!ifs3.eof())
	{
		ifs3 >> chat_name >> user_num >> chat_num;
		chat_temp.setChttingRoomName(chat_name);
		
		if (ifs3.fail()) // 파일이 끝이면 빠져나간다
			break;

		for (int i = 0; i < user_num; i++)
		{
			ifs3 >> user_id >> user_name;
			user_temp.SetFriendID(user_id);
			user_temp.SetFriendName(user_name);

			chat_temp.getUserList()->Add(user_temp);
		}

		for (int i = 0; i < chat_num; i++)
		{
			ifs3 >> user_id >> content;
			message_temp.setSentID(user_id);
			user_temp.SetFriendID(user_id);
			chat_temp.getUserList()->Get(user_temp);
			message_temp.setSentName(user_temp.GetFriendName());
			message_temp.setContent(content);

			chat_temp.getMessageList()->Add(message_temp);
		} // 하나의 채팅방 객체 set완료

		/* 해시 펑션으로 유저와 대응되는 해시 인덱스에 채팅방 삽입 핵심 */
		int key;
		Friend _temp;
		chat_temp.getUserList()->ResetList();
		for (int i = 0; i < chat_temp.getUserList()->GetLength(); i++)
		{
			chat_temp.getUserList()->GetNextItem(_temp);
			key = _temp.hash_function(_temp.GetFriendID()); // 키 값을 유저의 아이디로 한다.
			chattingList.AddHashData(key, chat_temp); // 해시 테이블에 채팅 방 삽입
		}
	}
	ifs3.close(); // 파일 닫기
}

// 클라이언트가 친구 추가하는 요청을 보내왔을때 실행되는 함수
void App::addFriendMenu(Member* mb)
{
	while (1)
	{
		cout << endl << endl << endl;
		cout << "\t            ADD FRIEND        \n";
		cout << "\t-------------------------------- " << endl << endl;
		cout << "\t   1 : Recommendation friend" << endl;
		cout << "\t   2 : Search Friend" << endl;
		cout << "\t   0 : Back" << endl;
		cout << endl << "\t -> ";
		cin >> m_Command;
		cout << endl;

		switch (m_Command)
		{
		case 1:
			cls;
			recommandMember(mb); // 추천 친구 목록
			break;
		case 2:
		{
			cls;

			cout << endl << endl << endl;
			cout << "\t   1 : Search by Name" << endl;
			cout << "\t   2 : Search by ID" << endl;
			cout << endl << "\t -> ";
			cin >> m_Command;

			if (m_Command == 1)
			{
				string name;
				cout << "\n\n\t Find Name : ";
				cin >> name;
				findSearchbyName(userList.root(), name); // 이름으로 찾기

				cout << "\n\n\t 1. Add friends\n";
				cout << "\t 0. Back\n\n\t -> ";
				cin >> m_Command;
			}
			else if(m_Command == 2) // 아이디로 찾기
			{
				string id;
				cout << "\n\n\t Find ID : ";
				cin >> id;
				Member f_t;
				Member* real;
				f_t.setID(id);
				userList.search(f_t);
				userList.Retrieve(f_t, real);
				
				cout << "\n" << *real;
				cout << "\n\n\t 1. Add friends\n";
				cout << "\t 0. Back\n\n\t -> ";
				cin >> m_Command;
			}


			switch (m_Command) 
			{
			case 1:
				addFriend(mb); // 친구 추가
				break;
			case 0:
				return;
			default:
				break;
			}
			pause;
			cls;
		}
			break;
		case 0:
			return;
		default:
			break;
		}
	}
}

// 이름으로 친구 찾기
void App::findSearchbyName(RedBlackNode<Member>* node, string name)
{
	if (node == nullptr)
		return;
	else // 재귀적 호출로 트리의 모든 부분을 탐색해야 한다.
	{
		if (node != nullptr && node->v_.getName() == name)
		{
			cout << endl << node->v_;
		}
		findSearchbyName(node->left_, name);
		findSearchbyName(node->right_, name);
	}
}

// 클라이언트의 친구 추가 요청 처리부
bool App::addFriend(Member* mb) 
{
	string temp;
	cout << "\t Friend ID to add : ";
	cin >> temp;

	Member compare;
	compare.setID(temp);
	Member* m_temp;
	Friend add_fd;

	if (userList.Retrieve(compare, m_temp)) // 회원목록에 add하려는 친구가 있고
	{
		add_fd.SetFriendID(m_temp->getID());
		if(!mb->findFriend(add_fd) && mb->getID() != temp)  // 내 친구가 아니고 내가 아니면
		{
			add_fd.SetFriendName(m_temp->getName());
			mb->addFriend(add_fd);
			cout << "\t SUCCESS\n";
			return true;
		}
	}
	cout << "\t Fail..\n";
	return false;
}

// 친구 추천 목록 함수
void App::recommandMember(Member* mb)
{

	Member data, friData;	//Get함수는 MemberType, a을 파라미터로 갖기 때문에 임의로 만들어준다.
	string temp;
	Friend temp1, fritemp;
	bool exist = false;
	mb->getFriendlist()->ResetList(); // 나의 친구 목록을 포인터 커서를 초기화 시키고

	if (mb->getFriendlist()->GetLength() == 0) // 친구 수가 0이면 예외처리
	{
		cout << "\n\n\tNo Recommend friends.";
		return;
	}
	for (int i = 0; i < mb->getFriendlist()->GetLength(); i++) // 친구 수만큼 돌면서
	{
		mb->getFriendlist()->GetNextItem(temp1); // 순차적으로 친구의 아이디를 받고
		data.setID(temp1.GetFriendID()); // Member형 변수 data에 ID를 넣는다.
		userList.search(data); // data는 온전한 객체가 되고
		data.getFriendlist()->ResetList(); // 객체의 친구 배열에 접근
		for (int j = 0; j < data.getFriendlist()->GetLength(); j++) // 친구의 친구수 만큼 돌면서
		{
			data.getFriendlist()->GetNextItem(fritemp); // 순차적으로 친구의 친구정보를 fritemp에 넣고
			friData.setID(fritemp.GetFriendID()); // fridata에 아이디를 얻고
			userList.search(friData); // 그 객체의 정보를 얻는다(친구의 친구의 온전한 정보)
			recommendationList.Add(friData); // 그 정보를 추천친구 목록에 넣는다.
		}
	}
	bool check = false; // 이미 친구관계인지 체크하는 변수
	mb->getFriendlist()->ResetList();  // 로그인 유저의 친구 목록 커서를 초기화한다.
	recommendationList.ResetList(); // 추천친구목록 커서르 초기화 한다.
	cout << "\n\n";
	for (int i = 0; i < recommendationList.GetLength(); i++) // 친구목록리스트를 돌면서
	{
		recommendationList.GetNextItem(data); // 추천친구 목록을 순차적으로 data에 얻고
		for (int j = 0; j < mb->getFriendlist()->GetLength(); j++) // 로그인한 유저의 친구 목록을 돌면서
		{
			mb->getFriendlist()->GetNextItem(temp1); // temp1에 로그인 유저의 친구를 넣는다.
			if (temp1.GetFriendID() == data.getID()) // 만약 추천친구가 이미 친구라면
				check = true; // 이미 친구라는 뜻으로 true;
		}
		if (data.getID() != mb->getID() && check == false) // 만약 친구관계가아니고 로그인한 사용자의 아이디가 아니라면
		{
			cout << data; // 추천친구목록을 출력한다.
			exist = true;
		}
		mb->getFriendlist()->ResetList(); // 그 후 다시 for문 재진입을 위해 리셋해준 후
		check = false; // 친구관계인지 체크하는 변수도 초기화 해준다.
	}
	if (!exist)
	{
		cout << "\t No friends recommended\n";
	}
	recommendationList.MakeEmpty(); // 그 후 친구 목록 메모리 삭제 추천친구 목록은 매우 유동적이므로 불러올때마다 새로 검색하고 메모리에서 삭제해준다.


	cout << "\n\n\t 1. Add friends\n";
	cout << "\t 0. Back\n\n\t -> ";
	cin >> m_Command;

	switch (m_Command)
	{
	case 1:
		addFriend(mb);
		break;
	case 0:
		cls;
		return;
	default:
		break;
	}
	pause;
	cls;
}

// 클라이언트의 친구 차단 요청 시 발동
void App::blockFriend(Member* mb)
{
	string id;
	Friend temp;

	cout << "\t ID : ";
	cin >> id;
	temp.SetFriendID(id);
	
	if (mb->getFriendlist()->Getitem(temp) != NULL) // 요청한 클라이언트의 친구목록에 차단 할 친구가 있다면
	{
		mb->getFriendlist()->Getitem(temp)->data.SetInterception(0);
		cout << "\t SUCCESS\n";
	}
	else   // 친구가 아닌데 차단 하려고 하면
		cout << "\t not found..\n";
}

// 클라이언트가 친구 즐겨 찾기 요청을 하였을 때 
void App::setFavorites(Member *mb)
{
	string id;
	Friend temp;

	cout << "\t ID : ";
	cin >> id;
	temp.SetFriendID(id);

	if (mb->getFriendlist()->Getitem(temp) != NULL) // 내 친구 관계가 맞으면
	{
		mb->getFriendlist()->Getitem(temp)->data.SetInterception(2);
		cout << "\t SUCCESS\n";
	}
	else
		cout << "\t not found..\n";
}

// 클라이언트가 친구 삭제를 요청 해왔을 때
void App::deleteFriend(Member* mb)
{
	string id;
	Friend temp;

	cout << "\t ID : ";
	cin >> id;
	temp.SetFriendID(id);

	if (mb->getFriendlist()->Get(temp)) // 친구 관계이면
	{
		mb->getFriendlist()->Delete(temp);
		cout << "\t SUCCESS\n";
	}
	else
		cout << "\t not found..\n";
}

// 파라미터로 넘어온 클라이언트와 멤버로 채팅방 생성
void App::createChatRoom(Member *mb, Client* cn)
{
	ChattingRoom newRoom;

	mb->DisplayFriendList();

	Friend temp;
	temp.SetFriendID(mb->getID()); // 생성 될 채팅방에 본인 1번 우선 넣고
	temp.SetFriendName(mb->getName());
	newRoom.getUserList()->Add(temp);


	cout << "\n\t  < 0. End input >";
	while (1)
	{
		string id;

		cout << "\n\n\t friend ID : ";
		cin >> id;


		if (id == "0")
			break;
		temp.SetFriendID(id);
		if (!newRoom.getUserList()->Get(temp) && mb->getFriendlist()->Get(temp)) // 생성 되는 방에 중복, 친구 관계 예외 처리
		{
			newRoom.getUserList()->Add(temp);
			cout << "\t Add Seccuss\n";
		}
		else
			cout << "\t Invalid value\n";
	}
	string name = "";

	newRoom.getUserList()->ResetList();	// 이름 설정
	for (int i = 0; i < newRoom.getUserList()->GetLength(); i++)
	{ // 길이 만큼 돌면서 채팅방 이름을 유저 이름의 나열로 설정
		newRoom.getUserList()->GetNextItem(temp);
		name += temp.GetFriendName();
		if (i < newRoom.getUserList()->GetLength() - 1) 
			name += ",";
	}
	newRoom.setChttingRoomName(name);

	int _key = temp.hash_function(mb->getID()); // 생성되면
	if (NULL != chattingList.FindHashData(_key, newRoom)) // 이미 존재하는 방이면
	{
		cout << "\t Exists Room\n";
		pause;
		return;
	}

	//else if (newRoom.getUserList()->GetLength() == 1) 개인 방을 없애려면 주석 부활
	//	return;

	int key;
	newRoom.getUserList()->ResetList();
	for (int i = 0; i < newRoom.getUserList()->GetLength(); i++) // 새로 생성 된 채팅방을 뿌린다.
	{
		newRoom.getUserList()->GetNextItem(temp);
		key = temp.hash_function(temp.GetFriendID());
		chattingList.AddHashData(key, newRoom);
	}

}

// 클라이언트의 채팅 방 목록을 갱신해준다.
void App::DisplayChatroom(Member* mb, Client* cur)
{
	Friend temp;
	temp.SetFriendID(mb->getID());

	int key = hash_function(mb->getID());

	Node<ChattingRoom>* m_temp = chattingList[key]; // 새로운 노드는 로그인 유저의 해시 키값이 놓인 레이블
	if (m_temp != NULL) // 안 비고
	{
		while (m_temp->hash_Next != NULL) // 넥스트 해시가 없을때까지 탐색
		{
			if (m_temp->data.getUserList()->Get(temp))
			{
				cur->addCattingList(m_temp->data);
			}
			m_temp = m_temp->hash_Next;
		}

		if (m_temp->data.getUserList()->Get(temp)) // 마지막 항목
		{
			cur->addCattingList(m_temp->data);
		}
	}
}

// 클라이언트가 sendmessage 메세지에 메세지 전송 요청 목록을 읽어와 전달
void App::sentToMessage()
{
	string chat_naem;
	string name, id;

	Friend reicever;
	string content;
	Message sendmg;
	ChattingRoom chatroom;
	int key;

	ifstream ifs("sendmessage.txt");

	ifs >> chat_naem >> id >> name >> content;
	sendmg.setSentID(id);
	sendmg.setSentName(name);
	sendmg.setContent(content);
	chatroom.setChttingRoomName(chat_naem); // 채팅방 이름 셋

	while (!ifs.eof())
	{	
		ifs >> id;
		if (ifs.fail()) // 파일이 끝이면 빠져나간다
			break;		reicever.SetFriendID(id);
		key = reicever.hash_function(reicever.GetFriendID()); // 해시 키값에 해당하는
		chattingList.FindHashData(key, chatroom)->data.getMessageList()->Add(sendmg); // 채팅방에 전송
	}
	ifs.close();

	ofstream ofs("serverLog.txt", std::ios_base::out | std::ios_base::app);
	ofs << sendmg.getSenderName() << "의 메세지 전송 완료.\n";
	ofs.close();
}

// 클라이언트가 메세지 삭제 요청을 했을때 텍스트를 읽어와 요청 처리
void App::deleteMessage()
{
	string chat_naem;
	string id;
	int index;
	ChattingRoom chatroom;
	int key;
	Friend temp;

	ifstream ifs("delmessage.txt");

	ifs >> chat_naem >> id >> index;;
	chatroom.setChttingRoomName(chat_naem);
	temp.SetFriendID(id);

	key = temp.hash_function(temp.GetFriendID()); // 해당 해시 키값
	chattingList.FindHashData(key, chatroom)->data.getMessageList()->DeletebyIndex(index); //삭제
	ifs.close();

	ofstream ofs("serverLog.txt", std::ios_base::out | std::ios_base::app);
	ofs << id << "(ID)의 메세지 삭제 완료.\n";
	ofs.close();
}

// 서버의 기록을 디스플레이 한다
void App::printServerLog()
{
	string a[4];
	ifstream ifs("serverLog.txt");

	while (!ifs.eof())
	{
		for (int i = 0; i < 4; i++)
		{
			ifs >> a[i];
			if (ifs.fail())
				break;
			cout << a[i] << " ";
			if (i == 3)
				cout << "\n";
		}
	}
	pause;
	cls;

	ifs.close();
}

// 해시 함수
int App::hash_function(string temp) // 해시 키 값이 될 변수는 user ID
{
	int prime[5] = { 6911, 7433, 2111, 419, 199 }; // 각 자리마다 가중치를 달리해 중복을 극소화 시킨다
	int hash_key = 0;

	int lenth = temp.size();
	for (int i = 0; i < lenth; i++) // 스트링을 아스키 코드값으로 변환하여 int형 변수로
	{
		if (i < 5)
			hash_key += (int)temp[i] * prime[i];
		else
			hash_key += (int)temp[i]; 
	}
	return hash_key % 100000; // 해시 키 값 범위 0 ~ 999999
}