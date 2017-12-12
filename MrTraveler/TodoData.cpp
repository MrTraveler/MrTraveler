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

void TodoData::TodoUpdate(Todo todo, int n)	//Todo �� ��ü�ϴ� �Լ�  n�� �ε���
{
	todoList.erase(todoList.begin() + n);
	todoList.insert(todoList.begin() + n, todo);
}

void TodoData::TodoAdd(Todo todo)		//Todo �� �߰��ϴ� �Լ�
{
	todoList.push_back(todo);
}

void TodoData::TodoRemove(int n)		//Todo �� �����ϴ� �Լ�  n�� �ε���
{
	todoList.erase(todoList.begin() + n);
}