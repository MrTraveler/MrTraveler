#pragma once

#include<iostream>
#include <fstream>
#include "json/json.h"
#include<afxinet.h>
class CMrTravelerParceHtml
{
public:
	CMrTravelerParceHtml();
	~CMrTravelerParceHtml();
	CString strHtml;
	void ParceHtml(CString strUrl,CString strFile);
	void RoadExchangeRate();
	double ExchangeRate[94];
};

