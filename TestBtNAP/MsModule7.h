#pragma once
#include "Public.h"
#include "BTModule.h"
#include "DLLModule.h"

class CMsModule7 :
    public CBTModule, public CDLLModule
{
public:
    static void CreateInstance();

    virtual BOOL IsHWDeviceReady(HWND);
    virtual BOOL InitBtModule(LPCTSTR);
    virtual BOOL StartInquiry(HWND);
    virtual void LoadAuthenticatedDevices(HWND hWnd, bool);
    virtual BOOL BindDevice(HWND, PBTDEVICE);
    virtual BOOL UnbindDevice(PBTDEVICE);
    virtual void StopInquiry(HWND);
    virtual void GetLocalDeviceInfo(PBTLOCALDEVICE);
    virtual BOOL IsRemoteDeviceConnectable(PBTDEVICE);

    DECLARE_DLL_FUNCTION(BOOL, WINAPIV, MsBt7_IsHWDeviceReady, (void))
    DECLARE_DLL_FUNCTION(BOOL, WINAPIV, MsBt7_NullAuthCb, (void))
    DECLARE_DLL_FUNCTION(void, WINAPIV, MsBt7_DiscoverRemoteDevices, (HWND, DWORD))
    DECLARE_DLL_FUNCTION(void, WINAPIV, MsBt7_GetAuthenticatedDevices, (HWND, bool))
    DECLARE_DLL_FUNCTION(BOOL, WINAPIV, MsBt7_ExecAuthenticateDeviceEx, (PBYTE, DWORD, PCHAR))
    DECLARE_DLL_FUNCTION(BOOL, WINAPIV, MsBt7_ExecRemoveAuthenticatedDevice, (PBYTE))
    DECLARE_DLL_FUNCTION(void, WINAPIV, MsBt7_StopDiscoverRemoteDevices, (HWND))
    DECLARE_DLL_FUNCTION(void, WINAPIV, MsBt7_GetLocalDeviceInfo, (PBTLOCALDEVICE))
    DECLARE_DLL_FUNCTION(BOOL, WINAPIV, MsBt7_IsRemoteDeviceConnectable, (LPCTSTR))

    BEGIN_DLL_INIT()
        INIT_DLL_FUNCTION(BOOL, WINAPIV, MsBt7_IsHWDeviceReady, (void), "MsBt7_IsHWDeviceReady")
        INIT_DLL_FUNCTION(BOOL, WINAPIV, MsBt7_NullAuthCb, (void), "MsBt7_NullAuthCb")
        INIT_DLL_FUNCTION(void, WINAPIV, MsBt7_DiscoverRemoteDevices, (HWND, DWORD), "MsBt7_DiscoverRemoteDevices")
        INIT_DLL_FUNCTION(void, WINAPIV, MsBt7_GetAuthenticatedDevices, (HWND, bool), "MsBt7_GetAuthenticatedDevices")
        INIT_DLL_FUNCTION(BOOL, WINAPIV, MsBt7_ExecAuthenticateDeviceEx, (PBYTE, DWORD, PCHAR), "MsBt7_ExecAuthenticateDeviceEx")
        INIT_DLL_FUNCTION(BOOL, WINAPIV, MsBt7_ExecRemoveAuthenticatedDevice, (PBYTE), "MsBt7_ExecRemoveAuthenticatedDevice")
        INIT_DLL_FUNCTION(void, WINAPIV, MsBt7_StopDiscoverRemoteDevices, (HWND), "MsBt7_StopDiscoverRemoteDevices")
        INIT_DLL_FUNCTION(void, WINAPIV, MsBt7_GetLocalDeviceInfo, (PBTLOCALDEVICE), "MsBt7_GetLocalDeviceInfo")
        INIT_DLL_FUNCTION(BOOL, WINAPIV, MsBt7_IsRemoteDeviceConnectable, (LPCTSTR), "MsBt7_IsRemoteDeviceConnectable")
    END_DLL_INIT()

public:
    CMsModule7(void);
    virtual ~CMsModule7(void);
};
