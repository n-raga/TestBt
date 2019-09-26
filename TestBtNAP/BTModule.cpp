#include "StdAfx.h"
#include "BTModule.h"

CBTModule* CBTModule::m_pInstance;

CBTModule::CBTModule(void)
{
    StackName(_T(""));
    StackIndex(0);
}

CBTModule::~CBTModule(void)
{
}

CBTModule* CBTModule::Instance()
{
    if(!m_pInstance)
        AfxMessageBox(_T("BtModule instance has not been created!"), MB_OK);
    return m_pInstance;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// CreateInstance
//-------------------------------------------------------------------------
void CBTModule::CreateInstance()
{
    // Only allow one instance of class to be generated.
    //ASSERT(NULL == m_pInstance);
    btLogger.AppendLog(LOG_INFO, _T("%s"), _T("Creating EMPTY Bluetooth module instance ..."));
    if (!m_pInstance)
        m_pInstance = new CBTModule();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// FreeInstance
//-------------------------------------------------------------------------
void CBTModule::FreeInstance(bool releaseAPI)
{
    btLogger.AppendLog(LOG_INFO, _T("%s"), _T("Releasing Bluetooth module ..."));
    if (m_pInstance)
    {
        if (releaseAPI)
            m_pInstance->FreeBtModule();

        delete m_pInstance;
        m_pInstance = NULL;
    }
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// IsRemoteDeviceConnectable
//-------------------------------------------------------------------------
BOOL CBTModule::IsRemoteDeviceConnectable(PBTDEVICE pBtd)
{
    CString fileName;
    fileName.Format(_T("\\\\.\\%s"), pBtd->bdComPort);
    HANDLE hSerial;
    hSerial = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 0);

    if (hSerial == INVALID_HANDLE_VALUE)
    {
        CloseHandle(hSerial);
        return (FALSE);
    }

    DCB serialParams = { 0 };
    serialParams.DCBlength = sizeof(serialParams);
    BOOL iRes = GetCommState(hSerial, &serialParams);
    if (FALSE == iRes)
    {
        CloseHandle(hSerial);
        btLogger.AppendLog(LOG_ERROR, _T("GetCommState() failure! Error: %d"), GetLastError());
        return (FALSE);
    }

    //iRes = SetCommState(hSerial, &serialParams);
    //if (FALSE == iRes)
    //{
    //    CloseHandle(hSerial);
    //    btLogger.AppendLog(LOG_ERROR, _T("SetCommState() failure! Error: %d"), GetLastError());
    //    return (FALSE);
    //}

    CloseHandle(hSerial);
    btLogger.AppendLog(LOG_INFO, _T("GetCommState() success."));
    return (TRUE);
}

//void CBTModule::SetConnEvent()
//{
//    if(NULL != m_eventWaitConn)
//        SetEvent(m_eventWaitConn);
//}

//CBTModule* g_btModule = NULL;

//void SetBtModule(CBTModule* module)
//{
//    ASSERT(NULL == g_btModule);
//    g_btModule = module;
//}

//CBTModule g_btModule;

//void SetBtModule(CBTModule module)
//{
//    ASSERT(NULL == g_btModule);
//    g_btModule = module;
//}
