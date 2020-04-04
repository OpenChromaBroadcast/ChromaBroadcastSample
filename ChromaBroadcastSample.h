
// ChromaBroadcastSample.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CChromaBroadcastSampleApp:
// See ChromaBroadcastSample.cpp for the implementation of this class
//

class CChromaBroadcastSampleApp : public CWinApp
{
private:
	HMODULE m_hModule;

public:
	CChromaBroadcastSampleApp();
	~CChromaBroadcastSampleApp();

	void setColors(COLORREF color1, COLORREF color2, COLORREF color3, COLORREF color4, COLORREF color5);

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CChromaBroadcastSampleApp theApp;
