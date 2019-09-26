#include "StdAfx.h"
#include "MsModule7.h"
#include "ws2bth.h"

CMsModule7::CMsModule7(void) : CDLLModule()
{
    StackName(_T("Microsoft"));
    StackIndex(1);
}

CMsModule7::~CMsModule7(void)
{
    CDLLModule::~CDLLModule();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// CreateInstance
//-------------------------------------------------------------------------
void CMsModule7::CreateInstance()
{
    // Only allow one instance of class to be generated.
    //ASSERT(NULL == m_pInstance);
    btLogger.AppendLog(LOG_INFO, _T("%s"), _T("Creating MICROSOFT7 Bluetooth module instance ..."));
    if (!m_pInstance ||(0 == m_pInstance->StackIndex()))
        m_pInstance = new CMsModule7();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// IsHWDeviceReady
//-------------------------------------------------------------------------
BOOL CMsModule7::IsHWDeviceReady(HWND hWnd)
{
    btLogger.AppendLog(LOG_INFO, _T("%s"), _T("Checking MICROSOFT7 local device status ..."));
    return MsBt7_IsHWDeviceReady();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// InitBtModule
//-------------------------------------------------------------------------
BOOL CMsModule7::InitBtModule(LPCTSTR szDll)
{
    if (!IsLoaded())
    {
        Init(szDll);
        if(!IsLoaded())
        {
            DWORD dwError = GetLastError();
            CString error_msg;
            static TCHAR errorMsg[512];
            FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, dwError, 0, errorMsg, 511, NULL);
            //error_msg.Format(_T("Unable to load BlueSoleil Bluetooth module (%s).\r\nError code: %d.\r\n%s"), szDll, dwError, errorMsg);
            //AfxMessageBox(error_msg, MB_OK);
            btLogger.AppendLog(LOG_ERROR, _T("MICROSOFT7 Bluetooth module initialization failure! Error %d (%s)"), dwError, errorMsg);
            return (FALSE);
        }
    }
    // Bug fix associazione COM -> eliminazione COM -> nuova ricerca -> associazione COM
    //MsBt7_NullAuthCb();
    btLogger.AppendLog(LOG_INFO, _T("%s"), _T("MICROSOFT7 Bluetooth module initialization done."));
    return (TRUE);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// StartInquiry
//-------------------------------------------------------------------------
BOOL CMsModule7::StartInquiry(HWND hWnd)
{
    btLogger.AppendLog(LOG_INFO, _T("%s"), _T("Starting MICROSOFT7 device inquiry ..."));
    CancelDiscoverRequired(false);
    MsBt7_DiscoverRemoteDevices(hWnd, 0);
    return (TRUE);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// LoadAuthenticatedDevices
//-------------------------------------------------------------------------
void CMsModule7::LoadAuthenticatedDevices(HWND hWnd, bool isWizardMode)
{
    btLogger.AppendLog(LOG_INFO, _T("%s"), _T("Loading MICROSOFT7 associated devices ..."));
    CancelDiscoverRequired(false);
    MsBt7_GetAuthenticatedDevices(hWnd, isWizardMode);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// BindDevice
//-------------------------------------------------------------------------
BOOL CMsModule7::BindDevice(HWND hWnd, PBTDEVICE pBtd)
{
	btLogger.AppendLog(LOG_INFO, _T("Binding device %s (class %08X)..."), pBtd->bdName, pBtd->bdClass);
    DWORD dwType = 0; // Default, strumento Texa
    //CString hexVal;
    //hexVal.Format(_T("%X"), pBtd->bdClass);
	if(0x00020000 == (pBtd->bdClass & 0x00020000))
	{
		dwType = 2; // TXT Multihub
	}
    //else if (_T("200") == hexVal.Mid(0, 3))
	else if (0x00200000 == (pBtd->bdClass & 00200000))
	{
		dwType = 1; // Headset Bluetooth (classe dispositivo: 0x200404)
	}

    CHAR pszComPort[6];

    if (FALSE == this->MsBt7_ExecAuthenticateDeviceEx(pBtd->bdAddr, dwType, pszComPort))
        return (FALSE);

    pBtd->authenticated = true;
    pBtd->remembered = true;

    if (0 == dwType)
    {
        pBtd->bdComPort = CString(pszComPort); //.Format(_T("%S"), pszComPort);
        btLogger.AppendLog(LOG_INFO, _T("%s: standard serial connection on %s."), pBtd->bdName, pBtd->bdComPort);
    }

    return (TRUE);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// BindDevice
//-------------------------------------------------------------------------
BOOL CMsModule7::UnbindDevice(PBTDEVICE pBtd)
{
    btLogger.AppendLog(LOG_INFO, _T("Unbinding device %s (%s)..."), pBtd->bdName, pBtd->bdComPort);
    if (FALSE == MsBt7_ExecRemoveAuthenticatedDevice(pBtd->bdAddr))
        return (FALSE);

    btLogger.AppendLog(LOG_INFO, _T("%s: standard serial connection (SPP SLAVE) successfully deleted. %s released."), pBtd->bdName, pBtd->bdComPort);

    pBtd->bdComPort = _T("");
    pBtd->authenticated = false;
    pBtd->remembered = false;

    return (TRUE);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// StopInquiry
//-------------------------------------------------------------------------
void CMsModule7::StopInquiry(HWND hWnd)
{
    btLogger.AppendLog(LOG_INFO, _T("%s"), _T("Stopping MICROSOFT7 device inquiry ..."));
    CancelDiscoverRequired(true);
    MsBt7_StopDiscoverRemoteDevices(hWnd);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// GetLocalDeviceInfo
//-------------------------------------------------------------------------
void CMsModule7::GetLocalDeviceInfo(PBTLOCALDEVICE pLocalDev)
{
    btLogger.AppendLog(LOG_INFO, _T("%s"), _T("Getting MICROSOFT7 local device info ..."));
    MsBt7_GetLocalDeviceInfo(pLocalDev);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// IsRemoteDeviceConnectable
//-------------------------------------------------------------------------
BOOL CMsModule7::IsRemoteDeviceConnectable(PBTDEVICE pBtd)
{
    if (!pBtd->authenticated)
    {
        return (FALSE);
    }

	SOCKET s = socket(AF_BTH, SOCK_STREAM, BTHPROTO_L2CAP);
	if (s == INVALID_SOCKET) {
		return (FALSE);
	}

	SOCKADDR_BTH sab;
	memset(&sab, 0, sizeof(sab));
	sab.addressFamily = AF_BTH;
	sab.serviceClassId = NAPServiceClass_UUID;
	sab.btAddr = BTH_ADDR(pBtd->bdAddr);

	if (0 != connect(s, (struct sockaddr *)&sab, sizeof(sab)))
	{
		return (FALSE);
	}

	return TRUE;
    //return MsBt7_IsRemoteDeviceConnectable(pBtd->bdComPort);
}
