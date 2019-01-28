#include "App.h"

App* App::server = nullptr; // instance �ʱ�ȭ

//�̱��� ������ ���� �Լ�. �����ڸ� ����� �����ϰ� �ϳ��� �ν��Ͻ��� ����� �Ѵ�.
App* App::getServer()
{
	if (server == nullptr) //  �ν��Ͻ��� ����Ű�� ���� ���ٸ�
	{
		App* newServer = new App(); // ���ο� �ν��Ͻ� ����
		server = newServer; // �ν��Ͻ��� command;

		return server; // ����
	}
	else
	{
		return server; // ����Ű�� ���� �ִٸ� ���� �ν��Ͻ� ��ȯ
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
			Login(); // �α���
			break;
		case 2:
			Join(); // ȸ�� ����
			break;
		case 3:
			printServerLog(); // ������ ó���� ��û ���
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

// ����ڿ��� ������ �Է¹ް� �ش� ������ Ŭ���̾�Ʈ ����
bool App::Login()
{
	cls;
	cout << "\n\n";
	
	Member m_temp;
	Member *temp;
	m_temp.setIDbyKB();
	m_temp.setPWbyKB();
	
	if (userList.Retrieve(m_temp,temp)) // ���̵�� ����� ã���� �ְ� 
	{
		if (m_temp.getPW() == temp->getPW()) // ����� ���ٸ�
		{
			Client *m_Clinet = new Client; // Ŭ���̾�Ʈ Ŭ���� ����
			m_Clinet->setCurruntUser(temp); // ���� set�ϰ�
			cls;
			m_Clinet->ClientMenu(); // Ŭ���̾�Ʈ �޴� ����
		
			delete m_Clinet; // Ŭ���̾�Ʈ ����� �޸� �Ҵ� ����
		}
		else
			cout << "\n\t  Password error..\n";
	}
	else
	{
		cout << "\n\tNo matching member information.." << endl; // ���н�
	}

	return false;
}

// ������ �Է¹޾� ȸ�� ���� ����
void App::Join()
{
	cls;

	cout << "\n\n";

	Member newMember;
	newMember.setUserbyKB(); // ���ο� ��� ���� set

	if (userList.insert(newMember)) // ������ ID �������� �ʴٸ�
		cout << "\n\t Seccess ! \n";
	else
		cout << "\n\t ID Duplication..\n";

	pause;
	cls;
}

// �Ķ���ͷ� �Ѿ�� ȸ�� ���� ���
void App::secession(Member* deleteMember)
{
	Member* del;

	userList.Retrieve(*deleteMember, del); // �Ķ���ͷ� �Ѿ�� ��带 ã�Ƽ�
	userList.erase(*del); // �����ع���
}

// �Ķ���ͷ� �Ѿ�� ȸ�� ���� ����
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
			re_member->setNamebyKB(); // �̸� ����
			break;
		case 2:
			re_member->setAreabyKB(); // ���� ����
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

// ���� �о����
void App::load_File()
{
	ifstream ifs("user.txt"); // user.txt�� ���ϴ�
	string  userId, pw, username, area;
	while (!ifs.eof()) // ������ ����������
	{
		Member member; // m_List�� �� ��� ��ü �ϳ� �����ϰ�

		ifs >> userId >> pw >> username >> area; // ������� �ڷḦ �а�
		if (ifs.fail()) // �����б⿡ �����ϸ� ���Ϲ� ����������.
			break;
		member.setID(userId); // ��� ��ü�� ������ ä���
		member.setPW(pw);
		member.setName(username);
		member.setArea(area);

		userList.insert(member);
	}
	ifs.close(); // ���� �ݱ�


	////////////////////////////////////////////

	ifstream ifs2("friend.txt"); // friend ������ ����
	while (!ifs2.eof()) // ������ ����������
	{
		string userId;
		int friendsCnt;
		string F_id, F_name;
		ifs2 >> userId >> friendsCnt; // ���� ���̵�, ģ�� ���� ī��Ʈ�ϰ�
		if (ifs2.fail()) // ������ ���̸� ����������
			break;

		Friend temp; // friendList�� �� ��ü �����ϰ�
		Member m_temp; // m_List�� ���� �ӽ� ��ü
		Member *user;
		m_temp.setID(userId);
		
		for (int i = 0; i < friendsCnt; i++) // ģ�� �� ��ŭ �����鼭
		{
			ifs2 >> F_id >> F_name; // ģ�� ������ �о����
			temp.SetFriendID(F_id); // �ӽ� FriendList�� �����Ѵ�
			temp.SetFriendName(F_name);

			userList.Retrieve(m_temp, user);
			user->addFriend(temp);
		}
	}
	ifs2.close();

	////////////////////////////////////

	ifstream ifs3("chatting.txt"); // message ���� ����

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
		
		if (ifs3.fail()) // ������ ���̸� ����������
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
		} // �ϳ��� ä�ù� ��ü set�Ϸ�

		/* �ؽ� ������� ������ �����Ǵ� �ؽ� �ε����� ä�ù� ���� �ٽ� */
		int key;
		Friend _temp;
		chat_temp.getUserList()->ResetList();
		for (int i = 0; i < chat_temp.getUserList()->GetLength(); i++)
		{
			chat_temp.getUserList()->GetNextItem(_temp);
			key = _temp.hash_function(_temp.GetFriendID()); // Ű ���� ������ ���̵�� �Ѵ�.
			chattingList.AddHashData(key, chat_temp); // �ؽ� ���̺� ä�� �� ����
		}
	}
	ifs3.close(); // ���� �ݱ�
}

// Ŭ���̾�Ʈ�� ģ�� �߰��ϴ� ��û�� ���������� ����Ǵ� �Լ�
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
			recommandMember(mb); // ��õ ģ�� ���
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
				findSearchbyName(userList.root(), name); // �̸����� ã��

				cout << "\n\n\t 1. Add friends\n";
				cout << "\t 0. Back\n\n\t -> ";
				cin >> m_Command;
			}
			else if(m_Command == 2) // ���̵�� ã��
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
				addFriend(mb); // ģ�� �߰�
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

// �̸����� ģ�� ã��
void App::findSearchbyName(RedBlackNode<Member>* node, string name)
{
	if (node == nullptr)
		return;
	else // ����� ȣ��� Ʈ���� ��� �κ��� Ž���ؾ� �Ѵ�.
	{
		if (node != nullptr && node->v_.getName() == name)
		{
			cout << endl << node->v_;
		}
		findSearchbyName(node->left_, name);
		findSearchbyName(node->right_, name);
	}
}

// Ŭ���̾�Ʈ�� ģ�� �߰� ��û ó����
bool App::addFriend(Member* mb) 
{
	string temp;
	cout << "\t Friend ID to add : ";
	cin >> temp;

	Member compare;
	compare.setID(temp);
	Member* m_temp;
	Friend add_fd;

	if (userList.Retrieve(compare, m_temp)) // ȸ����Ͽ� add�Ϸ��� ģ���� �ְ�
	{
		add_fd.SetFriendID(m_temp->getID());
		if(!mb->findFriend(add_fd) && mb->getID() != temp)  // �� ģ���� �ƴϰ� ���� �ƴϸ�
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

// ģ�� ��õ ��� �Լ�
void App::recommandMember(Member* mb)
{

	Member data, friData;	//Get�Լ��� MemberType, a�� �Ķ���ͷ� ���� ������ ���Ƿ� ������ش�.
	string temp;
	Friend temp1, fritemp;
	bool exist = false;
	mb->getFriendlist()->ResetList(); // ���� ģ�� ����� ������ Ŀ���� �ʱ�ȭ ��Ű��

	if (mb->getFriendlist()->GetLength() == 0) // ģ�� ���� 0�̸� ����ó��
	{
		cout << "\n\n\tNo Recommend friends.";
		return;
	}
	for (int i = 0; i < mb->getFriendlist()->GetLength(); i++) // ģ�� ����ŭ ���鼭
	{
		mb->getFriendlist()->GetNextItem(temp1); // ���������� ģ���� ���̵� �ް�
		data.setID(temp1.GetFriendID()); // Member�� ���� data�� ID�� �ִ´�.
		userList.search(data); // data�� ������ ��ü�� �ǰ�
		data.getFriendlist()->ResetList(); // ��ü�� ģ�� �迭�� ����
		for (int j = 0; j < data.getFriendlist()->GetLength(); j++) // ģ���� ģ���� ��ŭ ���鼭
		{
			data.getFriendlist()->GetNextItem(fritemp); // ���������� ģ���� ģ�������� fritemp�� �ְ�
			friData.setID(fritemp.GetFriendID()); // fridata�� ���̵� ���
			userList.search(friData); // �� ��ü�� ������ ��´�(ģ���� ģ���� ������ ����)
			recommendationList.Add(friData); // �� ������ ��õģ�� ��Ͽ� �ִ´�.
		}
	}
	bool check = false; // �̹� ģ���������� üũ�ϴ� ����
	mb->getFriendlist()->ResetList();  // �α��� ������ ģ�� ��� Ŀ���� �ʱ�ȭ�Ѵ�.
	recommendationList.ResetList(); // ��õģ����� Ŀ���� �ʱ�ȭ �Ѵ�.
	cout << "\n\n";
	for (int i = 0; i < recommendationList.GetLength(); i++) // ģ����ϸ���Ʈ�� ���鼭
	{
		recommendationList.GetNextItem(data); // ��õģ�� ����� ���������� data�� ���
		for (int j = 0; j < mb->getFriendlist()->GetLength(); j++) // �α����� ������ ģ�� ����� ���鼭
		{
			mb->getFriendlist()->GetNextItem(temp1); // temp1�� �α��� ������ ģ���� �ִ´�.
			if (temp1.GetFriendID() == data.getID()) // ���� ��õģ���� �̹� ģ�����
				check = true; // �̹� ģ����� ������ true;
		}
		if (data.getID() != mb->getID() && check == false) // ���� ģ�����谡�ƴϰ� �α����� ������� ���̵� �ƴ϶��
		{
			cout << data; // ��õģ������� ����Ѵ�.
			exist = true;
		}
		mb->getFriendlist()->ResetList(); // �� �� �ٽ� for�� �������� ���� �������� ��
		check = false; // ģ���������� üũ�ϴ� ������ �ʱ�ȭ ���ش�.
	}
	if (!exist)
	{
		cout << "\t No friends recommended\n";
	}
	recommendationList.MakeEmpty(); // �� �� ģ�� ��� �޸� ���� ��õģ�� ����� �ſ� �������̹Ƿ� �ҷ��ö����� ���� �˻��ϰ� �޸𸮿��� �������ش�.


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

// Ŭ���̾�Ʈ�� ģ�� ���� ��û �� �ߵ�
void App::blockFriend(Member* mb)
{
	string id;
	Friend temp;

	cout << "\t ID : ";
	cin >> id;
	temp.SetFriendID(id);
	
	if (mb->getFriendlist()->Getitem(temp) != NULL) // ��û�� Ŭ���̾�Ʈ�� ģ����Ͽ� ���� �� ģ���� �ִٸ�
	{
		mb->getFriendlist()->Getitem(temp)->data.SetInterception(0);
		cout << "\t SUCCESS\n";
	}
	else   // ģ���� �ƴѵ� ���� �Ϸ��� �ϸ�
		cout << "\t not found..\n";
}

// Ŭ���̾�Ʈ�� ģ�� ��� ã�� ��û�� �Ͽ��� �� 
void App::setFavorites(Member *mb)
{
	string id;
	Friend temp;

	cout << "\t ID : ";
	cin >> id;
	temp.SetFriendID(id);

	if (mb->getFriendlist()->Getitem(temp) != NULL) // �� ģ�� ���谡 ������
	{
		mb->getFriendlist()->Getitem(temp)->data.SetInterception(2);
		cout << "\t SUCCESS\n";
	}
	else
		cout << "\t not found..\n";
}

// Ŭ���̾�Ʈ�� ģ�� ������ ��û �ؿ��� ��
void App::deleteFriend(Member* mb)
{
	string id;
	Friend temp;

	cout << "\t ID : ";
	cin >> id;
	temp.SetFriendID(id);

	if (mb->getFriendlist()->Get(temp)) // ģ�� �����̸�
	{
		mb->getFriendlist()->Delete(temp);
		cout << "\t SUCCESS\n";
	}
	else
		cout << "\t not found..\n";
}

// �Ķ���ͷ� �Ѿ�� Ŭ���̾�Ʈ�� ����� ä�ù� ����
void App::createChatRoom(Member *mb, Client* cn)
{
	ChattingRoom newRoom;

	mb->DisplayFriendList();

	Friend temp;
	temp.SetFriendID(mb->getID()); // ���� �� ä�ù濡 ���� 1�� �켱 �ְ�
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
		if (!newRoom.getUserList()->Get(temp) && mb->getFriendlist()->Get(temp)) // ���� �Ǵ� �濡 �ߺ�, ģ�� ���� ���� ó��
		{
			newRoom.getUserList()->Add(temp);
			cout << "\t Add Seccuss\n";
		}
		else
			cout << "\t Invalid value\n";
	}
	string name = "";

	newRoom.getUserList()->ResetList();	// �̸� ����
	for (int i = 0; i < newRoom.getUserList()->GetLength(); i++)
	{ // ���� ��ŭ ���鼭 ä�ù� �̸��� ���� �̸��� ������ ����
		newRoom.getUserList()->GetNextItem(temp);
		name += temp.GetFriendName();
		if (i < newRoom.getUserList()->GetLength() - 1) 
			name += ",";
	}
	newRoom.setChttingRoomName(name);

	int _key = temp.hash_function(mb->getID()); // �����Ǹ�
	if (NULL != chattingList.FindHashData(_key, newRoom)) // �̹� �����ϴ� ���̸�
	{
		cout << "\t Exists Room\n";
		pause;
		return;
	}

	//else if (newRoom.getUserList()->GetLength() == 1) ���� ���� ���ַ��� �ּ� ��Ȱ
	//	return;

	int key;
	newRoom.getUserList()->ResetList();
	for (int i = 0; i < newRoom.getUserList()->GetLength(); i++) // ���� ���� �� ä�ù��� �Ѹ���.
	{
		newRoom.getUserList()->GetNextItem(temp);
		key = temp.hash_function(temp.GetFriendID());
		chattingList.AddHashData(key, newRoom);
	}

}

// Ŭ���̾�Ʈ�� ä�� �� ����� �������ش�.
void App::DisplayChatroom(Member* mb, Client* cur)
{
	Friend temp;
	temp.SetFriendID(mb->getID());

	int key = hash_function(mb->getID());

	Node<ChattingRoom>* m_temp = chattingList[key]; // ���ο� ���� �α��� ������ �ؽ� Ű���� ���� ���̺�
	if (m_temp != NULL) // �� ���
	{
		while (m_temp->hash_Next != NULL) // �ؽ�Ʈ �ؽð� ���������� Ž��
		{
			if (m_temp->data.getUserList()->Get(temp))
			{
				cur->addCattingList(m_temp->data);
			}
			m_temp = m_temp->hash_Next;
		}

		if (m_temp->data.getUserList()->Get(temp)) // ������ �׸�
		{
			cur->addCattingList(m_temp->data);
		}
	}
}

// Ŭ���̾�Ʈ�� sendmessage �޼����� �޼��� ���� ��û ����� �о�� ����
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
	chatroom.setChttingRoomName(chat_naem); // ä�ù� �̸� ��

	while (!ifs.eof())
	{	
		ifs >> id;
		if (ifs.fail()) // ������ ���̸� ����������
			break;		reicever.SetFriendID(id);
		key = reicever.hash_function(reicever.GetFriendID()); // �ؽ� Ű���� �ش��ϴ�
		chattingList.FindHashData(key, chatroom)->data.getMessageList()->Add(sendmg); // ä�ù濡 ����
	}
	ifs.close();

	ofstream ofs("serverLog.txt", std::ios_base::out | std::ios_base::app);
	ofs << sendmg.getSenderName() << "�� �޼��� ���� �Ϸ�.\n";
	ofs.close();
}

// Ŭ���̾�Ʈ�� �޼��� ���� ��û�� ������ �ؽ�Ʈ�� �о�� ��û ó��
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

	key = temp.hash_function(temp.GetFriendID()); // �ش� �ؽ� Ű��
	chattingList.FindHashData(key, chatroom)->data.getMessageList()->DeletebyIndex(index); //����
	ifs.close();

	ofstream ofs("serverLog.txt", std::ios_base::out | std::ios_base::app);
	ofs << id << "(ID)�� �޼��� ���� �Ϸ�.\n";
	ofs.close();
}

// ������ ����� ���÷��� �Ѵ�
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

// �ؽ� �Լ�
int App::hash_function(string temp) // �ؽ� Ű ���� �� ������ user ID
{
	int prime[5] = { 6911, 7433, 2111, 419, 199 }; // �� �ڸ����� ����ġ�� �޸��� �ߺ��� �ؼ�ȭ ��Ų��
	int hash_key = 0;

	int lenth = temp.size();
	for (int i = 0; i < lenth; i++) // ��Ʈ���� �ƽ�Ű �ڵ尪���� ��ȯ�Ͽ� int�� ������
	{
		if (i < 5)
			hash_key += (int)temp[i] * prime[i];
		else
			hash_key += (int)temp[i]; 
	}
	return hash_key % 100000; // �ؽ� Ű �� ���� 0 ~ 999999
}