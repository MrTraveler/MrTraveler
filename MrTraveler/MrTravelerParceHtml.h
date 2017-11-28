#pragma once
#include<afxinet.h>
class CMrTravelerParceHtml
{
public:
	CMrTravelerParceHtml();
	~CMrTravelerParceHtml();
	CString strHtml;
	void ParceHtml(CString strUrl);

};

