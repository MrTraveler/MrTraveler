#pragma once
#include "DrawView.h"
class AccountBookView :
	public DrawView
{
public:
	AccountBookView();
	~AccountBookView();
	virtual void OnDraw(CDC * dc);
	virtual void OnLButtonDown(CPoint point);
	void DrawCalander(CDC * dc);
	void DrawData(CDC * dc);
	void DrawButton(CDC * dc);
	void DrawPlan(CDC * dc);
public:
	const CString weekLabel[7] = { _T("Mon"),_T("Tue"),_T("Wed"),_T("Thu"),_T("Fri"),_T("Sat"),_T("Sun") };
	int year;
	int month;
};
