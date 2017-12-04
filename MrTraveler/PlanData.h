#pragma once
#include <vector>
struct Plan
{
	CTime from;
	CTime to;
	CString title;
	CString content;
	COLORREF color;
	double budget;	//��ȭ ����
};
class PlanData
{
private:
	PlanData();
	static PlanData * instance;
	static bool instanceFlag;
public:	//	����
	std::vector<Plan> planList;
public:
	static PlanData* GetInstance();
	std::vector<Plan> FindInPlan(CTime from , CTime to);
	std::vector<Plan> FindBorderPlan(CTime from, CTime to);
	void AddPlan(CTime from, CTime to, CString title, CString content, COLORREF color);
	~PlanData();
};

