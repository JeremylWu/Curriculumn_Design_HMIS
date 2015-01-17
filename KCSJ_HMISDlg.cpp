
// KCSJ_HMISDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "KCSJ_HMIS.h"
#include "KCSJ_HMISDlg.h"
#include "afxdialogex.h"
#include "KCSJ_CUSTOMER.h"
#include "KCSJ_ROOM.h"
#include "KCSJ_EMPLOYEE.h"
#include "KCSJ_BOOK.h"
#include "KCSJ_SERVE.h"
#include "MIS.h"
#include "Account.h"
#include "Global.h"
#include "KCSJ_ACCOUNT.h"
#include "KCSJ_ABOUT.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CKCSJ_HMISDlg 对话框



CKCSJ_HMISDlg::CKCSJ_HMISDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CKCSJ_HMISDlg::IDD, pParent)
	, m_Handle(_T(""))
	, m_Password(_T(""))
	, m_status(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON2);				//ICO
}

void CKCSJ_HMISDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Handle);
	DDX_Text(pDX, IDC_EDIT2, m_Password);
	DDX_Text(pDX, IDC_EDIT3, m_status);
}

BEGIN_MESSAGE_MAP(CKCSJ_HMISDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CKCSJ_HMISDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CKCSJ_HMISDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CKCSJ_HMISDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CKCSJ_HMISDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CKCSJ_HMISDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CKCSJ_HMISDlg::OnBnClickedButton6)
	ON_EN_CHANGE(IDC_EDIT3, &CKCSJ_HMISDlg::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_BUTTON7, &CKCSJ_HMISDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CKCSJ_HMISDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CKCSJ_HMISDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CKCSJ_HMISDlg::OnBnClickedButton10)
END_MESSAGE_MAP()


// CKCSJ_HMISDlg 消息处理程序

BOOL CKCSJ_HMISDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。
	 CFont *pFont = new CFont;
	 pFont->CreatePointFont(200,_T("David"));
	 ((CWnd*)GetDlgItem(IDC_STATIC7))->SetFont(pFont);
	 CFont *pFonti = new CFont;
	 pFonti->CreatePointFont(120,_T("David"));
	 ((CWnd*)GetDlgItem(IDC_STATIC8))->SetFont(pFonti);
	 CFont *pFontii = new CFont;
	 pFontii->CreatePointFont(130,_T("David"));
	 ((CWnd*)GetDlgItem(IDC_STATIC9))->SetFont(pFontii);
	 CFont *pFontiii = new CFont;
	 pFontiii->CreatePointFont(200,_T("David"));
	 ((CWnd*)GetDlgItem(IDC_STATIC10))->SetFont(pFontiii);
	 CFont *pFontiiii = new CFont;
	 pFontiiii->CreatePointFont(210,_T("David"));
	 ((CWnd*)GetDlgItem(IDC_STATIC11))->SetFont(pFontiiii);
	 CFont *pFont_Edit = new CFont;
	 pFont_Edit->CreatePointFont(105,_T("Stencil Std"));
	 ((CWnd*)GetDlgItem(IDC_EDIT3))->SetFont(pFont_Edit);
	 m_status  = L"{Not Logined}";
	 UpdateData(false);
	 

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CKCSJ_HMISDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CKCSJ_HMISDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//CDialogEx::OnPaint();
				CPaintDC dc(this);
			CRect rc;
			GetClientRect(&rc);
			CDC dcMem;
			dcMem.CreateCompatibleDC(&dc);
			CBitmap bmpBackground;
			bmpBackground.LoadBitmap(IDB_BITMAP3);

			BITMAP bitmap;
			bmpBackground.GetBitmap(&bitmap);
			CBitmap* pbmpPri = dcMem.SelectObject(&bmpBackground);
			dc.StretchBlt(0,0,rc.Width(), rc.Height(), &dcMem,0,0,bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CKCSJ_HMISDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CKCSJ_HMISDlg::OnBnClickedButton1()		//Customer	
{
	if(m_status.Compare(L"{Not Logined}") == 0){
		MessageBox(L"Please Login to USE");
		return ;
	} else if(m_status.Compare(L"Guest                                             ") == 0){
		MessageBox(L"Guest Refuesed. Please choose 【Available】 Module!");
		return ;
	}  else if(m_status.Compare(L"User                                              ") == 0){
		MessageBox(L"Uesr Refuesed. Please choose 【Available】 Module!");
		return ;
	}
	
	// TODO: 在此添加控件通知处理程序代码
	KCSJ_CUSTOMER *pTD = new KCSJ_CUSTOMER();  
	pTD->Create(IDD_KCSJ_CUSTOMER); //创建一个非模态对话框  
	pTD->ShowWindow(SW_SHOWNORMAL); //显示非模态对话框  
}


void CKCSJ_HMISDlg::OnBnClickedButton2()		//Room
{
	if(m_status.Compare(L"{Not Logined}") == 0){
		MessageBox(L"Please Login to USE");
		return ;
	} else if(m_status.Compare(L"Guest                                             ") == 0){
		MessageBox(L"Guest Refuesed. Please choose 【Available】 Module!");
		return ;
	}  else if(m_status.Compare(L"User                                              ") == 0){
		MessageBox(L"Uesr Refuesed. Please choose 【Available】 Module!");
		return ;
	}
	// TODO: 在此添加控件通知处理程序代码
	KCSJ_ROOM *pTD = new KCSJ_ROOM();  
	pTD->Create(IDD_KCSJ_ROOM); //创建一个非模态对话框  
	pTD->ShowWindow(SW_SHOWNORMAL); //显示非模态对话框  
}


void CKCSJ_HMISDlg::OnBnClickedButton3()		//Employee
{
	if(m_status.Compare(L"{Not Logined}") == 0){
		MessageBox(L"Please Login to USE");
		return ;
	} else if(m_status.Compare(L"Guest                                             ") == 0){
		MessageBox(L"Guest Refuesed. Please choose 【Available】 Module!");
		return ;
	}  else if(m_status.Compare(L"User                                              ") == 0){
		MessageBox(L"Uesr Refuesed. Please choose 【Available】 Module!");
		return ;
	}
	// TODO: 在此添加控件通知处理程序代码
	KCSJ_EMPLOYEE *pTD = new KCSJ_EMPLOYEE();  
	pTD->Create(IDD_KCSJ_EMPLOYEE); //创建一个非模态对话框  
	pTD->ShowWindow(SW_SHOWNORMAL); //显示非模态对话框  
}


void CKCSJ_HMISDlg::OnBnClickedButton4()				//Book : Guest Only
{
	
	if(m_status.Compare(L"{Not Logined}") == 0){
		MessageBox(L"Please Login to USE");
		return ;
	}
	
	// TODO: 在此添加控件通知处理程序代码
	KCSJ_BOOK *pTD = new KCSJ_BOOK();  
	pTD->Create(IDD_KCSJ_BOOK); //创建一个非模态对话框  
	pTD->ShowWindow(SW_SHOWNORMAL); //显示非模态对话框  
}


void CKCSJ_HMISDlg::OnBnClickedButton5()			//Serve 
{
	if(m_status.Compare(L"{Not Logined}") == 0){
		MessageBox(L"Please Login to USE");
		return ;
	} else if(m_status.Compare(L"Guest                                             ") == 0){
		MessageBox(L"Guest Refuesed. Please choose 【Available】 Module!");
		return ;
	}
	// TODO: 在此添加控件通知处理程序代码
	KCSJ_SERVE *pTD = new KCSJ_SERVE();  
	pTD->Create(IDD_KCSJ_SERVE); //创建一个非模态对话框  
	pTD->ShowWindow(SW_SHOWNORMAL); //显示非模态对话框  
}


void CKCSJ_HMISDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);					//READ
	CAccount m_set;
	try{
		if (m_set.IsOpen())
			m_set.Close();		
		if (!m_set.Open(CRecordset::snapshot, L"select * from Account where Handle = '" \
			+ m_Handle + L"' and Password = substring(sys.fn_sqlvarbasetostr(HashBytes('MD5', '"\
			+ m_Password + "')),3,32) order by Uid" )){
			MessageBox(L"打开数据库失败", L"数据库错误", MB_OK);
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}
	if(m_set.IsBOF() || m_set.IsEOF()){
		MessageBox(L"Wrong Handle or Wrong Password. Please check again!", L"Warning", MB_ICONERROR);
		return;
	}
	m_status = m_set.m_Authority;
	m_Password = L"******";
	Message = m_status;
	UpdateData(false);
	MessageBox(L"Login 【SUCCESS】");
	m_set.Close();
}


void CKCSJ_HMISDlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

//#1015

	// TODO:  在此添加控件通知处理程序代码
}


void CKCSJ_HMISDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	m_status = L"{Not Logined}";
	m_Handle = L"";
	m_Password = L"";

	MessageBox(L"Logout【SUCCESS】",L"Information",MB_RIGHT);
	UpdateData(false);
}


void CKCSJ_HMISDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	if(Message.Compare(L"Super_Administrator                               ") != 0){
		MessageBox(L"This module ONLY for Super_Administrator");
		return;
	}
	
	KCSJ_ACCOUNT *pTD = new KCSJ_ACCOUNT();
	pTD->Create(IDD_KCSJ_ACCOUNT); //创建一个非模态对话框  
	pTD->ShowWindow(SW_SHOWNORMAL); //显示非模态对话框  
}

void CKCSJ_HMISDlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	if(Message.Compare(L"Administrator                                     ") != 0){
		MessageBox(L"This module ONLY for Administrator");
		return;
	}
	
	KCSJ_ACCOUNT *pTD = new KCSJ_ACCOUNT();
	pTD->Create(IDD_KCSJ_ACCOUNT); //创建一个非模态对话框  
	pTD->ShowWindow(SW_SHOWNORMAL); //显示非模态对话框  
}


void CKCSJ_HMISDlg::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	KCSJ_ABOUT *pTD = new KCSJ_ABOUT();
	pTD->Create(IDD_KCSJ_ABOUT); //创建一个非模态对话框  
	pTD->ShowWindow(SW_SHOWNORMAL); //显示非模态对话框  

}
