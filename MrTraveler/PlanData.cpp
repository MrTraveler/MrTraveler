#include "stdafx.h"
#include "PlanData.h"
#include <vector>
PlanData * PlanData::instance = NULL;
bool PlanData::instanceFlag = false;
PlanData::PlanData()
{

}
PlanData::~PlanData()
{
	instanceFlag = false;
}

PlanData * PlanData::GetInstance()
{
	if (instance == NULL)
	{
		instance = new PlanData();
		instanceFlag = true;
	}
	return instance;
}
std::vector<Plan> PlanData::FindBorderPlan(CTime from , CTime to)
{
	std::vector<Plan> findedPlanList;
	for (int i = 0; i < planList.size(); i++)
		if ((planList[i].from <= from && planList[i].to >= from)
			|| (planList[i].from <= to && planList[i].to >= to))
			findedPlanList.push_back(planList[i]);			
	return findedPlanList;
}
std::vector<Plan> PlanData::FindInPlan(CTime from, CTime to)
{
	std::vector<Plan> findedPlanList;
	for (int i = 0; i < planList.size(); i++)
		if (planList[i].from <= from && planList[i].to >= to)
			findedPlanList.push_back(planList[i]);
	return findedPlanList;
}
void PlanData::AddPlan(CTime from, CTime to, CString title, CString content, COLORREF color = RGB(255, 170, 50))
{
	Plan plan = { from, to, title, content, color };
}