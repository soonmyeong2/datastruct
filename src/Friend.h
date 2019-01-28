#pragma once

class Friend
{
public:
	// ������ ģ�� ���¸� 1(����)�� ���Ѵ�.
	Friend() { Interception = 1; }

	// ���������
	Friend(const Friend& fr) {
		ID = fr.ID;
		Name = fr.Name;
		Interception = fr.Interception;
	}

	~Friend() {}
	
	// ģ���� id�� set 
	void SetFriendID(string id) { ID = id; }

	// ģ���� �̸��� set
	void SetFriendName(string name) { Name = name; }

	// ģ���� id�� get
	string GetFriendID() { return ID; }

	// ���� ģ���� ���¸� set
	void SetInterception(int check) { Interception = check; }

	// ���� ģ���� ���¸� get
	int GetInterception() { return Interception; }

	// ���� ģ���� �̸��� get
	string GetFriendName() { return Name; }


	/**
	*	@brief	������ ���۷�����. ���̵� ������ ���Ѵ�.
	*	@post	�޼��� ������ �־���Ѵ�.
	*	@return	���̸� 1
	*/
	bool operator > (Friend& F) { return (ID > F.ID); }
	bool operator < (Friend& F) { return (ID < F.ID); }
	bool operator == (Friend& F) { return (ID == F.ID); }


	// �ؽ� ���
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
	string ID;		//ģ���� ���̵�
	string Name; // ģ���� �̸�
	int Interception; // ģ�� state �÷��� (0. ���� / 1. ���� / 2. ���ã��)
};