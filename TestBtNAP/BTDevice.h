#pragma once
#include <string>

#define BD_ADDR_LEN                6 
typedef BYTE BD_ADDR[BD_ADDR_LEN];
typedef ULONG BD_CLASS;


class CBTDevice
{

public:
    BD_ADDR bd_address;        // Unique ID del dispositivo;
    CString bd_name;        // Nome del dispositivo
    CString bd_COM_port;    // Porta COM dispositivo 
    BD_CLASS bd_class;        // Classe del dispositivo
    int bd_type;            // Tipo dispositivo (Texa)
    bool bd_authenticated;    // Flag device authenticated/paired/bonded
    bool bd_connected;        // Flag device connected/in use
    bool bd_remembered;        // Flag device remembered

//public:
//    CBTDevice(void);
//    CBTDevice(CString name, BD_ADDR address, CString COMPort, BD_CLASS classOfDev, bool authenticated, bool connected, bool remembered);
//    virtual ~CBTDevice(void);
//    
//    //BYTE* bd_address(BYTE * m_bd_address)            { return m_bd_address; };
//    BD_ADDR&    GetAddress()                        { return bd_address; };
//    void        SetAddress(BD_ADDR value)            { memcpy (bd_address, value, BD_ADDR_LEN); };
//
//    CString        GetName()                            { return bd_name; };
//    void        SetName(CString value)                { bd_name = value; };
//
//    CString        GetCOMPort()                        { return bd_COM_port; };
//    void        SetCOMPort(CString value)            { bd_COM_port = value; };
//
//    BD_CLASS    GetClassOfDevice()                    { return bd_class; };
//    void        SetClassOfDevice(BD_CLASS value)    { bd_class = value; };
//
//    bool        IsAuthenticated()                    { return bd_authenticated; };
//    void        IsAuthenticated(bool value)            { bd_authenticated = value; };
//
//    bool        IsConnected()                        { return bd_connected; };
//    void        IsConnected(bool value)                { bd_connected = value; };
//
//    bool        IsRemembered()                        { return bd_remembered; };
//    void        IsRemembered(bool value)            { bd_remembered = value; };

};
