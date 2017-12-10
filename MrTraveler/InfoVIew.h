#pragma once
#include "afxwin.h"
#include "MrTravelerParceHtml.h"
#include "CWebBrowser2.h"

class CMainFrame;

// CInfoVIew 폼 뷰입니다.
class CMrTravelerParceHtml;
class CInfoVIew : public CFormView
{
	DECLARE_DYNCREATE(CInfoVIew)

protected:

public:
	CInfoVIew();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CInfoVIew();
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CMrTravelerParceHtml* Parce;
	int country;
	int opnum = 0;
	CComboBox m_Currency_unit;
	afx_msg void OnCbnSelchangeConutry();
	CButton m_ExchangeRate1;
	CButton m_ExchangeRate2;
	afx_msg void OnEnUpdateExchangerate1();
	CFont m_ExchangeRatefont;
	CStatic m_krw;
	CWebBrowser2 m_GoogleMap;
	CString GetResURL(int szResID);

	
	CString m_conitem=0;
	afx_msg void OnBnClickedBackbutton();
	CButton m_btnBack;
	CString m_Operator;
	afx_msg void OnBnClickedButtonPlus();
	afx_msg void OnBnClickedButtonMinus();
	afx_msg void OnBnClickedButtonMul();
	afx_msg void OnBnClickedButtonDiv();
	afx_msg void OnEnChangeEditx();
	afx_msg void OnEnChangeEdity();
};


