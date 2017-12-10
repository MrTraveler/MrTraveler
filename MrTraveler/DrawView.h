#pragma once
class CMrTravelerView;
class DrawView
{
public:
	CRect viewRect;
	CMrTravelerView *parentView;
	virtual void StartView(CRect viewRect, CMrTravelerView * parent);
	virtual void EndView();
	virtual void OnDraw(CDC * dc);
	virtual void OnLButtonDown(CPoint point);
	virtual void OnRButtonDown(CPoint point);
	virtual void OnMouseMove(CPoint point);
	virtual void OnLButtonUp(CPoint point);
	virtual void OnLButtonDblClk(CPoint point);
	/*
		��Ÿ ��� �޼��� �߰�
	*/
	DrawView();
	~DrawView();
};

