// TodoDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MrTraveler.h"
#include "TodoDlg.h"
#include "afxdialogex.h"
#include "TodoData.h"

// TodoDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(TodoDlg, CDialogEx)

TodoDlg::TodoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, title(_T(""))
	, icon(0)
	, todo(_T(""))
{

}

TodoDlg::~TodoDlg()
{
}

void TodoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TO_1, title);
	DDX_CBIndex(pDX, IDC_TO_2, icon);
	DDX_Text(pDX, IDC_TO_3, todo);
	DDX_Control(pDX, IDC_TO_4, todoListBox);
}


BEGIN_MESSAGE_MAP(TodoDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &TodoDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON4, &TodoDlg::OnBnClickedButton4)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// TodoDlg �޽��� ó�����Դϴ�.


void TodoDlg::OnBnClickedOk()
{
	int count = todoListBox.GetCount();
	for (int i = 0; i < count; i++)
	{
		CString str;
		todoListBox.GetText(i, str);
		ptodo->list.push_back(str);
	}
	CDialogEx::OnOK();
}


void TodoDlg::OnBnClickedButton4()
{
	CString str;
	GetDlgItemText(IDC_TO_3, str);
	todoListBox.AddString(str);
}


BOOL TodoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
