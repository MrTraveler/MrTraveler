#include "stdafx.h"
#include "TodoData.h"
#include <vector>
bool TodoData::instanceFlag = false;
TodoData* TodoData::instance = NULL;

TodoData::TodoData()
{

}	
TodoData::~TodoData()
{
	instanceFlag = false;
}
TodoData* TodoData::GetInstance()
{
	if (!instance)
	{
		instance = new TodoData();
		instanceFlag = true;
	}
	return TodoData::instance;
}

void TodoData::TodoUpdate(Todo todo, int n)
{
	todoList.erase(todoList.begin() + n);
	todoList.insert(todoList.begin() + n, todo);
}

void TodoData::TodoAdd(Todo todo)
{
	todoList.push_back(todo);
}
