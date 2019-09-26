#pragma once
#include <vector>
#include "Public.h"
#include "FileLog.h"

using namespace std;

class CBTModule
{
public:
    static CBTModule* Instance();
    static void CreateInstance();
    static void FreeInstance(bool);

protected:
    CBTModule(void);
    ~CBTModule(void);
    static CBTModule* m_pInstance;

private:
    CBTModule(CBTModule const&);
    CBTModule& operator = (CBTModule const*);

public:
    // Generali
    CString StackName() { return m_szStackName; };
    int StackIndex() { return m_iStackIndex; };
    bool CancelDiscoverRequired() { return m_bCancelDiscoverRequired; };

    virtual BOOL IsHWDeviceReady(HWND) { return (FALSE); };
    virtual void FreeBtModule() {};
    virtual BOOL BindDevice(HWND, PBTDEVICE) { return (TRUE); };
    virtual BOOL UnbindDevice(PBTDEVICE) { return (TRUE); };
    virtual void LoadAuthenticatedDevices(HWND, bool) {};
    virtual BOOL InitBtModule(LPCTSTR) { return (TRUE); };
    virtual BOOL InitStack(HWND, PCHAR) { return (TRUE); };
    virtual BOOL StartInquiry(HWND) { return (FALSE); };
    virtual void StopInquiry(HWND) {};
    virtual void GetLocalDeviceInfo(PBTLOCALDEVICE) {};
    virtual BOOL IsRemoteDeviceConnectable(PBTDEVICE);
    virtual BOOL InitComPorts() { return (TRUE); };
    //void SetConnEvent(void);

protected:
    CString m_szStackName;
    int m_iStackIndex;
    bool m_bCancelDiscoverRequired;
    void StackName(CString value) { m_szStackName = value; };
    void StackIndex(int value) { m_iStackIndex = value; };
    void CancelDiscoverRequired(bool value) { m_bCancelDiscoverRequired = value; };
    //const vector<BTDEVICE> m_discoveredDevices;
    //HANDLE m_eventWaitConn;
};

//extern CBTModule g_btModule;
//extern void SetBtModule(CBTModule module);
