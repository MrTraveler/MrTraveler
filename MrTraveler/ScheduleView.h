#pragma once
#include "DrawView.h"

class CalendarView;
class ScheduleView : public DrawView
{
public:
	ScheduleView();
	~ScheduleView();
	virtual void OnDraw(CDC * dc);
	virtual void OnLButtonDown(CPoint point);
	void DrawTable(CDC * dc);
	void DrawPlan(CDC * dc);
	void DrawBackGround(CDC * dc);
	void DrawButton(CDC * dc);
	void DrawPlanLabel(CDC * dc);

public:
	CTime today;

	CalendarView* calendarView;

	//PlanDlg planDlg;
//	int selectedCellX;
//	int selectedCellY;

};

