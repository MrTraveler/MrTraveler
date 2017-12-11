#include "stdafx.h"
#include "ScheduleView.h"
#include "Util.h"
#include "PlanData.h"
#include "MrTravelerView.h"
#include "PlanDlg.h"
ScheduleView::ScheduleView()
{	
	today = CTime::GetCurrentTime();
	today = CTime(today.GetYear(), today.GetMonth(), today.GetDay(), 0, 0, 0);
}


ScheduleView::~ScheduleView()
{
}
void ScheduleView::DrawBackGround(CDC * dc)
{
	CBrush brush(RGB(0xCA,0xDB,0xE9));

	dc->FillRect(CRect(0, 0, 1000, 1000), &brush);

}
void ScheduleView::DrawButton(CDC * dc)
{
	CBrush brush(RGB(150, 190, 255));
	Util::DrawImage(dc, _T("img\\LeftArrow.png"), CRect(810, 10, 890, 90));
	Util::DrawImage(dc, _T("img\\RightArrow.png"), CRect(910, 10, 990, 90));
}
void ScheduleView::DrawTable(CDC * dc)
{

	//표바탕 칠하기
	CBrush brush1(RGB(0x4B, 0x68, 0x8B));
	
	dc->FillRect(CRect(0, 100, 1000, 100 + (int)((float)900 / 25)),&brush1);
	dc->FillRect(CRect(0, 100 + (int)((float)900 / 25), 100, 1000), &brush1);
	CBrush brush2(RGB(0x14, 0x31, 0x53));
	dc->FillRect(CRect(0,0,1000,100), &brush2);


	//표그리기
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(120, 120, 120));
	dc->SelectObject(&pen);
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
	//표 라벨 그리기
	CFont font;
	font.CreatePointFont(150, _T("맑은 고딕"));
	CFont *oldFont = dc->SelectObject(&font);
	dc->SetTextAlign(TA_CENTER);
	dc->SetBkMode(TRANSPARENT);
	dc->SetTextColor(RGB(255,255,255));
	//여기 아래부터 나중에 데이터로 자동화
	CTimeSpan oneDay = CTimeSpan(1, 0, 0, 0);
	dc->TextOut((int)((float)900 / 3 / 2 * 1 + 100), 100, (today - oneDay).Format(_T("%m 월 %d 일")));
	dc->TextOut((int)((float)900 / 3 / 2 * 3 + 100), 100, today.Format(_T("%m 월 %d 일")));
	dc->TextOut((int)((float)900 / 3 / 2 * 5 + 100), 100, (today + oneDay).Format(_T("%m 월 %d 일")));
	CFont font2;
	font2.CreatePointFont(100, _T("맑은 고딕"));
	dc->SelectObject(&font2);
	dc->SetTextAlign(TA_RIGHT);
	for (int i = 1; i <= 24; i++)
	{
		CString str;
		str.Format(_T("%02d:00"), i);
		dc->TextOutW(100 - 2, 900 / 25 / 2  * (i * 2 + 1) + 103, str);
	}
	CFont font3;
	font3.CreatePointFont(500, _T("Consolas"));
	dc->SelectObject(&font3);
	dc->SetTextAlign(TA_LEFT);
	dc->SetTextColor(RGB(255, 255, 255));
	dc->TextOut(50, 17, _T("Schedule"));
	dc->SelectObject(oldFont);
}
void ScheduleView::DrawPlan(CDC * dc)
{
	CTime ht = today;
	CTimeSpan oneDay = CTimeSpan(1, 0, 0, 0);
	ht -= oneDay;
	CFont font;
	font.CreatePointFont(100, _T("맑은 고딕"));
	dc->SelectObject(&font);
	dc->SetTextAlign(TA_LEFT);
	dc->SetTextColor(RGB(0, 0, 0));
	dc->SetBkMode(TRANSPARENT);
	for (int i = 0; i < 3; i++)
	{
		std::vector<Plan> v = PlanData::GetInstance()->FindBorderPlan(ht, ht + oneDay);
	
		for (int j = 0; j < v.size(); j++)
		{
			Plan p = v[j];
			CBrush brush(p.color);

			double sh;	//startHour
			double eh;	//endHour
			if (p.from <= ht)
				sh = 1;
			else
				sh = p.from.GetHour() +(float)p.from.GetMinute() / 60 + 1;
			if (p.to >= ht + oneDay)
				eh = 25;
			else
				eh = p.to.GetHour() + (float)p.to.GetMinute() / 60 + 1;
			dc->FillRect(CRect((int)((float)900 / 3 * i + 100), (sh * 900 / 25) + 100,
				(int)((float)900 / 3 * (i + 1) + 100), (eh * 900 / 25) + 100), &brush);
			if (sh != 1)
			{
				CString str;
				str.Format(_T("%s          %d원"), p.title, p.budget);
				dc->TextOut((int)((float)900 / 3 * i + 100), (sh * 900 / 25) + 100 + 10, str);
			}
			
			
		}
		ht += oneDay;
	}
}
void ScheduleView::OnDraw(CDC * dc)
{
	dc->SetMapMode(MM_ANISOTROPIC);
	CRect orgViewRect = { 0,0,viewRect.right - viewRect.left, viewRect.bottom - viewRect.top };	//view의 원래 크기
	dc->SetWindowExt(1000, 1000);
	dc->SetViewportExt(orgViewRect.right, orgViewRect.bottom);
	DrawBackGround(dc);
	DrawPlan(dc);
	DrawTable(dc);
	DrawButton(dc);
}
void ScheduleView::OnLButtonDown(CPoint point)
{
	CTimeSpan oneDay = CTimeSpan(1, 0, 0, 0);
	//포인트 비율 변환
	point.x = (int)(((float)point.x - viewRect.left) / (viewRect.right - viewRect.left) * 1000);
	point.y = (int)(((float)point.y - viewRect.top) / (viewRect.bottom - viewRect.top) * 1000);
	/////////////////
	if (!Util::IsPointInRect(CRect(0, 0, 1000, 1000), point))	//마우스가 뷰안에 있지 않을때
		return;
	if (Util::IsPointInRect(CRect(810, 10, 890, 90), point))
		today -= oneDay;
	if (Util::IsPointInRect(CRect(910, 10, 990, 90), point))
		today += oneDay;

	if (Util::IsPointInRect(CRect(100, 100, 1000, 1000), point))
	{
		double ch = ((double)point.y - 100 - 900 / 25) / (900 / 25);
		int cd = (point.x - 100) / (900 / 3);
		
		CTime ct = today;
		if (cd == 0)
			ct -= oneDay;
		else if (cd == 2)
			ct += oneDay;
		ct += CTimeSpan(0, (int)ch, (int)((ch - (int)ch) * 60), 0);

		std::vector<Plan> v = PlanData::GetInstance()->FindBorderPlan(ct, ct);

		PlanDlg planDlg;
		bool isNew = false;
		if (v.size() == 1)	//기존에 있는 내용 수정
		{
			Plan p = v[0];
			planDlg.m_color = p.color;
			planDlg.m_content = p.content;
			planDlg.m_title = p.title;
			planDlg.m_fromTime = CTime(p.from.GetYear(), p.from.GetMonth(), p.from.GetDay(), 0, 0, 0);
			planDlg.m_fromTimeHour = p.from.GetHour();
			planDlg.m_fromTimeMin = p.from.GetMinute() ;
			planDlg.m_toTime = CTime(p.to.GetYear(), p.to.GetMonth(), p.to.GetDay(), 0, 0, 0);
			planDlg.m_toTimeHour = p.to.GetHour();
			planDlg.m_toTimeMin = p.to.GetMinute();
			planDlg.m_budget = p.budget;
		}
		else // 새로 추가
		{
			
			planDlg.m_fromTime = CTime(ct.GetYear(), ct.GetMonth(), ct.GetDay(), 0, 0, 0);
			planDlg.m_fromTimeHour = ct.GetHour();
			planDlg.m_fromTimeMin = ct.GetMinute();
			planDlg.m_toTime = CTime(ct.GetYear(), ct.GetMonth(), ct.GetDay(), 0, 0, 0);
			planDlg.m_toTimeHour = ct.GetHour();
			planDlg.m_toTimeMin = ct.GetMinute();
			planDlg.m_color = RGB(123, 123, 255);
			isNew = true;
		}
		if (planDlg.DoModal() == IDOK)
		{
			CTime from;
			CTime to;
			CString title;
			CString content;
			COLORREF color;
			double budget;	//원화 기준
			Plan newPlan = { planDlg.m_fromTime + CTimeSpan(0, planDlg.m_fromTimeHour, planDlg.m_fromTimeMin, 0)
				, planDlg.m_toTime + CTimeSpan(0, planDlg.m_toTimeHour, planDlg.m_toTimeMin, 0)
				, planDlg.m_title, planDlg.m_content, planDlg.m_color ,planDlg.m_budget };
			if (isNew)
				PlanData::GetInstance()->AddPlan(newPlan);
			else
				PlanData::GetInstance()->ChangePlanData(v[0], newPlan);
		}
	}
	parentView->Invalidate();
	
}
