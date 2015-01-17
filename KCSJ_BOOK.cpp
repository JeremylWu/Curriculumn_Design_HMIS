// KCSJ_BOOK.cpp : 实现文件
//

#include "stdafx.h"
#include "KCSJ_HMIS.h"
#include "KCSJ_BOOK.h"
#include "afxdialogex.h"
#include "Book.h"
#include "Customer.h"
#include "Room.h"
#include "Global.h"


// KCSJ_BOOK 对话框

IMPLEMENT_DYNAMIC(KCSJ_BOOK, CDialog)

KCSJ_BOOK::KCSJ_BOOK(CWnd* pParent /*=NULL*/)
	: CDialog(KCSJ_BOOK::IDD, pParent)
	, B_date(_T(""))
	, B_day(_T(""))
	, B_bookday(_T(""))
	, B_ID(_T(""))
	, C_ID(_T(""))
	, R_ID(_T(""))
	, num_radio(0)
	, m_name(_T(""))
	, m_sex(_T(""))
	, m_age(0)
	, m_type(_T(""))
	, m_status(_T(""))
	, m_price(0)
{

}

KCSJ_BOOK::~KCSJ_BOOK()
{
}

void KCSJ_BOOK::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, B_date);
	DDX_Text(pDX, IDC_EDIT2, B_day);
	DDX_Text(pDX, IDC_EDIT3, B_bookday);
	DDX_Text(pDX, IDC_EDIT5, B_ID);
	DDX_Text(pDX, IDC_EDIT4, C_ID);
	DDX_Text(pDX, IDC_EDIT6, R_ID);
	DDX_Control(pDX, IDC_LIST1, m_list_BOOK);
	DDX_Control(pDX, IDC_EDIT5, PRI_KEY);
	DDX_Text(pDX, IDC_EDIT7, m_name);
	DDX_Text(pDX, IDC_EDIT8, m_sex);
	DDX_Text(pDX, IDC_EDIT9, m_addr);
	DDX_Text(pDX, IDC_EDIT10, m_age);
	DDX_Text(pDX, IDC_EDIT12, m_type);
	DDX_Text(pDX, IDC_EDIT14, m_status);
	DDX_Text(pDX, IDC_EDIT13, m_price);
}


BEGIN_MESSAGE_MAP(KCSJ_BOOK, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &KCSJ_BOOK::OnNMClickList1)
	ON_BN_CLICKED(IDC_BUTTON1, &KCSJ_BOOK::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &KCSJ_BOOK::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_RADIO1, &KCSJ_BOOK::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &KCSJ_BOOK::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &KCSJ_BOOK::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &KCSJ_BOOK::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &KCSJ_BOOK::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO6, &KCSJ_BOOK::OnBnClickedRadio6)
	ON_BN_CLICKED(IDC_BUTTON5, &KCSJ_BOOK::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON2, &KCSJ_BOOK::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &KCSJ_BOOK::OnBnClickedButton4)
END_MESSAGE_MAP()


// KCSJ_BOOK 消息处理程序
BOOL KCSJ_BOOK::OnInitDialog(){
	HBook m_set;
	m_set.Open();
	m_set.MoveFirst();
	
	B_date = m_set.m_B_date;
	B_day = m_set.m_B_day;
	B_bookday = m_set.m_B_bookday;
	C_ID = m_set.m_C_ID;
	R_ID = m_set.m_R_ID;
	B_ID = m_set.m_B_ID;

	UpdateData(false);
	
	LONG lStyle;
	lStyle = GetWindowLong(m_list_BOOK.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_list_BOOK, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle = m_list_BOOK.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	m_list_BOOK.SetExtendedStyle(dwStyle); //设置扩展风格
	
	/*
	DWORD dwExStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE;
	m_list.SetExtendedStyle(dwExStyle);
	*/
	
	m_list_BOOK.SetTextColor(RGB(255, 0, 0));
	m_list_BOOK.SetBkColor(RGB(240, 247, 233));
	m_list_BOOK.InsertColumn(0, L"date", LVCFMT_CENTER, 75, 0);
	m_list_BOOK.InsertColumn(1, L"Day", LVCFMT_CENTER, 75, 0);
	m_list_BOOK.InsertColumn(2, L"Bookday", LVCFMT_CENTER, 75, 0);
	m_list_BOOK.InsertColumn(3, L"C_ID", LVCFMT_CENTER, 110, 0);
	m_list_BOOK.InsertColumn(4, L"R_ID", LVCFMT_CENTER, 110, 0);
	m_list_BOOK.InsertColumn(5, L"B_ID", LVCFMT_CENTER, 110, 0);

	CString strsql;
	strsql.Format(L"select * from Book order by B_ID");
	List_All(strsql);
	
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON2);
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	return true;
}

void KCSJ_BOOK::List_All(CString str){
	m_list_BOOK.DeleteAllItems();
	HBook Customer;
	
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
		
		m_list_BOOK.InsertItem(&litem);
		m_list_BOOK.SetItemText(nindex, 0, Customer.m_B_date);
		m_list_BOOK.SetItemText(nindex, 1, Customer.m_B_day);
		m_list_BOOK.SetItemText(nindex, 2, Customer.m_B_bookday);
		m_list_BOOK.SetItemText(nindex, 3, Customer.m_C_ID);
		m_list_BOOK.SetItemText(nindex, 4, Customer.m_R_ID);
		m_list_BOOK.SetItemText(nindex, 5, Customer.m_B_ID);
		
		Customer.MoveNext();
		nindex++;
	}
	Customer.Close();
}

void KCSJ_BOOK::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	POSITION pos = m_list_BOOK.GetFirstSelectedItemPosition();

	int r = m_list_BOOK.GetNextSelectedItem(pos);
	B_date = m_list_BOOK.GetItemText(r, 0);
	B_day = m_list_BOOK.GetItemText(r, 1);
	B_bookday = m_list_BOOK.GetItemText(r, 2);
	C_ID = m_list_BOOK.GetItemText(r, 3);
	R_ID = m_list_BOOK.GetItemText(r, 4);
	B_ID = m_list_BOOK.GetItemText(r, 5);
	
	HCustomer m_set_Customer;
	m_set_Customer.Open();
	m_set_Customer.MoveFirst();
	while(!m_set_Customer.IsEOF()){
		if(m_set_Customer.m_C_ID == C_ID){
			m_name = m_set_Customer.m_C_name;
			m_sex = m_set_Customer.m_C_sex;
			m_addr  = m_set_Customer.m_C_addr;
			m_age = m_set_Customer.m_C_age;
			break;
		}
		m_set_Customer.MoveNext();
	}
	m_set_Customer.Close();
	HRoom m_set_Room;
	m_set_Room.Open();
	m_set_Room.MoveFirst();
	while(!m_set_Room.IsEOF()){
		if(m_set_Room.m_R_ID == R_ID){
			m_type = m_set_Room.m_R_type;
			m_status = m_set_Room.m_R_status;
			m_price  = m_set_Room.m_R_price;
			break;
		}
		 m_set_Room.MoveNext();
	}
	m_set_Room.Close();
	UpdateData(false);
}


void KCSJ_BOOK::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if(Message.Compare(L"Guest                                             ") == 0){
		MessageBox(L"permission denied");
		return ;
	}
	
	HBook m_set;
	if(m_set.IsOpen()){
		m_set.Close();
	}
	//m_set.Open(CRecordset::snapshot, L"select * from Customer");
	m_set.Open();
	m_set.AddNew();
	UpdateData(true);	
	m_set.m_B_date = B_date;
	m_set.m_B_day = B_day;
	m_set.m_B_bookday = B_bookday;
	m_set.m_C_ID = C_ID;
	m_set.m_R_ID = R_ID;
	m_set.m_B_ID = B_ID;
	
	//MessageBox(m_set.m_dboCustomerC_ID);
	UpdateData(false);
	m_set.Update();
	m_set.Close();
	List_All(L"select * from Book order by B_ID");
}


void KCSJ_BOOK::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	if(Message.Compare(L"Guest                                             ") == 0){
		MessageBox(L"permission denied");
		return ;
	} else if(Message.Compare(L"Administrator                                     ") == 0){
		MessageBox(L"permission denied");
		return ;
	}
	HBook m_set;
	m_set.Open();
	m_set.MoveFirst();
	while(!m_set.IsEOF()){
		if(m_set.m_B_ID == B_ID){
			m_set.Delete();
			break;
		}
		m_set.MoveNext();
	}
	m_set.Close();
	List_All(L"select * from Book order by B_ID");
}


void KCSJ_BOOK::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	num_radio = 1;
}



void KCSJ_BOOK::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	num_radio = 2;
}



void KCSJ_BOOK::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	num_radio = 3;
}



void KCSJ_BOOK::OnBnClickedRadio4()
{
	// TODO: 在此添加控件通知处理程序代码
	num_radio = 4;
}



void KCSJ_BOOK::OnBnClickedRadio5()
{
	// TODO: 在此添加控件通知处理程序代码
	num_radio = 5;
}


void KCSJ_BOOK::OnBnClickedRadio6()
{
	// TODO: 在此添加控件通知处理程序代码
	num_radio = 5;
}


void KCSJ_BOOK::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);

	switch(num_radio){
	case 1:List_All(L"select * from Book where B_date = '" + B_date + L"'");
		break;
	case 2:List_All(L"select * from Book where B_day = '" + B_day + L"'");
		break;
	case 3:List_All(L"select * from Book where B_bookday = '" + B_bookday + L"'");
		break;
	case 4:List_All(L"select * from Book where C_ID = '" + C_ID + L"'");
		break;
	case 5:List_All(L"select * from Book where R_ID = '" + R_ID + L"'");
		break;
	case 6:List_All(L"select * from Book where B_ID = '" + B_ID + L"'");
	default: break;
	}
}


void KCSJ_BOOK::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if(Message.Compare(L"Guest                                             ") == 0){
		MessageBox(L"permission denied");
		return ;
	} else if(Message.Compare(L"Administrator                                     ") == 0){
		MessageBox(L"permission denied");
		return ;
	}
	UpdateData(true);
	HBook m_revise;
	m_revise.Open();
	if(m_revise.IsEOF()){
		MessageBox(L"Not Found");
		return;
	}
	if(!m_revise.CanUpdate()){
		MessageBox(L"Update Failed");
		return;
	}

	//m_revise.Edit();
	m_revise.MoveFirst();
	while(!m_revise.IsEOF()){
		if(m_revise.m_C_ID == C_ID){
			m_revise.Delete();
			break;
		}
		m_revise.MoveNext();
	}
	m_revise.AddNew();
	UpdateData(true);	
	m_revise.m_B_date = B_date;
	m_revise.m_B_day = B_day;
	m_revise.m_B_bookday = B_bookday;
	m_revise.m_C_ID = C_ID;
	m_revise.m_R_ID = R_ID;
	m_revise.m_B_ID = B_ID;
	//MessageBox(m_set.m_dboCustomerC_ID);
	UpdateData(false);
	m_revise.Update();

	m_revise.Close();
	MessageBox(L"Succeed");
	List_All(L"select * from Book order by B_ID");
}


void KCSJ_BOOK::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	List_All(L"select * from Book order by B_ID");
}
