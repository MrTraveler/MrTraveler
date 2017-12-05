// CalendarView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MrTraveler.h"
#include "CalendarView.h"


// CalendarView

IMPLEMENT_DYNCREATE(CalendarView, CView)

CalendarView::CalendarView()
{

}

CalendarView::~CalendarView()
{
}

BEGIN_MESSAGE_MAP(CalendarView, CView)
END_MESSAGE_MAP()


// CalendarView 그리기입니다.

void CalendarView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// CalendarView 진단입니다.

#ifdef _DEBUG
void CalendarView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CalendarView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CalendarView 메시지 처리기입니다.
void CalendarView::drawCalendar(CDC * pDC)
{
	//화면 고정 규격 : 1475 * 950
	drawMonthRgn(pDC);//월 리전 생성
	drawMonthText(pDC);
	drawNextMonth(pDC);
	drawPrevMonth(pDC);
	drawPlusButton(pDC);
	drawTimeBlock(pDC);
	//요일 리전 생성 및 출력
	drawDayRgn(pDC);
	drawDayText(pDC);
	//날짜 리전 생성 및 출력
	drawDateRgn(pDC);
	drawDateText(pDC);

}
int CalendarView::getDay(int date){
	return (firstDay+date-1)%7;
}
void CalendarView::drawTimeBlock(CDC * pDC){
	int week = 1;
	int start_week = 1;
	/*
	for (int i = mr->startDate; i <= mr->endDate; i++) {
		if (getDay(i) == 1)week++;
	}
	for (int i = 1; i <= mr->startDate; i++) {
		if (getDay(i) == 1)start_week++;
	}
	for (int i = 1; i <= week; i++) {
		if(i==1){
			blockRgn[idx].CreateRoundRectRgn(firstDay + getDay(mr->startDate), 100 * (getDay(mr->startDate) - 1), 250 + start_week * 200, 100 * (getDay(mr->startDate) - 1) + 100 * (7 - getDay(mr->startDate) + 1), 20, 20);
			pDC->FillRgn(&blockRgn[idx], &CBrush(RGB(154, 202, 235)));
		}
		else if(i==week){
		
		}
		else{}
	}
	*/
}

void CalendarView::drawPlusButton(CDC * pDC)
{

	plusButtonRgn.CreateEllipticRgn(1275, 75, 1375, 175);
	//prevMonthRgn.CreateEllipticRgn((1400 - 150) / 2 + 25 - 200 + 50 + 25, 50 - 50 + 25, (1400 - 150) / 2 + 150 + 25 - 200 + 25, 200 - 50 - 25);
	pDC->FillRgn(&plusButtonRgn, &CBrush(RGB(216, 216, 216)));

	CFont font;
	font.CreatePointFont(400, _T("바탕체"));
	pDC->SetBkColor(RGB(216, 216, 216));
	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->SelectObject(&font);
	pDC->TextOut(1305, 85, _T("+"));

}

void CalendarView::drawMonthRgn(CDC * pDC) {
	monthRgn.CreateEllipticRgn((1400 - 150) / 2 + 25, 50 - 50, (1400 - 150) / 2 + 150 + 25, 200 - 50);
	pDC->FillRgn(&monthRgn, &CBrush(RGB(154, 202, 235)));
}

void CalendarView::drawMonthText(CDC * pDC)
{
	CFont font;
	font.CreatePointFont(400, _T("바탕체"));
	CString strMonth;
	strMonth.Format(_T("%d"), curMonth);
	pDC->SetBkColor(RGB(154, 202, 235));
	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->SelectObject(&font);
	if (curMonth > 9)
		pDC->TextOut((1400 - 150) / 2 + 32 + 25, 50 + 32 + 5 - 50, strMonth);
	else
		pDC->TextOut((1400 - 150) / 2 + 32 + 25+25, 50 + 32 + 5 - 50, strMonth);
}

void CalendarView::drawDayRgn(CDC * pDC)
{
	for (int day = 0; day < 7; day++) {
		dayRgn[day].CreateRoundRectRgn(day % 7 * 200 + 25, 200, (day % 7 + 1) * 200 + 25, 250, 20, 20);
		pDC->FillRgn(&dayRgn[day], &CBrush(RGB(154, 202, 235)));
	}

}

void CalendarView::drawDayText(CDC * pDC)
{
	for (int day = 0; day < 7; day++) {
		CFont font;
		font.CreatePointFont(150, _T("바탕"));
		pDC->SetBkColor(RGB(154, 202, 235));
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SelectObject(&font);
		if (day == 0)
			pDC->TextOut(25 + day * 200 + 80, 210, _T("SUN"));
		else if (day == 1)
			pDC->TextOut(25 + day * 200 + 80, 210, _T("MON"));
		else if (day == 2)
			pDC->TextOut(25 + day * 200 + 80, 210, _T("TUE"));
		else if (day == 3) {
			pDC->TextOut(25 + day * 200 + 80, 210, _T("WED"));

			//현재년도 출력
			//월 리전 밑에 출력하려했더니 좌표가 꼬여서 수요일 리전 위에다 생성
			pDC->SetBkColor(RGB(255, 255, 255));
			pDC->SetTextColor(RGB(0, 0, 0));
			CString strYear;
			strYear.Format(_T("%d"), curYear);
			pDC->TextOut(15 + day * 200 + 80, 160, strYear);
		}
		else if (day == 4)
			pDC->TextOut(25 + day * 200 + 80, 210, _T("THU"));
		else if (day == 5)
			pDC->TextOut(25 + day * 200 + 80, 210, _T("FRI"));
		else if (day == 6)
			pDC->TextOut(25 + day * 200 + 80, 210, _T("SAT"));
	}
}

void CalendarView::drawDateRgn(CDC * pDC)
{

	//월별 일수 및 윤년 처리
	if (!(curYear % 4) && ((curYear % 100) || !(curYear % 400))) end_of_mon[1] = 29;

	//일 리전 생성 및 출력
	//헤더에 전역변수 dateRgn[day] 생성
	//dateRgn[0]=1일 참조bl
	//dateRgn[1]=2일 참조
	if (firstDay <= 0)firstDay += 7;
	for (int day = firstDay - 1; day < end_of_mon[curMonth - 1] + firstDay - 1; day++) {
		dateRgn[day - firstDay + 1].CreateRoundRectRgn((day) % 7 * 200 + 25, 250 + (day) / 7 * 100, ((day) % 7 + 1) * 200 + 25, 250 + ((day) / 7 + 1) * 100, 20, 20);
		if((curYear == cTime.GetYear())&&(curMonth == cTime.GetMonth()&&(day - firstDay + 2==curDate))) pDC->FillRgn(&dateRgn[day - firstDay + 1], &CBrush(RGB(219, 236, 255)));
		else pDC->FillRgn(&dateRgn[day - firstDay + 1], &CBrush(RGB(255, 255, 255)));
		pDC->FrameRgn(&dateRgn[day - firstDay + 1], &CBrush(RGB(216, 216, 216)), 2, 2);
	}
}

void CalendarView::drawDateText(CDC * pDC)
{

	//월별 일수 및 윤년 처리
	if (!(curYear % 4) && ((curYear % 100) || !(curYear % 400))) end_of_mon[1] = 29;

	//일 리전 생성 및 출력
	//헤더에 전역변수 dateRgn[day] 생성
	//dateRgn[0]=1일 참조
	//dateRgn[1]=2일 참조
	for (int day = firstDay - 1; day < end_of_mon[curMonth - 1] + firstDay - 1; day++) {
		CFont font;
		font.CreatePointFont(100, _T("바탕"));
		CString strDate;
		strDate.Format(_T("%d"), day - firstDay + 2);
		if ((curYear == cTime.GetYear()) && (curMonth == cTime.GetMonth() && (day - firstDay + 2 == curDate))) pDC->SetBkColor(RGB(219, 236, 255));
		else pDC->SetBkColor(RGB(255, 255, 255));
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SelectObject(&font);
		pDC->TextOut((day) % 7 * 200 + 25 + 10, 250 + (day) / 7 * 100 + 10, strDate);
	}
}

void CalendarView::drawNextMonth(CDC * pDC)
{
	nextMonthRgn.CreateEllipticRgn((1400 - 150) / 2 + 25 - 200 + 50 + 25 + 300, 50 - 50 + 25, (1400 - 150) / 2 + 150 + 25 - 200 + 25 + 300, 200 - 50 - 25);
	pDC->FillRgn(&nextMonthRgn, &CBrush(RGB(216, 216, 216)));
	
	CFont font;
	font.CreatePointFont(400, _T("바탕체"));
	pDC->SetBkColor(RGB(216, 216, 216));
	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->SelectObject(&font);
	pDC->TextOut((1400 - 150) / 2 + 25 - 200 + 50 + 25 + 20 + 5 + 300 + 10, 50 - 50 + 25 + 10, _T(">"));
	
}

void CalendarView::drawPrevMonth(CDC * pDC)
{
	prevMonthRgn.CreateEllipticRgn((1400 - 150) / 2 + 25 - 200 + 50 + 25, 50 - 50 + 25, (1400 - 150) / 2 + 150 + 25 - 200 + 25, 200 - 50 - 25);
	pDC->FillRgn(&prevMonthRgn, &CBrush(RGB(216, 216, 216)));
	
	CFont font;
	font.CreatePointFont(400, _T("바탕체"));
	pDC->SetBkColor(RGB(216, 216, 216));
	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->SelectObject(&font);
	pDC->TextOut((1400 - 150) / 2 + 25 - 200 + 50 + 25 + 20 + 5, 50 - 50 + 25 + 10, _T("<"));	
	
}

void CalendarView::drawLogo(CDC * pDC)
{
}



