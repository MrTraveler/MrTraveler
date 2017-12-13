#pragma once

// CalendarView 뷰입니다.

class CMrTravelerView;

class CalendarView : public CView
{
	DECLARE_DYNCREATE(CalendarView)

public:
	CalendarView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CalendarView();
public:
	CMrTravelerView* mr;
	CTime cTime = CTime::GetCurrentTime();//현재 정보 불러오기
	int curYear = cTime.GetYear();//현재 년도
	int curMonth = cTime.GetMonth();//현재 월
	int curDate = cTime.GetDay();//현재 날짜
	int curDay = cTime.GetDayOfWeek();//현재 요일
	int firstDay = curDay - (curDate % 7 - 1);//현재 월의 1일의 요일 구하기
	int end_of_mon[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };//월별 총 일수
	CRgn monthRgn;//월 리전
	CRgn nextMonthRgn;
	CRgn prevMonthRgn;
	CRgn plusButtonRgn;
	bool dragFlag;
	bool plus = FALSE;
	int startYear, startMonth, startDate, endYear, endMonth, endDate;
	bool relatedCalendar = FALSE;
	CRgn dateRgn[43];
	CRgn dayRgn[7];//요일 리전
	CRgn blockRgn[31];
	int idx = 0;
	CFont font;
public:
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
	void drawCalendar(CDC* pDC);
	void drawTimeBlock(CDC* pDC);
	void drawPlusButton(CDC* pDC);
	void drawMonthRgn(CDC* pDC);
	void drawMonthText(CDC* pDC);
	void drawDayRgn(CDC* pDC);
	void drawDayText(CDC* pDC);
	void drawDateRgn(CDC* pDC);
	void drawDateText(CDC* pDC);
	void drawNextMonth(CDC* pDC);
	void drawPrevMonth(CDC* pDC);
	void drawLogo(CDC* pDC);
	int getDay(int date);
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


