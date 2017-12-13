#include <afxwin.h>
#include "stdafx.h"
#include "ManageData.h"
#include "PlanData.h"
#include "TodoData.h"
#include "AccountData.h"
#include "json/json.h"
#include <iostream>
#include <fstream>
#include<stdlib.h>
#include <string.h>
bool CManageData::instanceFlag = false;
CManageData* CManageData::instance = NULL;
CManageData::CManageData()
{
	d_Plan = PlanData::GetInstance();
	d_Todo = TodoData::GetInstance();
	d_Account = AccountData::GetInstance();
}


CManageData::~CManageData()
{
}



int CManageData::RoadData()
{
	TCHAR fileFilter[] = _T("MrTraveler����(*.mt)|*.mt");
	TCHAR name[] = _T("MrTraveler.mt");
	TCHAR Ext[] = _T("mt");
	CFileDialog dlg(TRUE, Ext, name, OFN_READONLY, fileFilter);
	if (IDOK == dlg.DoModal()) {
		std::ifstream stream;
		stream.open(dlg.GetPathName());
		Json::Value root;
		stream >> root;
		Json::Value Size = root["size"];
		Json::Value day = root["day"];
		Json::Value clist = root["clist"];
		Json::Value cnum = root["cnum"];
		{
			const char * str = day["Start"].asCString();
			char x[20];
			strcpy(x, str);
			int nYear = atoi(strtok(x, "|"));
			int nMon = atoi(strtok(NULL, "|"));
			int nDay = atoi(strtok(NULL, "|"));
			int nHour = atoi(strtok(NULL, "|"));
			int nMin = atoi(strtok(NULL, "|"));
			int nSec = atoi(strtok(NULL, "|"));
			CTime start(nYear, nMon, nDay, nHour, nMin, nSec);
			d_Plan->startDate = start;
		}
		{
			const char * str = day["End"].asCString();
			char x[20];
			strcpy(x, str);
			int nYear = atoi(strtok(x, "|"));
			int nMon = atoi(strtok(NULL, "|"));
			int nDay = atoi(strtok(NULL, "|"));
			int nHour = atoi(strtok(NULL, "|"));
			int nMin = atoi(strtok(NULL, "|"));
			int nSec = atoi(strtok(NULL, "|"));
			CTime End(nYear, nMon, nDay, nHour, nMin, nSec);
			d_Plan->endDate = End;
		}
		Json::Value plan = root["Plan"];
		for (int i = 0; i < Size["Account"].asInt(); i++) {
			double budget = plan[i]["budget"].asDouble();
			string contentc = plan[i]["content"].asString();
			CString content=CString::CStringT(CA2CT(contentc.c_str()));
			string titlec = plan[i]["title"].asString();
			CString title = CString::CStringT(CA2CT(titlec.c_str()));
			CTime from, to;
			{
				const char * str = plan[i]["from"].asCString();
				char x[20];
				strcpy(x, str);
				int nYear = atoi(strtok(x, "|"));
				int nMon = atoi(strtok(NULL, "|"));
				int nDay = atoi(strtok(NULL, "|"));
				int nHour = atoi(strtok(NULL, "|"));
				int nMin = atoi(strtok(NULL, "|"));
				int nSec = atoi(strtok(NULL, "|"));
				CTime End(nYear, nMon, nDay, nHour, nMin, nSec);
				from = End;
			}
			{
				const char * str = plan[i]["to"].asCString();
				char x[20];
				strcpy(x, str);
				int nYear = atoi(strtok(x, "|"));
				int nMon = atoi(strtok(NULL, "|"));
				int nDay = atoi(strtok(NULL, "|"));
				int nHour = atoi(strtok(NULL, "|"));
				int nMin = atoi(strtok(NULL, "|"));
				int nSec = atoi(strtok(NULL, "|"));
				CTime End(nYear, nMon, nDay, nHour, nMin, nSec);
				to = End;
			}
			d_Plan->AddPlan(from, to, title, content, budget);
		}
		Json::Value toDo = root["Todo"];
		for (int i = 0; i < Size["Todo"].asInt(); i++) {
			Todo todo;
			todo.icon = toDo[i]["icon"].asInt();
			string titles = toDo[i]["title"].asString();
			CString strtitle = CString::CStringT(CA2CT(titles.c_str()));
			todo.title=strtitle;
			for (int j = 0; j < cnum[i].asInt(); j++) {
				string tmp = clist[i + j].asString();
				CString str = CString::CStringT(CA2CT(tmp.c_str()));
				todo.list.push_back(str);
			}

			d_Todo->TodoAdd(todo);
		}
		Json::Value account = root["Account"];
		for (int i = 0; i < Size["Account"].asInt(); i++) {
			AccountInfo accountinfo;
			accountinfo.year = account[i]["year"].asInt();
			accountinfo.month = account[i]["month"].asInt();
			accountinfo.day = account[i]["day"].asInt();
			string str= account[i]["content"].asString();
			CString constr = CString::CStringT(CA2CT(str.c_str()));
			accountinfo.content = constr;
			accountinfo.money = account[i]["money"].asInt();
			d_Account->accountList.push_back(accountinfo);
		}
	}
	return 0;
}


int CManageData::SaveData()
{
	int PlanListSize, TodoListSize, AccountListSize;
	PlanListSize = d_Plan->planList.size();
	TodoListSize = d_Todo->todoList.size();
	AccountListSize = d_Account->accountList.size();
	Json::Value root;
	Json::Value day;
	Json::Value cnum;
	Json::Value clist;
	day["Start"] = std::string(CT2CA(d_Plan->startDate.Format(_T("%Y|%m|%d|%H|%M|%S"))));
	day["End"] = std::string(CT2CA(d_Plan->endDate.Format(_T("%Y|%m|%d|%H|%M|%S"))));
	root["day"] = day;
	//����, ������ �߰�
	// plan����Ʈ �߰�
	Json::Value PlanList;
	for (int i = 0; i < PlanListSize; i++) {
		Json::Value list;
		list["from"] = std::string(CT2CA(d_Plan->planList.at(i).from.Format(_T("%Y|%m|%d|%H|%M|%S"))));
		list["to"] = std::string(CT2CA(d_Plan->planList.at(i).to.Format(_T("%Y|%m|%d|%H|%M|%S"))));
		list["title"] = std::string(CT2CA(d_Plan->planList.at(i).title));
		list["content"] = std::string(CT2CA(d_Plan->planList.at(i).content));
		list["budget"] = d_Plan->planList.at(i).budget;
		PlanList.append(list);
	}
	//todo����Ʈ �߰�
	Json::Value TodoList;

	for (int i = 0; i < TodoListSize; i++) {
		Json::Value list;
		list["icon"] = d_Todo->todoList.at(i).icon;
		list["title"] = std::string(CT2CA(d_Todo->todoList.at(i).title));
		int dolist = d_Todo->todoList.at(i).list.size();
		cnum.append(dolist);
		if (dolist == 0)clist.append("");
		for (int j = 0; j < dolist; j++) {
			clist.append(std::string(CT2CA(d_Todo->todoList.at(i).list.at(j))));
		}
		TodoList.append(list);
	}
	//account����Ʈ �߰�
	Json::Value AccountList;

	for (int i = 0; i < AccountListSize; i++) {
		Json::Value list;
		list["year"] = d_Account->accountList.at(i).year;
		list["month"] = d_Account->accountList.at(i).month;
		list["day"] = d_Account->accountList.at(i).day;
		list["content"] = std::string(CT2CA(d_Account->accountList.at(i).content));
		list["money"] = d_Account->accountList.at(i).money;
		AccountList.append(list);
	}
	Json::Value size;
	size["Plan"] = PlanListSize;
	size["Account"] = AccountListSize;
	size["Todo"] = TodoListSize;

	root["size"] = size;
	root["Plan"] = PlanList;
	root["Todo"] = TodoList;
	root["cnum"] = cnum;
	root["clist"] = clist;
	root["Account"] = AccountList;

	Json::StyledWriter writer;
	std::string strJson = writer.write(root);

	errno_t err;

	TCHAR fileFilter[] = _T("MrTraveler����(*.mt)|*.mt");
	TCHAR name[] = _T("MrTraveler.mt");
	TCHAR Ext[] = _T("mt");
	CFileDialog dlg(FALSE, Ext, name, OFN_HIDEREADONLY, fileFilter);
	if (IDOK == dlg.DoModal()) {
		CString strPathName = dlg.GetPathName();
		CFile Wfile;
		if (!Wfile.Open(dlg.GetPathName(), CFile::modeCreate |	CFile::modeWrite))
		{
			AfxMessageBox(_T("Can't Create testfile.txt !"));
			return 0;
		}
		Wfile.Write(strJson.c_str(), strJson.size());
		Wfile.Close();
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



