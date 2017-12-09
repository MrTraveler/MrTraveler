// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "MrTraveler.h"

#include "MainFrm.h"
#include "MrTravelerView.h"
#include "InfoVIew.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_INFO, &CMainFrame::OnInfo)
	ON_COMMAND(ID_MRTRAVELER, &CMainFrame::OnMrtraveler)
END_MESSAGE_MAP()

// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.

}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	SetMenu(NULL);
	//if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
	//	!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	//{
	//	TRACE0("도구 모음을 만들지 못했습니다.\n");
	//	return -1;      // 만들지 못했습니다.
	//}

	//// TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar);


	return 0;
}


// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기



BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	cs.cx = 1475; 
	cs.cy = 950;


	return CFrameWnd::PreCreateWindow(cs);
}


void CMainFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	lpMMI->ptMinTrackSize.x = 1475; 
	lpMMI->ptMinTrackSize.y = 950;
	lpMMI->ptMaxTrackSize.x = 1475; 
	lpMMI->ptMaxTrackSize.y = 950; 
	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_pwndMrTravelerView = new CMrTravelerView;
	m_pwndInfoView = new CInfoVIew;


	m_pwndMrTravelerView->Create(NULL, NULL, WS_CHILD, CFrameWnd::rectDefault, this, VIEWID_MRTRAVELER, pContext);
	m_pwndInfoView->Create(NULL, NULL, WS_CHILD, CFrameWnd::rectDefault, this, VIEWID_INFOVIEW, pContext);
	return CFrameWnd::OnCreateClient(lpcs, pContext);
}
void CMainFrame::SwitchView(int nID)
{
	CView* pOldView = GetActiveView();
	CView* pNewView = NULL;

	switch (nID)
	{
	case VIEWID_MRTRAVELER:
		AfxMessageBox(_T("VIEWID_HTML"));
		pNewView = (CView*)m_pwndMrTravelerView;
		break;
	case VIEWID_INFOVIEW:
		AfxMessageBox(_T("VIEWID_EDIT"));
		pNewView = (CView*)m_pwndInfoView;
		break;
	}
	if (pNewView)
	{
		if (pOldView == pNewView)
			return;
		pOldView->ShowWindow(SW_HIDE);
		pOldView->SetDlgCtrlID(nID);
		pNewView->SetDlgCtrlID(AFX_IDW_PANE_FIRST);
		pNewView->ShowWindow(SW_SHOW);
		SetActiveView(pNewView);
		RecalcLayout();
	}
	else
		AfxMessageBox(_T("pNewView가 NULL??"));
}

void CMainFrame::OnInfo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	SwitchView(VIEWID_INFOVIEW);
}


void CMainFrame::OnMrtraveler()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	SwitchView(VIEWID_MRTRAVELER);
}