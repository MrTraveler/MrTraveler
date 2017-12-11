#pragma once
#include "afxwin.h"
#include <vector>
// AccountBookDlg 대화 상자입니다.
class AccountInfo;
class AccountBookDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AccountBookDlg)

public:
	AccountBookDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~AccountBookDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	std::vector<AccountInfo> accountList;
	afx_msg void OnBnClickedModify();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedAdd();
	int day;
	int year;
	int month;
	afx_msg void OnLbnSelchangeList2();
	CString m_content;
	int m_type;
	int m_money;
	CListBox m_accountListBox;
	CString m_date;
	virtual BOOL OnInitDialog();
};
