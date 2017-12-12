#pragma once
using namespace std;
#include <vector>
struct Todo
{
	int icon;	//아이콘 번호
	CString title;	//제목
	std::vector<CString> list;	//할일 문자열 (vector : 가변 배열이랑 비슷)
};
class TodoData
{
private:
	TodoData();	// 외부에서 생성자 사용불가능
	static TodoData* instance;	//싱글톤 Instnace 사용방법  TodoData::GetInstance() 로 얻어오기
	static bool instanceFlag;
public:
	std::vector<Todo> todoList;	//Todo 를 모와 놓은 vector	//이거 저장하면됨
	~TodoData();
	static TodoData* GetInstance();
	void TodoUpdate(Todo todo, int n);
	void TodoAdd(Todo todo);
	void TodoRemove(int n);
};

