#pragma once
#include <ws2bth.h>
#include <BluetoothAPIs.h>
#include <SetupAPI.h>
#include <devguid.h>
#include <vector>
#include <algorithm>
#include "..\TestBtNAP\Public.h"
//#include <iostream>
//#include <functional>

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

    HBLUETOOTH_AUTHENTICATION_REGISTRATION authCallbackHandle = NULL;

    HBLUETOOTH_AUTHENTICATION_REGISTRATION authCallbackHandleHs = NULL;

	HBLUETOOTH_AUTHENTICATION_REGISTRATION authCallbackHandleSPP = NULL;

    AFX_EXT_API void MsBt7_NullAuthCb(void);

    AFX_EXT_API BOOL MsBt7_IsHWDeviceReady(void);

    AFX_EXT_API void MsBt7_DiscoverRemoteDevices(HWND, DWORD);

    AFX_EXT_API void MsBt7_GetAuthenticatedDevices(HWND, bool);

    AFX_EXT_API BOOL MsBt7_ExecAuthenticateDeviceEx(PBYTE, DWORD, PCHAR);

    AFX_EXT_API BOOL MsBt7_ExecRemoveAuthenticatedDevice(PBYTE);

    AFX_EXT_API void MsBt7_StopDiscoverRemoteDevices(HWND);

    AFX_EXT_API void MsBt7_GetLocalDeviceInfo(PBTLOCALDEVICE);

    AFX_EXT_API BOOL MsBt7_IsRemoteDeviceConnectable(LPCTSTR);

#ifdef __cplusplus
}
#endif
