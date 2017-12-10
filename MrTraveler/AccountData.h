#pragma once
#include <vector>
struct AccountInfo
{
	int year;
	int month;
	int day;
	CString content;
	int money;
};
class AccountData
{
private:
	AccountData();
	static AccountData * instance;
	static bool instanceFlag;
public:
	std::vector<AccountInfo> accountList;
public:
	~AccountData();
	std::vector<AccountInfo> findAccount(int year, int month);
	std::vector<AccountInfo> findAccount(int year, int month, int day);
	static AccountData * GetInstance();
	void eraseAccount(int year, int month, int day);

};

