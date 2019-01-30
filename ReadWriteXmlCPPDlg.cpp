
// ReadWriteXmlCPPDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ReadWriteXmlCPP.h"
#include "ReadWriteXmlCPPDlg.h"
#include "afxdialogex.h"



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
	, m_strFileCreatePath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReadWriteXmlCPPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCEDITBROWSE_FILE, m_ctrlXmlFileName);
	DDX_Control(pDX, IDC_LST_DISP_DATA, m_lstCtrl);
	DDX_Text(pDX, IDC_MFCEDITBROWSE_FILE, m_strXmlFileName);
	DDX_Text(pDX, IDC_MFCEDITBROWSE_FILE_CREATE, m_strFileCreatePath);
}

BEGIN_MESSAGE_MAP(CReadWriteXmlCPPDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_DISP, &CReadWriteXmlCPPDlg::OnBnClickedBtnDisp)
	ON_BN_CLICKED(IDC_BTN_Write, &CReadWriteXmlCPPDlg::OnBnClickedBtnWrite)
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
	bool bValid = true;
	
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
			bValid = FALSE;
			return bValid;
		}

		MSXML2::IXMLDOMNodePtr pXmldoc = pDocument;
		if (pXmldoc)
		{
			std::wstring strSourceTag = L"AOI";
			
			MSXML2::IXMLDOMNodePtr c_pXmlRootNode = pXmldoc->selectSingleNode(strSourceTag.c_str());
			if (!c_pXmlRootNode)
			{
				bValid = FALSE;
				return bValid;
			}
			std::wstring strPath = L"MISCELLANEOUS";
			MSXML2::IXMLDOMNodePtr nodeptr = c_pXmlRootNode->selectSingleNode(strPath.c_str());

			std::vector<MSXML2::IXMLDOMNodePtr> vctr;

			vctr = GetChilds(nodeptr);
			MSXML2::IXMLDOMNodePtr pnodePtr;
			std::wstring wstrDataType, wstrDataValType;
			//iterate and read the data from list 
			for (auto itr = vctr.begin(); itr != vctr.end(); itr++)
			{
				std::wstring strPath1 = L"Property";
				pnodePtr = (*itr);
				wstrDataType = L"Comment";
				if (GetAttribute(pnodePtr, wstrDataType, wstrDataValType))
				{
					std::wstring st = wstrDataValType;
				}
			}
			
		}
	
		return TRUE;
}

bool CReadWriteXmlCPPDlg::GetAttribute(const MSXML2::IXMLDOMNodePtr &nodePtr,const std::wstring &data, std::wstring &val)
{
	MSXML2::IXMLDOMNodePtr node = nodePtr;
	MSXML2::IXMLDOMNamedNodeMapPtr nodeMapPtr;
	nodeMapPtr = node->attributes;
	_bstr_t  value;
	MSXML2::IXMLDOMNodePtr node1 = nodeMapPtr->getNamedItem(data.data());
	if (node1 == nullptr)
	{
		return FALSE;
	}
	value = node1->nodeValue;
	val = value.copy(FALSE);
	return true;
}

std::vector<MSXML2::IXMLDOMNodePtr> CReadWriteXmlCPPDlg::GetChilds(const MSXML2::IXMLDOMNodePtr &nodeptr)
{
	std::vector<MSXML2::IXMLDOMNodePtr> vctr;
	MSXML2::IXMLDOMNodeListPtr lstPtr = nodeptr->childNodes;
	if (lstPtr)
	{
		int count = lstPtr->length;
		if (count > 0)
		{
			for (int i = 0; i < count; i++)
			{
				MSXML2::IXMLDOMNodePtr nodeptr = lstPtr->item[i];
				vctr.push_back(nodeptr);
			}
		}
	}
	return vctr;
}

void CReadWriteXmlCPPDlg::OnBnClickedBtnWrite()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (!m_strFileCreatePath.IsEmpty())
	{
		std::wstring strFileName = m_strFileCreatePath + L"\\" + L"Output.xml";
		WriteXml(strFileName);
	}
}

bool CReadWriteXmlCPPDlg::WriteXml(const std::wstring &wstrFileName)
{
	HRESULT hResult = S_OK;
	MSXML2::IXMLDOMDocument2Ptr spDocOutput;
	MSXML2::IXMLDOMProcessingInstructionPtr spXMLDecl;
	MSXML2::IXMLDOMElementPtr spElemRoot, spElemCamera, spProperty, spExample;
	// Create the COM DOM Document object
	hResult = spDocOutput.CreateInstance(__uuidof(MSXML2::DOMDocument60));
	if FAILED(hResult)
	{
		//cerr << "Failed to create Document instance" << endl;
		return FALSE;
	}
	spXMLDecl = spDocOutput->createProcessingInstruction("xml", "version=\"1.0\" encoding=\"euc-kr\" standalone=\"yes\" ");
	spDocOutput->appendChild(spXMLDecl);

	spElemRoot = spDocOutput->createElement("AOI");
	spDocOutput->appendChild(spElemRoot);

	spElemCamera = spDocOutput->createElement("Camera");
	spElemRoot->appendChild(spElemCamera);

	spProperty = spDocOutput->createElement("Property");
	spElemCamera->appendChild(spProperty);

	AddAttrToXml(spProperty, L"JMV", L"JMD");

	spExample = spDocOutput->createElement("Example");
	spElemCamera->appendChild(spExample);

	hResult = spDocOutput->save(wstrFileName.c_str());
	return TRUE;
}

bool CReadWriteXmlCPPDlg::AddAttrToXml(const MSXML2::IXMLDOMElementPtr spElem, std::wstring attrData, std::wstring attrVal)
{
	VARIANT varVal;
	VariantInit(&varVal);
	varVal.vt = VT_BSTR;
	// given std::wstring ws
	//NodeName
	varVal.bstrVal = SysAllocStringLen(attrVal.data(), (UINT)attrVal.size());
	HRESULT hr = spElem->setAttribute(attrData.c_str(), varVal);

	SysFreeString(varVal.bstrVal);

	if (SUCCEEDED(hr))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
