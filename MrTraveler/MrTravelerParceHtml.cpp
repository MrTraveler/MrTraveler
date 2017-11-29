#include "stdafx.h"
#include "MrTravelerParceHtml.h"


CMrTravelerParceHtml::CMrTravelerParceHtml()
{
	CString strHtml;
}


CMrTravelerParceHtml::~CMrTravelerParceHtml()
{
}

void CMrTravelerParceHtml::ParceHtml(CString strUrl,CString strFile) {

	CInternetSession session;
	CHttpFile* pHttpFile = NULL;
	CString strTemp;
	try
	{
		pHttpFile = (CHttpFile*)session.OpenURL(strUrl);
	}
	catch (CInternetException* e) {
		CString strError;
		e->GetErrorMessage(strError.GetBuffer(1024), 1024);
		_tprintf(_T("%s\n"), strError);
		e->Delete();
		strError.ReleaseBuffer();
	}
	if (pHttpFile != NULL) {
		// 한 줄씩 읽어서 합치기
		while (pHttpFile->ReadString(strTemp))
		{
			strHtml += strTemp.GetBuffer();
			strTemp.ReleaseBuffer();
		}
		_tprintf(_T("%s\n\n"), strHtml);
		session.Close();
		pHttpFile->Close();
		delete pHttpFile;
	}
	else {
		_tprintf(_T("pFile is NULL.\n"));
	}
	CFile file;
	file.Open(strFile, CFile::modeCreate | CFile::modeWrite, NULL);
	file.Write(strHtml, strHtml.GetLength() * sizeof(TCHAR)); 
	file.Close();

}
void CMrTravelerParceHtml::RoadExchangeRate() {
	char iso3166[94][5] = {"AED","AMD","ANG","AOA","ARS","AUD","BBD","BDT","BGN","BHD","BRL","BSD","BWP","BYN","CAD","CHF","CLP","CNY","COP","CZK","DKK","DOP","EGP","ETB","EUR","FJD","GBP","GHS","GTQ","HKD","HNL","HRK","HUF","IDR","ILS","INR","IQD","IRR","ISK","JMD","JOD","JPY","KES","KHR","KWD","KZT","LAK","LBP","LKR","MAD","MKD","MMK","MUR","MXN","MYR","NAD","NGN","NOK","NZD","OMR","PAB","PEN","PGK","PHP","PKR","PLN","PYG","QAR","RON","RSD","RUB","SAR","SCR","SEK","SGD","THB","TJS","TND","TRY","TTD","TWD","TZS","UAH","USD","UYU","UZS","VEF","VND","XAF","XCD","XOF","XPF","ZAR","ZMW"};
	std::ifstream stream;
	stream.open("ExchangeRate.json");
	Json::Value root;
	stream >> root; // 읽어온 데이터를 root에 넣는다.
	Json::Value rates = root["rates"];
	for (int i = 0; i < 94; i++) 
		ExchangeRate[i] = rates[iso3166[i]].asDouble();
}