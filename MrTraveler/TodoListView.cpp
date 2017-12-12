#include "stdafx.h"
#include "TodoListView.h"
#include "TodoData.h"
#include "Util.h"
#include "MrTravelerView.h"
#include "TodoDlg.h"
#include "resource.h"
TodoListView::TodoListView()
{
	startDrawY = 0;	//스크롤할시 그리기 시작점	//아직 미구현
	isDrag = false;
}


TodoListView::~TodoListView()
{
}

void TodoListView::DrawMetroRect(CDC * dc ,CRect rect, Todo * todo,int color)
{
	COLORREF colorList[] =
	{
		RGB(0X4C,0X69,0X8B),
		RGB(0x2B,0x49,0x6E),
		RGB(0x06,0x1D,0x39),
		RGB(0x02,0x10,0x21)
	};
	CFont font;
	font.CreatePointFont(220, _T("맑은 고딕"));
	CBrush brush(colorList[color]);
	dc->FillRect(CRect(rect.left + 15, rect.top + 15, rect.right - 15, rect.bottom - 15), &brush);
	dc->SelectObject(&font);
	dc->SetTextColor(RGB(255, 255, 255));
	dc->SetBkMode(TRANSPARENT);
	dc->TextOut(rect.left +  130, rect.top + 30, todo->title);
	
	int iconID[] = { IDB_ICON1,IDB_ICON2,IDB_ICON3,IDB_ICON4,IDB_ICON5 };
	Util::DrawImage(dc, iconID[todo->icon], CRect(rect.left + 30, rect.top + 30, rect.left + 130, rect.bottom - 30));
}
void TodoListView::DrawMetro(CDC * dc)
{

	CBrush brush1(RGB(0x14, 0x31, 0x53));
	dc->FillRect(CRect(0,0,1000,1000), &brush1);
	int countTodo = TodoData::GetInstance()->todoList.size();
	for (int i = 0; i < countTodo; i += 2)
	{
		if ((i / 2) % 2 == 0)
		{
			DrawMetroRect(dc, CRect(0, i / 2 * 250 - startDrawY, 1000 / 3 * 2, (i / 2 + 1) * 250 - startDrawY), &TodoData::GetInstance()->todoList[i],i % 4);
			if (i != countTodo - 1)
				DrawMetroRect(dc, CRect((int)((float)1000 / 3 * 2), i / 2 * 250 - startDrawY, 1000, (i / 2 + 1) * 250 - startDrawY), &TodoData::GetInstance()->todoList[i + 1],(i+1)%4);
		}
		else
		{
			DrawMetroRect(dc, CRect(0, i / 2 * 250 - startDrawY, 1000 / 3, (i / 2 + 1) * 250 - startDrawY), &TodoData::GetInstance()->todoList[i], i % 4);
			if (i != countTodo - 1)
				DrawMetroRect(dc, CRect(1000 / 3, i / 2 * 250 - startDrawY, 1000, (i / 2 + 1) * 250 - startDrawY), &TodoData::GetInstance()->todoList[i + 1], (i + 1) % 4);
		}
	}
}
void TodoListView::OnLButtonDown(CPoint point)
{
	point.x = (int)(((float)point.x - viewRect.left) / (viewRect.right - viewRect.left) * 1000);
	point.y = (int)(((float)point.y - viewRect.top) / (viewRect.bottom - viewRect.top) * 1000);
	point.y += startDrawY;


}
void TodoListView::OnMouseMove(CPoint point)
{
}
void TodoListView::OnLButtonUp(CPoint point)
{
}
void TodoListView::OnRButtonDown(CPoint point)
{
	TodoDlg dlg;
	Todo dtodo;
	dlg.title = dtodo.title = _T("Unknown");
	dlg.icon = dtodo.icon = 0;
	dlg.todo = _T("");
	dlg.ptodo = &dtodo;
	if (dlg.DoModal() == IDOK)
	{
		dtodo.title = dlg.title;
		dtodo.icon = dlg.icon;
		TodoData::GetInstance()->TodoAdd(dtodo);
	}
	parentView->Invalidate();
}
void TodoListView::OnLButtonDblClk(CPoint point)
{
	point.x = (int)(((float)point.x - viewRect.left) / (viewRect.right - viewRect.left) * 1000);
	point.y = (int)(((float)point.y - viewRect.top) / (viewRect.bottom - viewRect.top) * 1000);
	point.y += startDrawY;
	int	row = point.y / 250;
	int col;
	CPoint marginCheckPoint;
	marginCheckPoint.y = point.y % 250;
	marginCheckPoint.x = point.x;
	if (!(row % 2))
	{
		if (point.x < (int)((float)1000 / 3 * 2))
			col = 0;
		else
		{
			col = 1;
			marginCheckPoint.x -= (int)((float)1000 / 3 * 2);
		}
	}
	else
	{
		if (point.x < (int)((float)1000 / 3 * 1))
			col = 0;
		else
		{
			col = 1;
			marginCheckPoint.x -= (int)((float)1000 / 3 * 1);
		}
	}
	bool selectedMargin = false;
	if ((row + col) % 2 == 1 && !Util::IsPointInRect(CRect(15, 15, 318, 235), marginCheckPoint))
		selectedMargin = true;
	else if ((row + col) % 2 == 0 && !Util::IsPointInRect(CRect(15, 15, 651, 235), marginCheckPoint))
		selectedMargin = true;

	if (!selectedMargin && (TodoData::GetInstance()->todoList.size() >= row * 2 + col))
	{
		TodoDlg dlg;
		Todo dtodo = TodoData::GetInstance()->todoList[row * 2 + col];
		dlg.title = dtodo.title;
		dlg.icon = dtodo.icon;
		dlg.todo = _T("");
		dlg.ptodo = &dtodo;
		int state = 0;
		if ((state = dlg.DoModal()) == IDOK)
		{
			dtodo.title = dlg.title;
			dtodo.icon = dlg.icon;
			TodoData::GetInstance()->TodoUpdate(dtodo, row * 2 + col);
		}
		else if(state == 1080)
		{
			TodoData::GetInstance()->TodoRemove(row * 2 + col);
		}
		parentView->Invalidate();
	}
}
void TodoListView::OnDraw(CDC * dc)
{
	//dc->SetViewportOrg(viewRect.left, viewRect.top);	// viewRect의 시작점을 원점으로 DC에 저장
	dc->SetMapMode(MM_ANISOTROPIC);
	CRect orgViewRect = { 0,0,viewRect.right - viewRect.left, viewRect.bottom - viewRect.top };	//view의 원래 크기
	dc->SetWindowExt(1000, 1000);
	dc->SetViewportExt(orgViewRect.right, orgViewRect.bottom);
	DrawMetro(dc);
	//int designType = 0;
}
