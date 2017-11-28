
// MrTravelerView.cpp : CMrTravelerView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "MrTraveler.h"
#endif

#include "MrTravelerDoc.h"
#include "MrTravelerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMrTravelerView

IMPLEMENT_DYNCREATE(CMrTravelerView, CView)

BEGIN_MESSAGE_MAP(CMrTravelerView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CMrTravelerView ����/�Ҹ�

CMrTravelerView::CMrTravelerView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CMrTravelerView::~CMrTravelerView()
{
}

BOOL CMrTravelerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMrTravelerView �׸���

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
	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


BOOL CMrTravelerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMrTravelerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMrTravelerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CMrTravelerView ����

#ifdef _DEBUG
void CMrTravelerView::AssertValid() const
{
	CView::AssertValid();
}

void CMrTravelerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMrTravelerDoc* CMrTravelerView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMrTravelerDoc)));
	return (CMrTravelerDoc*)m_pDocument;
}
#endif //_DEBUG


// CMrTravelerView �޽��� ó����


void CMrTravelerView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CView::OnLButtonUp(nFlags, point);
}
