
// MrTravelerView.h : CMrTravelerView Ŭ������ �������̽�
//

#pragma once


class CMrTravelerView : public CView
{
protected: // serialization������ ��������ϴ�.
	CMrTravelerView();
	DECLARE_DYNCREATE(CMrTravelerView)

// Ư���Դϴ�.
public:
	CMrTravelerDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CMrTravelerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MrTravelerView.cpp�� ����� ����
inline CMrTravelerDoc* CMrTravelerView::GetDocument() const
   { return reinterpret_cast<CMrTravelerDoc*>(m_pDocument); }
#endif

