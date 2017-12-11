#pragma once
#include "afxwin.h"
#include <vector>
// AccountBookDlg ��ȭ �����Դϴ�.
class AccountInfo;
class AccountBookDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AccountBookDlg)

public:
	AccountBookDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~AccountBookDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
};
