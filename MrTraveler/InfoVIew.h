#pragma once
#include "afxwin.h"
#include "MrTravelerParceHtml.h"



// CInfoVIew �� ���Դϴ�.
class CMrTravelerParceHtml;
class CInfoVIew : public CFormView
{
	DECLARE_DYNCREATE(CInfoVIew)

protected:

public:
	CInfoVIew();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CMrTravelerParceHtml* Parce;
	int country;
	CComboBox m_Currency_unit;
	afx_msg void OnCbnSelchangeConutry();
	CButton m_ExchangeRate1;
	CButton m_ExchangeRate2;
	afx_msg void OnEnUpdateExchangerate1();
	CFont m_ExchangeRatefont;
	CStatic m_krw;
};


