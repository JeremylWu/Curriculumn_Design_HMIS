#pragma once


// KCSJ_ABOUT 对话框

class KCSJ_ABOUT : public CDialog
{
	DECLARE_DYNAMIC(KCSJ_ABOUT)

public:
	KCSJ_ABOUT(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~KCSJ_ABOUT();

// 对话框数据
	enum { IDD = IDD_KCSJ_ABOUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();	
	DECLARE_MESSAGE_MAP()
};
