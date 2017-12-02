#pragma once
#include "DrawView.h"
class ScheduleView : public DrawView
{
public:
	ScheduleView();
	~ScheduleView();
	virtual void OnDraw(CDC * dc);
	void DrawTable(CDC * dc);
	void DrawLabel(CDC * dc);
};

