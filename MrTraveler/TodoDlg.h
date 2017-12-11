#pragma once
#include "afxwin.h"


// TodoDlg ��ȭ �����Դϴ�.
struct Todo;
class TodoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(TodoDlg)

public:
	TodoDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~TodoDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
