// PlanDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MrTraveler.h"
#include "PlanDlg.h"
#include "afxdialogex.h"


// PlanDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(PlanDlg, CDialogEx)

PlanDlg::PlanDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_title(_T(""))
	, m_content(_T(""))
	, m_fromTime(0)
	, m_toTime(0)
	, m_fromTimeHour(0)
	, m_fromTimeMin(0)
	, m_toTimeHour(0)
	, m_toTimeMin(0)
	, m_budget(0)
{
	
}

PlanDlg::~PlanDlg()
{
}

void PlanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_title);
	DDX_Text(pDX, IDC_EDIT2, m_content);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_fromTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER3, m_toTime);
	DDX_Control(pDX, IDC_SHOWCOLOR, m_showColor);
	DDX_Text(pDX, IDC_EDIT5, m_fromTimeHour);
	DDV_MinMaxInt(pDX, m_fromTimeHour, 0, 23);
	DDX_Text(pDX, IDC_EDIT7, m_fromTimeMin);
	DDV_MinMaxInt(pDX, m_fromTimeMin, 0, 59);
	DDX_Text(pDX, IDC_EDIT6, m_toTimeHour);
	DDV_MinMaxInt(pDX, m_toTimeHour, 0, 23);
	DDX_Text(pDX, IDC_EDIT8, m_toTimeMin);
	DDV_MinMaxInt(pDX, m_toTimeMin, 0, 59);
	DDX_Text(pDX, IDC_EDIT3, m_budget);
	DDV_MinMaxInt(pDX, m_budget, 0, 999999999);
}


BEGIN_MESSAGE_MAP(PlanDlg, CDialogEx)
	ON_BN_CLICKED(IDC_MORECOLOR, &PlanDlg::OnBnClickedMorecolor)
	ON_BN_CLICKED(IDCANCLE, &PlanDlg::OnBnClickedCancle)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// PlanDlg 메시지 처리기입니다.


void PlanDlg::OnBnClickedMorecolor()
{
	CColorDialog colorDlg;
	if (colorDlg.DoModal() == IDOK)
		m_color = colorDlg.GetColor();
	Invalidate();
}


void PlanDlg::OnBnClickedCancle()
{
	EndDialog(IDCANCLE);
}


void PlanDlg::OnPaint()
{
	CPaintDC dc(this);
	CRect rect;
	CBrush brush(m_color);
	m_showColor.GetClientRect(&rect);
	CDC * adc = m_showColor.GetDC();
	adc->FillRect(rect, &brush);
	m_showColor.ReleaseDC(adc);
}
