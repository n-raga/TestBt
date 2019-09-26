
// TestBtNAP.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include "FileLog.h"

// CTestBtNAPApp:
// See TestBtNAP.cpp for the implementation of this class
//

class CTestBtNAPApp : public CWinApp
{
public:
	CTestBtNAPApp();

// Overrides
public:
	virtual BOOL InitInstance();
	bool InitLog();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CTestBtNAPApp theApp;