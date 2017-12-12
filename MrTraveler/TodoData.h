#pragma once
using namespace std;
#include <vector>
struct Todo
{
	int icon;	//������ ��ȣ
	CString title;	//����
	std::vector<CString> list;	//���� ���ڿ� (vector : ���� �迭�̶� ���)
};
class TodoData
{
private:
	TodoData();	// �ܺο��� ������ ���Ұ���
	static TodoData* instance;	//�̱��� Instnace �����  TodoData::GetInstance() �� ������
	static bool instanceFlag;
public:
	std::vector<Todo> todoList;	//Todo �� ��� ���� vector	//�̰� �����ϸ��
	~TodoData();
	static TodoData* GetInstance();
	void TodoUpdate(Todo todo, int n);
	void TodoAdd(Todo todo);
	void TodoRemove(int n);
};

