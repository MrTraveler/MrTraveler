// MrTravelerView.h : CMrTravelerView Ŭ������ �������̽�
//

#pragma once

class CMrTravelerParceHtml;
class TodoListView;
class ScheduleView;
class CalendarView;
class TodoData;
class PlanData;
class CMrTravelerDoc;
class CMainFrame;
class AccountBookView;
class CMrTravelerView : public CView
{
protected: // serialization������ ��������ϴ�.
	DECLARE_DYNCREATE(CMrTravelerView)

// Ư���Դϴ�.
public:
	CMrTravelerView();
	CMrTravelerDoc* GetDocument() const;

// �۾��Դϴ�.
public:
	TodoListView* todoListView;
	ScheduleView* scheduleView;
	CalendarView* calendarView;
	CMainFrame* mainfrm;
	AccountBookView *accountBookView;
	CPoint m_pt;
	CRgn tapRgn[6];
	bool dragFlag;
	bool isDragged = FALSE;
	int clickedTapIndex;//Ŭ���� �� �ε���
	
	CFont font;
	CDC *pDC;
// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	void drawTapRgn(CDC* pDC);
	void drawTapText(CDC* pDC);

    void drawLogo(CDC* pdc);
	void deleteRgn();
	void testinit();
	void setDrag(int i);
	void setPrevMonth();
	void setNextMonth();
	void setPlusButton();
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CMrTravelerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // MrTravelerView.cpp�� ����� ����
inline CMrTravelerDoc* CMrTravelerView::GetDocument() const
   { return reinterpret_cast<CMrTravelerDoc*>(m_pDocument); }
#endif

