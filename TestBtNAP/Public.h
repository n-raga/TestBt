//#pragma once

#ifndef PUBLIC_H
#define PUBLIC_H

#define WM_APP_INQUIRYSTART         (WM_APP + 1)
#define WM_APP_BT_INQUIRYSTART      (WM_APP + 2)
#define WM_APP_INQUIRYEND           (WM_APP + 3)
#define WM_APP_DEVICEFOUND          (WM_APP + 4)
#define WM_APP_BINDDEVICE           (WM_APP + 5)
#define WM_APP_SILENTBINDDEVICE     (WM_APP + 6)
#define WM_APP_UNBINDDEVICE         (WM_APP + 7)
#define WM_APP_INQUIRYSTOP          (WM_APP + 8)
#define WM_APP_DISCOVERDEVICE2      (WM_APP + 9)
#define WM_APP_HFPCONNECT           (WM_APP + 10)
#define WM_APP_UPDATEITEMSTATUS     (WM_APP + 11)
#define WM_APP_CONNECTCOMM2         (WM_APP + 12)
#define WM_APP_TESTDEVICECONN       (WM_APP + 13)
#define WM_APP_SILENTUNBINDDEVICE   (WM_APP + 14)

///////////////////////////////////////////////////////////////////////////
#ifdef ETS_BUILD
class CBluetoothManagerApp;
static CBluetoothManagerApp* g_pTheApp = NULL;
#endif

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// AXONE4: attivazione/disattivazione rotazione
//-------------------------------------------------------------------------
static UINT  UWM_ENABLE_ROTATION = ::RegisterWindowMessage( _T("F08DAA3A-1159-4288-87D4-F57F2AE694A9__ENABLE-ROTATION") );

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// AXONE4: attivazione/disattivazione Bluetooth
//-------------------------------------------------------------------------
static UINT UWM_ENABLE_BLUETOOTH = ::RegisterWindowMessage( _T("F08DAA3A-1159-4288-87D4-F57F2AE694A9__ENABLE-BLUETOOTH") );

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// AXONE4: modificata configurazione GPS
//-------------------------------------------------------------------------
static UINT UWM_NAVIGATION_GPS_SETTINGS_CHANGED = ::RegisterWindowMessage(_T("D90EF69E-CE95-41ed-83E9-83D81E5A137E_NAVIGATION_GPS_SETTINGS_CHANGED"));

////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//// IDC4: avvio clessidra
////-------------------------------------------------------------------------
//static const UINT WM_MSTARTLOADING = RegisterWindowMessage(_T("3CF60186-63B5-4597-8516-FD89E678245C"));
//
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//// IDC4: stop clessidra
////-------------------------------------------------------------------------
//static const UINT WM_MSTOPLOADING = RegisterWindowMessage(_T("3CF60186-63B5-4597-8516-FD89E678245B"));

///////////////////////////////////////////////////////////////////////////

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// UWM_BT_DISCOVERDEVICE_START (Global)
//-------------------------------------------------------------------------
static const UINT UWM_BT_DISCOVERDEVICE_START = ::RegisterWindowMessage(_T("39F630A7-1C81-424d-86F8-3D0D527CD02D__BT_DISCOVERDEVICE_START"));

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// UWM_BT_FOUNDDEVICE (Global)
//-------------------------------------------------------------------------
static const UINT UWM_BT_FOUNDDEVICE = ::RegisterWindowMessage(_T("65AD7BDC-53D7-4000-BCA1-EC9550374C0D__BT_FOUNDDEVICE"));

////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//// UWM_BT_HFFOUNDDEVICE (Global)
////-------------------------------------------------------------------------
//static const UINT UWM_BT_HFFOUNDDEVICE = ::RegisterWindowMessage(_T("65AD7BDC-53D7-4000-BCA1-EC9550374C0D__BT_HFFOUNDDEVICE"));

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// UWM_BT_DISCOVERDEVICE_END (Global)
//-------------------------------------------------------------------------
static const UINT UWM_BT_DISCOVERDEVICE_END = ::RegisterWindowMessage(_T("C057920E-AC45-4f58-8090-2FCD3C077654__BT_DISCOVERDEVICE_END"));

///////////////////////////////////////////////////////////////////////////

////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//// UWM_DISCOVERDEVICE2 (TosBtAPI)
////-------------------------------------------------------------------------
//static const UINT UWM_DISCOVERDEVICE2 = ::RegisterWindowMessage(_T("3C1255D4-79C4-4092-AFA2-6874B309D92D__TosBtAPI_DISCOVERDEVICE2"));

////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//// UWM_DISCOVERNAME (TosBtAPI)
////-------------------------------------------------------------------------
//static const UINT UWM_DISCOVERNAME = ::RegisterWindowMessage(_T("D2E66F14-9082-4819-8E0E-11675F654143__TosBtAPI_DISCOVERNAME"));

////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//// UWM_CONNECTCOMM (TosBtAPI)
////-------------------------------------------------------------------------
//static const UINT UWM_CONNECTCOMM = ::RegisterWindowMessage(_T("39A2398D-CC4C-4c9f-9ECE-E9EFDA7A1B57__TosBtAPI_CONNECTCOMM"));

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// UWM_DEV_TURNED_ON (TosBtAPI)
//-------------------------------------------------------------------------
static const UINT UWM_DEV_TURNED_ON = ::RegisterWindowMessage(_T("841A2500-7E3B-42c1-B2C7-056CABA4DF0B__TosBtAPI_DEV_TURNED_ON"));

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// UWM_DEV_TURNED_OFF (TosBtAPI)
//-------------------------------------------------------------------------
static const UINT UWM_DEV_TURNED_OFF = ::RegisterWindowMessage(_T("AC47CFA8-52E3-47f7-9CAB-6C5F4C3477C4__TosBtAPI_DEV_TURNED_OFF"));

////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//// UWM_HFCONNECT (TosBtAPI)
////-------------------------------------------------------------------------
//static const UINT UWM_HFCONNECT = ::RegisterWindowMessage(_T("46B4AF6D-3DF1-4fdf-9EE6-ABC23689C9BB__TosBtAPI_HFCONNECT"));

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// UWM_WIZ_CLOSEAPP (Global)
//-------------------------------------------------------------------------
static const UINT UWM_WIZ_CLOSEAPP = ::RegisterWindowMessage(_T("861180ED-B94C-4e04-B6C4-9D14F41EA343__WIZ_CLOSEAPP"));

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// UWM_WIZ_STOP_REQUEST (Global)
//-------------------------------------------------------------------------
static const UINT UWM_WIZ_STOP_REQUEST = ::RegisterWindowMessage(_T("C63310AD-8A1F-4b7c-BF54-F3671B6E9C8E__WIZ_STOP_REQUEST"));

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// WM_DEVICE_CONFIGURATION_CHANGED (Global)
// Notifica cambiamenti di configurazione ad autodiagnosi
//-------------------------------------------------------------------------
static const UINT WM_DEVICE_CONFIGURATION_CHANGED = ::RegisterWindowMessage(_T("14EE8916-AB36-4443-AAE9-67BBF1F12317"));

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// WM_DEVICE_CONFIGURATION_CHANGED (Global)
// Notifica cambiamenti di configurazione ad autodiagnosi
//-------------------------------------------------------------------------
static const UINT WM_DEVICES_DISCOVERY_END = ::RegisterWindowMessage(_T("C63310AD-8A1F-4b7c-BF54-F3671B6E9C8E__DEVICES_DISCOVERY_END"));

///////////////////////////////////////////////////////////////////////////

typedef struct BTDEVICE
{
    BYTE        bdAddr[6];  // ID univoco dispositivo
    CString     bdName;     // Nome del dispositivo
    CString     bdComPort;  // Porta COM (COMxx: se xx > 0, dispositivo autenticato)
    ULONG       bdClass;    // Classe del dispositivo
    BYTE        bdSCN;      // Canale di comunicazione Bluetooth del dispositivo
    bool        discovered;
    bool        remembered;
    bool        authenticated;

    bool operator==(const BTDEVICE& btd)
    {
        return (0 == memcmp(bdAddr, btd.bdAddr, 6));
    }
}BTDEVICE, *PBTDEVICE;

///////////////////////////////////////////////////////////////////////////

typedef struct BTLOCALDEVICE
{
    BYTE        bldAddr[6];     // ID univoco dispositivo
    CString     bldName;        // Nome del dispositivo
    CString     bldVersion;     // Versione BT
    CString     stackName;

    bool operator==(const BTLOCALDEVICE& btld)
    {
        if (0 == memcmp(bldAddr, btld.bldAddr, 6))
            return true;
        else
            return false;
    }
} BTLOCALDEVICE, *PBTLOCALDEVICE;

///////////////////////////////////////////////////////////////////////////

#define BT_ERROR_SUCCESS                0
#define BT_ERROR_LOAD_MODULE            1
#define BT_ERROR_DEVICE_NOT_READY       2
#define BT_ERROR_INIT_STACK             3
#define BT_ERROR_INIT_COMM              4

///////////////////////////////////////////////////////////////////////////

#define BT_HEADSET_NAME                 _T("B01")
#define BT_HEADSET_NAME_2               _T("3904175")

#endif
