
// MrTraveler.h : MrTraveler ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMrTravelerApp:
// �� Ŭ������ ������ ���ؼ��� MrTraveler.cpp�� �����Ͻʽÿ�.
//

class CMrTravelerApp : public CWinApp
{
public:
	CMrTravelerApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMrTravelerApp theApp;
