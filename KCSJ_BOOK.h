#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// KCSJ_BOOK 对话框

class KCSJ_BOOK : public CDialog
{
	DECLARE_DYNAMIC(KCSJ_BOOK)

public:
	KCSJ_BOOK(CWnd* pParent = NULL);   // 标准构造函数
	void List_All(CString);
	virtual ~KCSJ_BOOK();

// 对话框数据
	enum { IDD = IDD_KCSJ_BOOK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();	
	HICON m_hIcon;
	DECLARE_MESSAGE_MAP()
public:
	CString B_date;
	CString B_day;
	CString B_bookday;
	CString B_ID;
	CString C_ID;
	CString R_ID;
	CListCtrl m_list_BOOK;
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit PRI_KEY;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	int num_radio;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio6();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	CString m_name;
	CString m_sex;
	CString m_addr;
	long m_age;
	CString m_type;
	CString m_status;
	long m_price;
};
