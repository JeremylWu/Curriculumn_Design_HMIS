#pragma once
#include "afxcmn.h"


// KCSJ_CUSTOMER 对话框

class KCSJ_CUSTOMER : public CDialog
{
	DECLARE_DYNAMIC(KCSJ_CUSTOMER)

public:
	KCSJ_CUSTOMER(CWnd* pParent = NULL);   // 标准构造函数
	void List_All(CString);
	virtual ~KCSJ_CUSTOMER();

// 对话框数据
	enum { IDD = IDD_KCSJ_CUSTOMER };

protected:
	HICON m_hIcon;
	virtual BOOL OnInitDialog();						//ADD
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	//afx_msg void OnPaint();								//ADD
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list_CUSTOMER;
	CString C_ID;
	CString C_name;
	CString C_sex;
	CString C_addr;
	long C_age;
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	int num_radio;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton5();
};
