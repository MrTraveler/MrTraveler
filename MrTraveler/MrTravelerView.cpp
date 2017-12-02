
// MrTravelerView.cpp : CMrTravelerView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MrTraveler.h"
#endif

#include "MrTravelerDoc.h"
#include "MrTravelerView.h"
#include "MrTravelerParceHtml.h"
#include "DrawView.h"
#include "TodoListView.h"
#include "ScheduleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMrTravelerView

IMPLEMENT_DYNCREATE(CMrTravelerView, CView)

BEGIN_MESSAGE_MAP(CMrTravelerView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONUP()
//	ON_WM_PAINT()
ON_WM_LBUTTONDOWN()
ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CMrTravelerView 생성/소멸

CMrTravelerView::CMrTravelerView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	dragFlag = false;
	CMrTravelerParceHtml *x = new CMrTravelerParceHtml();
	x->ParceHtml(_T("https://v3.exchangerate-api.com/bulk/3090405efae2c21d79cc569c/KRW"), _T("ExchangeRate.json"));
	x->RoadExchangeRate();
	testinit();

}

CMrTravelerView::~CMrTravelerView()
{
}

void CMrTravelerView::testinit()	//테스트 용도로 만든거
{
	todoListView = new TodoListView();
	scheduleView = new ScheduleView();
	Todo todo1;
	todo1.color = RGB(10, 10, 240);
	todo1.title = _T("Title_1");
	Todo todo2;
	todo2.color = RGB(20, 20, 230);
	todo2.title = _T("Title_2");
	Todo todo3;
	todo3.color = RGB(30,30, 220);
	todo3.title = _T("Title_3");
	Todo todo4;
	todo4.color = RGB(40,40, 210);
	todo4.title = _T("Title_4");
	Todo todo5;
	todo5.color = RGB(50, 50, 200);
	todo5.title = _T("Title_5");
	Todo todo6;
	todo6.color = RGB(60, 60, 190);
	todo6.title = _T("Title_6");
	todoListView->todoList.push_back(todo1);
	todoListView->todoList.push_back(todo2);
	todoListView->todoList.push_back(todo3);
	todoListView->todoList.push_back(todo4);
	todoListView->todoList.push_back(todo5);
	todoListView->todoList.push_back(todo6);

}
BOOL CMrTravelerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}




// CMrTravelerView 그리기

void CMrTravelerView::OnDraw(CDC* pDC)
{
	CMrTravelerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect window;
	GetWindowRect(&window);
	if (clickedTapIndex == 0)
	{
		drawCalendar(pDC);
	}
	else if (clickedTapIndex == 1) 
	{
		CRect rect;
		GetClientRect(&rect);
		scheduleView->StartView(rect);
		scheduleView->OnDraw(pDC);

	}
	else if (clickedTapIndex == 2)
	{
		CRect rect;
		GetClientRect(&rect);
		todoListView->StartView(rect);
		todoListView->OnDraw(pDC);
	}
	else if (clickedTapIndex == 3) {}
	else if (clickedTapIndex == 4) {}
	else if (clickedTapIndex == 5) {}
}

void CMrTravelerView::drawCalendar(CDC * pDC)
{
	//화면 고정 규격 : 1475 * 950
	drawMonthRgn(pDC);//월 리전 생성
	drawMonthText(pDC);
	//요일 리전 생성 및 출력
	drawDayRgn(pDC);
	drawDayText(pDC);
	//날짜 리전 생성 및 출력
	drawDateRgn(pDC);
	drawDateText(pDC);
	//탭 리전 생성 및 출력
	drawTapRgn(pDC);
	drawTapText(pDC);
}

void CMrTravelerView::drawMonthRgn(CDC * pDC){
	monthRgn.CreateEllipticRgn((1400 - 150) / 2 + 25, 50 - 50, (1400 - 150) / 2 + 150 + 25, 200 - 50);
	pDC->FillRgn(&monthRgn, &CBrush(RGB(154, 202, 235)));
}

void CMrTravelerView::drawMonthText(CDC * pDC)
{
	CFont font;
	font.CreatePointFont(400, _T("바탕체"));
	CString strMonth;
	strMonth.Format(_T("%d"), curMonth);
	pDC->SetBkColor(RGB(154, 202, 235));
	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->SelectObject(&font);
	pDC->TextOut((1400 - 150) / 2 + 32 + 25, 50 + 32 + 5 - 50, strMonth);
}

void CMrTravelerView::drawDayRgn(CDC * pDC)
{
	for (int day = 0; day < 7; day++) {
		dayRgn[day].CreateRoundRectRgn(day % 7 * 200 + 25, 200, (day % 7 + 1) * 200 + 25, 250, 20, 20);
		pDC->FillRgn(&dayRgn[day], &CBrush(RGB(154, 202, 235)));
	}

}

void CMrTravelerView::drawDayText(CDC * pDC)
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

void CMrTravelerView::drawDateRgn(CDC * pDC)
{

	//월별 일수 및 윤년 처리
	if (!(curYear % 4) && ((curYear % 100) || !(curYear % 400))) end_of_mon[1] = 29;

	//일 리전 생성 및 출력
	//헤더에 전역변수 dateRgn[day] 생성
	//dateRgn[0]=1일 참조
	//dateRgn[1]=2일 참조
	for (int day = firstDay - 1; day < end_of_mon[curMonth - 1] + firstDay - 1; day++) {
		dateRgn[day - firstDay + 1].CreateRoundRectRgn((day) % 7 * 200 + 25, 250 + (day) / 7 * 100, ((day) % 7 + 1) * 200 + 25, 250 + ((day) / 7 + 1) * 100, 20, 20);
		pDC->FillRgn(&dateRgn[day - firstDay + 1], &CBrush(RGB(255, 255, 255)));
		pDC->FrameRgn(&dateRgn[day - firstDay + 1], &CBrush(RGB(216, 216, 216)), 2, 2);
	}
}

void CMrTravelerView::drawDateText(CDC * pDC)
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
		pDC->SetBkColor(RGB(255, 255, 255));
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SelectObject(&font);
		pDC->TextOut((day) % 7 * 200 + 25 + 10, 250 + (day) / 7 * 100 + 10, strDate);
	}
}

void CMrTravelerView::drawTapRgn(CDC * pDC)
{
	//CRgn tapRgn[6] 탭 리전 전역변수 선언
	for (int i = 0; i < 6; i++) {
		tapRgn[i].CreateRoundRectRgn(i % 7 * 200, 850, (i % 7 + 1) * 200, 900, 20, 20);
		pDC->FillRgn(&tapRgn[i], &CBrush(RGB(154, 202, 235)));
	}
}

void CMrTravelerView::drawTapText(CDC * pDC)
{
	for (int i = 0; i < 6; i++) {
		CFont font;
		font.CreatePointFont(100, _T("바탕"));
		pDC->SetBkColor(RGB(154, 202, 235));
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SelectObject(&font);
		if (i == 0)
			pDC->TextOut(25 + i * 200 + 40, 860, _T("캘린더"));
		else if (i == 1)
			pDC->TextOut(25 + i * 200 + 50, 860, _T("일정"));
		else if (i == 2)
			pDC->TextOut(25 + i * 200 + 30, 860, _T("TO DO List"));
		else if (i == 3)
			pDC->TextOut(25 + i * 200 + 40, 860, _T("가계부"));
		else if (i == 4)
			pDC->TextOut(25 + i * 200 + 35, 860, _T("다이어리"));
		else if (i == 5)
			pDC->TextOut(25 + i * 200 + 45, 860, _T("INFO"));
	}
}

void CMrTravelerView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	m_pt = point;
	//일 리전 드래그 처리
	for (int i = 0; i < 31; i++) {
		if (dateRgn[i].PtInRegion(m_pt)) {
			dragFlag = true;
			startPos = i;//드래그 시작 일 리전 인덱스
			dc.FillRgn(&dateRgn[startPos], &CBrush(RGB(230, 230, 230)));
			//drawDateText(pDC);
			break;
		}
	}
	//탭 리전 클릭 처리
	for (int i = 0; i < 6; i++) {
		if (tapRgn[i].PtInRegion(m_pt)) {
			clickedTapIndex = i;//드래그 시작 일 리전 인덱스
			//drawTapRgn(pDC);
			dc.FillRgn(&tapRgn[clickedTapIndex], &CBrush(RGB(216, 216, 216)));
			//drawTapText(pDC);
			break;
		}
	}
	CView::OnLButtonDown(nFlags, point);
}

void CMrTravelerView::OnMouseMove(UINT nFlags, CPoint point)
{
	CView::OnMouseMove(nFlags, point);
}

void CMrTravelerView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	m_pt = point;
	if (dragFlag) {//드래그 처리
		for (int i = 0; i < 31; i++) {
			if (dateRgn[i].PtInRegion(m_pt)) {
				endPos = i;
				if (startPos > endPos) {//스와핑
					int tmp; tmp = startPos; startPos = endPos; endPos = tmp;
				}
				break;
			}
		}

		for (int i = startPos; i <= endPos; i++) {
			dc.FillRgn(&dateRgn[i], &CBrush(RGB(230, 230, 230)));
		}
		//drawDateText(pDC);
		dragFlag = false;
	}

	CView::OnLButtonUp(nFlags, point);
}


BOOL CMrTravelerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMrTravelerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMrTravelerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMrTravelerView 진단

#ifdef _DEBUG


void CMrTravelerView::AssertValid() const
{
	CView::AssertValid();
}

void CMrTravelerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMrTravelerDoc* CMrTravelerView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMrTravelerDoc)));
	return (CMrTravelerDoc*)m_pDocument;
}
#endif //_DEBUG


// CMrTravelerView 메시지 처리기


