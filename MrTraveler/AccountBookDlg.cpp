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
	ON_BN_CLICKED(IDC_MODIFY, &AccountBookDlg::OnBnClickedModify)
	ON_BN_CLICKED(IDC_DELETE, &AccountBookDlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_ADD, &AccountBookDlg::OnBnClickedAdd)
	ON_LBN_SELCHANGE(IDC_LIST2, &AccountBookDlg::OnLbnSelchangeList2)
END_MESSAGE_MAP()


// AccountBookDlg 메시지 처리기입니다.


void AccountBookDlg::OnBnClickedModify()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void AccountBookDlg::OnBnClickedDelete()
{

}


void AccountBookDlg::OnBnClickedAdd()
{
	AccountInfo info;
	info.content = m_content;
	info.day = day;
	info.month = month;
	info.year = year;
	if (m_type == 0)
		info.money = m_money;
	else if (m_type == 1)
		info.money = -m_money;
	printf("m_content  : %s\n", m_content);
	m_accountListBox.AddString(m_content);
	accountList.push_back(info);
}


void AccountBookDlg::OnLbnSelchangeList2()
{
	int sel = m_accountListBox.GetCurSel();
	AccountInfo info = accountList[sel];
	m_content = info.content;
	m_type = info.money < 0 ? 1 : 0;
	m_money = abs(info.money);

}
