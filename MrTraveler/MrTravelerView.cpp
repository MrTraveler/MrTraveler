
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

void CMrTravelerView::OnDraw(CDC* /*pDC*/)
{
	CMrTravelerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CMrTravelerView �μ�

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
