#pragma once
class CMrTravelerView;
class DrawView
{
public:
	CRect viewRect;
	CMrTravelerView *parentView;
	int startDrawY;
	virtual void StartView(CRect viewRect, CMrTravelerView * parent);
	virtual void EndView();
	virtual void OnDraw(CDC * dc);
	virtual void OnLButtonDown(CPoint point);
	virtual void OnRButtonDown(CPoint point);
	/*
		��Ÿ ��� �޼��� �߰�
	*/
	DrawView();
	~DrawView();
};

