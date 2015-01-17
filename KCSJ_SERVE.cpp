// KCSJ_SERVE.cpp : 实现文件
//

#include "stdafx.h"
#include "KCSJ_HMIS.h"
#include "KCSJ_SERVE.h"
#include "afxdialogex.h"
#include "Serve.h"
#include "Employee.h"
#include "Room.h"
#include "Global.h"

// KCSJ_SERVE 对话框

IMPLEMENT_DYNAMIC(KCSJ_SERVE, CDialog)

KCSJ_SERVE::KCSJ_SERVE(CWnd* pParent /*=NULL*/)
	: CDialog(KCSJ_SERVE::IDD, pParent)
	, S_serve(_T(""))
	, R_ID(_T(""))
	, E_ID(_T(""))
	, S_ID(_T(""))
	, num_radio(0)
	, m_name(_T(""))
	, m_sex(_T(""))
	, m_age(0)
	, m_pos(_T(""))
	, m_type(_T(""))
	, m_status(_T(""))
	, m_price(0)
{

}

KCSJ_SERVE::~KCSJ_SERVE()
{
}

void KCSJ_SERVE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list_SERVE);
	DDX_Text(pDX, IDC_EDIT1, S_serve);
	DDX_Text(pDX, IDC_EDIT3, R_ID);
	DDX_Text(pDX, IDC_EDIT2, E_ID);
	DDX_Text(pDX, IDC_EDIT4, S_ID);
	DDX_Text(pDX, IDC_EDIT6, m_name);
	DDX_Text(pDX, IDC_EDIT8, m_sex);
	DDX_Text(pDX, IDC_EDIT7, m_age);
	DDX_Text(pDX, IDC_EDIT9, m_pos);
	DDX_Text(pDX, IDC_EDIT10, m_type);
	DDX_Text(pDX, IDC_EDIT12, m_status);
	DDX_Text(pDX, IDC_EDIT11, m_price);
}


BEGIN_MESSAGE_MAP(KCSJ_SERVE, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &KCSJ_SERVE::OnNMClickList1)
	ON_BN_CLICKED(IDC_BUTTON1, &KCSJ_SERVE::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &KCSJ_SERVE::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_RADIO1, &KCSJ_SERVE::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &KCSJ_SERVE::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &KCSJ_SERVE::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &KCSJ_SERVE::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_BUTTON5, &KCSJ_SERVE::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON2, &KCSJ_SERVE::OnBnClickedButton2)
END_MESSAGE_MAP()


// KCSJ_SERVE 消息处理程序
BOOL KCSJ_SERVE::OnInitDialog(){
	HServe m_set;
	m_set.Open();
	m_set.MoveFirst();
	
	S_serve = m_set.m_S_ser;
	R_ID = m_set.m_R_ID;
	E_ID = m_set.m_E_ID;
	S_ID = m_set.m_S_ID;

	UpdateData(false);
	
	LONG lStyle;
	lStyle = GetWindowLong(m_list_SERVE.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_list_SERVE, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle = m_list_SERVE.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	m_list_SERVE.SetExtendedStyle(dwStyle); //设置扩展风格
	
	/*
	DWORD dwExStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE;
	m_list.SetExtendedStyle(dwExStyle);
	*/
	
	m_list_SERVE.SetTextColor(RGB(255, 0, 0));
	m_list_SERVE.SetBkColor(RGB(240, 247, 233));
	m_list_SERVE.InsertColumn(0, L"Serve", LVCFMT_CENTER, 75, 0);
	m_list_SERVE.InsertColumn(1, L"R_ID", LVCFMT_CENTER, 110, 0);
	m_list_SERVE.InsertColumn(2, L"E_ID", LVCFMT_CENTER, 110, 0);
	m_list_SERVE.InsertColumn(3, L"S_ID", LVCFMT_CENTER, 110, 0);

	
	CString strsql;
	strsql.Format(L"select * from Serve order by S_ID");
	List_All(strsql);
	
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
		m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON2);
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	return true;
}

void KCSJ_SERVE::List_All(CString str){
	m_list_SERVE.DeleteAllItems();
	HServe Customer;
	
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
		
		m_list_SERVE.InsertItem(&litem);
		m_list_SERVE.SetItemText(nindex, 0, Customer.m_S_ser);
		m_list_SERVE.SetItemText(nindex, 1, Customer.m_R_ID);
		m_list_SERVE.SetItemText(nindex, 2, Customer.m_E_ID);
		m_list_SERVE.SetItemText(nindex, 3, Customer.m_S_ID);

		Customer.MoveNext();
		nindex++;
	}
	Customer.Close();
}

void KCSJ_SERVE::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	POSITION pos = m_list_SERVE.GetFirstSelectedItemPosition();

	int r = m_list_SERVE.GetNextSelectedItem(pos);
	S_serve = m_list_SERVE.GetItemText(r, 0);
	R_ID = m_list_SERVE.GetItemText(r, 1);
	E_ID = m_list_SERVE.GetItemText(r, 2);
	S_ID = m_list_SERVE.GetItemText(r, 3);

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
	HEmployee m_set_Employee;
	m_set_Employee.Open();
	m_set_Employee.MoveFirst();
	while(!m_set_Employee.IsEOF()){
		if(m_set_Employee.m_E_ID == E_ID){
			m_name = m_set_Employee.m_E_name;
			m_sex = m_set_Employee.m_E_sex;
			m_age  = m_set_Employee.m_E_age;
			m_pos = m_set_Employee.m_E_pos;
			break;
		}
		 m_set_Employee.MoveNext();
	}
	m_set_Employee.Close();
	UpdateData(false);
}


void KCSJ_SERVE::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_status.Compare(L"User                                              ") == 0){
		MessageBox(L"permission denied");
		return ;
	}
	HServe m_set;
	if(m_set.IsOpen()){
		m_set.Close();
	}
	//m_set.Open(CRecordset::snapshot, L"select * from Customer");
	m_set.Open();
	m_set.AddNew();
	UpdateData(true);	

	m_set.m_S_ser = S_serve;
	m_set.m_R_ID = R_ID;
	m_set.m_E_ID = E_ID;
	m_set.m_S_ID = S_ID;
	
	//MessageBox(m_set.m_dboCustomerC_ID);
	UpdateData(false);
	m_set.Update();
	m_set.Close();
	List_All(L"select * from Serve order by S_ID");
}


void KCSJ_SERVE::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_status.Compare(L"User                                              ") == 0){
		MessageBox(L"permission denied");
		return ;
	} else if(Message.Compare(L"Administrator                                     ") == 0){
		MessageBox(L"permission denied");
		return ;
	}
	HServe m_set;
	m_set.Open();
	m_set.MoveFirst();
	while(!m_set.IsEOF()){
		if(m_set.m_S_ID == S_ID){
			m_set.Delete();
			break;
		}
		m_set.MoveNext();
	}
	m_set.Close();
	List_All(L"select * from Serve order by S_ID");
}


void KCSJ_SERVE::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	num_radio = 1;
}


void KCSJ_SERVE::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	num_radio = 2;
}


void KCSJ_SERVE::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	num_radio = 3;
}


void KCSJ_SERVE::OnBnClickedRadio4()
{
	// TODO: 在此添加控件通知处理程序代码
	num_radio = 4;
}


void KCSJ_SERVE::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	switch(num_radio){
	case 1:List_All(L"select * from Serve where S_ser = '" + S_serve + L"'");
		break;
	case 2:List_All(L"select * from Serve where R_ID = '" + R_ID + L"'");
		break;
	case 3:List_All(L"select * from Serve where E_ID = '" + E_ID + L"'");
		break;
	case 4:List_All(L"select * from Serve where S_ID = '" + S_ID + L"'");
		break;
	default: break;
	}
}


void KCSJ_SERVE::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_status.Compare(L"User                                              ") == 0){
		MessageBox(L"permission denied");
		return ;
	} else if(Message.Compare(L"Administrator                                     ") == 0){
		MessageBox(L"permission denied");
		return ;
	}
	UpdateData(true);
	HServe m_revise;
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
		if(m_revise.m_S_ID == S_ID){
			m_revise.Delete();
			break;
		}
		m_revise.MoveNext();
	}
	m_revise.AddNew();
	UpdateData(true);	

	m_revise.m_S_ser = S_serve;
	m_revise.m_R_ID = R_ID;
	m_revise.m_E_ID = E_ID;
	m_revise.m_S_ID = S_ID;
	//MessageBox(m_set.m_dboCustomerC_ID);
	UpdateData(false);
	m_revise.Update();

	m_revise.Close();
	MessageBox(L"Succeed");
	List_All(L"select * from Serve order by S_ID");
}
