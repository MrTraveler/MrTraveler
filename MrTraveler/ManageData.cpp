#include "stdafx.h"
#include "ManageData.h"
#include "PlanData.h"
#include "TodoData.h"
#include "AccountData.h"
#include "json/json.h"
bool CManageData::instanceFlag = false;
CManageData* CManageData::instance = NULL;
CManageData::CManageData()
{
	Plan = PlanData::GetInstance();
	Todo = TodoData::GetInstance();
	Account = AccountData::GetInstance();
}


CManageData::~CManageData()
{
}



int CManageData::RoadData()
{
	int PlanListSize, TodoListSize, AccountListSize;
	PlanListSize = Plan->planList.size();
	TodoListSize = Todo->todoList.size();
	AccountListSize = Account->accountList.size();
	//시작, 종료일 추가
	// plan리스트 추가
	for (int i = 0; i < PlanListSize; i++) {

	}
	//todo리스트 추가
	for (int i = 0; i < TodoListSize; i++) {

	}
	//account리스트 추가
	for (int i = 0; i < AccountListSize; i++) {

	}
	return 0;
}


int CManageData::SaveData()
{
	int PlanListSize,TodoListSize,AccountListSize;
	PlanListSize = Plan->planList.size();
	TodoListSize = Todo->todoList.size();
	AccountListSize = Account->accountList.size();
	Json::Value root;
	Json::Value day;
	Json::Value cnum;
	Json::Value clist;
	day["Start"] = std::string(CT2CA(Plan->startDate.Format(_T("%Y-%m-%d %H:%M:%S"))));
	day["End"]= std::string(CT2CA(Plan->endDate.Format(_T("%Y-%m-%d %H:%M:%S"))));
	root["day"] = day;
	//시작, 종료일 추가
	// plan리스트 추가
	Json::Value PlanList;
	for (int i = 0; i < PlanListSize; i++) {
		Json::Value list;
		list["from"]= std::string(CT2CA(Plan->planList.at(i).from.Format(_T("%Y-%m-%d %H:%M:%S"))));
		list["to"]= std::string(CT2CA(Plan->planList.at(i).to.Format(_T("%Y-%m-%d %H:%M:%S"))));
		list["title"]= std::string(CT2CA(Plan->planList.at(i).title));
		list["content"]= std::string(CT2CA(Plan->planList.at(i).content));
		list["budget"]= Plan->planList.at(i).budget;
		PlanList.append(list);
	}
	//todo리스트 추가
	Json::Value TodoList;

	for (int i = 0; i < TodoListSize; i++) {
		Json::Value list;
		list["icon"] = Todo->todoList.at(i).icon;
		list["title"] = std::string(CT2CA(Todo->todoList.at(i).title));
		int dolist = Todo->todoList.at(i).list.size();
		cnum.append(dolist);
		if (dolist == 0)clist.append("");
		for (int j = 0; j < dolist; j++) {
			clist.append(std::string(CT2CA(Todo->todoList.at(i).list.at(j))));
		}
		TodoList.append(list);
	}
	//account리스트 추가
	Json::Value AccountList;

	for (int i = 0; i < AccountListSize; i++) {
		Json::Value list;
		list["year"] = Account->accountList.at(i).year;
		list["month"] = Account->accountList.at(i).month;
		list["day"] = Account->accountList.at(i).day;
		list["content"] = std::string(CT2CA(Account->accountList.at(i).content));
		list["money"] = Account->accountList.at(i).money;
		AccountList.append(list);
	}
	Json::Value size;
	size["Plan"] = PlanListSize;
	size["Account"] = AccountListSize;
	size["Todo"] = TodoListSize;

	root["size"]=size;
	root["Plan"]=PlanList;
	root["Todo"]=TodoList;
	root["cnum"] = cnum;
	root["clist"] = clist;
	root["Account"]=AccountList;

	Json::StyledWriter writer;
	std::string strJson = writer.write(root);

	errno_t err;
	FILE* JSonFile = NULL;

	//생성된 Json 정보들을 파일에 쓰는 부분입니다.
	err = fopen_s(&JSonFile, "MrTraveler.mt", "wb");

	if (err == 0) //정상적으로 파일이 생성된 경우
	{
		fputs(strJson.c_str(), JSonFile);
		fclose(JSonFile);
	}


	return 0;
}


CManageData * CManageData::GetInstance() 
{
		if (!instance)
		{
			instance = new CManageData();
			instanceFlag = true;
		}
		return CManageData::instance;
}

