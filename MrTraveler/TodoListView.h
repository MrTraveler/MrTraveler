#pragma once
#include "DrawView.h"
#include <vector>
struct SubTodo
{
	CString content;
	bool isDone;
};
struct Todo
{
	COLORREF color;
	//이미지
	CString title;
	std::vector<SubTodo> list;
};
class TodoListView : public DrawView
	{
	public:
	TodoListView();
	~TodoListView();
	std::vector<Todo> todoList;
	virtual void OnDraw(CDC * dc);
	void DrawMetroRect(CDC * dc, CRect rect, Todo * todoList);
	
	//Todo 관련 함수 나중에 추가
};

