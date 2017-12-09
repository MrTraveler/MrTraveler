#pragma once
#include "DrawView.h"
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

public:
	CTime today;
//	int selectedCellX;
//	int selectedCellY;

};

