#pragma once
using namespace std;
#include <vector>
struct SubTodo
{
	CString content;
	bool isDone;
};
struct Todo
{
	COLORREF color;
	//¿ÃπÃ¡ˆ
	CString title;
	std::vector<SubTodo> list;
};
class TodoData
{
private:
	TodoData();
	static TodoData* instance;
	static bool instanceFlag;
public:
	std::vector<Todo> todoList;
	~TodoData();
	static TodoData* GetInstance();
};

