// AccountBookDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MrTraveler.h"
#include "AccountBookDlg.h"
#include "afxdialogex.h"
#include "AccountData.h"

// AccountBookDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(AccountBookDlg, CDialogEx)

AccountBookDlg::AccountBookDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, m_content(_T(""))
	, m_type(0)
	, m_money(0)
	, m_date(_T(""))
{

}

AccountBookDlg::~AccountBookDlg()
{
}

void AccountBookDlg::DoDataExchange(CDataExchange* pDX)		//DDX �������� �˾Ƽ� ��ġ���
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_content);
	DDX_CBIndex(pDX, IDC_COMBO1, m_type);
	DDX_Text(pDX, IDC_EDIT4, m_money);
	DDX_Control(pDX, IDC_LIST2, m_accountListBox);
	DDX_Text(pDX, IDC_EDIT2, m_date);
}


BEGIN_MESSAGE_MAP(AccountBookDlg, CDialogEx)
	ON_BN_CLICKED(IDC_DELETE, &AccountBookDlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_ADD, &AccountBookDlg::OnBnClickedAdd)
	ON_LBN_SELCHANGE(IDC_LIST2, &AccountBookDlg::OnLbnSelchangeList2)
END_MESSAGE_MAP()


// AccountBookDlg �޽��� ó�����Դϴ�.



void AccountBookDlg::OnBnClickedDelete()
{
	int sel = m_accountListBox.GetCurSel();
	if (sel == LB_ERR)
		return;
	m_accountListBox.DeleteString(sel);
	accountList.erase(accountList.begin() + sel);
}


void AccountBookDlg::OnBnClickedAdd()
{
	AccountInfo info;
	UpdateData(true);
	info.content = m_content;
	info.day = day;
	info.month = month;
	info.year = year;
	if (m_type == 0)
		info.money = m_money;
	else if (m_type == 1)
		info.money = -m_money;
	CString str;
	str.Format(_T("%-15s%10d"),m_content, (m_type == 0 ? 1 : -1) * m_money);
	m_accountListBox.AddString(str);
	accountList.push_back(info);
}


void AccountBookDlg::OnLbnSelchangeList2()
{
	UpdateData(true);
	int sel = m_accountListBox.GetCurSel();
	AccountInfo info = accountList[sel];
	m_content = info.content;
	m_type = info.money < 0 ? 1 : 0;
	m_money = abs(info.money);
	UpdateData(false);
}


BOOL AccountBookDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	for (int i = 0; i < accountList.size(); i++)
	{
		AccountInfo info = accountList[i];
		CString str;
		str.Format(_T("%-15s%10d"), info.content, info.money);
		m_accountListBox.AddString(str);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
