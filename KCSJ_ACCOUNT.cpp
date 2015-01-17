// KCSJ_ACCOUNT.cpp : 实现文件
//

#include "stdafx.h"
#include "KCSJ_HMIS.h"
#include "KCSJ_ACCOUNT.h"
#include "afxdialogex.h"
#include "Account.h"
#include "Global.h"

// KCSJ_ACCOUNT 对话框

IMPLEMENT_DYNAMIC(KCSJ_ACCOUNT, CDialog)

KCSJ_ACCOUNT::KCSJ_ACCOUNT(CWnd* pParent /*=NULL*/)
	: CDialog(KCSJ_ACCOUNT::IDD, pParent)
	, m_Uid(_T(""))
	, m_Handle(_T(""))
	, m_Password(_T(""))
	, m_Authority(_T(""))
{

}

KCSJ_ACCOUNT::~KCSJ_ACCOUNT()
{
}

void KCSJ_ACCOUNT::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_list);
	DDX_Text(pDX, IDC_EDIT1, m_Uid);
	DDX_Text(pDX, IDC_EDIT2, m_Handle);
	DDX_Text(pDX, IDC_EDIT3, m_Password);
	DDX_Text(pDX, IDC_EDIT4, m_Authority);
}


BEGIN_MESSAGE_MAP(KCSJ_ACCOUNT, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &KCSJ_ACCOUNT::OnNMClickList2)
	ON_BN_CLICKED(IDC_BUTTON2, &KCSJ_ACCOUNT::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &KCSJ_ACCOUNT::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &KCSJ_ACCOUNT::OnBnClickedButton3)
END_MESSAGE_MAP()


// KCSJ_ACCOUNT 消息处理程序

BOOL KCSJ_ACCOUNT::OnInitDialog(){
	CAccount m_set;
	m_set.Open();
	m_set.MoveFirst();
	
	m_Uid = m_set.m_Uid;
	m_Handle = m_set.m_Handle;
	m_Password = m_set.m_Password;
	m_Authority = m_set.m_Authority;

	UpdateData(false);
	
	LONG lStyle;
	lStyle = GetWindowLong(m_list.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_list, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle = m_list.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	m_list.SetExtendedStyle(dwStyle); //设置扩展风格
	
	/*
	DWORD dwExStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE;
	m_list.SetExtendedStyle(dwExStyle);
	*/
	
	m_list.SetTextColor(RGB(255, 0, 0));
	m_list.SetBkColor(RGB(240, 247, 233));
	m_list.InsertColumn(0, L"Uid", LVCFMT_CENTER, 75, 0);
	m_list.InsertColumn(1, L"Handle", LVCFMT_CENTER, 120, 0);
	m_list.InsertColumn(2, L"Password", LVCFMT_CENTER, 75, 0);
	m_list.InsertColumn(3, L"Authority", LVCFMT_CENTER, 120, 0);
	
	CString strsql;
	strsql.Format(L"select * from Account order by Uid");
	List_All(strsql);
	
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	/*
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON2);
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	*/
	return true;
}

void KCSJ_ACCOUNT::List_All(CString str){
	m_list.DeleteAllItems();
	CAccount Customer;
	
	try{
		if (Customer.IsOpen())
			Customer.Close();		
		if (!Customer.Open(CRecordset::snapshot, str)){
			MessageBox(L"打开数据库失败", L"数据库错误", MB_OK);
			return;
		}
	}
	catch (CDBException *e){
		e->ReportError();
	}

	Customer.MoveFirst();
	CString uage;				//change to String
	int nindex = 0;
	while (!Customer.IsEOF()){
		LV_ITEM litem;
		litem.mask = LVIF_TEXT;
		litem.iItem = nindex;
		litem.iSubItem = 0;
		litem.pszText = L"";
		
		m_list.InsertItem(&litem);
		m_list.SetItemText(nindex, 0, Customer.m_Uid);
		m_list.SetItemText(nindex, 1, Customer.m_Handle);
		m_list.SetItemText(nindex, 2, Customer.m_Password);
		m_list.SetItemText(nindex, 3, Customer.m_Authority);
		
		Customer.MoveNext();
		nindex++;
	}
	Customer.Close();
}

void KCSJ_ACCOUNT::OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	int r = m_list.GetNextSelectedItem(pos);
	m_Uid = m_list.GetItemText(r, 0);
	m_Handle = m_list.GetItemText(r, 1);
	m_Password = m_list.GetItemText(r, 2);
	m_Authority = m_list.GetItemText(r, 3);
	UpdateData(false);
}


void KCSJ_ACCOUNT::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	CDatabase db;
	db.Open(L"_SQL", FALSE, FALSE,  L"ODBC;", TRUE);
	CString sql;
	sql.Format(L"insert into Account values ('" + m_Uid + L"', '" + m_Handle + L"', substring(sys.fn_sqlvarbasetostr(HashBytes('MD5','" + m_Password + L"')),3,32), '" + m_Authority +L"')");
	db.ExecuteSQL(sql);
	MessageBox(L"Creat 【SUCCESS】");
	db.Close();
	List_All(L"select * from Account order by Uid");
	
}

void KCSJ_ACCOUNT::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if(Message.Compare(L"Administrator                                     ") == 0){
		MessageBox(L"permission denied");
		return ;
	} 
	CAccount m_set;
	m_set.Open();
	m_set.MoveFirst();
	while(!m_set.IsEOF()){
		if(m_set.m_Uid == m_Uid){
			m_set.Delete();
			break;
		}
		m_set.MoveNext();
	}
	m_set.Close();
	List_All(L"select * from Account order by Uid");
}



void KCSJ_ACCOUNT::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	if(Message.Compare(L"Administrator                                     ") == 0){
		MessageBox(L"permission denied");
		return ;
	} 
	UpdateData(true);
	CAccount m_revise;
	m_revise.Open();
	if(m_revise.IsEOF()){
		MessageBox(L"Not Found");
		return;
	}
	if(!m_revise.CanUpdate()){
		MessageBox(L"Update Failed");
		return;
	}

	m_revise.MoveFirst();
	while(!m_revise.IsEOF()){
		if(m_revise.m_Uid == m_Uid){
			m_revise.Delete();
			break;
		}
		m_revise.MoveNext();
	}
	
	UpdateData(true);	
	CDatabase db;
	db.Open(L"_SQL", FALSE, FALSE,  L"ODBC;", TRUE);
	CString sql;
	sql.Format(L"insert into Account values ('" + m_Uid + L"', '" + m_Handle + L"', substring(sys.fn_sqlvarbasetostr(HashBytes('MD5','" + m_Password + L"')),3,32), '" + m_Authority +L"')");
	db.ExecuteSQL(sql);
	MessageBox(L"Creat 【SUCCESS】");
	db.Close();
	m_revise.Close();
	List_All(L"select * from Account order by Uid");
}
