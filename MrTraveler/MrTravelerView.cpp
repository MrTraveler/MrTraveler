
// MrTravelerView.cpp : CMrTravelerView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MrTraveler.h"
#endif
#include "PlanDlg.h"
#include "MrTravelerDoc.h"
#include "MrTravelerView.h"
#include "MrTravelerParceHtml.h"
#include "DrawView.h"
#include "TodoListView.h"
#include "ScheduleView.h"
#include "CalendarView.h"
#include "TodoData.h"
#include "PlanData.h"
#include "MainFrm.h"
#include "AccountBookView.h"
#include "Util.h"
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
ON_WM_LBUTTONDBLCLK()
ON_WM_RBUTTONDOWN()
ON_WM_CREATE()
END_MESSAGE_MAP()

// CMrTravelerView 생성/소멸

CMrTravelerView::CMrTravelerView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	clickedTapIndex=0;//클릭된 탭 인덱스
	dragFlag = false;
	CMrTravelerParceHtml *x = new CMrTravelerParceHtml();
	//x->ParceHtml(_T("https://v3.exchangerate-api.com/bulk/3090405efae2c21d79cc569c/KRW"), _T("ExchangeRate.json"));
	testinit();
	//rgn 생성
	for (int i = 0; i < 5; i++) 
		tapRgn[i].CreateRoundRectRgn(i % 7 * 200, 850, (i % 7 + 1) * 200, 900, 20, 20);

}

CMrTravelerView::~CMrTravelerView()
{
}
void CMrTravelerView::testinit()	//테스트 용도로 만든거
{
	todoListView = new TodoListView();
	scheduleView = new ScheduleView();
	calendarView = new CalendarView();
	accountBookView = new AccountBookView();
	Todo todo1;
	todo1.title = _T("Title_1");
	todo1.icon = 0;
	Todo todo2;
	todo2.title = _T("Title_2");
	todo2.icon = 1;
	Todo todo3;
	todo3.title = _T("Title_3");
	todo3.icon = 2;
	Todo todo4;
	todo4.title = _T("Title_4");
	todo4.icon = 3;
	Todo todo5;
	todo5.title = _T("Title_5");
	todo5.icon = 4;
	Todo todo6;
	todo6.title = _T("Title_6");
	todo6.icon = 1;
	TodoData::GetInstance()->todoList.push_back(todo1);
	TodoData::GetInstance()->todoList.push_back(todo2);
	TodoData::GetInstance()->todoList.push_back(todo3);
	TodoData::GetInstance()->todoList.push_back(todo4);
	TodoData::GetInstance()->todoList.push_back(todo5);
	TodoData::GetInstance()->todoList.push_back(todo6);

	PlanData::GetInstance()->AddPlan(CTime(2017, 12, 05, 10, 5, 0), CTime(2017, 12, 06, 10, 5, 0), _T("치킨 뜯기")
		, _T(""), RGB(255, 154, 23),10000);
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
	//탭 리전 생성 및 출력
	drawTapRgn(pDC);
	drawTapText(pDC);

	CRect window;
	GetWindowRect(&window);
	if (clickedTapIndex == 0)
	{
		calendarView->drawCalendar(pDC);
	}
	else if (clickedTapIndex == 1) 
	{
		CRect rect;
		GetClientRect(&rect);
		rect.bottom = 840;
		scheduleView->StartView(rect,this);
		scheduleView->OnDraw(pDC);

	}
	else if (clickedTapIndex == 2)
	{
		CRect rect;
		GetClientRect(&rect);
		rect.bottom = 840;
		todoListView->StartView(rect,this);
		todoListView->OnDraw(pDC);
	}
	else if (clickedTapIndex == 3){
		CRect rect;
		GetClientRect(&rect);
		rect.bottom = 840;
		accountBookView->StartView(rect, this);
		accountBookView->OnDraw(pDC);
	}
	//else if (clickedTapIndex == 4) {}
	else if (clickedTapIndex == 4) {
		clickedTapIndex = 0;
		CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
		pFrame->OnInfo();
		deleteRgn();
	}
}


void CMrTravelerView::drawTapRgn(CDC * pDC)
{
	//CRgn tapRgn[6] 탭 리전 전역변수 선언
	for (int i = 0; i < 5; i++) {
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
			pDC->TextOut(25 + i * 200 + 35, 860, _T("INFO"));
		//else if (i == 5)
			//pDC->TextOut(25 + i * 200 + 45, 860, _T("INFO"));
	}
}

void CMrTravelerView::deleteRgn(){
	calendarView->prevMonthRgn.DeleteObject();
	calendarView->nextMonthRgn.DeleteObject();
	calendarView->plusButtonRgn.DeleteObject();
	calendarView->monthRgn.DeleteObject();
	for (int i = 0; i < 7; i++) {
		calendarView->dayRgn[i].DeleteObject();
	}
	for (int i = 0; i < calendarView->end_of_mon[calendarView->curMonth-1]; i++) {
		calendarView->dateRgn[i].DeleteObject();
	}
}


void CMrTravelerView::setPrevMonth()
{
	if (calendarView->curMonth == 1) {
		calendarView->curYear -= 1;
		calendarView->curMonth = 12;
		calendarView->firstDay = calendarView->firstDay - calendarView->end_of_mon[11] % 7;
		if (calendarView->firstDay <= 0)calendarView->firstDay += 7;
	}
	else {
		calendarView->firstDay = calendarView->firstDay - calendarView->end_of_mon[calendarView->curMonth - 2] % 7;
		if (calendarView->firstDay <= 0)calendarView->firstDay += 7;
		calendarView->curMonth -= 1;
	}
}
void CMrTravelerView::setNextMonth()
{
	calendarView->firstDay = (calendarView->firstDay + calendarView->end_of_mon[calendarView->curMonth - 1]) % 7;
	if (calendarView->curMonth == 12) {
		calendarView->curYear += 1;
		calendarView->curMonth = 1;
	}
	else calendarView->curMonth += 1;
}
void CMrTravelerView::setDrag(int i)
{
	CClientDC dc(this);
	isDragged = TRUE;
	dragFlag = true;
	calendarView->startDate= i;//드래그 시작 일 리전 인덱스
	dc.FillRgn(&calendarView->dateRgn[calendarView->startDate], &CBrush(RGB(230, 230, 230)));
}
void CMrTravelerView::setPlusButton()
{

	//parentView->Invalidate();
}
void CMrTravelerView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	m_pt = point;
	CRect rect;
	GetClientRect(&rect);
	rect.bottom = 840;

	//탭 리전 클릭 처리
	for (int i = 0; i < 6; i++) {
		if (tapRgn[i].PtInRegion(m_pt)) {
			clickedTapIndex = i;//드래그 시작 일 리전 인덱스
			dc.FillRgn(&tapRgn[clickedTapIndex], &CBrush(RGB(216, 216, 216)));
			break;
		}
	}
	if (clickedTapIndex == 0 && Util::IsPointInRect(rect, point)) {
		//일 리전 드래그 처리
		for (int i = 0; i < calendarView->end_of_mon[calendarView->curMonth - 1]; i++) {
			if (calendarView->dateRgn[i].PtInRegion(m_pt) && clickedTapIndex == 0) {
				setDrag(i);
				break;
			}
		}

		//이전 달 넘어가기
		if (calendarView->prevMonthRgn.PtInRegion(m_pt) && clickedTapIndex == 0) {
			setPrevMonth();

		}
		//다음 달 넘어가기
		else if (calendarView->nextMonthRgn.PtInRegion(m_pt) && clickedTapIndex == 0) {
			//다음 달 처리
			setNextMonth();
		}

		for (int i = 0; i < calendarView->end_of_mon[calendarView->curMonth - 1]; i++) {
			if (!calendarView->dateRgn[i].PtInRegion(m_pt) && clickedTapIndex == 0 && !calendarView->plusButtonRgn.PtInRegion(m_pt))
			{
				isDragged = FALSE;
			}
		}
		//플러스
		if (calendarView->plusButtonRgn.PtInRegion(m_pt))	//임시
		{
			calendarView->relatedCalendar = TRUE;
			clickedTapIndex = 1;
			/*
			if (calendarView->relatedCalendar) {
				CTime(calendarView->curYear, calendarView->curYear, endDate, 0, 0, 0);
				calendarView->relatedCalendar = FALSE;
			}
			*/
			scheduleView->OnLButtonDown(point);
			CView::OnLButtonDown(nFlags, point);
			return;
		}
	}
	else if (clickedTapIndex == 1 && Util::IsPointInRect(rect, point))	//임시
	{
		scheduleView->OnLButtonDown(point);
		CView::OnLButtonDown(nFlags, point);
		return;
	}
	else if (clickedTapIndex == 2 && Util::IsPointInRect(rect, point))
	{
		todoListView->OnLButtonDown(point);
		CView::OnLButtonDown(nFlags, point);
		return;
	}
	else if (clickedTapIndex == 3 && Util::IsPointInRect(rect, point))
	{
		accountBookView->OnLButtonDown(point);
		CView::OnLButtonDown(nFlags, point);
		return;
	}
	if (clickedTapIndex == 0) {
		deleteRgn();
	}
	Invalidate();
	CView::OnLButtonDown(nFlags, point);
}

void CMrTravelerView::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	m_pt = point;
	int prev_end = calendarView->startDate;
	int next_end = calendarView->startDate;
	if (dragFlag) {//드래그 처리
		
		for (int i = 0; i < 31; i++) {
			if (calendarView->dateRgn[i].PtInRegion(m_pt)) {
				prev_end = next_end;
				next_end = i;
				break;
			}
		}
		if (calendarView->startDate> next_end) {//스와핑
			int tmp; tmp = calendarView->startDate; calendarView->startDate = next_end; next_end = tmp;
		}
		//if (startDate < prev_end&&next_end < prev_end) 
		for (int i = calendarView->startDate; i <= next_end; i++) {
			dc.FillRgn(&calendarView->dateRgn[i], &CBrush(RGB(230, 230, 230)));
		}
	}
	CView::OnMouseMove(nFlags, point);
}

void CMrTravelerView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	m_pt = point;
	if (dragFlag) {//드래그 처리
		for (int i = 0; i < 31; i++) {
			if (calendarView->dateRgn[i].PtInRegion(m_pt)) {
				calendarView->endDate = i;
				if (calendarView->startDate > calendarView->endDate) {//스와핑
					int tmp; tmp = calendarView->startDate; calendarView->startDate = calendarView->endDate; calendarView->endDate = tmp;
				}
				break;
			}
		}

		for (int i = calendarView->startDate; i <= calendarView->endDate; i++) {
			dc.FillRgn(&calendarView->dateRgn[i], &CBrush(RGB(230, 230, 230)));
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




void CMrTravelerView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;
	GetClientRect(&rect);
	rect.bottom = 840;
	if (clickedTapIndex == 2 && Util::IsPointInRect(rect, point))	//임시
	{
		todoListView->OnLButtonDblClk(point);
		CView::OnLButtonDblClk(nFlags, point);
		return;
	}
	CView::OnLButtonDblClk(nFlags, point);
}


void CMrTravelerView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;
	GetClientRect(&rect);
	rect.bottom = 840;
	if (clickedTapIndex == 2 && Util::IsPointInRect(rect, point))	//임시
	{
		todoListView->OnRButtonDown(point);
		CView::OnRButtonDblClk(nFlags, point);
		return;
	}
	CView::OnRButtonDown(nFlags, point);
}
