#pragma once
class DrawView
{
public:
	CRect viewRect;
	int startDrawY;
	virtual void StartView(CRect viewRect);
	virtual void EndView();
	virtual void OnDraw(CDC * dc);
	virtual void OnLButtonDown(CPoint point);
	virtual void OnRButtonDown(CPoint point);
	/*
		기타 등등 메세지 추가
	*/
	DrawView();
	~DrawView();
};

