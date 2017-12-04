#include "stdafx.h"
#include "ScheduleView.h"


ScheduleView::ScheduleView()
{	
	today = CTime::GetCurrentTime();
}


ScheduleView::~ScheduleView()
{
}
void ScheduleView::DrawBackGround(CDC * dc)
{
	CBrush brush(RGB(100,100,255));
	dc->FillRect(CRect(0, 0, 1000, 1000), &brush);

}
void ScheduleView::DrawButton(CDC * dc)
{
	CBrush brush(RGB(150, 190, 255));
	dc->FillRect(CRect(10, 10, 90, 90), &brush);
	dc->FillRect(CRect(110, 10, 190, 90), &brush);
	dc->SetTextAlign(TA_CENTER);
	dc->SetBkMode(TRANSPARENT);
	dc->SetTextColor(RGB(0, 0, 0));
	dc->TextOut(50, 35, _T("Icon"));
	dc->TextOut(150, 35, _T("Icon"));
}
void ScheduleView::DrawTable(CDC * dc)
{
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(120,120,120));
	CPen *oldPen = dc->SelectObject(&pen);
	for (int i = 0; i < 26; i++)
	{
		dc->MoveTo(0, (int)((float)900 / 25 * i + 100));
		dc->LineTo(1000, (int)((float)900 / 25 * i + 100));
	}
	dc->MoveTo(0, 100);
	dc->LineTo(0, 1000);
	for (int i = 0; i < 3; i++)
	{
		dc->MoveTo((int)((float)900 / 3) * i + 100,100);
		dc->LineTo((int)((float)900 / 3) * i + 100,1000);
	}
			
	dc->SelectObject(oldPen);
}
void ScheduleView::DrawLabel(CDC * dc)
{
	CFont font;
	font.CreatePointFont(150, _T("맑은 고딕"));
	CFont *oldFont = dc->SelectObject(&font);
	dc->SetTextAlign(TA_CENTER);
	dc->SetBkMode(TRANSPARENT);
	dc->SetTextColor(RGB(0, 0, 0));
	//여기 아래부터 나중에 데이터로 자동화
	CTimeSpan oneDay = CTimeSpan(1, 0, 0, 0);
	dc->TextOut((int)((float)900 / 3 / 2 * 1 + 100), 100, (today - oneDay).Format(_T("%m 월 %d 일")));
	dc->TextOut((int)((float)900 / 3 / 2 * 3 + 100), 100, today.Format(_T("%m 월 %d 일")));
	dc->TextOut((int)((float)900 / 3 / 2 * 5 + 100), 100, (today + oneDay).Format(_T("%m 월 %d 일")));
	CFont font2;
	font2.CreatePointFont(70, _T("맑은 고딕"));
	dc->SelectObject(&font2);
	dc->SetTextAlign(TA_RIGHT);
	for (int i = 1; i <= 24; i++)
	{
		CString str;
		str.Format(_T("%02d:00"),i);
		dc->TextOutW(100, 900 / 25 / 2 * (i * 2 + 1) + 105, str);
	}
	dc->SelectObject(oldFont);
}
void ScheduleView::OnDraw(CDC * dc)
{
	dc->SetMapMode(MM_ANISOTROPIC);
	CRect orgViewRect = { 0,0,viewRect.right - viewRect.left, viewRect.bottom - viewRect.top };	//view의 원래 크기
	dc->SetWindowExt(1000, 1000);
	dc->SetViewportExt(orgViewRect.right, orgViewRect.bottom);
	DrawBackGround(dc);
	DrawTable(dc);
	DrawLabel(dc);
	DrawButton(dc);
}
void ScheduleView::OnLButtonDown(CPoint point)
{
	
}
