
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
	int curDay = cTime.GetDayOfWeek();
	int firstDay = curDay - (curDate % 7 - 1);//���� �� 1�� ����

	CRgn monthRgn;
	monthRgn.CreateEllipticRgn((1400 - 150) / 2+25, 50-50, (1400 - 150) / 2+ 150+25, 200-50);
	pDC->FillRgn(&monthRgn, &CBrush(RGB(154, 202, 235)));
	
	CFont font;
	font.CreatePointFont(400, _T("����ü")); 
	CString strMonth;
	strMonth.Format(_T("%d"), curMonth);
	pDC->SetBkColor(RGB(154, 202, 235));
	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->SelectObject(&font);
	pDC->TextOut((1400 - 150) / 2 + 32+25, 50+32+5-50,strMonth);

	CRgn dayRgn[7];
	for (int day = 0; day < 7; day++) {
		dayRgn[day].CreateRoundRectRgn(day % 7 * 200 + 25, 200, (day % 7 + 1) * 200 + 25, 250, 20, 20);
		pDC->FillRgn(&dayRgn[day], &CBrush(RGB(154, 202, 235)));

		CFont font;
		font.CreatePointFont(150, _T("����ü"));
		pDC->SetBkColor(RGB(154, 202, 235));
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SelectObject(&font);
		if (day == 0)
			pDC->TextOut(25 + day * 200+80, 210, _T("SUN"));
		else if (day == 1)
			pDC->TextOut(25 + day * 200 + 80, 210, _T("MON"));
		else if (day == 2)
			pDC->TextOut(25 + day * 200 + 80, 210, _T("TUE"));
		else if (day == 3) {
			pDC->TextOut(25 + day * 200 + 80, 210, _T("WED"));
			pDC->SetBkColor(RGB(255, 255, 255));
			pDC->SetTextColor(RGB(0,0,0));
			CString strYear;
			strYear.Format(_T("%d"), curYear);
			pDC->TextOut(15+ day * 200 + 80, 160, strYear);
		}
		else if (day == 4)
			pDC->TextOut(25 + day * 200 + 80, 210, _T("THU"));
		else if (day == 5)
			pDC->TextOut(25 + day * 200 + 80, 210, _T("FRI"));
		else if (day == 6)
			pDC->TextOut(25 + day * 200 + 80, 210, _T("SAT"));

	}

	int end_of_mon[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (!(curYear % 4) && ((curYear % 100) || !(curYear % 400))) end_of_mon[1] = 29;
	
	CRgn dateRgn[43];
	for (int day = firstDay-1; day < end_of_mon[curMonth-1]+firstDay-1; day++) {
		dateRgn[day].CreateRoundRectRgn((day) % 7 * 200 + 25,
			250+(day)/7*100,
			((day) % 7 + 1) * 200 + 25, 
			250 + ((day) / 7+1) * 100,
			20, 20);
		pDC->FillRgn(&dateRgn[day], &CBrush(RGB(255, 255, 255)));
		pDC->FrameRgn(&dateRgn[day], &CBrush(RGB(216,216,216)), 2, 2);

		CFont font;
		font.CreatePointFont(100, _T("������"));
		CString strDate;
		strDate.Format(_T("%d"), day-firstDay+2);
		pDC->SetBkColor(RGB(255, 255, 255));
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SelectObject(&font);
		pDC->TextOut((day) % 7 * 200 + 25+10,
			250 + (day) / 7 * 100+10, strDate);
	}

	CRgn tapRgn[6];
	for (int i = 0; i < 6; i++) {
		tapRgn[i].CreateRoundRectRgn(i % 7 * 200, 850, (i % 7 + 1) * 200, 900, 20, 20);
		pDC->FillRgn(&tapRgn[i], &CBrush(RGB(154, 202, 235)));

		CFont font;
		font.CreatePointFont(100, _T("����ü"));
		pDC->SetBkColor(RGB(154, 202, 235));
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SelectObject(&font);
		if (i == 0)
			pDC->TextOut(25 + i * 200 + 40, 860, _T("Ķ����"));
		else if (i == 1)
			pDC->TextOut(25 + i * 200 + 50, 860, _T("�� ��"));
		else if (i == 2)
			pDC->TextOut(25 + i * 200 + 30, 860, _T("TO DO List"));
		else if (i == 3)
			pDC->TextOut(25 + i * 200 + 40, 860, _T("�����"));
		else if (i == 4)
			pDC->TextOut(25 + i * 200 + 35, 860, _T("���̾"));
		else if (i == 5)
			pDC->TextOut(25 + i * 200 + 45, 860, _T("INFO"));
	}
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
