
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

	if (clickedTapIndex == 0) {
		drawCalendar(pDC);
	}
	else if (clickedTapIndex == 1) {}
	else if (clickedTapIndex == 2) {}
	else if (clickedTapIndex == 3) {}
	else if (clickedTapIndex == 4) {}
	else if (clickedTapIndex == 5) {}
}

void CMrTravelerView::drawCalendar(CDC * pDC)
{

	//화면 고정 규격 : 1475 * 950

	//현재 년도,월,일,요일 저장
	CTime cTime = CTime::GetCurrentTime();//현재 정보 불러오기
	int curYear = cTime.GetYear();//현재 년도
	int curMonth = cTime.GetMonth();//현재 월
	int curDate = cTime.GetDay();//현재 날짜
	int curDay = cTime.GetDayOfWeek();//현재 요일
	int firstDay = curDay - (curDate % 7 - 1);//현재 월의 1일의 요일 구하기

											  //월 리전 생성 및 출력
	CRgn monthRgn;//월 리전
	monthRgn.CreateEllipticRgn((1400 - 150) / 2 + 25, 50 - 50, (1400 - 150) / 2 + 150 + 25, 200 - 50);
	pDC->FillRgn(&monthRgn, &CBrush(RGB(154, 202, 235)));
	CFont font;
	font.CreatePointFont(400, _T("바탕체"));
	CString strMonth;
	strMonth.Format(_T("%d"), curMonth);
	pDC->SetBkColor(RGB(154, 202, 235));
	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->SelectObject(&font);
	pDC->TextOut((1400 - 150) / 2 + 32 + 25, 50 + 32 + 5 - 50, strMonth);

	//요일 리전 생성 및 출력
	CRgn dayRgn[7];//요일 리전
	for (int day = 0; day < 7; day++) {
		dayRgn[day].CreateRoundRectRgn(day % 7 * 200 + 25, 200, (day % 7 + 1) * 200 + 25, 250, 20, 20);
		pDC->FillRgn(&dayRgn[day], &CBrush(RGB(154, 202, 235)));

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

	//월별 일수 및 윤년 처리
	int end_of_mon[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };//월별 총 일수
	if (!(curYear % 4) && ((curYear % 100) || !(curYear % 400))) end_of_mon[1] = 29;

	//일 리전 생성 및 출력
	//헤더에 전역변수 dateRgn[day] 생성
	//dateRgn[0]=1일 참조
	//dateRgn[1]=2일 참조
	for (int day = firstDay - 1; day < end_of_mon[curMonth - 1] + firstDay - 1; day++) {
		dateRgn[day - firstDay + 1].CreateRoundRectRgn((day) % 7 * 200 + 25, 250 + (day) / 7 * 100, ((day) % 7 + 1) * 200 + 25, 250 + ((day) / 7 + 1) * 100, 20, 20);
		pDC->FillRgn(&dateRgn[day - firstDay + 1], &CBrush(RGB(255, 255, 255)));
		pDC->FrameRgn(&dateRgn[day - firstDay + 1], &CBrush(RGB(216, 216, 216)), 2, 2);

		CFont font;
		font.CreatePointFont(100, _T("바탕"));
		CString strDate;
		strDate.Format(_T("%d"), day - firstDay + 2);
		pDC->SetBkColor(RGB(255, 255, 255));
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SelectObject(&font);
		pDC->TextOut((day) % 7 * 200 + 25 + 10, 250 + (day) / 7 * 100 + 10, strDate);
	}

	//탭 리전 생성 및 출력
	//CRgn tapRgn[6] 탭 리전 전역변수 선언
	for (int i = 0; i < 6; i++) {
		tapRgn[i].CreateRoundRectRgn(i % 7 * 200, 850, (i % 7 + 1) * 200, 900, 20, 20);
		pDC->FillRgn(&tapRgn[i], &CBrush(RGB(154, 202, 235)));

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
			break;
		}
	}
	//탭 리전 처리
	for (int i = 0; i < 6; i++) {
		if (tapRgn[i].PtInRegion(m_pt)) {
			clickedTapIndex = i;//드래그 시작 일 리전 인덱스
			dc.FillRgn(&tapRgn[clickedTapIndex], &CBrush(RGB(216, 216, 216)));
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
	if (dragFlag) {
		for (int i = 0; i < 31; i++) {
			if (dateRgn[i].PtInRegion(m_pt)) {
				endPos = i;
				break;
			}
		}

		for (int i = startPos; i <= endPos; i++) {
			dc.FillRgn(&dateRgn[i], &CBrush(RGB(230, 230, 230)));
		}
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


