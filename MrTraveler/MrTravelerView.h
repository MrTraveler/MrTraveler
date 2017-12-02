
// MrTravelerView.h : CMrTravelerView 클래스의 인터페이스
//

#pragma once

class CMrTravelerParceHtml;
class CMrTravelerView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMrTravelerView();
	DECLARE_DYNCREATE(CMrTravelerView)

// 특성입니다.
public:
	CMrTravelerDoc* GetDocument() const;

// 작업입니다.
public:
	CPoint m_pt;
	bool dragFlag;
	CRgn dateRgn[43];
	CRgn dayRgn[7];//요일 리전
	CRgn tapRgn[6];
	CRgn monthRgn;//월 리전
	int startPos, endPos;
	int clickedTapIndex=0;//클릭된 탭 인덱스
	CTime cTime = CTime::GetCurrentTime();//현재 정보 불러오기
	int curYear = cTime.GetYear();//현재 년도
	int curMonth = cTime.GetMonth();//현재 월
	int curDate = cTime.GetDay();//현재 날짜
	int curDay = cTime.GetDayOfWeek();//현재 요일
	int firstDay = curDay - (curDate % 7 - 1);//현재 월의 1일의 요일 구하기
	int end_of_mon[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };//월별 총 일수
	CDC *pDC;
// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void drawCalendar(CDC* pDC);
	void drawMonthRgn(CDC* pDC);
	void drawMonthText(CDC* pDC);
	void drawDayRgn(CDC* pDC);
	void drawDayText(CDC* pDC);
	void drawDateRgn(CDC* pDC);
	void drawDateText(CDC* pDC);
	void drawTapRgn(CDC* pDC);
	void drawTapText(CDC* pDC);
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

