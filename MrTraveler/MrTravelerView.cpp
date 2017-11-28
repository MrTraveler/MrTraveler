
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
END_MESSAGE_MAP()

// CMrTravelerView 생성/소멸

CMrTravelerView::CMrTravelerView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	CMrTravelerParceHtml *x = new CMrTravelerParceHtml();
	x->ParceHtml(_T("https://v3.exchangerate-api.com/bulk/3090405efae2c21d79cc569c/KRW"));
}

CMrTravelerView::~CMrTravelerView()
{
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

	CTime cTime = CTime::GetCurrentTime();
	int curYear, curMonth, curDate;
	curYear = cTime.GetYear();
	curMonth= cTime.GetMonth();
	curDate = cTime.GetDay();

	CRgn monthRgn;
	monthRgn.CreateEllipticRgn((1400 - 150) / 2, 0, (1400 - 150) / 2+ 150, 150);
	pDC->FillRgn(&monthRgn, &CBrush(RGB(154, 202, 235)));

	int curDay = cTime.GetDayOfWeek();

	CRgn dayRgn[7];
	for (int day = 0; day < 7; day++) {
		dayRgn[day].CreateRoundRectRgn(day % 7 * 200, 150, (day % 7 + 1) * 200, 200, 20, 20);
		pDC->FillRgn(&dayRgn[day], &CBrush(RGB(154, 202, 235)));
	}

	int end_of_mon[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (!(curYear % 4) && ((curYear % 100) || !(curYear % 400))) end_of_mon[1] = 29;
	
	CRgn dateRgn[43];
	for (int day = 0; day < end_of_mon[curMonth-1]; day++) {
		dateRgn[day + curDay].CreateRoundRectRgn((day + curDay) % 7 * 200, 200+(day + curDay )/7*100,
			((day + curDay) % 7 + 1) * 200, 200 + ((day + curDay) / 7+1) * 100, 20, 20);
		pDC->FillRgn(&dateRgn[day], &CBrush(RGB(255, 255, 255)));
		pDC->FrameRgn(&dateRgn[day], &CBrush(RGB(154, 202, 235)), 1.5, 1.5);
	}

	CRgn tapRgn[6];
	for (int i = 0; i < 6; i++) {
		tapRgn[i].CreateRoundRectRgn(i % 7 * 200, 800, (i % 7 + 1) * 200, 850, 20, 20);
		pDC->FillRgn(&tapRgn[i], &CBrush(RGB(154, 202, 235)));
	}

	//CRgn dayRgn[32];//
/*
	for (int day = 0; day <= 35; day++) {
		CRect rt();
		dayRgn[day].CreateRectRgnIndirect(&rt);
		pDC->FillRgn(&dayRgn[day], &CBrush(RGB(255, 255, 255)));
		pDC->FrameRgn(&dayRgn[day], &CBrush(RGB(255, 197, 108)), 1, 1);
		dayRgn[day].DeleteObject();
	}
	*/
	//CRgn tapRgn[6];
	/*
	for (int i = 0; i < 6; i++) {
		CRect rt(i%6*window.right/6,window.bottom-100, (i % 6+1) * window.right / 6, window.bottom );
		tapRgn[i].CreateRectRgnIndirect(&rt);
		pDC->FillRgn(&tapRgn[i], &CBrush(RGB(255, 255, 255)));
		pDC->FrameRgn(&tapRgn[i], &CBrush(RGB(255, 197, 108)), 1, 1);
		tapRgn[i].DeleteObject();
	}*/
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
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


void CMrTravelerView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnLButtonUp(nFlags, point);
}