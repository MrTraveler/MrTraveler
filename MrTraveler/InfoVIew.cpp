// InfoVIew.cpp : 구현 파일입니다.
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
	m_ExchangeRatefont.CreateFont(30, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,	DEFAULT_PITCH | FF_SWISS, _T("굴림체"));
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
	DDX_Control(pDX, IDC_EXPLORER1, m_GoogleMap);
	m_GoogleMap.Navigate(GetResURL(IDR_HTML_GOOGLEMAP),NULL,NULL,NULL,NULL);
}

BEGIN_MESSAGE_MAP(CInfoVIew, CFormView)
	ON_CBN_SELCHANGE(IDC_COUNTRY, &CInfoVIew::OnCbnSelchangeConutry)
	ON_EN_UPDATE(IDC_ExchangeRate1, &CInfoVIew::OnEnUpdateExchangerate1)
END_MESSAGE_MAP()


// CInfoVIew 진단입니다.

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


// CInfoVIew 메시지 처리기입니다.




void CInfoVIew::OnCbnSelchangeConutry()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nIndex = m_Currency_unit.GetCurSel();
	CString str;
	str.Format(_T("%d"), nIndex);
	country = _ttoi(str);
	OnEnUpdateExchangerate1();
//	AfxMessageBox(str);
}


void CInfoVIew::OnEnUpdateExchangerate1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하여, IParam 마스크에 OR 연산하여 설정된 ENM_SCROLL 플래그를 지정하여 컨트롤에 EM_SETEVENTMASK 메시지를 보내지 않으면
	// 편집 컨트롤이 바뀐 텍스트를 표시하려고 함을 나타냅니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	double ER1, ER2;
	CString str,str2;
	GetDlgItem(IDC_ExchangeRate1)->SetFont(&m_ExchangeRatefont);
	GetDlgItem(IDC_KRW)->SetFont(&m_ExchangeRatefont);
	GetDlgItem(IDC_ExchangeRate1)->GetWindowText(str);
	ER1 = _wtof(str);
	ER2 = ER1*(1/Parce->ExchangeRate[country]);
	str2.Format(_T(" = %.2lf원"), ER2);
	GetDlgItem(IDC_KRW)->SetWindowText(str2);

}





CString CInfoVIew::GetResURL(int szResID)

{
	CString sRes;
	TCHAR szExePath[MAX_PATH];
	GetModuleFileName(NULL, szExePath, sizeof(szExePath));
	sRes.Format(_T("res://%s/%d"), szExePath, szResID);
	return sRes;
}


