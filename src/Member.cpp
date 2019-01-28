#include "Member.h"

// 친구 리스트를 출력
void Member::DisplayFriendList()
{
	cout << "\n\n\n";
	cout << "\t         FRIEND LIST       \n";
	cout << "\t---------------------------- " << endl << endl;

	int length = friendList.GetLength();

	if (length == 0) // 친구 없으면
		cout << "\t No Friends..\n";
	else
	{
		Friend temp;

		friendList.ResetList();  // 즐겨찾기 된 친구 출력
		for (int i = 0; i < length; i++)
		{
			friendList.GetNextItem(temp);
			if (temp.GetInterception() == 2)
			{
				cout << "\t " << temp.GetFriendName() << '(' << temp.GetFriendID() << ")  ★ " << endl;
			}
		}
		cout << "\n";
		friendList.ResetList(); // 모든 친구 출력
		for (int i = 0; i < length; i++)
		{
			friendList.GetNextItem(temp);
			if (!temp.GetInterception()) // 차단친구는 빨간색으로 출력
			{
				textcolor(RED);
			}
			cout << "\t " << temp.GetFriendName() << '(' << temp.GetFriendID()<<')' << endl;
			textcolor(LIGHTGRAY);
		}
	}
}

// 콘솔 글씨 색상을 바꾸는 핸들러
void Member::textcolor(int color) 
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}