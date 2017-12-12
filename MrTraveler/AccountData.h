#pragma once
#include <vector>
struct AccountInfo
{
	int year;	//년
	int month;	//월
	int day;	//일
	CString content; //내용
	int money;	//돈(-이면 지출	+ 수입)
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
	std::vector<AccountInfo> findAccount(int year, int month);	//날짜로 AccountInfo 찾는 함수
	std::vector<AccountInfo> findAccount(int year, int month, int day);	
	static AccountData * GetInstance();
	void eraseAccount(int year, int month, int day);

};

