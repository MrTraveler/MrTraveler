// InfoVIew.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MrTraveler.h"
#include "InfoVIew.h"


// CInfoVIew

IMPLEMENT_DYNCREATE(CInfoVIew, CFormView)

CInfoVIew::CInfoVIew()
	: CFormView(IDD_FORMVIEW)
{
	Parce = new CMrTravelerParceHtml;
	Parce->RoadExchangeRate();
	m_ExchangeRatefont.CreateFont(30, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,	DEFAULT_PITCH | FF_SWISS, _T("����ü"));
	country = 0;
}

CInfoVIew::~CInfoVIew()
{
}

void CInfoVIew::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COUNTRY, m_Currency_unit);
	DDX_Control(pDX, IDC_ExchangeRate1, m_ExchangeRate1);
	DDX_Control(pDX, IDC_KRW, m_krw);
}

BEGIN_MESSAGE_MAP(CInfoVIew, CFormView)
	ON_CBN_SELCHANGE(IDC_COUNTRY, &CInfoVIew::OnCbnSelchangeConutry)
	ON_EN_UPDATE(IDC_ExchangeRate1, &CInfoVIew::OnEnUpdateExchangerate1)
END_MESSAGE_MAP()


// CInfoVIew �����Դϴ�.

#ifdef _DEBUG
void CInfoVIew::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CInfoVIew::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CInfoVIew �޽��� ó�����Դϴ�.




void CInfoVIew::OnCbnSelchangeConutry()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int nIndex = m_Currency_unit.GetCurSel();
	CString str;
	str.Format(_T("%d"), nIndex);
	country = _ttoi(str);
	OnEnUpdateExchangerate1();
//	AfxMessageBox(str);
}


void CInfoVIew::OnEnUpdateExchangerate1()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CFormView::OnInitDialog() �Լ��� ������ 
	//�Ͽ�, IParam ����ũ�� OR �����Ͽ� ������ ENM_SCROLL �÷��׸� �����Ͽ� ��Ʈ�ѿ� EM_SETEVENTMASK �޽����� ������ ������
	// ���� ��Ʈ���� �ٲ� �ؽ�Ʈ�� ǥ���Ϸ��� ���� ��Ÿ���ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	double ER1, ER2;
	CString str,str2;
	GetDlgItem(IDC_ExchangeRate1)->SetFont(&m_ExchangeRatefont);
	GetDlgItem(IDC_KRW)->SetFont(&m_ExchangeRatefont);
	GetDlgItem(IDC_ExchangeRate1)->GetWindowText(str);
	ER1 = _wtof(str);
	ER2 = ER1*(1/Parce->ExchangeRate[country]);
	str2.Format(_T(" = %.2lf��"), ER2);
	GetDlgItem(IDC_KRW)->SetWindowText(str2);

}


