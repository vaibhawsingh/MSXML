
// ReadWriteXmlCPPDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ReadWriteXmlCPP.h"
#include "ReadWriteXmlCPPDlg.h"
#include "afxdialogex.h"
#import "msxml6.dll"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CReadWriteXmlCPPDlg dialog



CReadWriteXmlCPPDlg::CReadWriteXmlCPPDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CReadWriteXmlCPPDlg::IDD, pParent)
	, m_strXmlFileName(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReadWriteXmlCPPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCEDITBROWSE_FILE, m_ctrlXmlFileName);
	DDX_Control(pDX, IDC_LST_DISP_DATA, m_lstCtrl);
	DDX_Text(pDX, IDC_MFCEDITBROWSE_FILE, m_strXmlFileName);
}

BEGIN_MESSAGE_MAP(CReadWriteXmlCPPDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_DISP, &CReadWriteXmlCPPDlg::OnBnClickedBtnDisp)
END_MESSAGE_MAP()


// CReadWriteXmlCPPDlg message handlers

BOOL CReadWriteXmlCPPDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CReadWriteXmlCPPDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CReadWriteXmlCPPDlg::OnPaint()
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
HCURSOR CReadWriteXmlCPPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CReadWriteXmlCPPDlg::OnBnClickedBtnDisp()
{
	// TODO: Add your control notification handler code here
	//Read The XML File and Display the data into List View.
	UpdateData(TRUE);
	m_strXmlFileName;
	if (!m_strXmlFileName.IsEmpty())
	{
		//m_lstCtrl.InsertItem(10, m_strXmlFileName);
		//read the XML file
		ReadXml();
	}
}

bool CReadWriteXmlCPPDlg::ReadXml()
{
	std::wstring wstrFilePath = m_strXmlFileName;
	
	
		CoInitialize(NULL);
		MSXML2::IXMLDOMDocument2Ptr  pDocument = MSXML2::IXMLDOMDocument2Ptr(__uuidof(MSXML2::DOMDocument60));
		HRESULT      hr;
		VARIANT_BOOL bSuccess = FALSE;
		_variant_t   var(wstrFilePath.c_str());

		if (pDocument == NULL)
			return FALSE;

		hr = pDocument->raw_load(var, &bSuccess);
		if (FAILED(hr))
		{
			MessageBox(L"XML File is empty");
		}

		MSXML2::IXMLDOMNodePtr pXmldoc = pDocument;
		if (pXmldoc)
	
	
}