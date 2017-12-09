// MrTravelerView.h : CMrTravelerView 클래스의 인터페이스
//

#pragma once

class CMrTravelerParceHtml;
class TodoListView;
class ScheduleView;
class CalendarView;
class TodoData;
class CMrTravelerDoc;
class CMainFrame;
class CMrTravelerView : public CView
{
protected: // serialization에서만 만들어집니다.
	DECLARE_DYNCREATE(CMrTravelerView)

// 특성입니다.
public:
	CMrTravelerView();
	CMrTravelerDoc* GetDocument() const;

// 작업입니다.
public:
	TodoListView* todoListView;
	ScheduleView* scheduleView;
	CalendarView* calendarView;
	CMainFrame* mainfrm;
	CPoint m_pt;
	CRgn tapRgn[6];
	bool dragFlag;

	int startYear, startMonth, startDate, endYear, endMonth, endDate;
	bool isDragged = FALSE;

	int clickedTapIndex;//클릭된 탭 인덱스
	CFont font;
	CDC *pDC;
// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	void drawTapRgn(CDC* pDC);
	void drawTapText(CDC* pDC);

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

// 구현입니다.
public:
	virtual ~CMrTravelerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // MrTravelerView.cpp의 디버그 버전
inline CMrTravelerDoc* CMrTravelerView::GetDocument() const
   { return reinterpret_cast<CMrTravelerDoc*>(m_pDocument); }
#endif

