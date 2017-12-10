#pragma once
class Util
{
private:
	Util();
public:
	~Util();
	static void DrawImage(CDC * dc,CString path, CRect rect);
	static bool IsPointInRect(CRect rect, CPoint point);
	static int GetMonthDay(int year, int month);
};

