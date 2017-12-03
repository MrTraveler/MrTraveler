#pragma once


// CalendarView ���Դϴ�.

class CalendarView : public CView
{
	DECLARE_DYNCREATE(CalendarView)

public:
	CalendarView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CalendarView();
public:
	CTime cTime = CTime::GetCurrentTime();//���� ���� �ҷ�����
	int curYear = cTime.GetYear();//���� �⵵
	int curMonth = cTime.GetMonth();//���� ��
	int curDate = cTime.GetDay();//���� ��¥
	int curDay = cTime.GetDayOfWeek();//���� ����
	int firstDay = curDay - (curDate % 7 - 1);//���� ���� 1���� ���� ���ϱ�
	int end_of_mon[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };//���� �� �ϼ�
	CRgn monthRgn;//�� ����
	bool dragFlag;
	CRgn dateRgn[43];
	CRgn dayRgn[7];//���� ����
public:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	void drawCalendar(CDC* pDC);
	void drawMonthRgn(CDC* pDC);
	void drawMonthText(CDC* pDC);
	void drawDayRgn(CDC* pDC);
	void drawDayText(CDC* pDC);
	void drawDateRgn(CDC* pDC);
	void drawDateText(CDC* pDC);
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


