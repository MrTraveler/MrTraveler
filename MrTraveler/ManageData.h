#pragma once
#pragma warning(disable:4996)
class PlanData;
class TodoData;
class AccountData;
class CManageData
{
private:
	CManageData();
	static CManageData* instance;	//싱글톤 Instnace 사용방법  TodoData::GetInstance() 로 얻어오기
	static bool instanceFlag;
public:
	~CManageData();
	int RoadData();
	int SaveData();
	PlanData* Plan;
	TodoData* Todo;
	AccountData* Account;
	static CManageData *GetInstance();
	//string MakeString(CString str);
};

