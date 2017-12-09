#include "stdafx.h"
#include "AccountData.h"

AccountData* AccountData::instance = NULL;
bool AccountData::instanceFlag = false;
AccountData::AccountData()
{

}
AccountData::~AccountData()
{
}
AccountData* AccountData::GetInstance()
{
	if (!instanceFlag)
		instance = new AccountData();
	return instance;
}
std::vector<AccountInfo> AccountData::findAccount(int year, int month)
{
	std::vector<AccountInfo> r;
	for (int i = 0; i < accountList.size(); i++)
	{
		AccountInfo info = accountList[i];
		if (info.year == year && info.month == month)
			r.push_back(info);
	}
	return r;
}
std::vector<AccountInfo> AccountData::findAccount(int year, int month,int day)
{
	std::vector<AccountInfo> r;
	for (int i = 0; i < accountList.size(); i++)
	{
		AccountInfo info = accountList[i];
		if (info.year == year && info.month == month && info.day == day)
			r.push_back(info);
	}
	return r;
}