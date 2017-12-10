#pragma once
#include "DrawView.h"
struct Todo;
class TodoListView : public DrawView
{
	public:
	TodoListView();
	~TodoListView();
	virtual void OnDraw(CDC * dc);
	void DrawMetroRect(CDC * dc, CRect rect, Todo * todoList,int color);
	void DrawMetro(CDC * dc);
	virtual void OnLButtonDown(CPoint point);
	virtual void OnMouseMove(CPoint point);
	virtual void OnLButtonUp(CPoint point);
	virtual void OnLButtonDblClk(CPoint point);
	virtual void OnRButtonDown(CPoint point);
	//Todo 관련 함수 나중에 추가

	public:
	int startDrawY;
	int lastClickY;
	bool isDrag;
};

