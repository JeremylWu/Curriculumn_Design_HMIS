#pragma once
#include "afxcmn.h"


// KCSJ_EMPLOYEE 对话框

class KCSJ_EMPLOYEE : public CDialog
{
	DECLARE_DYNAMIC(KCSJ_EMPLOYEE)

public:
	KCSJ_EMPLOYEE(CWnd* pParent = NULL);   // 标准构造函数
	void List_All(CString);
	virtual ~KCSJ_EMPLOYEE();

// 对话框数据
	enum { IDD = IDD_KCSJ_EMPLOYEE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	HICON m_hIcon;
	DECLARE_MESSAGE_MAP()
public:
	CString E_ID;
	CString E_name;
	CString E_sex;
	CString E_pos;
	CListCtrl m_list_EMPLOYEE;
	long E_age;
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
