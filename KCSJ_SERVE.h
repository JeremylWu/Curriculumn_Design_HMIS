#pragma once
#include "afxcmn.h"


// KCSJ_SERVE 对话框

class KCSJ_SERVE : public CDialog
{
	DECLARE_DYNAMIC(KCSJ_SERVE)

public:
	KCSJ_SERVE(CWnd* pParent = NULL);   // 标准构造函数
	void List_All(CString);
	virtual ~KCSJ_SERVE();

// 对话框数据
	enum { IDD = IDD_KCSJ_SERVE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();	
	HICON m_hIcon;
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list_SERVE;
	CString S_serve;
	CString R_ID;
	CString E_ID;
	CString S_ID;
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	int num_radio;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton2();
	CString m_name;
	CString m_sex;
	long m_age;
	CString m_pos;
	CString m_type;
	CString m_status;
	long m_price;
};
