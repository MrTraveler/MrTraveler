#pragma once
#include "afxwin.h"


// TodoDlg 대화 상자입니다.
struct Todo;
class TodoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(TodoDlg)

public:
	TodoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~TodoDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString title;
	int icon;
	CString todo;
	CListBox todoListBox;
	int count;
	Todo *ptodo;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton4();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedDelete();
};
