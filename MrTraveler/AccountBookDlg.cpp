// AccountBookDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MrTraveler.h"
#include "AccountBookDlg.h"
#include "afxdialogex.h"
#include "AccountData.h"

// AccountBookDlg 대화 상자입니다.

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

void AccountBookDlg::DoDataExchange(CDataExchange* pDX)		//DDX 버그있음 알아서 고치삼요
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


// AccountBookDlg 메시지 처리기입니다.



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
	
	m_accountListBox.AddString(m_content);
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
		m_accountListBox.AddString(info.content);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
