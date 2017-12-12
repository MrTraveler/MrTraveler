// InfoVIew.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MrTraveler.h"
#include "InfoVIew.h"
#include "MainFrm.h"
#include "ManageData.h"



// CInfoVIew

IMPLEMENT_DYNCREATE(CInfoVIew, CFormView)

CInfoVIew::CInfoVIew()
	: CFormView(IDD_FORMVIEW)
	, m_conitem(_T(""))
	, m_Operator(_T(""))
{

	//CRect window;
	//GetWindowRect(&window);
	Parce = new CMrTravelerParceHtml;
	Parce->RoadExchangeRate();
	m_ExchangeRatefont.CreateFont(30, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("굴림체"));
	country = 0;
	m_Operator.Format(_T("+"));
}

CInfoVIew::~CInfoVIew()
{
}

void CInfoVIew::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	ResizeParentToFit(FALSE);
	DDX_Control(pDX, IDC_COUNTRY, m_Currency_unit);
	DDX_Control(pDX, IDC_ExchangeRate1, m_ExchangeRate1);
	DDX_Control(pDX, IDC_KRW, m_krw);
	DDX_Control(pDX, IDC_EXPLORER1, m_GoogleMap);
	m_GoogleMap.Navigate(GetResURL(IDR_HTML_GOOGLEMAP), NULL, NULL, NULL, NULL);
	DDX_CBString(pDX, IDC_COUNTRY, m_conitem);
	DDX_Control(pDX, IDC_BackButton, m_btnBack);

	DDX_Text(pDX, IDC_Operator, m_Operator);
	GetDlgItem(IDC_BUTTON_PLUS)->SetFont(&m_ExchangeRatefont);
	GetDlgItem(IDC_BUTTON_MINUS)->SetFont(&m_ExchangeRatefont);
	GetDlgItem(IDC_BUTTON_MUL)->SetFont(&m_ExchangeRatefont);
	GetDlgItem(IDC_BUTTON_DIV)->SetFont(&m_ExchangeRatefont);
	GetDlgItem(IDC_Operator)->SetFont(&m_ExchangeRatefont);
	GetDlgItem(IDC_EDITY)->SetFont(&m_ExchangeRatefont);
	GetDlgItem(IDC_EDITX)->SetFont(&m_ExchangeRatefont);
	GetDlgItem(IDC_EDITANS)->SetFont(&m_ExchangeRatefont);
	GetDlgItem(IDC_EQUAL)->SetFont(&m_ExchangeRatefont);
	GetDlgItem(IDC_Operator)->SetWindowText(m_Operator);
	GetDlgItem(IDC_EDITY)->SetWindowText(_T("1"));
	DDX_Control(pDX, IDC_GGoogle, m_GGoogleMap);
	DDX_Control(pDX, IDC_GExchangeRate, m_GExchangeRate);
	DDX_Control(pDX, IDC_Calculator, m_GCalculator);
	DDX_Control(pDX, IDC_GMemo, m_GMemo);
	DDX_Control(pDX, IDC_EDITX, m_X);
	DDX_Control(pDX, IDC_Operator, m_operater);
	DDX_Control(pDX, IDC_EDITY, m_Y);
	DDX_Control(pDX, IDC_EQUAL, m_Equal);
	DDX_Control(pDX, IDC_EDITANS, m_Ans);
	DDX_Control(pDX, IDC_BUTTON_PLUS, m_Add);
	DDX_Control(pDX, IDC_BUTTON_MINUS, m_Sub);
	DDX_Control(pDX, IDC_BUTTON_MUL, m_Mul);
	DDX_Control(pDX, IDC_BUTTON_DIV, m_Div);
	DDX_Control(pDX, IDC_EDIT1, m_Note);
	DDX_Control(pDX, IDC_AboutBox, m_AboutBox);
}

BEGIN_MESSAGE_MAP(CInfoVIew, CFormView)
	ON_CBN_SELCHANGE(IDC_COUNTRY, &CInfoVIew::OnCbnSelchangeConutry)
	ON_EN_UPDATE(IDC_ExchangeRate1, &CInfoVIew::OnEnUpdateExchangerate1)
	ON_BN_CLICKED(IDC_BackButton, &CInfoVIew::OnBnClickedBackbutton)
	ON_BN_CLICKED(IDC_BUTTON_PLUS, &CInfoVIew::OnBnClickedButtonPlus)
	ON_BN_CLICKED(IDC_BUTTON_MINUS, &CInfoVIew::OnBnClickedButtonMinus)
	ON_BN_CLICKED(IDC_BUTTON_MUL, &CInfoVIew::OnBnClickedButtonMul)
	ON_BN_CLICKED(IDC_BUTTON_DIV, &CInfoVIew::OnBnClickedButtonDiv)
	ON_EN_CHANGE(IDC_EDITX, &CInfoVIew::OnEnChangeEditx)
	ON_EN_CHANGE(IDC_EDITY, &CInfoVIew::OnEnChangeEdity)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_AboutBox, &CInfoVIew::OnBnClickedAboutbox)
	ON_BN_CLICKED(IDC_SAVE, &CInfoVIew::OnBnClickedSave)
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
	CString str, str2;
	GetDlgItem(IDC_ExchangeRate1)->SetFont(&m_ExchangeRatefont);
	GetDlgItem(IDC_KRW)->SetFont(&m_ExchangeRatefont);
	GetDlgItem(IDC_ExchangeRate1)->GetWindowText(str);
	ER1 = _wtof(str);
	ER2 = ER1*(1 / Parce->ExchangeRate[country]);
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




void CInfoVIew::OnBnClickedBackbutton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->OnMrtraveler();
}


void CInfoVIew::OnBnClickedButtonPlus()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_Operator.Format(_T("+"));
	GetDlgItem(IDC_Operator)->SetWindowText(m_Operator);
	opnum = 0;
	OnEnChangeEditx();
}


void CInfoVIew::OnBnClickedButtonMinus()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_Operator.Format(_T("-"));
	GetDlgItem(IDC_Operator)->SetWindowText(m_Operator);
	opnum = 1;
	OnEnChangeEditx();
}


void CInfoVIew::OnBnClickedButtonMul()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_Operator.Format(_T("*"));
	GetDlgItem(IDC_Operator)->SetWindowText(m_Operator);
	opnum = 2;
	OnEnChangeEditx();
}


void CInfoVIew::OnBnClickedButtonDiv()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_Operator.Format(_T("/"));
	GetDlgItem(IDC_Operator)->SetWindowText(m_Operator);
	opnum = 3;
	OnEnChangeEditx();
}


void CInfoVIew::OnEnChangeEditx()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (opnum == 0) {
		double x, y;
		CString X, Y, ANS;
		GetDlgItem(IDC_EDITX)->GetWindowText(X);
		GetDlgItem(IDC_EDITY)->GetWindowText(Y);
		x = _wtof(X);
		y = _wtof(Y);
		ANS.Format(_T("%lf"), x + y);
		GetDlgItem(IDC_EDITANS)->SetWindowText(ANS);
	}
	else if (opnum == 1) {
		double x, y;
		CString X, Y, ANS;
		GetDlgItem(IDC_EDITX)->GetWindowText(X);
		GetDlgItem(IDC_EDITY)->GetWindowText(Y);
		x = _wtof(X);
		y = _wtof(Y);
		ANS.Format(_T("%lf"), x - y);
		GetDlgItem(IDC_EDITANS)->SetWindowText(ANS);
	}
	else if (opnum == 2) {
		double x, y;
		CString X, Y, ANS;
		GetDlgItem(IDC_EDITX)->GetWindowText(X);
		GetDlgItem(IDC_EDITY)->GetWindowText(Y);
		x = _wtof(X);
		y = _wtof(Y);
		ANS.Format(_T("%lf"), x * y);
		GetDlgItem(IDC_EDITANS)->SetWindowText(ANS);
	}
	else if (opnum == 3) {
		double x, y;
		CString X, Y, ANS;
		GetDlgItem(IDC_EDITX)->GetWindowText(X);
		GetDlgItem(IDC_EDITY)->GetWindowText(Y);
		x = _wtof(X);
		y = _wtof(Y);
		ANS.Format(_T("%lf"), x / y);
		GetDlgItem(IDC_EDITANS)->SetWindowText(ANS);
	}
}


void CInfoVIew::OnEnChangeEdity()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (opnum == 0) {
		double x, y;
		CString X, Y, ANS;
		GetDlgItem(IDC_EDITX)->GetWindowText(X);
		GetDlgItem(IDC_EDITY)->GetWindowText(Y);
		x = _wtof(X);
		y = _wtof(Y);
		ANS.Format(_T("%lf"), x + y);
		GetDlgItem(IDC_EDITANS)->SetWindowText(ANS);
	}
	else if (opnum == 1) {
		double x, y;
		CString X, Y, ANS;
		GetDlgItem(IDC_EDITX)->GetWindowText(X);
		GetDlgItem(IDC_EDITY)->GetWindowText(Y);
		x = _wtof(X);
		y = _wtof(Y);
		ANS.Format(_T("%lf"), x - y);
		GetDlgItem(IDC_EDITANS)->SetWindowText(ANS);
	}
	else if (opnum == 2) {
		double x, y;
		CString X, Y, ANS;
		GetDlgItem(IDC_EDITX)->GetWindowText(X);
		GetDlgItem(IDC_EDITY)->GetWindowText(Y);
		x = _wtof(X);
		y = _wtof(Y);
		ANS.Format(_T("%lf"), x * y);
		GetDlgItem(IDC_EDITANS)->SetWindowText(ANS);
	}
	else if (opnum == 3) {
		double x, y;
		CString X, Y, ANS;
		GetDlgItem(IDC_EDITX)->GetWindowText(X);
		GetDlgItem(IDC_EDITY)->GetWindowText(Y);
		x = _wtof(X);
		y = _wtof(Y);
		ANS.Format(_T("%lf"), x / y);
		GetDlgItem(IDC_EDITANS)->SetWindowText(ANS);
	}
}


void CInfoVIew::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CRect clientRect;
	GetClientRect(clientRect);
	//그룹 좌표
	if (m_GGoogleMap.GetSafeHwnd() != NULL) {
		CRect Rect;
		m_GGoogleMap.GetWindowRect(Rect);
		ScreenToClient(Rect);
		Rect.left = clientRect.right*0.005;
		Rect.right = clientRect.right*0.63;
		Rect.top = clientRect.bottom*0.04;
		Rect.bottom = clientRect.bottom*0.91;
		m_GGoogleMap.MoveWindow(Rect);
	}
	if (m_GExchangeRate.GetSafeHwnd() != NULL) {
		CRect Rect;
		m_GExchangeRate.GetWindowRect(Rect);
		ScreenToClient(Rect);
		Rect.left = clientRect.right*0.64;
		Rect.right = clientRect.right*0.99;
		Rect.top = clientRect.bottom*0.04;
		Rect.bottom = clientRect.bottom*0.2;
		m_GExchangeRate.MoveWindow(Rect);
	}
	if (m_GCalculator.GetSafeHwnd() != NULL) {
		CRect Rect;
		m_GCalculator.GetWindowRect(Rect);
		ScreenToClient(Rect);
		Rect.left = clientRect.right*0.64;
		Rect.right = clientRect.right*0.99;
		Rect.top = clientRect.bottom*0.21;
		Rect.bottom = clientRect.bottom*0.42;
		m_GCalculator.MoveWindow(Rect);
	}
	if (m_GMemo.GetSafeHwnd() != NULL) {
		CRect Rect;
		m_GCalculator.GetWindowRect(Rect);
		ScreenToClient(Rect);
		Rect.left = clientRect.right*0.64;
		Rect.right = clientRect.right*0.99;
		Rect.top = clientRect.bottom*0.43;
		Rect.bottom = clientRect.bottom*0.91;
		m_GMemo.MoveWindow(Rect);
	}
	//컨트롤 좌표
	if (m_GoogleMap.GetSafeHwnd() != NULL) {
		CRect Rect;
		m_GoogleMap.GetWindowRect(Rect);
		ScreenToClient(Rect);
		Rect.left = clientRect.right*0.01;
		Rect.right = clientRect.right*0.62;
		Rect.top = clientRect.bottom*0.07;
		Rect.bottom = clientRect.bottom*0.9;
		m_GoogleMap.MoveWindow(Rect);
	}
	if (m_Currency_unit.GetSafeHwnd() != NULL) {
		CRect Rect;
		m_Currency_unit.GetWindowRect(Rect);
		ScreenToClient(Rect);
		Rect.left = clientRect.right*0.66;
		Rect.right = clientRect.right*0.85;
		Rect.top = clientRect.bottom*0.07;
		Rect.bottom = clientRect.bottom*0.4;
		m_Currency_unit.MoveWindow(Rect);
	}
	if (m_ExchangeRate1.GetSafeHwnd() != NULL) {
		CRect Rect;
		m_ExchangeRate1.GetWindowRect(Rect);
		ScreenToClient(Rect);
		Rect.left = clientRect.right*0.66;
		Rect.right = clientRect.right*0.78;
		Rect.top = clientRect.bottom*0.12;
		Rect.bottom = clientRect.bottom*0.17;
		m_ExchangeRate1.MoveWindow(Rect);
	}
	if (m_krw.GetSafeHwnd() != NULL) {
		CRect Rect;
		m_krw.GetWindowRect(Rect);
		ScreenToClient(Rect);
		Rect.left = clientRect.right*0.79;
		Rect.right = clientRect.right*0.97;
		Rect.top = clientRect.bottom*0.12;
		Rect.bottom = clientRect.bottom*0.17;
		m_krw.MoveWindow(Rect);
	}
	if (m_X.GetSafeHwnd() != NULL) {
		CRect Rect;
		m_X.GetWindowRect(Rect);
		ScreenToClient(Rect);
		Rect.left = clientRect.right*0.66;
		Rect.right = clientRect.right*0.75;
		Rect.top = clientRect.bottom*0.255;
		Rect.bottom = clientRect.bottom*0.305;
		m_X.MoveWindow(Rect);
	}
	if (m_operater.GetSafeHwnd() != NULL) {
		CRect Rect;
		m_operater.GetWindowRect(Rect);
		ScreenToClient(Rect);
		Rect.left = clientRect.right*0.759;
		Rect.right = clientRect.right*0.779;
		Rect.top = clientRect.bottom*0.26;
		Rect.bottom = clientRect.bottom*0.305;
		m_operater.MoveWindow(Rect);
	}
	if (m_Y.GetSafeHwnd() != NULL) {
		CRect Rect;
		m_X.GetWindowRect(Rect);
		ScreenToClient(Rect);
		Rect.left = clientRect.right*0.78;
		Rect.right = clientRect.right*0.86;
		Rect.top = clientRect.bottom*0.255;
		Rect.bottom = clientRect.bottom*0.305;
		m_Y.MoveWindow(Rect);
	}
	if (m_Equal.GetSafeHwnd() != NULL) {
		CRect Rect;
		m_Equal.GetWindowRect(Rect);
		ScreenToClient(Rect);
		Rect.left = clientRect.right*0.867;
		Rect.right = clientRect.right*0.88;
		Rect.top = clientRect.bottom*0.26;
		Rect.bottom = clientRect.bottom*0.305;
		m_Equal.MoveWindow(Rect);
	}
	if (m_Ans.GetSafeHwnd() != NULL) {
		CRect Rect;
		m_Ans.GetWindowRect(Rect);
		ScreenToClient(Rect);
		Rect.left = clientRect.right*0.885;
		Rect.right = clientRect.right*0.97;
		Rect.top = clientRect.bottom*0.255;
		Rect.bottom = clientRect.bottom*0.305;
		m_Ans.MoveWindow(Rect);
	}
	if (m_Add.GetSafeHwnd() != NULL) {
		CRect Rect;
		m_Add.GetWindowRect(Rect);
		ScreenToClient(Rect);
		Rect.left = clientRect.right*0.7;
		Rect.right = clientRect.right*0.74;
		Rect.top = clientRect.bottom*0.34;
		Rect.bottom = clientRect.bottom*0.4;
		m_Add.MoveWindow(Rect);
	}
	if (m_Sub.GetSafeHwnd() != NULL) {
		CRect Rect;
		m_Sub.GetWindowRect(Rect);
		ScreenToClient(Rect);
		Rect.left = clientRect.right*0.76;
		Rect.right = clientRect.right*0.80;
		Rect.top = clientRect.bottom*0.34;
		Rect.bottom = clientRect.bottom*0.4;
		m_Sub.MoveWindow(Rect);
	}
	if (m_Mul.GetSafeHwnd() != NULL) {
		CRect Rect;
		m_Mul.GetWindowRect(Rect);
		ScreenToClient(Rect);
		Rect.left = clientRect.right*0.82;
		Rect.right = clientRect.right*0.86;
		Rect.top = clientRect.bottom*0.34;
		Rect.bottom = clientRect.bottom*0.4;
		m_Mul.MoveWindow(Rect);
	}
	if (m_Div.GetSafeHwnd() != NULL) {
		CRect Rect;
		m_Div.GetWindowRect(Rect);
		ScreenToClient(Rect);
		Rect.left = clientRect.right*0.88;
		Rect.right = clientRect.right*0.92;
		Rect.top = clientRect.bottom*0.34;
		Rect.bottom = clientRect.bottom*0.4;
		m_Div.MoveWindow(Rect);
	}
	if (m_Note.GetSafeHwnd() != NULL) {
		CRect Rect;
		m_Note.GetWindowRect(Rect);
		ScreenToClient(Rect);
		Rect.left = clientRect.right*0.65;
		Rect.right = clientRect.right*0.98;
		Rect.top = clientRect.bottom*0.455;
		Rect.bottom = clientRect.bottom*0.9;
		m_Note.MoveWindow(Rect);
	}
	if (m_btnBack.GetSafeHwnd() != NULL) {
		CRect Rect;
		m_btnBack.GetWindowRect(Rect);
		ScreenToClient(Rect);
		Rect.left = clientRect.right*0.92;
		Rect.right = clientRect.right*0.98;
		Rect.top = clientRect.bottom*0.94;
		Rect.bottom = clientRect.bottom*0.98;
		m_btnBack.MoveWindow(Rect);
	}
	if (m_AboutBox.GetSafeHwnd() != NULL) {
		CRect Rect;
		m_AboutBox.GetWindowRect(Rect);
		ScreenToClient(Rect);
		Rect.left = clientRect.right*0.01;
		Rect.right = clientRect.right*0.07;
		Rect.top = clientRect.bottom*0.94;
		Rect.bottom = clientRect.bottom*0.98;
		m_AboutBox.MoveWindow(Rect);
	}
}


void CInfoVIew::OnBnClickedAboutbox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog aboutDlg(IDD_ABOUTBOX);
	aboutDlg.DoModal();
}


void CInfoVIew::OnBnClickedSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CManageData::GetInstance()->SaveData();
}
