#pragma once
#include <vector>
struct Plan
{
	CTime from;
	CTime to;
	CString title;
	CString content;
	COLORREF color;
	double budget;	//원화 기준
};
class PlanData
{
private:
	PlanData();
	static PlanData * instance;
	static bool instanceFlag;
public:	//	변수
	std::vector<Plan> planList;
public:
	static PlanData* GetInstance();
	std::vector<Plan> FindInPlan(CTime from , CTime to);
	std::vector<Plan> FindBorderPlan(CTime from, CTime to);
	void ChangePlanData(Plan oldPlan, Plan newPlan);
	void AddPlan(CTime from, CTime to, CString title, CString content, COLORREF color,int budget);
	void AddPlan(Plan plan);
	~PlanData();
};

