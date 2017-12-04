#pragma once
#include "DrawView.h"
struct Todo;
class TodoListView : public DrawView
{
	public:
	TodoListView();
	~TodoListView();
	virtual void OnDraw(CDC * dc);
	void DrawMetroRect(CDC * dc, CRect rect, Todo * todoList);
	
	
	//Todo 관련 함수 나중에 추가
};

