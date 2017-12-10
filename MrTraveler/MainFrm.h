
// MainFrm.h : CMainFrame 클래스의 인터페이스
//
#define VIEWID_DEFAULT AFX_IDW_PANE_FIRST
#define VIEWID_MRTRAVELER AFX_IDW_PANE_FIRST+10
#define VIEWID_INFOVIEW AFX_IDW_PANE_FIRST+20
#pragma once
class CInfoVIew;
class CMrTravelerView;
class CMainFrame : public CFrameWnd
{
	
protected: // serialization에서만 만들어집니다.
	DECLARE_DYNCREATE(CMainFrame)

// 특성입니다.
public:
	CView* m_pwndInfoView;
	CView* m_pwndMrTravelerView;
// 작업입니다.
public:

// 재정의입니다.
public:
//	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	CMainFrame();
	virtual ~CMainFrame();
	void SwitchView(int nID);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


protected:  // 컨트롤 모음이 포함된 멤버입니다.
	CToolBar          m_wndToolBar;

// 생성된 메시지 맵 함수
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	afx_msg void OnInfo();
	afx_msg void OnMrtraveler();
};

