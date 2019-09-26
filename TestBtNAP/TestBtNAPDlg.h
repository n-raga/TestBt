
// TestBtNAPDlg.h : header file
//

#pragma once
#include "afxcmn.h"

#include <vector>
#include "Public.h"


// CTestBtNAPDlg dialog
class CTestBtNAPDlg : public CDialogEx
{
// Construction
public:
	CTestBtNAPDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TESTBTNAP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedSearch();
	afx_msg void OnBnClickedPair();
	afx_msg void OnBnClickedUnpair();
	afx_msg void OnBnClickedConnect();
	afx_msg void OnBnClickedDisconnect();

	afx_msg LRESULT OnFoundDevice(WPARAM, LPARAM);

	int InitBluetooth();
	void InitListControl(void);
	int GetSelectedItemDevice();
	void AddRow(BTDEVICE device);
	bool AddDeviceToList(BTDEVICE device, CString deviceDisplayName);

protected:
	bool m_initBtFlag;
	CListCtrl m_list;
	std::vector<BTDEVICE> m_devicesList;
};
