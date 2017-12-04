#include "stdafx.h"
#include "ScheduleView.h"


ScheduleView::ScheduleView()
{
}


ScheduleView::~ScheduleView()
{
}
void ScheduleView::DrawTable(CDC * dc)
{
	CPen pen;
	pen.CreatePen(PS_SOLID, 3, RGB(0,0,0));
	CPen *oldPen = dc->SelectObject(&pen);
	for (int i = 0; i < 25; i++)
		for (int j = 0; j < 4; j++)
			dc->Rectangle(1000 / 4 * j, 945 / 25 * i, 1000 / 4 * (j + 1), 945 / 25 * (i + 1));
	dc->SelectObject(oldPen);
}
void ScheduleView::DrawLabel(CDC * dc)
{
	CFont font;
	font.CreatePointFont(220, _T("���� ���"));
	CFont *oldFont = dc->SelectObject(&font);
	dc->SetTextAlign(TA_CENTER);
	dc->SetBkMode(TRANSPARENT);
	//���� �Ʒ����� ���߿� �����ͷ� �ڵ�ȭ
	dc->TextOut(1000 / 4 / 2 * 3, 0, _T("3�� 21��"));
	dc->TextOut(1000 / 4 / 2 * 5, 0, _T("3�� 22��"));
	dc->TextOut(1000 / 4 / 2 * 7, 0, _T("3�� 23��"));
	for (int i = 1; i < 25; i++)
	{
		CString str;
		str.Format(_T("%d"), i);
		dc->TextOutW(1000 / 4 / 2, 1000 / 25 / 2 * (i * 2 + 1) - 20, str);
	}
	dc->SelectObject(oldFont);
}
void ScheduleView::OnDraw(CDC * dc)
{
	dc->SetMapMode(MM_ANISOTROPIC);
	CRect orgViewRect = { 0,0,viewRect.right - viewRect.left, viewRect.bottom - viewRect.top };	//view�� ���� ũ��
	dc->SetWindowExt(1000, 1000);
	dc->SetViewportExt(orgViewRect.right, orgViewRect.bottom);
	DrawTable(dc);
	DrawLabel(dc);
}
