#pragma once
using namespace std;
#include <vector>
struct Todo
{
	int icon;
	CString title;
	std::vector<CString> list;
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
	void TodoUpdate(Todo todo, int n);
	void TodoAdd(Todo todo);
};

