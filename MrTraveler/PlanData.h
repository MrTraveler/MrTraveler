#pragma once
#include <vector>
struct Plan
{
	CTime from;	//시작 시간
	CTime to;	//끝나는 시간
	CString title;	//제목
	CString content;	//내용
	double budget;	//예산
};
class PlanData
{
private:
	PlanData();
	static PlanData * instance;
	static bool instanceFlag;
public:	//	변수
	std::vector<Plan> planList;	//이거 저장하면됨
public:
	static PlanData* GetInstance();
	std::vector<Plan> FindInPlan(CTime from , CTime to);	//사용하지 않는 함수
	std::vector<Plan> FindBorderPlan(CTime from, CTime to);	//from ~ to 사이에 조금이라도 포함되있는 Plan 얻어오기
	void ChangePlanData(Plan oldPlan, Plan newPlan);	// oldPlan 을 new Plan으로 교체하는 함수
	void AddPlan(CTime from, CTime to, CString title, CString content,int budget);	//Plan을 추가하는 함수
	void AddPlan(Plan plan);
	~PlanData();
};

