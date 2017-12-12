#pragma once
#include "atltime.h"
#include "afxwin.h"


// PlanDlg 대화 상자입니다.

class PlanDlg : public CDialogEx
{
	DECLARE_DYNAMIC(PlanDlg)

public:
	PlanDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~PlanDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_title;
	CString m_content;
	CTime m_fromTime;
	CTime m_toTime;
	CStatic m_showColor;
	int m_fromTimeHour;
	int m_fromTimeMin;
	int m_toTimeHour;
	int m_toTimeMin;
	int m_budget;
	afx_msg void OnBnClickedCancle();
};
