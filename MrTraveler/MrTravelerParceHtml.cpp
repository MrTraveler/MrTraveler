#include "stdafx.h"
#include "MrTravelerParceHtml.h"


CMrTravelerParceHtml::CMrTravelerParceHtml()
{
	CString strHtml;
}


CMrTravelerParceHtml::~CMrTravelerParceHtml()
{
}

void CMrTravelerParceHtml::ParceHtml(CString strUrl) {

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
		// �� �پ� �о ��ġ��
		while (pHttpFile->ReadString(strTemp))
		{
			// �� ������ ���ڵ��� UTF-8�̹Ƿ� �����ڵ�� ����
//			strHtml += CA2W((LPCSTR)strTemp.GetBuffer(), CP_UTF8);
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
	file.Open(_T("ExchangeRate.json"), CFile::modeCreate | CFile::modeWrite, NULL);
	file.Write(strHtml, strHtml.GetLength() * sizeof(TCHAR)); 

	file.Close();
}