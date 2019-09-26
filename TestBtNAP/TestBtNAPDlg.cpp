
// TestBtNAPDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestBtNAP.h"
#include "TestBtNAPDlg.h"
#include "afxdialogex.h"

#include <algorithm>

#include "MsModule7.h"

#include <iostream>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



const CString UNKNOWN_DEVICE = _T("Unknown Device");
const CString UNSUPPORTED_DEVICE = _T("-");

#define BD_ADDR_LEN                6
typedef BYTE BD_ADDR[BD_ADDR_LEN];
typedef ULONG BD_CLASS;

struct addr_equal : std::unary_function<BTDEVICE, bool>
{
	addr_equal(const BTDEVICE &dev) : dev_(dev) {}
	bool operator()(const BTDEVICE &arg) const { return (0 == memcmp(arg.bdAddr, dev_.bdAddr, sizeof(BD_ADDR))); }
	const BTDEVICE &dev_;
};


CTestBtNAPDlg::CTestBtNAPDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestBtNAPDlg::IDD, pParent)
	, m_initBtFlag(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestBtNAPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DEVICES, m_list);
}

BEGIN_MESSAGE_MAP(CTestBtNAPDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTestBtNAPDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTestBtNAPDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BTN_SEARCH, &CTestBtNAPDlg::OnBnClickedSearch)
	ON_BN_CLICKED(IDC_BTN_PAIR, &CTestBtNAPDlg::OnBnClickedPair)
	ON_BN_CLICKED(IDC_BTN_UNPAIR, &CTestBtNAPDlg::OnBnClickedUnpair)
	ON_BN_CLICKED(IDC_BTN_CONNECT, &CTestBtNAPDlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_BTN_DISCONNECT, &CTestBtNAPDlg::OnBnClickedDisconnect)
	ON_REGISTERED_MESSAGE(UWM_BT_FOUNDDEVICE, &CTestBtNAPDlg::OnFoundDevice)
END_MESSAGE_MAP()


// CTestBtNAPDlg message handlers

BOOL CTestBtNAPDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon



	// ********** ********** ********** ********** **********

	int init_code = InitBluetooth();

	InitListControl();


	if ((BT_ERROR_SUCCESS) != init_code)
	{
		MessageBox(_T("Error InitBluetooth()"));

		EndDialog(IDCANCEL);
		return (FALSE);
	}


	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestBtNAPDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestBtNAPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestBtNAPDlg::OnBnClickedOk()
{
	// Do nothing
	//CDialogEx::OnOK();
}


void CTestBtNAPDlg::OnBnClickedCancel()
{
	// Exit
	CDialogEx::OnCancel();
}


void CTestBtNAPDlg::OnBnClickedSearch()
{
	m_devicesList.clear();

	m_list.DeleteAllItems();
	GetDlgItem(IDC_LIST_DEVICES)->UpdateWindow();

	CBTModule::Instance()->StartInquiry(GetSafeHwnd());

	MessageBox(L"Search done!");
}


void CTestBtNAPDlg::OnBnClickedPair()
{
	int nItem = GetSelectedItemDevice();
	if (nItem < 0)	return;

	if (TRUE == CBTModule::Instance()->BindDevice(GetSafeHwnd(), &m_devicesList[nItem]))
	{
		MessageBox(L"Pair done!");
	}else{
		MessageBox(L"Pair failed!");
	}
}


void CTestBtNAPDlg::OnBnClickedUnpair()
{
	int nItem = GetSelectedItemDevice();
	if (nItem < 0)	return;

	if (TRUE == CBTModule::Instance()->UnbindDevice(&m_devicesList[nItem]))
	{
		MessageBox(L"Unpair done!");
	}else{
		MessageBox(L"Unpair failed!");
	}
}


void CTestBtNAPDlg::OnBnClickedConnect()
{
	int nItem = GetSelectedItemDevice();
	if (nItem < 0)	return;

	if (TRUE == CBTModule::Instance()->IsRemoteDeviceConnectable(&m_devicesList[nItem]))
	{
		MessageBox(L"Connect success!");
	}
	else {
		MessageBox(L"Connect failed!");
	}
}


void CTestBtNAPDlg::OnBnClickedDisconnect()
{
	// ???
}

LRESULT CTestBtNAPDlg::OnFoundDevice(WPARAM wParam, LPARAM lParam)
{
	if (CBTModule::Instance()->CancelDiscoverRequired())
		return (TRUE);

	PBTDEVICE pBtd = reinterpret_cast<PBTDEVICE>(wParam);

	BTDEVICE device;
	device.bdName = pBtd->bdName;
	ZeroMemory(device.bdAddr, sizeof(device.bdAddr));
	CopyMemory(device.bdAddr, pBtd->bdAddr, sizeof(device.bdAddr));
	device.bdComPort = pBtd->bdComPort;
	device.bdClass = pBtd->bdClass;
	device.discovered = pBtd->discovered;
	device.remembered = pBtd->remembered;
	device.authenticated = pBtd->authenticated;

	// Aggiunta del dispositivo alla lista
	AddRow(device);

	return (TRUE);
}


int CTestBtNAPDlg::InitBluetooth()
{
	LPCTSTR szDll;

	TCHAR currentDir[MAX_PATH];
	::GetCurrentDirectory(MAX_PATH, currentDir);

	CMsModule7::CreateInstance();
	szDll = _T("MsBTManager7.dll");

	CString path;
	path.Format(_T("%s\\%s"), currentDir, szDll);

	if ((FALSE) == CBTModule::Instance()->InitBtModule((LPCTSTR)path))
	{
		btLogger.AppendLog(LOG_ERROR, _T("Unable to load %s Bluetooth module or bluetooth loca device is not ready!"), CBTModule::Instance()->StackName().MakeUpper());
		return BT_ERROR_LOAD_MODULE; // BT_ERROR_LOAD_MODULE
	}

	if (!m_initBtFlag)
	{
		if ((FALSE) == CBTModule::Instance()->InitStack(GetSafeHwnd(), "BluetoothManager"))
		{
			m_initBtFlag = false;
			btLogger.AppendLog(LOG_ERROR, _T("Cannot initialize %s Bluetooth stack!"), CBTModule::Instance()->StackName().MakeUpper());
			return BT_ERROR_INIT_STACK; // BT_ERROR_INIT_STACK
		}
		m_initBtFlag = true;
	}

	if ((FALSE) == CBTModule::Instance()->IsHWDeviceReady(GetSafeHwnd()))
	{
		btLogger.AppendLog(LOG_ERROR, _T("%s Bluetooth local device is not ready!"),
			CBTModule::Instance()->StackName().MakeUpper());
		return BT_ERROR_DEVICE_NOT_READY; // BT_ERROR_DEVICE_NOT_READY
	}

	if ((FALSE) == CBTModule::Instance()->InitComPorts())
	{
		btLogger.AppendLog(LOG_ERROR, _T("Cannot initialize %s Bluetooth COM ports"),
			CBTModule::Instance()->StackName().MakeUpper());
		return BT_ERROR_INIT_COMM; // BT_ERROR_INIT_COMM
	}

	btLogger.AppendLog(LOG_INFO, _T("%s Bluetooth stack successfully initialized."),
		CBTModule::Instance()->StackName().MakeUpper());
	return BT_ERROR_SUCCESS; // BT_ERROR_SUCCESS
}

void CTestBtNAPDlg::InitListControl(void)
{
	TRACE(_T("OnInitListControl\r\n"));

	//m_list.SetImageList(&m_imageList, LVSIL_SMALL);
	UINT style = m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES;
	m_list.SetExtendedStyle(style);

	LVCOLUMNW lvColumn;
	int nColumn = 0;

	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;// | LVCFMT_FIXED_WIDTH;
	lvColumn.pszText = _T("Name");
	lvColumn.cx = 300;
	m_list.InsertColumn(nColumn++, &lvColumn);

	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;// | LVCFMT_FIXED_WIDTH;
	lvColumn.pszText = _T("ComPort");
	lvColumn.cx = 100;
	m_list.InsertColumn(nColumn++, &lvColumn);

	lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvColumn.fmt = LVCFMT_LEFT;// | LVCFMT_FIXED_WIDTH;
	lvColumn.pszText = _T("State");
	lvColumn.cx = 200;
	m_list.InsertColumn(nColumn++, &lvColumn);
}

int CTestBtNAPDlg::GetSelectedItemDevice()
{
	POSITION pstn = m_list.GetFirstSelectedItemPosition();
	return m_list.GetNextSelectedItem(pstn);
}

void CTestBtNAPDlg::AddRow(BTDEVICE device)
{
	LVITEM lvItem;
	int nItem;

	CString deviceDisplayName(device.bdName);

	if (!AddDeviceToList(device, deviceDisplayName))
		return;

	// STRUMENTO
	lvItem.mask = LVIF_IMAGE | LVIF_TEXT;
	lvItem.iItem = m_devicesList.size();
	lvItem.iImage = 0;
	lvItem.iSubItem = 0;
	lvItem.pszText = deviceDisplayName.GetBuffer();
	deviceDisplayName.ReleaseBuffer();
	nItem = m_list.InsertItem(&lvItem);
	// PORTA COM
	CString com_port;
	com_port = device.bdComPort;// != _T("0") ? device.bdComPort : _T("");
	m_list.SetItemText(nItem, 1, com_port);
	// ATTIVO/NON ATTIVO
	CString is_bound;
	is_bound = (device.authenticated ? _T("Autenticated") : _T("Not Authenticated"));
	m_list.SetItemText(nItem, 2, is_bound);

	GetDlgItem(IDC_LIST_DEVICES)->UpdateWindow();
	GetForegroundWindow()->UpdateWindow();
}

bool CTestBtNAPDlg::AddDeviceToList(BTDEVICE device, CString deviceDisplayName)
{
	std::vector<BTDEVICE>::iterator it;
	it = std::find_if(m_devicesList.begin(), m_devicesList.end(), addr_equal(device));
	
	// se il nome da visualizzare non è definito
	// o se il dispositivo non è più supportato
	// => NON aggiungo il dispositivo alla lista
	if ((deviceDisplayName.Trim().CompareNoCase(UNKNOWN_DEVICE) == 0)
		|| (deviceDisplayName.Trim().Find(UNSUPPORTED_DEVICE) == 0))
	{
		return FALSE;
	}

	// dispositivo è già presente
	// => il dispositivo viene sostituito da quello trovato
	if (it != m_devicesList.end())
	{
		it = m_devicesList.erase(it);
		it = m_devicesList.insert(it, device);
		return (FALSE);
	}

	m_devicesList.push_back(device);
	return (TRUE);
}
