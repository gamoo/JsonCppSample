
// CWndSample.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CCWndSampleApp:
// �� Ŭ������ ������ ���ؼ��� CWndSample.cpp�� �����Ͻʽÿ�.
//

class CCWndSampleApp : public CWinApp
{
public:
	CCWndSampleApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CCWndSampleApp theApp;