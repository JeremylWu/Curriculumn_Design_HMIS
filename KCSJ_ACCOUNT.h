#pragma once
#include "afxcmn.h"


// KCSJ_ACCOUNT 对话框

class KCSJ_ACCOUNT : public CDialog
{
	DECLARE_DYNAMIC(KCSJ_ACCOUNT)

public:
	KCSJ_ACCOUNT(CWnd* pParent = NULL);   // 标准构造函数
	void List_All(CString);
	virtual ~KCSJ_ACCOUNT();

// 对话框数据
	enum { IDD = IDD_KCSJ_ACCOUNT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	CListCtrl m_list;
	CString m_Uid;
	CString m_Handle;
	CString m_Password;
	CString m_Authority;
	afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
};
