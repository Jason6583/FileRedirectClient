
// FileRedirectClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFileRedirectClientApp: 
// �йش����ʵ�֣������ FileRedirectClient.cpp
//

class CFileRedirectClientApp : public CWinApp
{
public:
	CFileRedirectClientApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFileRedirectClientApp theApp;