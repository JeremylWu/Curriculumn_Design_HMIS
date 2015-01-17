// KCSJ_EMPLOYEE.cpp : 实现文件
//

#include "stdafx.h"
#include "KCSJ_HMIS.h"
#include "KCSJ_EMPLOYEE.h"
#include "afxdialogex.h"
#include "Employee.h"
#include "Serve.h"
#include "Global.h"

// KCSJ_EMPLOYEE 对话框

IMPLEMENT_DYNAMIC(KCSJ_EMPLOYEE, CDialog)

KCSJ_EMPLOYEE::KCSJ_EMPLOYEE(CWnd* pParent /*=NULL*/)
	: CDialog(KCSJ_EMPLOYEE::IDD, pParent)
	, E_ID(_T(""))
	, E_name(_T(""))
	, E_sex(_T(""))
	, E_pos(_T(""))
	, E_age(0)
	, num_radio(0)
{

}

KCSJ_EMPLOYEE::~KCSJ_EMPLOYEE()
{
}

void KCSJ_EMPLOYEE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, E_ID);
	DDX_Text(pDX, IDC_EDIT2, E_name);
	DDX_Text(pDX, IDC_EDIT3, E_sex);
	DDX_Text(pDX, IDC_EDIT5, E_pos);
	DDX_Control(pDX, IDC_LIST1, m_list_EMPLOYEE);
	DDX_Text(pDX, IDC_EDIT4, E_age);
}


BEGIN_MESSAGE_MAP(KCSJ_EMPLOYEE, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &KCSJ_EMPLOYEE::OnNMClickList1)
	ON_BN_CLICKED(IDC_BUTTON1, &KCSJ_EMPLOYEE::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &KCSJ_EMPLOYEE::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_RADIO1, &KCSJ_EMPLOYEE::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &KCSJ_EMPLOYEE::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &KCSJ_EMPLOYEE::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &KCSJ_EMPLOYEE::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &KCSJ_EMPLOYEE::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_BUTTON4, &KCSJ_EMPLOYEE::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &KCSJ_EMPLOYEE::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &KCSJ_EMPLOYEE::OnBnClickedButton5)
END_MESSAGE_MAP()


// KCSJ_EMPLOYEE 消息处理程序
BOOL KCSJ_EMPLOYEE::OnInitDialog(){
	HEmployee m_set;
	m_set.Open();
	m_set.MoveFirst();
	
	E_ID = m_set.m_E_ID;
	E_name = m_set.m_E_name;
	E_sex = m_set.m_E_sex;
	E_age = m_set.m_E_age;
	E_pos = m_set.m_E_pos;

	UpdateData(false);
	
	LONG lStyle;
	lStyle = GetWindowLong(m_list_EMPLOYEE.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_list_EMPLOYEE, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle = m_list_EMPLOYEE.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	m_list_EMPLOYEE.SetExtendedStyle(dwStyle); //设置扩展风格
	
	/*
	DWORD dwExStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE;
	m_list.SetExtendedStyle(dwExStyle);
	*/
	
	m_list_EMPLOYEE.SetTextColor(RGB(255, 0, 0));
	m_list_EMPLOYEE.SetBkColor(RGB(240, 247, 233));
	m_list_EMPLOYEE.InsertColumn(0, L"Employee ID", LVCFMT_CENTER, 110, 0);
	m_list_EMPLOYEE.InsertColumn(1, L"Name", LVCFMT_CENTER, 75, 0);
	m_list_EMPLOYEE.InsertColumn(2, L"Sex", LVCFMT_CENTER, 70, 0);
	m_list_EMPLOYEE.InsertColumn(3, L"age", LVCFMT_CENTER, 50, 0);
	m_list_EMPLOYEE.InsertColumn(4, L"pos", LVCFMT_CENTER, 80, 0);
	
	CString strsql;
	strsql.Format(L"select * from Employee order by E_ID");
	List_All(strsql);
	
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON2);
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	return true;
}

void KCSJ_EMPLOYEE::List_All(CString str){
	m_list_EMPLOYEE.DeleteAllItems();
	HEmployee Customer;
	
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
		
		m_list_EMPLOYEE.InsertItem(&litem);
		m_list_EMPLOYEE.SetItemText(nindex, 0, Customer.m_E_ID);
		m_list_EMPLOYEE.SetItemText(nindex, 1, Customer.m_E_name);
		m_list_EMPLOYEE.SetItemText(nindex, 2, Customer.m_E_sex);
		

		uage.Format(L"%3d",Customer.m_E_age);
		m_list_EMPLOYEE.SetItemText(nindex, 3, uage);
		m_list_EMPLOYEE.SetItemText(nindex, 4, Customer.m_E_pos);
		
		Customer.MoveNext();
		nindex++;
	}
	Customer.Close();
}

void KCSJ_EMPLOYEE::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	POSITION pos = m_list_EMPLOYEE.GetFirstSelectedItemPosition();
	int r = m_list_EMPLOYEE.GetNextSelectedItem(pos);
	E_ID = m_list_EMPLOYEE.GetItemText(r, 0);
	E_name = m_list_EMPLOYEE.GetItemText(r, 1);
	E_sex = m_list_EMPLOYEE.GetItemText(r, 2);
	CString gg = m_list_EMPLOYEE.GetItemText(r, 3);
	E_age = _ttol(gg);						//ADD
	E_pos = m_list_EMPLOYEE.GetItemText(r, 4);
	
	UpdateData(false);
}


void KCSJ_EMPLOYEE::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	HEmployee m_set;
	if(m_set.IsOpen()){
		m_set.Close();
	}
	//m_set.Open(CRecordset::snapshot, L"select * from Customer");
	m_set.Open();
	m_set.AddNew();
	UpdateData(true);	
	m_set.m_E_ID = E_ID;
	m_set.m_E_name = E_name;
	m_set.m_E_sex = E_sex;
	m_set.m_E_pos = E_pos;
	m_set.m_E_age = E_age;
	
	//MessageBox(m_set.m_dboCustomerC_ID);
	UpdateData(false);
	m_set.Update();
	m_set.Close();
	List_All(L"select * from Employee order by E_ID");
}


void KCSJ_EMPLOYEE::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	if(Message.Compare(L"Administrator                                     ") == 0){
		MessageBox(L"permission denied");
		return ;
	}
	HEmployee m_set;
	m_set.Open();
	m_set.MoveFirst();
	while(!m_set.IsEOF()){
		if(m_set.m_E_ID == E_ID){
			m_set.Delete();
			break;
		}
		m_set.MoveNext();
	}
	m_set.Close();
	List_All(L"select * from Employee order by E_ID");
}


void KCSJ_EMPLOYEE::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	num_radio = 1;
}



void KCSJ_EMPLOYEE::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	num_radio = 2;
}


void KCSJ_EMPLOYEE::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	num_radio = 3;
}


void KCSJ_EMPLOYEE::OnBnClickedRadio4()
{
	// TODO: 在此添加控件通知处理程序代码
	num_radio = 4;
}


void KCSJ_EMPLOYEE::OnBnClickedRadio5()
{
	// TODO: 在此添加控件通知处理程序代码
	num_radio = 5;
}


void KCSJ_EMPLOYEE::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	CString hh;
	hh.Format(L"%3d",E_age);

	switch(num_radio){
	case 1:List_All(L"select * from Employee where E_ID = '" + E_ID + L"'");
		break;
	case 2:List_All(L"select * from Employee where E_name = '" + E_name + L"'");
		break;
	case 3:List_All(L"select * from Employee where E_sex = '" + E_sex + L"'");
		break;
	case 4:List_All(L"select * from Employee where E_age = '" + hh + L"'");
		break;
	case 5:List_All(L"select * from Employee where E_pos = '" + E_pos + L"'");
		break;
	default: break;
	}
}


void KCSJ_EMPLOYEE::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if(Message.Compare(L"Administrator                                     ") == 0){
		MessageBox(L"permission denied");
		return ;
	}
	UpdateData(true);
	HEmployee m_revise;
	HServe m_revise_add;
	m_revise.Open();
	m_revise_add.Open();
	if(m_revise.IsEOF()){
		MessageBox(L"Not Found");
		return;
	}
	if(!m_revise.CanUpdate()){
		MessageBox(L"Update Failed");
		return;
	}
	if(m_revise_add.IsEOF()){
		m_revise.MoveFirst();
		while(!m_revise.IsEOF()){
			if(m_revise.m_E_ID == E_ID){
				m_revise.Delete();
				break;
			}
			m_revise.MoveNext();
		}
		//m_revise.Edit();

		m_revise.AddNew();
		UpdateData(true);	
		m_revise.m_E_ID = E_ID;
		m_revise.m_E_name = E_name;
		m_revise.m_E_sex = E_sex;
		m_revise.m_E_pos = E_pos;
		m_revise.m_E_age = E_age;
	
		//MessageBox(m_set.m_dboCustomerC_ID);
		UpdateData(false);
		m_revise.Update();

		m_revise.Close();
		m_revise_add.Close();
		MessageBox(L"Succeed");
		List_All(L"select * from Employee order by E_ID");
		return;
	}
	if(!m_revise_add.CanUpdate()){
		MessageBox(L"Update Failed");
		return;
	}
	m_revise.MoveFirst();
	m_revise_add.MoveFirst();
	while(!m_revise.IsEOF()){
		if(m_revise.m_E_ID == E_ID){
			while(!m_revise_add.IsEOF()){
				if(m_revise_add.m_E_ID == E_ID){
					m_revise_add.Delete();
				}
				m_revise_add.MoveNext();
			}
			m_revise.Delete();
			break;
		}
		m_revise.MoveNext();
	}
	//m_revise.Edit();

	m_revise.AddNew();
	UpdateData(true);	
	m_revise.m_E_ID = E_ID;
	m_revise.m_E_name = E_name;
	m_revise.m_E_sex = E_sex;
	m_revise.m_E_pos = E_pos;
	m_revise.m_E_age = E_age;
	
	//MessageBox(m_set.m_dboCustomerC_ID);
	UpdateData(false);
	m_revise.Update();

	m_revise.Close();
	m_revise_add.Close();
	MessageBox(L"Succeed");
	List_All(L"select * from Employee order by E_ID");
}


void KCSJ_EMPLOYEE::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	List_All(L"select * from Employee order by E_ID");
}
