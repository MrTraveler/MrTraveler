// CalendarView.cpp : ���� �����Դϴ�.
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


// CalendarView �׸����Դϴ�.

void CalendarView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
}


// CalendarView �����Դϴ�.

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


// CalendarView �޽��� ó�����Դϴ�.
void CalendarView::drawCalendar(CDC * pDC)
{
	//ȭ�� ���� �԰� : 1475 * 950
	drawMonthRgn(pDC);//�� ���� ����
	drawMonthText(pDC);
	//���� ���� ���� �� ���
	drawDayRgn(pDC);
	drawDayText(pDC);
	//��¥ ���� ���� �� ���
	drawDateRgn(pDC);
	drawDateText(pDC);

}

void CalendarView::drawMonthRgn(CDC * pDC) {
	monthRgn.CreateEllipticRgn((1400 - 150) / 2 + 25, 50 - 50, (1400 - 150) / 2 + 150 + 25, 200 - 50);
	pDC->FillRgn(&monthRgn, &CBrush(RGB(154, 202, 235)));
}

void CalendarView::drawMonthText(CDC * pDC)
{
	CFont font;
	font.CreatePointFont(400, _T("����ü"));
	CString strMonth;
	strMonth.Format(_T("%d"), curMonth);
	pDC->SetBkColor(RGB(154, 202, 235));
	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->SelectObject(&font);
	pDC->TextOut((1400 - 150) / 2 + 32 + 25, 50 + 32 + 5 - 50, strMonth);
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
		font.CreatePointFont(150, _T("����"));
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

			//����⵵ ���
			//�� ���� �ؿ� ����Ϸ��ߴ��� ��ǥ�� ������ ������ ���� ������ ����
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

	//���� �ϼ� �� ���� ó��
	if (!(curYear % 4) && ((curYear % 100) || !(curYear % 400))) end_of_mon[1] = 29;

	//�� ���� ���� �� ���
	//����� �������� dateRgn[day] ����
	//dateRgn[0]=1�� ����
	//dateRgn[1]=2�� ����
	if (firstDay < 0)firstDay += 7;
	for (int day = firstDay - 1; day < end_of_mon[curMonth - 1] + firstDay - 1; day++) {
		dateRgn[day - firstDay + 1].CreateRoundRectRgn((day) % 7 * 200 + 25, 250 + (day) / 7 * 100, ((day) % 7 + 1) * 200 + 25, 250 + ((day) / 7 + 1) * 100, 20, 20);
		pDC->FillRgn(&dateRgn[day - firstDay + 1], &CBrush(RGB(255, 255, 255)));
		pDC->FrameRgn(&dateRgn[day - firstDay + 1], &CBrush(RGB(216, 216, 216)), 2, 2);
	}
}

void CalendarView::drawDateText(CDC * pDC)
{

	//���� �ϼ� �� ���� ó��
	if (!(curYear % 4) && ((curYear % 100) || !(curYear % 400))) end_of_mon[1] = 29;

	//�� ���� ���� �� ���
	//����� �������� dateRgn[day] ����
	//dateRgn[0]=1�� ����
	//dateRgn[1]=2�� ����
	for (int day = firstDay - 1; day < end_of_mon[curMonth - 1] + firstDay - 1; day++) {
		CFont font;
		font.CreatePointFont(100, _T("����"));
		CString strDate;
		strDate.Format(_T("%d"), day - firstDay + 2);
		pDC->SetBkColor(RGB(255, 255, 255));
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SelectObject(&font);
		pDC->TextOut((day) % 7 * 200 + 25 + 10, 250 + (day) / 7 * 100 + 10, strDate);
	}
}

