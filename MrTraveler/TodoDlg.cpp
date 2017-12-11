// TodoDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MrTraveler.h"
#include "TodoDlg.h"
#include "afxdialogex.h"+
#include "TodoData.h"

// TodoDlg 대화 상자입니다.

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
	ON_BN_CLICKED(IDC_BUTTON5, &TodoDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDDELETE, &TodoDlg::OnBnClickedDelete)
END_MESSAGE_MAP()


// TodoDlg 메시지 처리기입니다.


void TodoDlg::OnBnClickedOk()
{
	int count = todoListBox.GetCount();
	std::vector<CString> v;
	for (int i = 0; i < count; i++)
	{
		CString str;
		todoListBox.GetText(i, str);
		v.push_back(str);
	}
	ptodo->list = v;
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

	for (int i = 0; i < ptodo->list.size(); i++)
		todoListBox.AddString(ptodo->list[i]);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void TodoDlg::OnBnClickedButton5()	//할일체크
{
	todoListBox.DeleteString(todoListBox.GetCurSel());
}


void TodoDlg::OnBnClickedDelete()
{
	EndDialog(IDDELETE);
}
