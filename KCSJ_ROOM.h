#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// KCSJ_ROOM 对话框

class KCSJ_ROOM : public CDialog
{
	DECLARE_DYNAMIC(KCSJ_ROOM)

public:
	KCSJ_ROOM(CWnd* pParent = NULL);   // 标准构造函数
	void List_All(CString);
	virtual ~KCSJ_ROOM();

// 对话框数据
	enum { IDD = IDD_KCSJ_ROOM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	HICON m_hIcon;
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list_ROOM;
	CString R_ID;
	CString R_status;
	CString R_type;
	long R_price;
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
	afx_msg void OnBnClickedButton4();
};
