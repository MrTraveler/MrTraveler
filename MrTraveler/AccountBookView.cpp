#include "stdafx.h"
#include "AccountBookView.h"
#include "MrTravelerView.h"
#include "Util.h"
#include "AccountData.h"
#include "AccountBookDlg.h"
AccountBookView::AccountBookView()
{
	CTime today = CTime::GetCurrentTime();
	year = today.GetYear();
	month = today.GetMonth();
}


AccountBookView::~AccountBookView()
{

}

void AccountBookView::OnDraw(CDC * dc)
{
	dc->SetMapMode(MM_ANISOTROPIC);
	CRect orgViewRect = { 0,0,viewRect.right - viewRect.left, viewRect.bottom - viewRect.top };	//view의 원래 크기
	dc->SetWindowExt(1000, 1000);
	dc->SetViewportExt(orgViewRect.right, orgViewRect.bottom);
	DrawCalander(dc);
	DrawButton(dc);
	DrawData(dc);
}
void AccountBookView::DrawData(CDC * dc)
{
	
}
void AccountBookView::OnLButtonDown(CPoint point)
{
	point.x = (int)(((float)point.x - viewRect.left) / (viewRect.right - viewRect.left) * 1000);
	point.y = (int)(((float)point.y - viewRect.top) / (viewRect.bottom - viewRect.top) * 1000);
	if (Util::IsPointInRect(CRect(10, 10, 90, 90), point))
	{
		month -= 1;
		if (month == 0)
		{
			year -= 1;
			month = 12;
		}
	}
	if (Util::IsPointInRect(CRect(910, 10, 990, 90), point))
	{
		month += 1;
		if (month == 13)
		{
			year += 1;
			month = 1;
		}
	}
	if (Util::IsPointInRect(CRect(0, 180, 1000, 1000), point))
	{
		CTime nowMonth = CTime(year, month, 1, 0, 0, 0);
		int prevMonthDay = Util::GetMonthDay(year - (month == 1 ? 1 : 0), (month % 12) + 1);
		int nowMonthDay = Util::GetMonthDay(year, month);
		int startDay = prevMonthDay - (nowMonth.GetDayOfWeek() + 5) % 7;
		int col = (int)(point.x / ((float)1000 / 7));
		int row = (int)((point.y - 180) / ((float)820 / 6));
		int nowDay = (startDay + 1 + col + row * 7) - prevMonthDay;

		if (nowDay >= 1 && nowDay <= nowMonthDay)
		{
			AccountBookDlg dlg;

			dlg.m_content = _T("");
			dlg.m_type = 0;
			dlg.m_money = 3000;
			CString str;
			str.Format(_T("%d년 %d월 %d일"), year, month,nowDay);
			dlg.m_date = str;
			dlg.day = nowDay;
			dlg.month = month;
			dlg.year = year;
			dlg.accountList = AccountData::GetInstance()->findAccount(year, month, nowDay);
		
			if (dlg.DoModal() == IDOK)
			{
				AccountData::GetInstance()->eraseAccount(year, month, nowDay);
				for (int i = 0; i < dlg.accountList.size(); i++)
				{
					AccountInfo info = dlg.accountList[i];
					AccountData::GetInstance()->accountList.push_back(info);
				}
				
			}
		}
	}
	parentView->Invalidate();

}

void AccountBookView::DrawCalander(CDC * dc)
{
	CBrush brush1(RGB(0x14, 0x31, 0x53));
	dc->FillRect(CRect(0, 0, 1000, 100), &brush1);
	CBrush brush2(RGB(0x4B, 0x68, 0x8B));
	dc->FillRect(CRect(0,100, 1000, 180), &brush2);

	for (int i = 0; i <= 6; i++)
	{
		dc->MoveTo(0, 180 + (int)((float)820 / 6 * i));
		dc->LineTo(1000, 180 + (int)((float)820 / 6 * i));
	}

	for (int i = 0; i <= 7; i++)
	{
		dc->MoveTo((int)((float)1000 / 7 * i), 100);
		dc->LineTo((int)((float)1000 / 7 * i), 1000);
	}

	CFont font1;
	font1.CreatePointFont(350, _T("Consolas"));
	dc->SelectObject(&font1);
	dc->SetTextAlign(TA_CENTER);
	dc->SetBkMode(TRANSPARENT);
	dc->SetTextColor(RGB(255, 255, 255));
	CTime t = CTime(year, month, 1, 0, 0, 0);
	dc->TextOut(500, 20, t.Format(_T("%B %Y")));

	CFont font2;
	font2.CreatePointFont(250, _T("Consolas"));
	dc->SelectObject(&font2);
	dc->SetTextColor(RGB(255, 255, 255));
	for (int i = 0; i < 7; i++)
		dc->TextOut((int)((float) 1000 / 7 * (2 * i + 1) / 2), 120, weekLabel[i]);
	CFont font3;
	font3.CreatePointFont(200, _T("Consolas"));
	dc->SelectObject(&font3);

	CFont font4;
	font4.CreatePointFont(250, _T("Consolas"));

	CFont font5;
	font5.CreatePointFont(120, _T("Consolas"));

	CTime nowMonth = CTime(year, month, 1, 0, 0, 0);
	int prevMonthDay = Util::GetMonthDay(year - (month == 1 ? 1 : 0), (month % 12) + 1);
	int nowMonthDay = Util::GetMonthDay(year, month);
	int startDay = prevMonthDay - (nowMonth.GetDayOfWeek() + 5) % 7;
	int	printDayState = 0;
	dc->SetTextColor(RGB(160, 160, 160));
	for(int i = 0; i < 6; i++)
		for (int j = 0; j < 7; j++)
		{
			if (printDayState == 0 && startDay == prevMonthDay)
			{
				startDay = 1;
				printDayState = 1;
			}
			else if (printDayState == 1 && startDay == nowMonthDay)
			{
				startDay = 1;
				printDayState = 2;
			}
			else
				++startDay;

			if (printDayState == 0)
			{
				dc->SetTextColor(RGB(160, 160, 160));
				dc->SelectObject(&font3);
			}
			else if (printDayState == 1)
			{
				dc->SetTextColor(RGB(0x14, 0x31, 0x53));
				dc->SelectObject(&font4);
			}
			else
			{
				dc->SetTextColor(RGB(160, 160, 160));
				dc->SelectObject(&font3);
			}
			CString str;
			str.Format(_T("%d"), startDay);
			dc->TextOut((int)((float)1000 / 7 * (2 * j + 1) / 2) - 50, 180 + (int)((float)820 / 6 * (i * 2 + 1) / 2) +20,str);
			
			if (printDayState == 1)
			{
				std::vector<AccountInfo> v = AccountData::GetInstance()->findAccount(year, month, startDay);
				int budget = 0;

				for (int i = 0; i < v.size(); i++)
					budget += v[i].money;
				CString str;
				str.Format(_T("%d원"), budget);
				if (budget == 0)
					dc->SetTextColor(RGB(120, 120, 120));
				else if (budget < 0)
					dc->SetTextColor(RGB(0xD2, 0x1A, 0x1A));
				else
					dc->SetTextColor(RGB(0x61,0xBB,0x17));
				dc->SelectObject(&font5);
				dc->TextOut((int)((float)1000 / 7 * (2 * j + 1) / 2) + 50, 180 + (int)((float)820 / 6 * (i * 2 + 1) / 2) + 30, str);	
			}

		}

}

void AccountBookView::DrawButton(CDC * dc)
{
	Util::DrawImage(dc, _T("img\\scheduleLeftArrow.png"), CRect(10, 10, 90, 90));
	Util::DrawImage(dc, _T("img\\scheduleRightArrow.png"), CRect(910, 10, 990, 90));
}