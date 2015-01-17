// KCSJ_ABOUT.cpp : 实现文件
//

#include "stdafx.h"
#include "KCSJ_HMIS.h"
#include "KCSJ_ABOUT.h"
#include "afxdialogex.h"


// KCSJ_ABOUT 对话框

IMPLEMENT_DYNAMIC(KCSJ_ABOUT, CDialog)

KCSJ_ABOUT::KCSJ_ABOUT(CWnd* pParent /*=NULL*/)
	: CDialog(KCSJ_ABOUT::IDD, pParent)
{

}

KCSJ_ABOUT::~KCSJ_ABOUT()
{
}

void KCSJ_ABOUT::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(KCSJ_ABOUT, CDialog)
END_MESSAGE_MAP()


// KCSJ_ABOUT 消息处理程序

BOOL KCSJ_ABOUT::OnInitDialog(){
	CFont *pFont1 = new CFont;
	 pFont1->CreatePointFont(130,_T("David"));
	 ((CWnd*)GetDlgItem(IDC_STATIC1))->SetFont(pFont1);
	 CFont *pFont2 = new CFont;
	 pFont2->CreatePointFont(130,_T("David"));
	 ((CWnd*)GetDlgItem(IDC_STATIC2))->SetFont(pFont2);
	 CFont *pFont3 = new CFont;
	 pFont3->CreatePointFont(130,_T("David"));
	 ((CWnd*)GetDlgItem(IDC_STATIC3))->SetFont(pFont3);
	 CFont *pFont4 = new CFont;
	 pFont4->CreatePointFont(130,_T("David"));
	 ((CWnd*)GetDlgItem(IDC_STATIC4))->SetFont(pFont4);
	 CFont *pFont5 = new CFont;
	 pFont5->CreatePointFont(130,_T("David"));
	 ((CWnd*)GetDlgItem(IDC_STATIC5))->SetFont(pFont5);
	return true;
}
