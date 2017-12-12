#pragma once
#include <vector>
struct Plan
{
	CTime from;	//���� �ð�
	CTime to;	//������ �ð�
	CString title;	//����
	CString content;	//����
	double budget;	//����
};
class PlanData
{
private:
	PlanData();
	static PlanData * instance;
	static bool instanceFlag;
public:	//	����
	std::vector<Plan> planList;	//�̰� �����ϸ��
public:
	static PlanData* GetInstance();
	std::vector<Plan> FindInPlan(CTime from , CTime to);	//������� �ʴ� �Լ�
	std::vector<Plan> FindBorderPlan(CTime from, CTime to);	//from ~ to ���̿� �����̶� ���Ե��ִ� Plan ������
	void ChangePlanData(Plan oldPlan, Plan newPlan);	// oldPlan �� new Plan���� ��ü�ϴ� �Լ�
	void AddPlan(CTime from, CTime to, CString title, CString content,int budget);	//Plan�� �߰��ϴ� �Լ�
	void AddPlan(Plan plan);
	~PlanData();
};

