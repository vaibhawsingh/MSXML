
// ReadWriteXmlCPPDlg.h : header file
//

#pragma once
#include "afxeditbrowsectrl.h"
#include "afxcmn.h"
#include <vector>
#import "msxml6.dll"
#include <string>

// CReadWriteXmlCPPDlg dialog
class CReadWriteXmlCPPDlg : public CDialogEx
{
// Construction
public:
	CReadWriteXmlCPPDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_READWRITEXMLCPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	bool ReadXml();
	afx_msg void OnBnClickedBtnDisp();
	CMFCEditBrowseCtrl m_ctrlXmlFileName;
	CListCtrl m_lstCtrl;
	CString m_strXmlFileName;
	bool GetAttribute(const MSXML2::IXMLDOMNodePtr &nodePtr, const std::wstring &data, std::wstring &val);
	std::vector<MSXML2::IXMLDOMNodePtr> GetChilds(const MSXML2::IXMLDOMNodePtr &nodeptr);
};
