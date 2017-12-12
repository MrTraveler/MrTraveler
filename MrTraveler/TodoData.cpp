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

void TodoData::TodoUpdate(Todo todo, int n)	//Todo 를 교체하는 함수  n은 인덱스
{
	todoList.erase(todoList.begin() + n);
	todoList.insert(todoList.begin() + n, todo);
}

void TodoData::TodoAdd(Todo todo)		//Todo 를 추가하는 함수
{
	todoList.push_back(todo);
}

void TodoData::TodoRemove(int n)		//Todo 를 제거하는 함수  n은 인덱스
{
	todoList.erase(todoList.begin() + n);
}