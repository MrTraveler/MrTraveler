#pragma once
#include "afxwin.h"
#include "MrTravelerParceHtml.h"
#include "CWebBrowser2.h"

class CMainFrame;
class CManageData;
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
	CString GetResURL(int szResID);
	afx_msg void OnCbnSelchangeConutry();
	afx_msg void OnEnUpdateExchangerate1();
	afx_msg void OnBnClickedBackbutton();
	afx_msg void OnBnClickedButtonPlus();
	afx_msg void OnBnClickedButtonMinus();
	afx_msg void OnBnClickedButtonMul();
	afx_msg void OnBnClickedButtonDiv();
	afx_msg void OnEnChangeEditx();
	afx_msg void OnEnChangeEdity();
	CString m_conitem=0;
	CString m_Operator;
	CFont m_ExchangeRatefont;
	//그룹
	CStatic m_GGoogleMap;
	CStatic m_GExchangeRate;
	CStatic m_GCalculator;
	CStatic m_GMemo;
	//컨트롤
	CWebBrowser2 m_GoogleMap;
	CComboBox m_Currency_unit;
	CButton m_ExchangeRate1;
	CStatic m_krw;
	CEdit m_X;
	CStatic m_operater;
	CEdit m_Y;
	CStatic m_Equal;
	CEdit m_Ans;
	CButton m_Add;
	CButton m_Sub;
	CButton m_Mul;
	CButton m_Div;
	CEdit m_Note;
	CButton m_btnBack;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CButton m_AboutBox;
	afx_msg void OnBnClickedAboutbox();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedRoad();
};


