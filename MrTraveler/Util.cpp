#include "stdafx.h"
#include "Util.h"


Util::Util()
{
}
Util::~Util()
{
}
void Util::DrawImage(CDC * dc,CString path, CRect rect)
{
	CImage image;
	image.Load(path);

	CBitmap bmp;
	bmp.Attach(image.Detach());
	CDC memDC;
	memDC.CreateCompatibleDC(dc);
	BITMAP bmpInfo;
	bmp.GetBitmap(&bmpInfo);
	memDC.SelectObject(&bmp);

	//임시용도 검은색을 투명색으로
	dc->TransparentBlt(rect.left, rect.top, (rect.right - rect.left), (rect.bottom - rect.top), &memDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, RGB(0,0,0));
}
bool Util::IsPointInRect(CRect rect, CPoint point)
{
	if (rect.left <= point.x && rect.top <= point.y && rect.right >= point.x && rect.bottom >= point.y)
		return true;
	return false;
}
