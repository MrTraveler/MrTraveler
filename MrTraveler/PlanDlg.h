#pragma once
#include "atltime.h"
#include "afxwin.h"


// PlanDlg ��ȭ �����Դϴ�.

class PlanDlg : public CDialogEx
{
	DECLARE_DYNAMIC(PlanDlg)

public:
	PlanDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~PlanDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
