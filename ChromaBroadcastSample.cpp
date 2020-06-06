#include "framework.h"
#include "ChromaBroadcastSample.h"
#include "ChromaBroadcastSampleDlg.h"
#include <RzErrors.h>
#include <RzChromaBroadcastAPITypes.h>
#include <RzChromaBroadcastAPIDefines.h>
#include <string>

using namespace RzChromaBroadcastAPI;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef _WIN64
#define CHROMABROADCASTAPIDLL        _T("RzChromaBroadcastAPI64.dll")
#else
#define CHROMABROADCASTAPIDLL        _T("RzChromaBroadcastAPI.dll")
#endif

typedef RZRESULT (*INIT)(RZAPPID app);
typedef RZRESULT (*INITEX)(int index, const char *title);
typedef RZRESULT (*UNINIT)();
typedef RZRESULT (*REGISTEREVENTNOTIFICATION)(RZEVENTNOTIFICATIONCALLBACK callback);
typedef RZRESULT (*UNREGISTEREVENTNOTIFICATION)();

INIT Init = nullptr;
INITEX InitEx = nullptr;
UNINIT UnInit = nullptr;
REGISTEREVENTNOTIFICATION RegisterEventNotification = nullptr;
UNREGISTEREVENTNOTIFICATION UnRegisterEventNotification = nullptr;

CChromaBroadcastSampleApp theApp;

BEGIN_MESSAGE_MAP(CChromaBroadcastSampleApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

RZRESULT BroadcastHandler(CHROMA_BROADCAST_TYPE type, PRZPARAM pData)
{
	switch (type)
	{
	case BROADCAST_EFFECT:
	{
		CHROMA_BROADCAST_EFFECT* effect = (CHROMA_BROADCAST_EFFECT*)pData;
		TRACE("BROADCAST_EFFECT: %x %x %x %x %x %x\n", effect->CL1, effect->CL2, effect->CL3, effect->CL4, effect->CL5, effect->IsAppSpecific);
		theApp.setColors(effect->CL1, effect->CL2, effect->CL3, effect->CL4, effect->CL5);
		break;
	}
	case BROADCAST_STATUS:
		TRACE("BROADCAST_STATUS: %x\n", pData);
		break;
	}

	return 0;
}

CChromaBroadcastSampleApp::CChromaBroadcastSampleApp()
{
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
	m_hModule = ::LoadLibrary(CHROMABROADCASTAPIDLL);
	if (m_hModule != NULL)
	{
		Init = (INIT)::GetProcAddress(m_hModule, "Init");
		InitEx = (INITEX)::GetProcAddress(m_hModule, "InitEx");
		UnInit = (UNINIT)::GetProcAddress(m_hModule, "UnInit");
		RegisterEventNotification = (REGISTEREVENTNOTIFICATION)::GetProcAddress(m_hModule, "RegisterEventNotification");
		UnRegisterEventNotification = (UNREGISTEREVENTNOTIFICATION)::GetProcAddress(m_hModule, "UnRegisterEventNotification");

		if (InitEx)
			InitEx(1001, "Open Chroma Broadcast Sample");

		if (RegisterEventNotification)
			RegisterEventNotification(BroadcastHandler);
	}
}

CChromaBroadcastSampleApp::~CChromaBroadcastSampleApp()
{
	if (UnRegisterEventNotification)
		UnRegisterEventNotification();

	if (UnInit)
		UnInit();

	::FreeLibrary(m_hModule);
	m_hModule = NULL;
}

void CChromaBroadcastSampleApp::setColors(COLORREF color1, COLORREF color2, COLORREF color3, COLORREF color4, COLORREF color5)
{
	((CChromaBroadcastSampleDlg *)m_pMainWnd)->setColors(color1, color2, color3, color4, color5);
}

BOOL CChromaBroadcastSampleApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	CShellManager *pShellManager = new CShellManager;

	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CChromaBroadcastSampleDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	return FALSE;
}

