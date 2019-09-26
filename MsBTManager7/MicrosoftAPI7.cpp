#include "StdAfx.h"
#include "MicrosoftAPI7.h"
#include "..\TestBtNAP\CLinkFileLog.h"

//HANDLE hLookup;
//HANDLE hRadio;
bool m_bStopRequest;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// MsBt7_AnalyzeClassOfDevice
//-------------------------------------------------------------------------
void MsBt7_AnalyzeClassOfDevice(DWORD    dwClassOfDevice,
                                TCHAR* pszMSCName,            // Major Service Class Name
                                TCHAR* pszMajorDCName,        // Major Device Class Name
                                TCHAR* pszMinorDCName)        // Minor Device Class Name
{
    TCHAR    szMSCName[256] = {0};        // MajorServiceClass
    TCHAR    szMajorDCName[256] = {0};    // MinorDeviceClass
    TCHAR    szMinorDCName[256] = {0};    // MinorDeviceClass

    // MajorServiceClass field(bit 13-23)
    if (dwClassOfDevice & 0x00800000)
    {
        _tcscat_s(szMSCName, _T("Information, "));
    }
    if (dwClassOfDevice & 0x00400000)
    {
        _tcscat_s(szMSCName, _T("Telephony, "));
    }
    if (dwClassOfDevice & 0x00200000)
    {
        _tcscat_s(szMSCName, _T("Audio, "));
    }
    if (dwClassOfDevice & 0x00100000)
    {
        _tcscat_s(szMSCName, _T("Object Transfer, "));
    }
    if (dwClassOfDevice & 0x00080000)
    {
        _tcscat_s(szMSCName, _T("Capturing, "));
    }
    if (dwClassOfDevice & 0x00040000)
    {
        _tcscat_s(szMSCName, _T("Rendering, "));
    }
    if (dwClassOfDevice & 0x00020000)
    {
        _tcscat_s(szMSCName, _T("Networking, "));
    }
    if (dwClassOfDevice & 0x00010000)
    {
        _tcscat_s(szMSCName, _T("Positioning, "));
    }
    if (dwClassOfDevice & 0x00008000)
    {
        _tcscat_s(szMSCName, _T("<unknown bit15>, "));
    }
    if (dwClassOfDevice & 0x00004000)
    {
        _tcscat_s(szMSCName, _T("<unknown bit14>, "));
    }
    if (dwClassOfDevice & 0x00002000)
    {
        _tcscat_s(szMSCName, _T("Limited Discoverable Mode, "));
    }
    if (szMSCName[0] == '\0')
    {
        _tcscat_s(szMSCName, _T("<No Major Service Classes>, "));
    }
    szMSCName[/*min(0, */lstrlen(szMSCName) - 2/*)*/] = '\0';    // delete string end ','

    // MajorDeviceClass field(bit 8-12)
    // MinorDeviceClass field(bit 2-7)
    switch (dwClassOfDevice & 0x00001F00)
    {
    case 0x00000000 :
        // Miscellaneous
        _tcscat_s(szMajorDCName, _T("Miscellaneous"));
        break;

    case 0x00000100 :
        // Computer
        _tcscat_s(szMajorDCName, _T("Computer"));
        // bit 2-7
        switch (dwClassOfDevice & 0x000000fc)
        {
        case 0x00000000 :
            _tcscat_s(szMinorDCName,  _T("Unclassified, code for device not assigned"));
            break;
        case 0x00000004:
            _tcscat_s(szMinorDCName,  _T("Desktop workstation"));
            break;
        case 0x00000008:
            _tcscat_s(szMinorDCName,  _T("Server-class computer"));
            break;
        case 0x0000000C:
            _tcscat_s(szMinorDCName,  _T("Laptop"));
            break;
        case 0x00000010:
            _tcscat_s(szMinorDCName,  _T("Handheld PC/PDA(clam shell)"));
            break;
        case 0x00000014:
            _tcscat_s(szMinorDCName,  _T("Palm sized PC/PDA"));
            break;
        case 0x00000018:
            _tcscat_s(szMinorDCName,  _T("Wearable computer"));
            break;
        default :
            _tcscat_s(szMinorDCName,  _T("<unknown>"));
            break;
        }
        break;

    case 0x00000200 :
        // Phone
        _tcscat_s(szMajorDCName, _T("Phone"));
        // bit 2-7
        switch (dwClassOfDevice & 0x000000fc)
        {
        case 0x00000000 :
            _tcscat_s(szMinorDCName,  _T("Unclassified, code not assigned"));
            break;
        case 0x00000004 :
            _tcscat_s(szMinorDCName,  _T("Cellular"));
            break;
        case 0x00000008 :
            _tcscat_s(szMinorDCName,  _T("Cordless"));
            break;
        case 0x0000000C :
            _tcscat_s(szMinorDCName,  _T("Smart phone"));
            break;
        case 0x00000010 :
            _tcscat_s(szMinorDCName,  _T("Wired modem or voice gateway"));
            break;
        case 0x00000014 :
            _tcscat_s(szMinorDCName,  _T("Common ISDN Access"));
            break;
        default :
            _tcscat_s(szMinorDCName,  _T("<unknown>"));
            break;
        }
        break;

    case 0x00000300 :
        // LAN / Network Access Point
        _tcscat_s(szMajorDCName, _T("LAN/Network Access Point"));
        // bit 5-7
        switch (dwClassOfDevice & 0x000000E0)
        {
        case 0x00000000 :
            _tcscat_s(szMinorDCName,  _T("Fully available, "));
            break;
        case 0x00000020 :
            _tcscat_s(szMinorDCName,  _T(" 1-17% utilized, "));
            break;
        case 0x00000040 :
            _tcscat_s(szMinorDCName,  _T("17-33% utilized, "));
            break;
        case 0x00000060 :
            _tcscat_s(szMinorDCName,  _T("33-50% utilized, "));
            break;
        case 0x00000080 :
            _tcscat_s(szMinorDCName,  _T("50-67% utilized, "));
            break;
        case 0x000000A0 :
            _tcscat_s(szMinorDCName,  _T("67-83% utilized, "));
            break;
        case 0x000000C0 :
            _tcscat_s(szMinorDCName,  _T("83-99% utilized, "));
            break;
        case 0x000000E0 :
            _tcscat_s(szMinorDCName,  _T("No Service Available, "));
            break;
        }
        // bit 2-4
        switch (dwClassOfDevice & 0x0000001C)
        {
        case 0x00000000 :
            _tcscat_s(szMinorDCName,  _T("Uncategorized(use this value if no other apply)"));
            break;
        default :
            _tcscat_s(szMinorDCName,  _T("<unknown>"));
            break;
        }
        break;

    case 0x00000400 :
        // Audio/Video
        _tcscat_s(szMajorDCName, _T("Audio/Video"));
        // bit 2-7
        switch (dwClassOfDevice & 0x000000fc)
        {
        case 0x00000000 :
            _tcscat_s(szMinorDCName,  _T("Uncategorized, code not assigned"));
            break;
        case 0x00000004 :
            _tcscat_s(szMinorDCName,  _T("Device conforms to the Headset profile"));
            break;
        case 0x00000008 :
            _tcscat_s(szMinorDCName,  _T("Hands-free"));
            break;
        case 0x00000010 :
            _tcscat_s(szMinorDCName,  _T("Microphone"));
            break;
        case 0x00000014 :
            _tcscat_s(szMinorDCName,  _T("Loudspeaker"));
            break;
        case 0x00000018 :
            _tcscat_s(szMinorDCName,  _T("Headphones"));
            break;
        case 0x0000001C :
            _tcscat_s(szMinorDCName,  _T("Portable Audio"));
            break;
        case 0x00000020 :
            _tcscat_s(szMinorDCName,  _T("Car Audio"));
            break;
        case 0x00000024 :
            _tcscat_s(szMinorDCName,  _T("Set-top box"));
            break;
        case 0x00000028 :
            _tcscat_s(szMinorDCName,  _T("HiFi Audio Device"));
            break;
        case 0x0000002C :
            _tcscat_s(szMinorDCName,  _T("VCR"));
            break;
        case 0x00000030 :
            _tcscat_s(szMinorDCName,  _T("Video Camera"));
            break;
        case 0x00000034 :
            _tcscat_s(szMinorDCName,  _T("Camcorder"));
            break;
        case 0x00000038 :
            _tcscat_s(szMinorDCName,  _T("Video Monitor"));
            break;
        case 0x0000003C :
            _tcscat_s(szMinorDCName,  _T("Video Display and Loudspeaker"));
            break;
        case 0x00000040 :
            _tcscat_s(szMinorDCName,  _T("Video Conferencing"));
            break;
        case 0x00000048 :
            _tcscat_s(szMinorDCName,  _T("Gaming/Toy"));
            break;
        default :
            _tcscat_s(szMinorDCName,  _T("<unknown>"));
            break;
        }
        break;

    case 0x00000500 :
        // Peripheral
        _tcscat_s(szMajorDCName, _T("Peripheral"));
        // bit 6-7
        switch (dwClassOfDevice & 0x000000C0)
        {
        case 0x00000040 :
            _tcscat_s(szMinorDCName,  _T("Keyboard, "));
            break;
        case 0x00000080 :
            _tcscat_s(szMinorDCName,  _T("Pointing device, "));
            break;
        case 0x000000C0 :
            _tcscat_s(szMinorDCName,  _T("Combo keyboard/pointing device, "));
            break;
        }
        // bit 2-5
        switch (dwClassOfDevice & 0x0000003C)
        {
        case 0x00000000 :
            _tcscat_s(szMinorDCName,  _T("Uncategorized device"));
            break;
        case 0x00000004 :
            _tcscat_s(szMinorDCName,  _T("Joystick"));
            break;
        case 0x00000008 :
            _tcscat_s(szMinorDCName,  _T("Gamepad"));
            break;
        case 0x0000000C :
            _tcscat_s(szMinorDCName,  _T("Remote control"));
            break;
        case 0x00000010 :
            _tcscat_s(szMinorDCName,  _T("Sensing device"));
            break;
        default :
            _tcscat_s(szMinorDCName,  _T("<unknown>"));
            break;
        }
        break;

    case 0x00000600 :
        // Imaging
        _tcscat_s(szMajorDCName, _T("Imaging"));
        // bit 4-7
        if (dwClassOfDevice & 0x00000010) _tcscat_s(szMinorDCName,  _T("Display, "));
        if (dwClassOfDevice & 0x00000020) _tcscat_s(szMinorDCName,  _T("Camera, "));
        if (dwClassOfDevice & 0x00000040) _tcscat_s(szMinorDCName,  _T("Scanner, "));
        if (dwClassOfDevice & 0x00000080) _tcscat_s(szMinorDCName,  _T("Printer, "));
        // bit 2-3
        switch (dwClassOfDevice & 0x0000000C)
        {
        case 0x00000000 :
            _tcscat_s(szMinorDCName,  _T("Uncategorized, default"));
            break;
        default :
            _tcscat_s(szMinorDCName,  _T("<unknown>"));
            break;
        }
        break;

    case 0x00001F00 :
        // Unclassified, specific device code not assigned
        _tcscat_s(szMajorDCName, _T("Uncategorized, specific device code not assigned"));
        break;

    default :
        // Unknown
        _tcscat_s(szMajorDCName, _T("<unknown>"));
        break;
    }

    _tcscpy(pszMSCName/*, sizeof(szMSCName)*/, &szMSCName[0]);
    _tcscpy(pszMajorDCName/*, sizeof(szMajorDCName)*/, &szMajorDCName[0]);
    _tcscpy(pszMinorDCName/*, sizeof(szMinorDCName)*/, &szMinorDCName[0]);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// MsBt7_ErrorDisp
//-------------------------------------------------------------------------
TCHAR* MsBt7_ErrorDisp(DWORD lastError)
{
    static TCHAR errorMsg[512];

    if (!FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, lastError, 0, errorMsg, 511, NULL))
    {
        // if this fail, call itself to find out why and return that error
        return (MsBt7_ErrorDisp(GetLastError()));
    }

    //AppendLogEx(LOG_ERROR_INFO, _T("Error: %s"), errorMsg);
    return errorMsg;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// MsBt7_GetCOMPortFromRegistry
//-------------------------------------------------------------------------
CString MsBt7_GetCOMPortFromRegistry(BLUETOOTH_ADDRESS BdAddr)
{
    CString instanceID;
    CString deviceID;
    CString portName;
    DWORD requiredSize;

    GUID classGuid[1];
    if ((FALSE) == SetupDiClassGuidsFromName(_T("PORTS"), classGuid, 1, &requiredSize))
    {
        AppendLogEx(LOG_WARNING, _T("%s"), _T("SetupDiClassGuidsFromName failure!"));
        return _T("");
    }

    HDEVINFO hDevInfoSet = SetupDiGetClassDevs(classGuid, NULL, NULL, DIGCF_PRESENT);
    if (INVALID_HANDLE_VALUE == hDevInfoSet)
    {
        AppendLogEx(LOG_WARNING, _T("%s"), _T("SetupDiGetClassDevs failure!"));
        return _T("");
    }

    SP_DEVINFO_DATA devInfo;
    devInfo.cbSize = sizeof(SP_DEVINFO_DATA);

    for (DWORD deviceIndex = 0; SetupDiEnumDeviceInfo(hDevInfoSet, deviceIndex, &devInfo); deviceIndex++)
    {
        SetupDiGetDeviceInstanceId(hDevInfoSet, &devInfo, NULL, 0, &requiredSize);
        SetupDiGetDeviceInstanceId(hDevInfoSet, &devInfo, instanceID.GetBuffer(requiredSize), requiredSize, NULL);
        AppendLogEx(LOG_INFO, _T("Instance ID: %s"), instanceID);
        instanceID.ReleaseBuffer();

        deviceID = instanceID.Mid(instanceID.ReverseFind('&') + 1);
        deviceID = deviceID.Left(deviceID.ReverseFind('_'));
        if (deviceID.Compare(_T("000000000000")) != 0 && deviceID.GetLength() != 0)
        {
            deviceID.Format(_T("%s:%s:%s:%s:%s:%s"), deviceID.Mid(0, 2), deviceID.Mid(2, 2),
                deviceID.Mid(4, 2), deviceID.Mid(6, 2), deviceID.Mid(8, 2), deviceID.Mid(10, 2));

            AppendLogEx(LOG_INFO, _T("Device ID: %s"), deviceID);

            CString devAddr;
            devAddr.Format(_T("%02X:%02X:%02X:%02X:%02X:%02X"), BdAddr.rgBytes[5], BdAddr.rgBytes[4],
                BdAddr.rgBytes[3], BdAddr.rgBytes[2],BdAddr.rgBytes[1], BdAddr.rgBytes[0]);
            if (0 == deviceID.Compare(devAddr))
            {
                HKEY hKey = SetupDiOpenDevRegKey(hDevInfoSet, &devInfo, DICS_FLAG_GLOBAL, 0, DIREG_DEV, KEY_READ);
                //if (INVALID_HANDLE_VALUE == hKey)
                //{
                //    continue;
                //}
                while (INVALID_HANDLE_VALUE == hKey)
                {
                    hKey = SetupDiOpenDevRegKey(hDevInfoSet, &devInfo, DICS_FLAG_GLOBAL, 0, DIREG_DEV, KEY_READ);
                }

                portName = _T("");
                //RegQueryValueEx(hKey, _T("PortName"), NULL, NULL, NULL, &requiredSize);
                //RegQueryValueEx(hKey, _T("PortName"), NULL, NULL, (LPBYTE)portName.GetBuffer(requiredSize), &requiredSize);
                while (portName == _T(""))
                {
                    RegQueryValueEx(hKey, _T("PortName"), NULL, NULL, NULL, &requiredSize);
                    RegQueryValueEx(hKey, _T("PortName"), NULL, NULL, (LPBYTE)portName.GetBuffer(requiredSize), &requiredSize);
                    portName.ReleaseBuffer();
                }
                AppendLogEx(LOG_INFO, _T("PortName: %s"), portName);

                RegCloseKey(hKey);

                TRACE(_T("DeviceID: %s\tPort: %s\n"), deviceID, portName);
                SetupDiDestroyDeviceInfoList(hDevInfoSet);
                return portName;
            }
        }
    }
    SetupDiDestroyDeviceInfoList(hDevInfoSet);
    return _T("");
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// MsBt7_GetCOMPortFromRegistry
//-------------------------------------------------------------------------
void MsBt7_GetCOMPortFromRegistry(BLUETOOTH_ADDRESS BdAddr, PCHAR pszPortName)
{
    CString szPortName = MsBt7_GetCOMPortFromRegistry(BdAddr);
    USES_CONVERSION;
    strcpy(pszPortName, W2A(szPortName.GetBuffer(szPortName.GetLength())));
    szPortName.ReleaseBuffer();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// MsBt7_NullAuthCb
//-------------------------------------------------------------------------
void MsBt7_NullAuthCb(void)
{
    authCallbackHandle = NULL;
    authCallbackHandleHs = NULL;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// MsBt7_IsHWDeviceReady
//-------------------------------------------------------------------------
BOOL MsBt7_IsHWDeviceReady(void)
{
    BLUETOOTH_FIND_RADIO_PARAMS btfrp = { sizeof(BLUETOOTH_FIND_RADIO_PARAMS) };
    HBLUETOOTH_RADIO_FIND hFind;

    HANDLE hRadio;
    AppendLogEx(LOG_INFO, _T("%s"), _T("BluetoothAPIs::BluetoothFindFirstRadio()"));
    hFind = BluetoothFindFirstRadio(&btfrp, &hRadio);
    if (NULL == hFind)
    {
        AppendLogEx(LOG_ERROR, _T("%s"), _T("BluetoothAPIs::BluetoothGetRadioInfo() failure!"));
        TRACE(_T("Failed to get Bluetooth radio! %s\r\n"), MsBt7_ErrorDisp(GetLastError()));
        return (FALSE);
    }

    BLUETOOTH_RADIO_INFO radioInfo = { sizeof(BLUETOOTH_RADIO_INFO) };
    AppendLogEx(LOG_INFO, _T("BluetoothAPIs::BluetoothGetRadioInfo()"));
    if (ERROR_SUCCESS == BluetoothGetRadioInfo(hRadio, &radioInfo))
    {
        TRACE(_T("Radio: %s\r\n"), radioInfo.szName);
        AppendLogEx(LOG_INFO, _T("%s"), _T("BluetoothAPIs::BluetoothGetRadioInfo() success."));
    }
    CloseHandle(hRadio);
    AppendLogEx(LOG_INFO, _T("%s"), _T("BluetoothAPIs::BluetoothFindRadioClose()"));
    BluetoothFindRadioClose(hFind);
    return (TRUE);
}

//struct ms_addr_equal : std::unary_function<BLUETOOTH_DEVICE_INFO_STRUCT,bool>
//{
//    ms_addr_equal(const BLUETOOTH_DEVICE_INFO_STRUCT &dev) : dev_(dev) {}
//    bool operator()(const BLUETOOTH_DEVICE_INFO_STRUCT &arg) const {
//        return (0 == memcmp(arg.Address.rgBytes, dev_.Address.rgBytes, sizeof(arg.Address.rgBytes)));
//    }
//    const BLUETOOTH_DEVICE_INFO_STRUCT &dev_;
//};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// MsBt7_DiscoverRemoteDevices
//-------------------------------------------------------------------------
void MsBt7_DiscoverRemoteDevices(HWND hWnd, DWORD dwMode)
{
    m_bStopRequest = false;

    BLUETOOTH_DEVICE_INFO_STRUCT deviceInfo = { sizeof(BLUETOOTH_DEVICE_INFO_STRUCT) };
    TCHAR strBuff[0xFF];
    TCHAR szMSCName[256];        // MajorServiceClass
    TCHAR szMajorDCName[256];    // MajorDeviceClass
    TCHAR szMinorDCName[256];    // MinorDeviceClass

    BLUETOOTH_FIND_RADIO_PARAMS btfrp = { sizeof(BLUETOOTH_FIND_RADIO_PARAMS) };
    HBLUETOOTH_RADIO_FIND hFind;
    HANDLE hRadio = NULL;

    AppendLogEx(LOG_INFO, _T("%s"), _T("BluetoothAPIs::BluetoothFindFirstRadio()"));
    hFind = BluetoothFindFirstRadio(&btfrp, &hRadio);

    if (NULL == hFind)
    {
        AppendLogEx(LOG_ERROR, _T("%s"), _T("BluetoothAPIs::BluetoothGetRadioInfo() failure!"));
        TRACE(_T("Failed to get Bluetooth radio! %s\r\n"), MsBt7_ErrorDisp(GetLastError()));
        ::SendMessage(hWnd, UWM_BT_DISCOVERDEVICE_END, 0, 0); //::PostMessage(hWnd, UWM_BT_DISCOVERDEVICE_END, 0, 0);
        return;
    }

    BLUETOOTH_RADIO_INFO radioInfo = { sizeof(BLUETOOTH_RADIO_INFO) };
    AppendLogEx(LOG_INFO, _T("%s"), _T("BluetoothAPIs::BluetoothGetRadioInfo()"));
    if (ERROR_SUCCESS == BluetoothGetRadioInfo(hRadio, &radioInfo))
    {
        TRACE(_T("Radio: %s\r\n"), radioInfo.szName);
        AppendLogEx(LOG_INFO, _T("%s"), _T("BluetoothAPIs::BluetoothGetRadioInfo() success."));
    }

    WSADATA m_data;
    AppendLogEx(LOG_INFO, _T("%s"), _T("WinSock2::WSAStartup()"));

    int iErr = WSAStartup(MAKEWORD(2, 2), &m_data);
    if (iErr != 0)
    {
        CloseHandle(hRadio);
        AppendLogEx(LOG_INFO, _T("BluetoothAPIs::BluetoothFindRadioClose()"));
        BluetoothFindRadioClose(hFind);
        AppendLogEx(LOG_ERROR, _T("WinSock2::WSAStartup() failure! Unable to initialize Winsock version 2.2. Error code: %d"), iErr);
        TRACE(_T("Unable to initialize Winsock version 2.2\r\n"));
        ::SendMessage(hWnd, UWM_BT_DISCOVERDEVICE_END, 0, 0); //::PostMessage(hWnd, UWM_BT_DISCOVERDEVICE_END, 0, 0);
        return;
    }

    AppendLogEx(LOG_INFO, _T("%s"), _T("WinSock2::socket()"));
    SOCKET s = ::socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
    if (s == INVALID_SOCKET)
    {
        CloseHandle(hRadio);
        AppendLogEx(LOG_INFO, _T("BluetoothAPIs::BluetoothFindRadioClose()"));
        BluetoothFindRadioClose(hFind);
        AppendLogEx(LOG_ERROR, _T("%s"), _T("WinSock2::socket() failure! Failed to get Bluetooth socket!"));
        TRACE(_T("Failed to get Bluetooth socket! %s\r\n"), MsBt7_ErrorDisp(GetLastError()));
        ::SendMessage(hWnd, UWM_BT_DISCOVERDEVICE_END, 0, 0); //::PostMessage(hWnd, UWM_BT_DISCOVERDEVICE_END, 0, 0);
        return;
    }

    WSAPROTOCOL_INFO protocolInfo;
    int protocolInfoSize = sizeof(protocolInfo);
    AppendLogEx(LOG_INFO, _T("%s"), _T("WinSock2::getsockopt()"));
    if (ERROR_SUCCESS != getsockopt(s, SOL_SOCKET, SO_PROTOCOL_INFO, (char*)&protocolInfo, &protocolInfoSize))
    {
        CloseHandle(hRadio);
        AppendLogEx(LOG_INFO, _T("BluetoothAPIs::BluetoothFindRadioClose()"));
        BluetoothFindRadioClose(hFind);
        AppendLogEx(LOG_ERROR, _T("%s"), _T("WinSock2::getsockopt() failure! Failed to retrieve socket option!"));
        TRACE(_T("Failed to retrieve socket option! %s\r\n"), MsBt7_ErrorDisp(GetLastError()));
        ::SendMessage(hWnd, UWM_BT_DISCOVERDEVICE_END, 0, 0); //::PostMessage(hWnd, UWM_BT_DISCOVERDEVICE_END, 0, 0);
        return;
    }

    //TRACE(_T("    START \t DiscoverRemoteDevices\r\n"));
    //AppendLogEx(LOG_INFO, _T("START DiscoverRemoteDevices."));
    //::PostMessage(hWnd, UWM_BT_DISCOVERDEVICE_START, 0, 0);

    WSAQUERYSET querySet = { sizeof(WSAQUERYSET) };
    querySet.dwNameSpace = NS_BTH;

    HANDLE hLookup = NULL;

    DWORD flags = LUP_DEEP | LUP_RETURN_NAME | LUP_CONTAINERS | LUP_RETURN_ADDR | LUP_FLUSHCACHE |
        LUP_RETURN_TYPE | LUP_RETURN_BLOB | LUP_RES_SERVICE;
    AppendLogEx(LOG_INFO, _T("WinSock2::WSALookupServiceBegin()"));
    int result = WSALookupServiceBegin(&querySet, flags, &hLookup);

    if (result != 0)
    {
        AppendLogEx(LOG_INFO, _T("%s"), _T("WinSock2::WSACleanup()"));
        if (0 != WSACleanup())
        {
            AppendLogEx(LOG_INFO, _T("WinSock2::WSACleanup() failure! %d (WSALookupServiceBegin)"), WSAGetLastError());
            TRACE(_T("WinSock2::WSACleanup() failure! %d (WSALookupServiceBegin)\r\n"), WSAGetLastError());
        }
        AppendLogEx(LOG_INFO, _T("%s"), _T("WinSock2::WSACleanup() success (WSALookupServiceBegin)."));

        AppendLogEx(LOG_ERROR, _T("WinSock2::WSALookupServiceBegin() failure! %d"), WSAGetLastError());
        TRACE(_T("%d\r\n"), WSAGetLastError());

        CloseHandle(hRadio);
        AppendLogEx(LOG_INFO, _T("BluetoothAPIs::BluetoothFindRadioClose()"));
        BluetoothFindRadioClose(hFind);

        ::SendMessage(hWnd, UWM_BT_DISCOVERDEVICE_END, 0, 0); //::PostMessage(hWnd, UWM_BT_DISCOVERDEVICE_END, 0, 0);
        return;
    }

    TRACE(_T("    START \t DiscoverRemoteDevices\r\n"));
    AppendLogEx(LOG_INFO, _T("%s"), _T("START DiscoverRemoteDevices."));
    ::PostMessage(hWnd, UWM_BT_DISCOVERDEVICE_START, 0, 0);

    AppendLogEx(LOG_INFO, _T("%s"), _T("WinSock2::WSALookupServiceBegin() success."));
    while ((ERROR_SUCCESS == result) && (!m_bStopRequest))
    {
        BYTE buffer[1024];
        DWORD bufferLength = sizeof(buffer);
        WSAQUERYSET *pResults = (WSAQUERYSET*)&buffer;
        AppendLogEx(LOG_INFO, _T("WinSock2::WSALookupServiceNext()"));
        result = WSALookupServiceNext(hLookup, flags, &bufferLength, pResults);

        if (CString(pResults->lpszServiceInstanceName) != _T(""))
            TRACE(_T("Device found: %s. Getting device info ...\r\n"), pResults->lpszServiceInstanceName);
        else
            TRACE(_T("Device found: <Unknown Device>. Getting device info ...\r\n"));

        if (m_bStopRequest)
            break;
        if (result != 0)
        {
            AppendLogEx(LOG_INFO, _T("WinSock2::WSALookupServiceNext() failure! Error code: %d"), result);
            break;
        }

        AppendLogEx(LOG_INFO, _T("%s"), _T("WinSock2::WSALookupServiceNext() success."));
        CSADDR_INFO *pCSAddr = (CSADDR_INFO *)pResults->lpcsaBuffer;
        BTH_DEVICE_INFO *pDeviceInfo = (BTH_DEVICE_INFO*)pResults->lpBlob;
        //GUID protocol = SerialPortServiceClass_UUID;
        WCHAR addressAsString[1024];
        DWORD addressSize = sizeof(addressAsString);
        AppendLogEx(LOG_INFO, _T("%s"), _T("WinSock2::WSAAddressToString()"));

        int rc = WSAAddressToString(pCSAddr->RemoteAddr.lpSockaddr, pCSAddr->RemoteAddr.iSockaddrLength,
            &protocolInfo, addressAsString, &addressSize);

        if (m_bStopRequest)
            break;
        if (rc != 0)
        {
            AppendLogEx(LOG_INFO, _T("WinSock2::WSAAddressToString() failure! Error code: %d"), rc);
            break;
        }

        // [adm 06-09-2016]
        // Need to re-allocate, else BluetoothGetDeviceInfo() will fail
        ZeroMemory(&deviceInfo, sizeof(BLUETOOTH_DEVICE_INFO_STRUCT));
        deviceInfo.dwSize = sizeof(BLUETOOTH_DEVICE_INFO_STRUCT);
        //

        CopyMemory(&deviceInfo.Address, &pCSAddr->RemoteAddr.lpSockaddr->sa_data, sizeof(deviceInfo.Address));

        // BluetoothGetDeviceInfo function retrieves information about a remote Bluetooth device.
        // The Bluetooth device must have been previously identified through a successful device inquiry function call
        AppendLogEx(LOG_INFO, _T("%s"), _T("BluetoothAPIs::BluetoothGetDeviceInfo()"));

        DWORD dwStatus = BluetoothGetDeviceInfo(hRadio, &deviceInfo);

        if (m_bStopRequest)
            break;
        if (dwStatus != 0)
        {
            /*AppendLogEx(LOG_ERROR, _T("BluetoothAPIs::BluetoothGetDeviceInfo() failure! Error code: %s"),
                MsBt7_ErrorDisp(GetLastError()));*/

            AppendLogEx(LOG_ERROR, _T("BluetoothAPIs::BluetoothGetDeviceInfo() failure! Error code: %d"), dwStatus);

            //TRACE(_T("Failed to retrieve device info! %s\r\n"), MsBt7_ErrorDisp(GetLastError()));
            //::SendMessage(hWnd, UWM_BT_DISCOVERDEVICE_END, 0, 0); //::PostMessage(hWnd, UWM_BT_DISCOVERDEVICE_END, 0, 0);
            break;
        }

        AppendLogEx(LOG_INFO, _T("%s"), _T("BluetoothAPIs::BluetoothGetDeviceInfo() success."));

        if (m_bStopRequest)
            break;

        CString devName;
        devName = CString(deviceInfo.szName).Trim();
        if ((0 == dwMode) && (devName.Compare(_T("")) == 0))
        {
            // Ciclo per trovare il nome del dispositivo nel caso non venga trovato subito. Timeout: 10 sec.
            int iterations = 0;
            do
            {
                ::Sleep(500);
                ZeroMemory(&deviceInfo, sizeof(BLUETOOTH_DEVICE_INFO_STRUCT));
                deviceInfo.dwSize = sizeof(BLUETOOTH_DEVICE_INFO_STRUCT);
                CopyMemory(&deviceInfo.Address, &pCSAddr->RemoteAddr.lpSockaddr->sa_data, sizeof(deviceInfo.Address));
                if ((ERROR_SUCCESS != BluetoothGetDeviceInfo(hRadio, &deviceInfo)) && (!m_bStopRequest))
                {
                    //#ifdef _DEBUG
                    //  AfxMessageBox((_T("Error on BluetoothGetDeviceInfo! Iteration: %d"), iterations));
                    //#endif
                    break;
                }
                devName = CString(deviceInfo.szName).Trim();
                iterations++;
            } while ((devName.Compare(_T("")) == 0) && !m_bStopRequest && iterations < 50);
        }

        if (m_bStopRequest)
            break;

        MsBt7_AnalyzeClassOfDevice(deviceInfo.ulClassofDevice, &szMSCName[0], &szMajorDCName[0], &szMinorDCName[0]);

        TRACE(_T("  \n\tDeviceName: %s\r\n"), deviceInfo.szName);
        TRACE(_T("  \tAddress: %02X:%02X:%02X:%02X:%02X:%02X\r\n"), deviceInfo.Address.rgBytes[5],
            deviceInfo.Address.rgBytes[4], deviceInfo.Address.rgBytes[3], deviceInfo.Address.rgBytes[2],
            deviceInfo.Address.rgBytes[1], deviceInfo.Address.rgBytes[0]);
        wsprintf(strBuff, _T("%02X:%02X:%02X:%02X:%02X:%02X"), deviceInfo.Address.rgBytes[5],
            deviceInfo.Address.rgBytes[4], deviceInfo.Address.rgBytes[3], deviceInfo.Address.rgBytes[2],
            deviceInfo.Address.rgBytes[1], deviceInfo.Address.rgBytes[0]);
        TRACE(_T("  \tClass of device: 0x%08x\r\n"), deviceInfo.ulClassofDevice);
        TRACE(_T("  \tConnected: %s\r\n"), deviceInfo.fConnected ? L"true" : L"false");
        TRACE(_T("  \tAuthenticated: %s\r\n"), deviceInfo.fAuthenticated ? L"true" : L"false");
        TRACE(_T("  \tRemembered: %s\r\n\n"), deviceInfo.fRemembered ? L"true" : L"false");

        if (m_bStopRequest)
            break;

        CString szComm = MsBt7_GetCOMPortFromRegistry(deviceInfo.Address).Trim();
        BOOL iDiscovered = szComm.CompareNoCase(_T("")) == 0
            ? (TRUE)
            : MsBt7_IsRemoteDeviceConnectable(szComm);

        if (m_bStopRequest)
            break;

        BTDEVICE device;
        device.bdName = deviceInfo.szName;
        ZeroMemory(device.bdAddr, sizeof(device.bdAddr));
        CopyMemory(device.bdAddr, deviceInfo.Address.rgBytes, sizeof(device.bdAddr));
        device.bdComPort = szComm;
        device.bdClass = deviceInfo.ulClassofDevice;
        device.discovered = iDiscovered == (TRUE);
        device.remembered = (deviceInfo.fRemembered != 0);
        device.authenticated = (deviceInfo.fAuthenticated != 0);
        AppendLogEx(LOG_INFO, _T("DEVICE FOUND: [%s | (%s) | %s | %s]"),
            device.bdName.MakeUpper(),
            strBuff,
            device.bdComPort,
            szMajorDCName);

        HWND mainWnd = GetParent(hWnd);
        if (mainWnd == NULL)
            mainWnd = hWnd;

        if (m_bStopRequest)
            break;

        ::SendMessage(mainWnd, UWM_BT_FOUNDDEVICE, reinterpret_cast<WPARAM>(&device), 0);
    }

    AppendLogEx(LOG_INFO, _T("%s"), _T("WinSock2::WSALookupServiceEnd()"));
    result = WSALookupServiceEnd(hLookup);

    AppendLogEx(LOG_INFO, _T("%s"), _T("WinSock2::WSACleanup()"));
    if (0 != WSACleanup())
    {
        AppendLogEx(LOG_INFO, _T("WinSock2::WSACleanup() failure! %d (End)"), WSAGetLastError());
        TRACE(_T("WinSock2::WSACleanup() failure! %d (End)\r\n"), WSAGetLastError());
    }
    AppendLogEx(LOG_INFO, _T("%s"), _T("WinSock2::WSACleanup() success (End)."));

    TRACE(_T("    END \t DiscoverRemoteDevices\r\n"));
    AppendLogEx(LOG_INFO, _T("%s"), _T("END DiscoverRemoteDevices."));

    CloseHandle(hRadio);
    BluetoothFindRadioClose(hFind);

    ::SendMessage(hWnd, UWM_BT_DISCOVERDEVICE_END, 0, 0); //::PostMessage(hWnd, UWM_BT_DISCOVERDEVICE_END, 0, 0);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// MsBt7_GetAuthenticatedDevices
//-------------------------------------------------------------------------
void MsBt7_GetAuthenticatedDevices(HWND hWnd, bool isWizardMode)
{
    HANDLE hDeviceFind;
    BLUETOOTH_DEVICE_INFO_STRUCT deviceInfo = { sizeof(BLUETOOTH_DEVICE_INFO_STRUCT) };
    TCHAR strBuff[0xFF];
    TCHAR szMSCName[256];        // MajorServiceClass
    TCHAR szMajorDCName[256];    // MajorDeviceClass
    TCHAR szMinorDCName[256];    // MinorDeviceClass

    BLUETOOTH_FIND_RADIO_PARAMS btfrp = { sizeof(BLUETOOTH_FIND_RADIO_PARAMS) };
    HBLUETOOTH_RADIO_FIND hFind;

    HANDLE hRadio;
    AppendLogEx(LOG_INFO, _T("%s"), _T("BluetoothAPIs::BluetoothFindFirstRadio()"));
    hFind = BluetoothFindFirstRadio(&btfrp, &hRadio);

    if (NULL == hFind)
    {
        AppendLogEx(LOG_ERROR, _T("%s"), _T("BluetoothAPIs::BluetoothGetRadioInfo() failure!"));
        TRACE(_T("Failed to get Bluetooth radio! %s\r\n"), MsBt7_ErrorDisp(GetLastError()));
        return;
    }

    BLUETOOTH_RADIO_INFO radioInfo = { sizeof(BLUETOOTH_RADIO_INFO) };
    AppendLogEx(LOG_INFO, _T("%s"), _T("BluetoothAPIs::BluetoothGetRadioInfo()"));
    if (ERROR_SUCCESS == BluetoothGetRadioInfo(hRadio, &radioInfo))
    {
        TRACE(_T("Radio: %s\r\n"), radioInfo.szName);
        AppendLogEx(LOG_INFO, _T("BluetoothAPIs::BluetoothGetRadioInfo() success."));
    }

    BLUETOOTH_DEVICE_SEARCH_PARAMS deviceSearchParams = { sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS) };
    deviceSearchParams.fReturnAuthenticated = true;
    deviceSearchParams.hRadio = hRadio;
    AppendLogEx(LOG_INFO, _T("BluetoothAPIs::BluetoothFindFirstDevice()"));
    hDeviceFind = BluetoothFindFirstDevice(&deviceSearchParams, &deviceInfo);

    if (NULL == hDeviceFind)
    {
        CloseHandle(hRadio);
        BluetoothFindRadioClose(hFind);
        AppendLogEx(LOG_ERROR, _T("BluetoothAPIs::BluetoothFindFirstDevice() failure! Error code: %d"), GetLastError());
        //TRACE(_T("%s\r\n"), MsBt7_ErrorDisp(GetLastError()));
        return;
    }

    int log_next = 0;
    AppendLogEx(LOG_INFO, _T("%s"), _T("BluetoothAPIs::BluetoothFindFirstDevice() success."));
    do
    {
        if (log_next > 0)
            AppendLogEx(LOG_INFO, _T("%s"), _T("BluetoothAPIs::BluetoothFindNextDevice()"));

        log_next = 1;

        MsBt7_AnalyzeClassOfDevice(deviceInfo.ulClassofDevice, &szMSCName[0], &szMajorDCName[0], &szMinorDCName[0]);

        TRACE(_T("  \n\tDeviceName: %s\r\n"), deviceInfo.szName);
        TRACE(_T("  \tAddress: %02X:%02X:%02X:%02X:%02X:%02X\r\n"), deviceInfo.Address.rgBytes[5],
            deviceInfo.Address.rgBytes[4], deviceInfo.Address.rgBytes[3], deviceInfo.Address.rgBytes[2],
            deviceInfo.Address.rgBytes[1], deviceInfo.Address.rgBytes[0]);
        wsprintf(strBuff, _T("%02X:%02X:%02X:%02X:%02X:%02X"), deviceInfo.Address.rgBytes[5],
            deviceInfo.Address.rgBytes[4], deviceInfo.Address.rgBytes[3], deviceInfo.Address.rgBytes[2],
            deviceInfo.Address.rgBytes[1], deviceInfo.Address.rgBytes[0]);
        TRACE(_T("  \tClass of device: 0x%08x\r\n"), deviceInfo.ulClassofDevice);
        TRACE(_T("  \tConnected: %s\r\n"), deviceInfo.fConnected ? L"true" : L"false");
        TRACE(_T("  \tAuthenticated: %s\r\n"), deviceInfo.fAuthenticated ? L"true" : L"false");
        TRACE(_T("  \tRemembered: %s\r\n\n"), deviceInfo.fRemembered ? L"true" : L"false");

        CString szPortName = MsBt7_GetCOMPortFromRegistry(deviceInfo.Address);
        bool isHeadset = wcsicmp(deviceInfo.szName, BT_HEADSET_NAME) == 0 ||
            wcsicmp(deviceInfo.szName, BT_HEADSET_NAME_2) == 0;
        if (szPortName.CompareNoCase(_T("")) == 0 && !isHeadset)
            continue;

        BTDEVICE device;
        device.bdName = deviceInfo.szName;
        ZeroMemory(device.bdAddr, sizeof(device.bdAddr));
        CopyMemory(device.bdAddr, deviceInfo.Address.rgBytes, sizeof(device.bdAddr));
        device.bdComPort = szPortName;
        device.bdClass = deviceInfo.ulClassofDevice;
        device.discovered = isWizardMode ? false : true;
        device.remembered = (deviceInfo.fRemembered != 0);
        device.authenticated = (deviceInfo.fAuthenticated != 0);
        AppendLogEx(LOG_INFO, _T("ASSOCIATED DEVICE FOUND: [%s | (%s) | %s | %s]"),
            device.bdName.MakeUpper(),
            strBuff,
            device.bdComPort,
            szMajorDCName);

        HWND mainWnd = GetParent(hWnd);
        if (mainWnd == NULL)
            mainWnd = hWnd;

        ::SendMessage(mainWnd, UWM_BT_FOUNDDEVICE, reinterpret_cast<WPARAM>(&device), 0);
    } while(BluetoothFindNextDevice(hDeviceFind, &deviceInfo));

    AppendLogEx(LOG_INFO, _T("BluetoothAPIs::BluetoothFindDeviceClose()"));
    BluetoothFindDeviceClose(hDeviceFind);
    CloseHandle(hRadio);
    AppendLogEx(LOG_INFO, _T("BluetoothAPIs::BluetoothFindRadioClose()"));
    BluetoothFindRadioClose(hFind);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// CALLBACK auth_callback_ex (WINVER >= VISTASP1+KB942567)
//-------------------------------------------------------------------------
BOOL CALLBACK auth_callback_ex(LPVOID pvParam, PBLUETOOTH_AUTHENTICATION_CALLBACK_PARAMS authParams)
{
    BLUETOOTH_AUTHENTICATE_RESPONSE response = { sizeof(BLUETOOTH_AUTHENTICATE_RESPONSE) };
    response.authMethod = authParams->authenticationMethod;
    response.bthAddressRemote = authParams->deviceInfo.Address;
    BLUETOOTH_PIN_INFO pininfo;
    pininfo.pinLength = 4;
    pininfo.pin[0] = '1';
    pininfo.pin[1] = '2';
    pininfo.pin[2] = '3';
    pininfo.pin[3] = '4';
    response.pinInfo = pininfo;
    response.negativeResponse = FALSE;

    //AppendLogEx(LOG_INFO, _T("BluetoothAPIs::BluetoothSendAuthenticationResponseEx()"));
    DWORD retVal = BluetoothSendAuthenticationResponseEx(NULL, &response);

    if (ERROR_SUCCESS != retVal)
    {
        //AppendLogEx(LOG_ERROR, _T("BluetoothAPIs::BluetoothSendAuthenticationResponseEx() failure!"));
        TRACE(_T("BluetoothSendAuthenticationResponseEx() failed! %s"), MsBt7_ErrorDisp(retVal));
        return (FALSE);
    }

    //AppendLogEx(LOG_INFO, _T("BluetoothAPIs::BluetoothSendAuthenticationResponseEx() success."));
    return (TRUE);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// CALLBACK auth_callback_ex (WINVER >= VISTASP1+KB942567)
//-------------------------------------------------------------------------
BOOL CALLBACK auth_callback_ex_ssp(LPVOID pvParam, PBLUETOOTH_AUTHENTICATION_CALLBACK_PARAMS authParams)
{
	BLUETOOTH_AUTHENTICATE_RESPONSE response = { sizeof(BLUETOOTH_AUTHENTICATE_RESPONSE) };

	TRACE(_T("auth_callback_ex_ssp() - Address 0x%x\n"), authParams->deviceInfo.Address.ullLong);
	TRACE(_T("auth_callback_ex_ssp() - AuthMethod %d\n"), authParams->authenticationMethod);

	response.authMethod = authParams->authenticationMethod;
	response.bthAddressRemote = authParams->deviceInfo.Address;
	response.numericCompInfo.NumericValue = 1;
	response.negativeResponse = FALSE;

	//AppendLogEx(LOG_INFO, _T("BluetoothAPIs::BluetoothSendAuthenticationResponseEx()"));
	DWORD retVal = BluetoothSendAuthenticationResponseEx(NULL, &response);

	if (ERROR_SUCCESS != retVal)
	{
		TRACE(_T("auth_callback_ex_ssp() - BluetoothSendAuthenticationResponseEx ret %d\n"), retVal);

		if (retVal == ERROR_CANCELLED)
		{
			TRACE(_T("auth_callback_ex_ssp() - Bluetooth device denied passkey response or communicatino problem.\n"));
		}
		else if (retVal == E_FAIL)
		{
			TRACE(_T("auth_callback_ex_ssp() - Device returned a failure code during authentication.\n"));
		}
		else if (retVal == 1244)
		{
			TRACE(_T("auth_callback_ex_ssp() - Not authenticated\n"));
		}

		TRACE(_T("BluetoothSendAuthenticationResponseEx() failed! %s"), MsBt7_ErrorDisp(retVal));
		//return (FALSE);
	}
	else
	{
		TRACE(_T("auth_callback_ex_ssp() -  success\n"));
	}

	return 1;
	//AppendLogEx(LOG_INFO, _T("BluetoothAPIs::BluetoothSendAuthenticationResponseEx() success."));
	//return (TRUE);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// CALLBACK auth_callback_ex_hs (WINVER >= VISTASP1+KB942567, Headset)
//-------------------------------------------------------------------------
BOOL CALLBACK auth_callback_ex_hs(LPVOID pvParam, PBLUETOOTH_AUTHENTICATION_CALLBACK_PARAMS authParams)
{
    BLUETOOTH_AUTHENTICATE_RESPONSE response = { sizeof(BLUETOOTH_AUTHENTICATE_RESPONSE) };
    response.authMethod = authParams->authenticationMethod;
    response.bthAddressRemote = authParams->deviceInfo.Address;
    BLUETOOTH_PIN_INFO pininfo;
    pininfo.pinLength = 4;
    pininfo.pin[0] = '0';
    pininfo.pin[1] = '0';
    pininfo.pin[2] = '0';
    pininfo.pin[3] = '0';
    response.pinInfo = pininfo;
    response.negativeResponse = FALSE;

    //AppendLogEx(LOG_INFO, _T("BluetoothAPIs::BluetoothSendAuthenticationResponseEx()"));
    DWORD retVal = BluetoothSendAuthenticationResponseEx(NULL, &response);

    if (retVal != ERROR_SUCCESS)
    {
        //AppendLogEx(LOG_ERROR, _T("BluetoothAPIs::BluetoothSendAuthenticationResponseEx() failure!"));
        TRACE(_T("BluetoothSendAuthenticationResponseEx() failed! %s"), MsBt7_ErrorDisp(retVal));
        return (FALSE);
    }

    //AppendLogEx(LOG_INFO, _T("BluetoothAPIs::BluetoothSendAuthenticationResponseEx() success."));
    return (TRUE);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// MsBt7_ExecAuthenticateDeviceEx (WINVER >= VISTASP1+KB942567)
//-------------------------------------------------------------------------
BOOL MsBt7_ExecAuthenticateDeviceEx(PBYTE BdAddr, DWORD dwType, PCHAR pszPortName)
{
    DWORD dwRes;
    GUID pServiceGuid;
	AUTHENTICATION_REQUIREMENTS authRequirements = MITMProtectionRequired;
    BLUETOOTH_DEVICE_INFO_STRUCT deviceInfo = { sizeof(BLUETOOTH_DEVICE_INFO_STRUCT) };
    BLUETOOTH_FIND_RADIO_PARAMS btfrp = { sizeof(BLUETOOTH_FIND_RADIO_PARAMS) };
    HBLUETOOTH_RADIO_FIND hFind;

    HANDLE hRadio;
    AppendLogEx(LOG_INFO, _T("%s"), _T("BluetoothAPIs::BluetoothFindFirstRadio()"));
    hFind = BluetoothFindFirstRadio(&btfrp, &hRadio);

    if (NULL == hFind)
    {
        AppendLogEx(LOG_ERROR, _T("%s"), _T("BluetoothAPIs::BluetoothGetRadioInfo() failure!"));
        TRACE(_T("Failed to get Bluetooth radio! %s\r\n"), MsBt7_ErrorDisp(GetLastError()));
        return (FALSE);
    }

    BLUETOOTH_RADIO_INFO radioInfo = { sizeof(BLUETOOTH_RADIO_INFO) };
    AppendLogEx(LOG_INFO, _T("%s"), _T("BluetoothAPIs::BluetoothGetRadioInfo()"));
    if (ERROR_SUCCESS == BluetoothGetRadioInfo(hRadio, &radioInfo))
    {
        TRACE(_T("Radio: %s\r\n"), radioInfo.szName);
        AppendLogEx(LOG_INFO, _T("%s"), _T("BluetoothAPIs::BluetoothGetRadioInfo() success."));
    }

    //if (authCallbackHandle != NULL)
    //{
    //    if (FALSE == BluetoothUnregisterAuthentication(authCallbackHandle))
    //        return (FALSE);
    //}

    CopyMemory(&deviceInfo.Address.rgBytes, BdAddr, sizeof(deviceInfo.Address.rgBytes));

    CString szPortName = MsBt7_GetCOMPortFromRegistry(deviceInfo.Address);
    if (0 == dwType && szPortName.CompareNoCase(_T("")) != 0)
    {
        AppendLogEx(LOG_WARNING, _T("%s"), _T("Device already authenticated!"));

        USES_CONVERSION;
        strcpy(pszPortName, W2A(szPortName.GetBuffer(szPortName.GetLength())));
        szPortName.ReleaseBuffer();

        CloseHandle(hRadio);
        AppendLogEx(LOG_INFO, _T("BluetoothAPIs::BluetoothFindRadioClose()"));
        BluetoothFindRadioClose(hFind);
        return TRUE;
    }

    AppendLogEx(LOG_INFO, _T("%s"), _T("BluetoothAPIs::BluetoothRegisterForAuthenticationEx()"));
    switch(dwType)
    {
        default:
        //case 0:
            if (NULL != authCallbackHandle)
            {
                AppendLogEx(LOG_INFO, _T("%s"), _T("BluetoothAPIs::BluetoothUnregisterAuthentication()"));
                BluetoothUnregisterAuthentication(authCallbackHandle); // Da Verificare
            }

            dwRes = BluetoothRegisterForAuthenticationEx(&deviceInfo,
                &authCallbackHandle, (PFN_AUTHENTICATION_CALLBACK_EX)auth_callback_ex, NULL);
			authRequirements = MITMProtectionRequired;
            pServiceGuid = SerialPortServiceClass_UUID;
            break;

        case 1:
            if (NULL != authCallbackHandleHs)
            {
                AppendLogEx(LOG_INFO, _T("%s"), _T("BluetoothAPIs::BluetoothUnregisterAuthentication()"));
                BluetoothUnregisterAuthentication(authCallbackHandleHs); // Da Verificare
            }

            dwRes = BluetoothRegisterForAuthenticationEx(&deviceInfo,
                &authCallbackHandleHs, (PFN_AUTHENTICATION_CALLBACK_EX)auth_callback_ex_hs, NULL);
			authRequirements = MITMProtectionRequired;
            //pServiceGuid = HeadsetServiceClass_UUID; //-> Cuffia Auricolare
            pServiceGuid = HandsfreeServiceClass_UUID; //-> Telefonia in viva voce
            break;
		case 2:
			if (NULL != authCallbackHandleSPP)
			{
				AppendLogEx(LOG_INFO, _T("%s"), _T("BluetoothAPIs::BluetoothUnregisterAuthentication()"));
				BluetoothUnregisterAuthentication(authCallbackHandleSPP); // Da Verificare
			}

			dwRes = BluetoothRegisterForAuthenticationEx(&deviceInfo,
				&authCallbackHandleSPP, (PFN_AUTHENTICATION_CALLBACK_EX)auth_callback_ex_ssp, NULL);
			//authRequirements = MITMProtectionNotRequired;
			//authRequirements = MITMProtectionRequiredGeneralBonding;
			pServiceGuid = NAPServiceClass_UUID; //-> TXT Multihub
			
			break;
    }

    if (ERROR_SUCCESS != dwRes)
    {
        AppendLogEx(LOG_ERROR, _T("BluetoothAPIs::BluetoothRegisterForAuthenticationEx() failure with err: %s!"), MsBt7_ErrorDisp(dwRes));
        AppendLogEx(LOG_INFO, _T("BluetoothAPIs::BluetoothFindRadioClose()"));
        BluetoothFindRadioClose(hFind);
        return FALSE;
    }

    deviceInfo.fAuthenticated = 0;

    AppendLogEx(LOG_INFO, _T("%s"), _T("BluetoothAPIs::BluetoothRegisterForAuthenticationEx() success."));

    AppendLogEx(LOG_INFO, _T("%s"), _T("BluetoothAPIs::BluetoothAuthenticateDeviceEx()"));
	dwRes = BluetoothAuthenticateDeviceEx(NULL, hRadio, &deviceInfo, NULL, authRequirements);
    if (ERROR_SUCCESS != dwRes)
    {
        AppendLogEx(LOG_ERROR, _T("%s"), _T("BluetoothAPIs::BluetoothAuthenticateDeviceEx() failure!"));
        TRACE(_T("BluetoothAuthenticateDeviceEx() failed! %s\r\n"), MsBt7_ErrorDisp(dwRes));

        CloseHandle(hRadio);
        AppendLogEx(LOG_INFO, _T("BluetoothAPIs::BluetoothFindRadioClose()"));
        BluetoothFindRadioClose(hFind);
        return (FALSE);
    }
    AppendLogEx(LOG_INFO, _T("%s"), _T("BluetoothAPIs::BluetoothAuthenticateDeviceEx() success."));

	AppendLogEx(LOG_INFO, _T("%s"), _T("BluetoothAPIs::BluetoothSetServiceState()"));

	dwRes = BluetoothSetServiceState(hRadio, &deviceInfo, &pServiceGuid, BLUETOOTH_SERVICE_ENABLE);

	if (2 == dwType && ERROR_ADAP_HDW_ERR == dwRes)
	{
		dwRes = ERROR_SUCCESS;
	}

	int iterations = 0;
	while (dwRes != ERROR_SUCCESS && iterations < 3)
	{
		::Sleep(100);
		dwRes = BluetoothSetServiceState(hRadio, &deviceInfo, &pServiceGuid, BLUETOOTH_SERVICE_ENABLE);
		iterations++;
	}

	if (ERROR_SUCCESS != dwRes)
	{
		AppendLogEx(LOG_ERROR, _T("%s"), _T("BluetoothAPIs::BluetoothSetServiceState() failure!"));
		TRACE(_T("BluetoothSetServiceState() failed! %s\r\n"), MsBt7_ErrorDisp(dwRes));
		// <TO DO>: MessageBox di errore stile IDC4?
		AfxMessageBox(MsBt7_ErrorDisp(dwRes));
		CloseHandle(hRadio);
		AppendLogEx(LOG_INFO, _T("BluetoothAPIs::BluetoothFindRadioClose()"));
		BluetoothFindRadioClose(hFind);
		return (FALSE);
	}

	AppendLogEx(LOG_INFO, _T("BluetoothAPIs::BluetoothSetServiceState() success."));

    if (0 == dwType)
        MsBt7_GetCOMPortFromRegistry(deviceInfo.Address, pszPortName);

    CloseHandle(hRadio);
    AppendLogEx(LOG_INFO, _T("BluetoothAPIs::BluetoothFindRadioClose()"));
    BluetoothFindRadioClose(hFind);
    return TRUE;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// MsBt7_ExecRemoveAuthenticatedDevice
//-------------------------------------------------------------------------
BOOL MsBt7_ExecRemoveAuthenticatedDevice(PBYTE BdAddr)
{
    BLUETOOTH_DEVICE_INFO_STRUCT deviceInfo = { sizeof(BLUETOOTH_DEVICE_INFO_STRUCT) };
    BLUETOOTH_FIND_RADIO_PARAMS btfrp = { sizeof(BLUETOOTH_FIND_RADIO_PARAMS) };
    HBLUETOOTH_RADIO_FIND hFind;

    HANDLE hRadio;
    AppendLogEx(LOG_INFO, _T("%s"), _T("BluetoothAPIs::BluetoothFindFirstRadio()"));
    hFind = BluetoothFindFirstRadio(&btfrp, &hRadio);

    if (NULL == hFind)
    {
        AppendLogEx(LOG_ERROR, _T("%s"), _T("BluetoothAPIs::BluetoothGetRadioInfo() failure!"));
        TRACE(_T("Failed to get Bluetooth radio! %s\r\n"), MsBt7_ErrorDisp(GetLastError()));
        return (FALSE);
    }

    BLUETOOTH_RADIO_INFO radioInfo = { sizeof(BLUETOOTH_RADIO_INFO) };
    AppendLogEx(LOG_INFO, _T("BluetoothAPIs::BluetoothGetRadioInfo()"));
    if (ERROR_SUCCESS == BluetoothGetRadioInfo(hRadio, &radioInfo))
    {
        TRACE(_T("Radio: %s\r\n"), radioInfo.szName);
        AppendLogEx(LOG_INFO, _T("%s"), _T("BluetoothAPIs::BluetoothGetRadioInfo() success."));
    }

    //if (authCallbackHandle != NULL)
    //{
    //    if (FALSE == BluetoothUnregisterAuthentication(authCallbackHandle))
    //        return (FALSE);
    //}

    CopyMemory(&deviceInfo.Address.rgBytes, BdAddr, sizeof(deviceInfo.Address.rgBytes));

    AppendLogEx(LOG_INFO, _T("BluetoothAPIs::BluetoothRemoveDevice()"));

    if (ERROR_SUCCESS != BluetoothRemoveDevice(&deviceInfo.Address))
    {
        AppendLogEx(LOG_ERROR, _T("BluetoothAPIs::BluetoothRemoveDevice() failure! %s"), MsBt7_ErrorDisp(GetLastError()));
        TRACE(_T("BluetoothRemoveDevice() failed! Error code: %d\r\n"), GetLastError());
        CloseHandle(hRadio);
        AppendLogEx(LOG_INFO, _T("BluetoothAPIs::BluetoothFindRadioClose()"));
        BluetoothFindRadioClose(hFind);
        return (FALSE);
    }

    AppendLogEx(LOG_INFO, _T("BluetoothAPIs::BluetoothRemoveDevice() success."));

    if (MsBt7_GetCOMPortFromRegistry(deviceInfo.Address).CompareNoCase(_T("")) != 0)
    {
        CloseHandle(hRadio);
        AppendLogEx(LOG_INFO, _T("BluetoothAPIs::BluetoothFindRadioClose()"));
        BluetoothFindRadioClose(hFind);
        return (FALSE);
    }
	
    CloseHandle(hRadio);
    AppendLogEx(LOG_INFO, _T("BluetoothAPIs::BluetoothFindRadioClose()"));
    BluetoothFindRadioClose(hFind);
    return (TRUE);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// MsBt7_StopDiscoverRemoteDevices
//-------------------------------------------------------------------------
void MsBt7_StopDiscoverRemoteDevices(HWND hWnd)
{
    m_bStopRequest = true;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// MsBt7_GetLocalDeviceInfo
//-------------------------------------------------------------------------
void MsBt7_GetLocalDeviceInfo(PBTLOCALDEVICE pLocalDev)
{
    // @Nome stack
    pLocalDev->stackName = _T("MICROSOFT");

    pLocalDev->bldVersion = _T("-"); // Default value
    pLocalDev->bldName = _T("-"); // Default value
    ZeroMemory(pLocalDev->bldAddr, sizeof(pLocalDev->bldAddr));

    TCHAR strBuff[0xFF] = { 0 };

    BLUETOOTH_DEVICE_INFO_STRUCT deviceInfo = { sizeof(BLUETOOTH_DEVICE_INFO_STRUCT) };
    BLUETOOTH_FIND_RADIO_PARAMS btfrp = { sizeof(BLUETOOTH_FIND_RADIO_PARAMS) };
    HBLUETOOTH_RADIO_FIND hFind;

    HANDLE hRadio;
    AppendLogEx(LOG_INFO, _T("%s"), _T("BluetoothAPIs::BluetoothFindFirstRadio()"));
    hFind = BluetoothFindFirstRadio(&btfrp, &hRadio);

    if (NULL == hFind)
    {
        AppendLogEx(LOG_ERROR, _T("%s"), _T("BluetoothAPIs::BluetoothGetRadioInfo() failure!"));
        TRACE(_T("Failed to get Bluetooth radio! %s\r\n"), MsBt7_ErrorDisp(GetLastError()));
        return;
    }

    BLUETOOTH_RADIO_INFO radioInfo = { sizeof(BLUETOOTH_RADIO_INFO) };
    AppendLogEx(LOG_INFO, _T("%s"), _T("BluetoothAPIs::BluetoothGetRadioInfo()"));
    if (ERROR_SUCCESS == BluetoothGetRadioInfo(hRadio, &radioInfo))
    {
        TRACE(_T("Radio: %s\r\n"), radioInfo.szName);
        AppendLogEx(LOG_INFO, _T("%s"), _T("BluetoothAPIs::BluetoothGetRadioInfo() success."));

        // @Indirizzo periferica
        CopyMemory(pLocalDev->bldAddr, radioInfo.address.rgBytes, sizeof(radioInfo.address.rgBytes));
        wsprintf(strBuff, _T("%02X:%02X:%02X:%02X:%02X:%02X"),
            pLocalDev->bldAddr[5], pLocalDev->bldAddr[4], pLocalDev->bldAddr[3],
            pLocalDev->bldAddr[2], pLocalDev->bldAddr[1], pLocalDev->bldAddr[0]);
        // @Nome dispositivo
        pLocalDev->bldName = radioInfo.szName;
    }

    AppendLogEx(LOG_INFO, _T("%s"), _T("Getting device info from registry ..."));

    SP_DEVINFO_DATA DeviceInfoData;
    DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
    DWORD DataT;
    LPTSTR location_info_buffer = NULL;
    DWORD buffersize = 0;

    // SetupDiGetClassDevs
    HDEVINFO DeviceInfoSet = SetupDiGetClassDevs(&GUID_DEVCLASS_BLUETOOTH, NULL, NULL, DIGCF_PRESENT);
    if (INVALID_HANDLE_VALUE == DeviceInfoSet)
    {
        CloseHandle(hRadio);
        AppendLogEx(LOG_INFO, _T("BluetoothAPIs::BluetoothFindRadioClose()"));
        BluetoothFindRadioClose(hFind);
        return;
    }

    // SetupDiEnumDeviceInfo
    for (DWORD deviceIndex = 0;
        SetupDiEnumDeviceInfo(DeviceInfoSet, deviceIndex, &DeviceInfoData);
        deviceIndex++)
    {
        // SetupDiGetDeviceRegistryProperty
        while(!SetupDiGetDeviceRegistryProperty(
            DeviceInfoSet,
            &DeviceInfoData,
            SPDRP_LOCATION_INFORMATION,
            &DataT,
            (PBYTE)location_info_buffer,
            buffersize,
            &buffersize))
        {
            if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
            {
                if (location_info_buffer)
                    LocalFree(location_info_buffer);
                location_info_buffer = (LPTSTR)LocalAlloc(LPTR, buffersize * 2);
            }
            else
                break;
        }

        if (location_info_buffer)
        {
            LocalFree(location_info_buffer);
            break;
        }
    }
    // SetupDiOpenDevRegKey
    HKEY hKey = SetupDiOpenDevRegKey(DeviceInfoSet, &DeviceInfoData, DICS_FLAG_GLOBAL, 0, DIREG_DRV, KEY_QUERY_VALUE);

    // @Versione stack
    if (INVALID_HANDLE_VALUE != hKey)
    {
        CString sVersion;
        DWORD dwBufferSize;

        // RegQueryValueEx
        if (ERROR_SUCCESS == RegQueryValueEx(hKey, _T("DriverVersion"), NULL, NULL, NULL, &dwBufferSize))
        {
            RegQueryValueEx(hKey, _T("DriverVersion"), NULL, NULL, (LPBYTE)sVersion.GetBuffer(dwBufferSize), &dwBufferSize);

            pLocalDev->bldVersion = sVersion;
            sVersion.ReleaseBuffer();

            RegCloseKey(hKey);
        }
    }
    SetupDiDestroyDeviceInfoList(DeviceInfoSet);

    AppendLogEx(LOG_INFO, _T("Driver version: %s"), pLocalDev->bldVersion);
    AppendLogEx(LOG_INFO, _T("Device name: %s"), pLocalDev->bldName);
    AppendLogEx(LOG_INFO, _T("Device address: %s"), strBuff);

    CloseHandle(hRadio);
    AppendLogEx(LOG_INFO, _T("BluetoothAPIs::BluetoothFindRadioClose()"));
    BluetoothFindRadioClose(hFind);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// MsBt7_IsRemoteDeviceConnectable
//-------------------------------------------------------------------------
BOOL MsBt7_IsRemoteDeviceConnectable(LPCTSTR szComm)
{
    if (wcscmp(szComm, _T("")) == 0)
        return (FALSE);

    CString fileName;
    fileName.Format(_T("\\\\.\\%s"), szComm);
    HANDLE hSerial;
    hSerial = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

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
        AppendLogEx(LOG_ERROR, _T("GetCommState() failure! Error: %d"), GetLastError());
        return (FALSE);
    }

    CloseHandle(hSerial);
    AppendLogEx(LOG_INFO, _T("GetCommState() success."));
    return (TRUE);
}
