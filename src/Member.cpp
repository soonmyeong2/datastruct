#include "Member.h"

// ģ�� ����Ʈ�� ���
void Member::DisplayFriendList()
{
	cout << "\n\n\n";
	cout << "\t         FRIEND LIST       \n";
	cout << "\t---------------------------- " << endl << endl;

	int length = friendList.GetLength();

	if (length == 0) // ģ�� ������
		cout << "\t No Friends..\n";
	else
	{
		Friend temp;

		friendList.ResetList();  // ���ã�� �� ģ�� ���
		for (int i = 0; i < length; i++)
		{
			friendList.GetNextItem(temp);
			if (temp.GetInterception() == 2)
			{
				cout << "\t " << temp.GetFriendName() << '(' << temp.GetFriendID() << ")  �� " << endl;
			}
		}
		cout << "\n";
		friendList.ResetList(); // ��� ģ�� ���
		for (int i = 0; i < length; i++)
		{
			friendList.GetNextItem(temp);
			if (!temp.GetInterception()) // ����ģ���� ���������� ���
			{
				textcolor(RED);
			}
			cout << "\t " << temp.GetFriendName() << '(' << temp.GetFriendID()<<')' << endl;
			textcolor(LIGHTGRAY);
		}
	}
}

// �ܼ� �۾� ������ �ٲٴ� �ڵ鷯
void Member::textcolor(int color) 
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}