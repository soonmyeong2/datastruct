#pragma once

class Friend
{
public:
	// 생성자 친구 상태를 1(평상시)로 셋한다.
	Friend() { Interception = 1; }

	// 복사생성자
	Friend(const Friend& fr) {
		ID = fr.ID;
		Name = fr.Name;
		Interception = fr.Interception;
	}

	~Friend() {}
	
	// 친구의 id를 set 
	void SetFriendID(string id) { ID = id; }

	// 친구의 이름을 set
	void SetFriendName(string name) { Name = name; }

	// 친구의 id를 get
	string GetFriendID() { return ID; }

	// 현재 친구의 상태를 set
	void SetInterception(int check) { Interception = check; }

	// 현재 친구의 상태를 get
	int GetInterception() { return Interception; }

	// 현재 친구의 이름을 get
	string GetFriendName() { return Name; }


	/**
	*	@brief	연산자 오퍼레이터. 아이디 값으로 비교한다.
	*	@post	메세지 내용이 있어야한다.
	*	@return	참이면 1
	*/
	bool operator > (Friend& F) { return (ID > F.ID); }
	bool operator < (Friend& F) { return (ID < F.ID); }
	bool operator == (Friend& F) { return (ID == F.ID); }


	// 해시 펑션
	int hash_function(string temp)
	{
		int prime[5] = { 6911, 7433, 2111, 419, 199 };
		int hash_key = 0;

		int lenth = temp.size();
		for (int i = 0; i < lenth; i++)
		{
			if (i < 5)
				hash_key += (int)temp[i] * prime[i];
			else
				hash_key += (int)temp[i];
		}
		return hash_key % 100000;
	}

private:
	string ID;		//친구의 아이디
	string Name; // 친구의 이름
	int Interception; // 친구 state 플래그 (0. 차단 / 1. 평상시 / 2. 즐겨찾기)
};