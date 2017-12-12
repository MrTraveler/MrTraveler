#include "stdafx.h"
#include "Util.h"


Util::Util()
{
}
Util::~Util()
{
}
void Util::DrawImage(CDC * dc,int id, CRect rect)
{
	CBitmap bmp;
	bmp.LoadBitmap(id);
	CDC memDC;
	memDC.CreateCompatibleDC(dc);
	BITMAP bmpInfo;
	bmp.GetBitmap(&bmpInfo);
	memDC.SelectObject(&bmp);

	//�ӽÿ뵵 �������� ���������
	dc->TransparentBlt(rect.left, rect.top, (rect.right - rect.left), (rect.bottom - rect.top), &memDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, RGB(0,0,0));
}
bool Util::IsPointInRect(CRect rect, CPoint point)
{
	if (rect.left <= point.x && rect.top <= point.y && rect.right >= point.x && rect.bottom >= point.y)
		return true;
	return false;
}
int Util::GetMonthDay(int year, int month)
 {
	int monthDay[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (year % 4 == 0 && !(year % 100 == 0 && year % 400 != 0))
		 monthDay[1] = 29;
	return monthDay[month - 1];
	}