// KCSJ_ROOM.cpp : 实现文件
//

#include "stdafx.h"
#include "KCSJ_HMIS.h"
#include "KCSJ_ROOM.h"
#include "afxdialogex.h"
#include "Room.h"
#include "Book.h"
#include "Serve.h"
#include "Global.h"

// KCSJ_ROOM 对话框

IMPLEMENT_DYNAMIC(KCSJ_ROOM, CDialog)

KCSJ_ROOM::KCSJ_ROOM(CWnd* pParent /*=NULL*/)
	: CDialog(KCSJ_ROOM::IDD, pParent)
	, R_ID(_T(""))
	, R_status(_T(""))
	, R_type(_T(""))
	, R_price(0)
	, num_radio(0)
{

}

KCSJ_ROOM::~KCSJ_ROOM()
{
}

void KCSJ_ROOM::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list_ROOM);
	DDX_Text(pDX, IDC_EDIT1, R_ID);
	DDX_Text(pDX, IDC_EDIT3, R_status);
	DDX_Text(pDX, IDC_EDIT2, R_type);
	DDX_Text(pDX, IDC_EDIT4, R_price);
}


BEGIN_MESSAGE_MAP(KCSJ_ROOM, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &KCSJ_ROOM::OnNMClickList1)
	ON_BN_CLICKED(IDC_BUTTON1, &KCSJ_ROOM::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &KCSJ_ROOM::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_RADIO1, &KCSJ_ROOM::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &KCSJ_ROOM::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &KCSJ_ROOM::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &KCSJ_ROOM::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_BUTTON5, &KCSJ_ROOM::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON2, &KCSJ_ROOM::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &KCSJ_ROOM::OnBnClickedButton4)
END_MESSAGE_MAP()


// KCSJ_ROOM 消息处理程序

BOOL KCSJ_ROOM::OnInitDialog(){
	HRoom m_set;
	m_set.Open();
	m_set.MoveFirst();
	
	R_ID = m_set.m_R_ID;
	R_type = m_set.m_R_type;
	R_status = m_set.m_R_status;
	R_price = m_set.m_R_price;
	
	UpdateData(false);
	
	LONG lStyle;
	lStyle = GetWindowLong(m_list_ROOM.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_list_ROOM, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle = m_list_ROOM.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	m_list_ROOM.SetExtendedStyle(dwStyle); //设置扩展风格
	
	/*
	DWORD dwExStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE;
	m_list.SetExtendedStyle(dwExStyle);
	*/
	
	m_list_ROOM.SetTextColor(RGB(255, 0, 0));
	m_list_ROOM.SetBkColor(RGB(240, 247, 233));
	m_list_ROOM.InsertColumn(0, L"Room ID", LVCFMT_CENTER, 110, 0);
	m_list_ROOM.InsertColumn(1, L"type", LVCFMT_CENTER, 170, 0);
	m_list_ROOM.InsertColumn(2, L"status", LVCFMT_CENTER, 160, 0);
	m_list_ROOM.InsertColumn(3, L"price", LVCFMT_CENTER, 80, 0);

	CString strsql;
	strsql.Format(L"select * from Room order by R_ID");
	List_All(strsql);

	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON2);
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	return true;
}

void KCSJ_ROOM::List_All(CString str){
	m_list_ROOM.DeleteAllItems();
	HRoom Customer;
	
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
		
		m_list_ROOM.InsertItem(&litem);
		m_list_ROOM.SetItemText(nindex, 0, Customer.m_R_ID);
		m_list_ROOM.SetItemText(nindex, 1, Customer.m_R_type);
		m_list_ROOM.SetItemText(nindex, 2, Customer.m_R_status);

		uage.Format(L"%3d",Customer.m_R_price);
		m_list_ROOM.SetItemText(nindex, 3, uage);
		
		Customer.MoveNext();
		nindex++;
	}
	Customer.Close();
}

void KCSJ_ROOM::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR); 
	*pResult = 0;
	POSITION pos = m_list_ROOM.GetFirstSelectedItemPosition();
	int r = m_list_ROOM.GetNextSelectedItem(pos);
	R_ID = m_list_ROOM.GetItemText(r, 0);
	R_type = m_list_ROOM.GetItemText(r, 1);
	R_status = m_list_ROOM.GetItemText(r, 2);
	CString gg = m_list_ROOM.GetItemText(r, 3);
	R_price = _ttol(gg);						//ADD
	
	UpdateData(false);
}

void KCSJ_ROOM::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	HRoom m_set;
	if(m_set.IsOpen()){
		m_set.Close();
	}
	//m_set.Open(CRecordset::snapshot, L"select * from Customer");
	m_set.Open();
	m_set.AddNew();
	UpdateData(true);	
	m_set.m_R_ID = R_ID;
	m_set.m_R_type = R_type;
	m_set.m_R_status = R_status;
	m_set.m_R_price = R_price;
	
	//MessageBox(m_set.m_dboCustomerC_ID);
	UpdateData(false);
	m_set.Update();
	m_set.Close();
	List_All(L"select * from Room order by R_ID");
}


void KCSJ_ROOM::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	if(Message.Compare(L"Administrator                                     ") == 0){
		MessageBox(L"permission denied");
		return ;
	}
	HRoom m_set;
	m_set.Open();
	m_set.MoveFirst();
	while(!m_set.IsEOF()){
		if(m_set.m_R_ID == R_ID){
			m_set.Delete();
			break;
		}
		m_set.MoveNext();
	}
	m_set.Close();
	List_All(L"select * from Room order by R_ID");
}


void KCSJ_ROOM::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	num_radio = 1;
}



void KCSJ_ROOM::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	num_radio = 2;
}


void KCSJ_ROOM::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	num_radio = 3;
}


void KCSJ_ROOM::OnBnClickedRadio4()
{
	// TODO: 在此添加控件通知处理程序代码
	num_radio = 4;
}


void KCSJ_ROOM::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	CString hh;
	hh.Format(L"%3d",R_price);

	switch(num_radio){
	case 1:List_All(L"select * from Room where R_ID = '" + R_ID + L"'");
		break;
	case 2:List_All(L"select * from Room where R_type = '" + R_type + L"'");
		break;
	case 3:List_All(L"select * from Room where R_status = '" + R_status + L"'");
		break;
	case 4:List_All(L"select * from Room where R_price = '" + hh + L"'");
		break;
	default: break;
	}
}


void KCSJ_ROOM::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if(Message.Compare(L"Administrator                                     ") == 0){
		MessageBox(L"permission denied");
		return ;
	}
	UpdateData(true);
	HRoom m_revise;
	HBook m_revise_add;
	HServe m_revise_add_add;
	m_revise.Open();
	m_revise_add.Open();
	m_revise_add_add.Open();
	if(m_revise.IsEOF()){
		MessageBox(L"Not Found");
		return;
	}
	if(!m_revise.CanUpdate()){
		MessageBox(L"Update Failed");
		return;
	}
	if(m_revise_add_add.IsEOF()){						//add_add Empty
		m_revise.MoveFirst();
		if(m_revise_add.IsEOF()){						//add Empty
			while(!m_revise.IsEOF()){
				if(m_revise.m_R_ID == R_ID){
					m_revise.Delete();
				}
				m_revise.MoveNext();
			}
			m_revise.AddNew();
			UpdateData(true);	
			m_revise.m_R_ID = R_ID;
			m_revise.m_R_type = R_type;
			m_revise.m_R_status = R_status;
			m_revise.m_R_price = R_price;
	
			//MessageBox(m_set.m_dboCustomerC_ID);
			UpdateData(false);
			m_revise.Update();

			m_revise.Close();
			m_revise_add.Close();
			m_revise_add_add.Close();
			MessageBox(L"Succeed");
			List_All(L"select * from Room order by R_ID");
			return;
		}
		m_revise_add.MoveFirst();
		while(!m_revise.IsEOF()){
			if(m_revise.m_R_ID == R_ID){
				while(!m_revise_add.IsEOF()){
					if(m_revise_add.m_R_ID == R_ID){
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
		m_revise.m_R_ID = R_ID;
		m_revise.m_R_type = R_type;
		m_revise.m_R_status = R_status;
		m_revise.m_R_price = R_price;
	
		//MessageBox(m_set.m_dboCustomerC_ID);
		UpdateData(false);
		m_revise.Update();

		m_revise.Close();
		m_revise_add.Close();
		m_revise_add_add.Close();
		MessageBox(L"Succeed");
		List_All(L"select * from Room order by R_ID");
		return;
	}
	if(!m_revise_add_add.CanUpdate()){
		MessageBox(L"Update Failed");
		return;
	}
	if(m_revise_add.IsEOF()){
		m_revise.MoveFirst();
		m_revise_add_add.MoveFirst();
		while(!m_revise.IsEOF()){
			if(m_revise.m_R_ID == R_ID){
				while(!m_revise_add_add.IsEOF()){
					if(m_revise_add_add.m_R_ID == R_ID){
						m_revise_add_add.Delete();
					}
					m_revise_add_add.MoveNext();
				}
				m_revise.Delete();
				break;
			}
			m_revise.MoveNext();
		}
		//m_revise.Edit();

		m_revise.AddNew();
		UpdateData(true);	
		m_revise.m_R_ID = R_ID;
		m_revise.m_R_type = R_type;
		m_revise.m_R_status = R_status;
		m_revise.m_R_price = R_price;
	
		//MessageBox(m_set.m_dboCustomerC_ID);
		UpdateData(false);
		m_revise.Update();

		m_revise.Close();
		m_revise_add.Close();
		m_revise_add_add.Close();
		MessageBox(L"Succeed");
		List_All(L"select * from Room order by R_ID");

		return;
	}
	if(!m_revise_add.CanUpdate()){
		MessageBox(L"Update Failed");
		return;
	}
	m_revise.MoveFirst();
	while(!m_revise.IsEOF()){
		m_revise_add.MoveFirst();			//Init
		m_revise_add_add.MoveFirst();
		if(m_revise.m_R_ID == R_ID){
			while(!m_revise_add.IsEOF()){
				if(m_revise_add.m_R_ID == R_ID){
					m_revise_add.Delete();
				}
				m_revise_add.MoveNext();
			}
			while(!m_revise_add_add.IsEOF()){
				if(m_revise_add_add.m_R_ID == R_ID){
					m_revise_add_add.Delete();
				}
				m_revise_add_add.MoveNext();
			}
			m_revise.Delete();
			break;
		}
		m_revise.MoveNext();
	}
	//m_revise.Edit();

	m_revise.AddNew();
	UpdateData(true);	
	m_revise.m_R_ID = R_ID;
	m_revise.m_R_type = R_type;
	m_revise.m_R_status = R_status;
	m_revise.m_R_price = R_price;
	
	//MessageBox(m_set.m_dboCustomerC_ID);
	UpdateData(false);
	m_revise.Update();

	m_revise.Close();
	m_revise_add.Close();
	MessageBox(L"Succeed");
	List_All(L"select * from Room order by R_ID");
}


void KCSJ_ROOM::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	List_All(L"select * from Room order by R_ID");
}
