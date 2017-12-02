#include "stdafx.h"
#include "TodoListView.h"


TodoListView::TodoListView()
{
	startDrawY = 0;	//��ũ���ҽ� �׸��� ������	//���� �̱���
}


TodoListView::~TodoListView()
{
}
void TodoListView::DrawMetroRect(CDC * dc ,CRect rect, Todo * todo)
{
	CBrush brush(todo->color);
	CFont font;
	font.CreatePointFont(220, _T("���� ���"));
	dc->FillRect(CRect(rect.left + 15, rect.top + 15, rect.right - 15, rect.bottom - 15), &brush);
	dc->SelectObject(&font);
	dc->SetTextColor(RGB(255, 255, 255));
	dc->SetBkMode(TRANSPARENT);
	dc->TextOut(rect.left +  130, rect.top + 30, todo->title);
	//���߿� �̹��� �߰� �߰�
}
void TodoListView::OnDraw(CDC * dc)
{
	//dc->SetViewportOrg(viewRect.left, viewRect.top);	// viewRect�� �������� �������� DC�� ����
	dc->SetMapMode(MM_ANISOTROPIC);
	CRect orgViewRect = { 0,0,viewRect.right - viewRect.left, viewRect.bottom - viewRect.top };	//view�� ���� ũ��
	dc->SetWindowExt(1000, 1000);
	dc->SetViewportExt(orgViewRect.right, orgViewRect.bottom);
	int countTodo = todoList.size();

	//int designType = 0;
	for (int i = 0; i < countTodo; i += 2)
	{
		if ((i / 2) % 2 == 0)
		{
			DrawMetroRect(dc, CRect(0, i / 2 * 150, 1000 / 3 * 2, (i / 2 + 1) * 150) , &todoList[i]);
			if(i % 2 != 1)
				DrawMetroRect(dc, CRect(1000 / 3 * 2, i / 2 * 150, 1000, (i / 2 + 1) * 150) ,&todoList[i + 1]);
		}
		else
		{
			DrawMetroRect(dc, CRect(0, i / 2 * 150, 1000 / 3, (i / 2 + 1) * 150), &todoList[i]);
			if (i % 2 != 1)
				DrawMetroRect(dc, CRect(1000 / 3, i / 2 * 150, 1000, (i / 2 + 1) * 150), &todoList[i + 1]);
		}
	}
}
