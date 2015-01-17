// KCSJ_CUSTOMER.cpp : 实现文件
//

#include "stdafx.h"
#include "KCSJ_HMIS.h"
#include "KCSJ_CUSTOMER.h"
#include "afxdialogex.h"
#include "Customer.h"
#include "Book.h"
#include "Global.h"



// KCSJ_CUSTOMER 对话框

IMPLEMENT_DYNAMIC(KCSJ_CUSTOMER, CDialog)

KCSJ_CUSTOMER::KCSJ_CUSTOMER(CWnd* pParent /*=NULL*/)
	: CDialog(KCSJ_CUSTOMER::IDD, pParent)
	, C_ID(_T(""))
	, C_name(_T(""))
	, C_sex(_T(""))
	, C_addr(_T(""))
	, C_age(0)
	, num_radio(0)
{

}

KCSJ_CUSTOMER::~KCSJ_CUSTOMER()
{
}

void KCSJ_CUSTOMER::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list_CUSTOMER);
	DDX_Text(pDX, IDC_EDIT1, C_ID);
	DDX_Text(pDX, IDC_EDIT2, C_name);
	DDX_Text(pDX, IDC_EDIT3, C_sex);
	DDX_Text(pDX, IDC_EDIT4, C_addr);
	DDX_Text(pDX, IDC_EDIT5, C_age);
}

BOOL KCSJ_CUSTOMER::OnInitDialog(){

	HCustomer m_set;
	m_set.Open();
	m_set.MoveFirst();
	
	C_ID = m_set.m_C_ID;
	C_name = m_set.m_C_name;
	C_sex = m_set.m_C_sex;
	C_addr = m_set.m_C_addr;
	C_age = m_set.m_C_age;

	UpdateData(false);
	
	LONG lStyle;
	lStyle = GetWindowLong(m_list_CUSTOMER.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_list_CUSTOMER, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle = m_list_CUSTOMER.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	m_list_CUSTOMER.SetExtendedStyle(dwStyle); //设置扩展风格
	
	/*
	DWORD dwExStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE;
	m_list.SetExtendedStyle(dwExStyle);
	*/
	
	m_list_CUSTOMER.SetTextColor(RGB(255, 0, 0));
	m_list_CUSTOMER.SetBkColor(RGB(240, 247, 233));
	m_list_CUSTOMER.InsertColumn(0, L"Customer ID", LVCFMT_CENTER, 110, 0);
	m_list_CUSTOMER.InsertColumn(1, L"Name", LVCFMT_CENTER, 75, 0);
	m_list_CUSTOMER.InsertColumn(2, L"Sex", LVCFMT_CENTER, 75, 0);
	m_list_CUSTOMER.InsertColumn(3, L"Addr", LVCFMT_CENTER, 80, 0);
	m_list_CUSTOMER.InsertColumn(4, L"Age", LVCFMT_CENTER, 40, 0);
		
	CString strsql;
	strsql.Format(L"select * from Customer order by C_ID");
	List_All(strsql);

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON2);
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	return true;
}
/*
void KCSJ_CUSTOMER::OnPaint()
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
        bmpBackground.LoadBitmap(IDB_BITMAP1);

        BITMAP bitmap;
        bmpBackground.GetBitmap(&bitmap);
        CBitmap* pbmpPri = dcMem.SelectObject(&bmpBackground);
        dc.StretchBlt(0,0,rc.Width(), rc.Height(), &dcMem,0,0,bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
		
	}
}
*/
BEGIN_MESSAGE_MAP(KCSJ_CUSTOMER, CDialog)
ON_WM_PAINT()							//ADD
ON_NOTIFY(NM_CLICK, IDC_LIST1, &KCSJ_CUSTOMER::OnNMClickList1)
ON_BN_CLICKED(IDC_BUTTON1, &KCSJ_CUSTOMER::OnBnClickedButton1)
ON_BN_CLICKED(IDC_BUTTON3, &KCSJ_CUSTOMER::OnBnClickedButton3)
ON_BN_CLICKED(IDC_RADIO1, &KCSJ_CUSTOMER::OnBnClickedRadio1)
ON_BN_CLICKED(IDC_RADIO2, &KCSJ_CUSTOMER::OnBnClickedRadio2)
ON_BN_CLICKED(IDC_RADIO3, &KCSJ_CUSTOMER::OnBnClickedRadio3)
ON_BN_CLICKED(IDC_RADIO4, &KCSJ_CUSTOMER::OnBnClickedRadio4)
ON_BN_CLICKED(IDC_RADIO5, &KCSJ_CUSTOMER::OnBnClickedRadio5)
ON_BN_CLICKED(IDC_BUTTON4, &KCSJ_CUSTOMER::OnBnClickedButton4)
ON_BN_CLICKED(IDC_BUTTON2, &KCSJ_CUSTOMER::OnBnClickedButton2)
ON_BN_CLICKED(IDC_BUTTON5, &KCSJ_CUSTOMER::OnBnClickedButton5)
END_MESSAGE_MAP()


// KCSJ_CUSTOMER 消息处理程序
void KCSJ_CUSTOMER::List_All(CString str){
	m_list_CUSTOMER.DeleteAllItems();
	HCustomer Customer;
	
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
		
		m_list_CUSTOMER.InsertItem(&litem);
		m_list_CUSTOMER.SetItemText(nindex, 0, Customer.m_C_ID);
		m_list_CUSTOMER.SetItemText(nindex, 1, Customer.m_C_name);
		m_list_CUSTOMER.SetItemText(nindex, 2, Customer.m_C_sex);
		m_list_CUSTOMER.SetItemText(nindex, 3, Customer.m_C_addr);

		uage.Format(L"%3d",Customer.m_C_age);
		m_list_CUSTOMER.SetItemText(nindex, 4, uage);
		
		Customer.MoveNext();
		nindex++;
	}
	Customer.Close();
}

void KCSJ_CUSTOMER::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	POSITION pos = m_list_CUSTOMER.GetFirstSelectedItemPosition();
	int r = m_list_CUSTOMER.GetNextSelectedItem(pos);
	C_ID = m_list_CUSTOMER.GetItemText(r, 0);
	C_name = m_list_CUSTOMER.GetItemText(r, 1);
	C_sex = m_list_CUSTOMER.GetItemText(r, 2);
	C_addr = m_list_CUSTOMER.GetItemText(r, 3);
	CString gg = m_list_CUSTOMER.GetItemText(r, 4);
	C_age = _ttol(gg);						//ADD
	UpdateData(false);
}

void KCSJ_CUSTOMER::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	HCustomer m_set;
	if(m_set.IsOpen()){
		m_set.Close();
	}
	//m_set.Open(CRecordset::snapshot, L"select * from Customer");
	m_set.Open();
	m_set.AddNew();
	UpdateData(true);	
	m_set.m_C_ID = C_ID;
	m_set.m_C_name = C_name;
	m_set.m_C_sex = C_sex;
	m_set.m_C_addr = C_addr;
	m_set.m_C_age = C_age;
	
	//MessageBox(m_set.m_dboCustomerC_ID);
	UpdateData(false);
	m_set.Update();
	m_set.Close();
	List_All(L"select * from Customer order by C_ID");
}


void KCSJ_CUSTOMER::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	if(Message.Compare(L"Administrator                                     ") == 0){
		MessageBox(L"permission denied");
		return ;
	}
	HCustomer m_set;
	m_set.Open();
	m_set.MoveFirst();
	while(!m_set.IsEOF()){
		if(m_set.m_C_ID == C_ID){
			m_set.Delete();
			break;
		}
		m_set.MoveNext();
	}
	m_set.Close();
	List_All(L"select * from Customer order by C_ID");
}


void KCSJ_CUSTOMER::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	num_radio = 1;
}


void KCSJ_CUSTOMER::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	num_radio = 2;
}


void KCSJ_CUSTOMER::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	num_radio = 3;
}


void KCSJ_CUSTOMER::OnBnClickedRadio4()
{
	// TODO: 在此添加控件通知处理程序代码
	num_radio = 4;
}


void KCSJ_CUSTOMER::OnBnClickedRadio5()
{
	// TODO: 在此添加控件通知处理程序代码
	num_radio = 5;
}


void KCSJ_CUSTOMER::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	CString hh;
	hh.Format(L"%3d",C_age);

	switch(num_radio){
	case 1:List_All(L"select * from Customer where C_ID = '" + C_ID + L"'");
		break;
	case 2:List_All(L"select * from Customer where C_name = '" + C_name + L"'");
		break;
	case 3:List_All(L"select * from Customer where C_sex = '" + C_sex + L"'");
		break;
	case 4:List_All(L"select * from Customer where C_addr = '" + C_addr + L"'");
		break;
	case 5:List_All(L"select * from Customer where C_age = '" + hh + L"'");
		break;
	default: break;
	}
}


void KCSJ_CUSTOMER::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if(Message.Compare(L"Administrator                                     ") == 0){
		MessageBox(L"permission denied");
		return ;
	}
	UpdateData(true);
	HCustomer m_revise;
	HBook m_revise_add;
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
			if(m_revise.m_C_ID == C_ID){
				m_revise.Delete();
				break;
			}
			m_revise.MoveNext();
		}
		//m_revise.Edit();

		m_revise.AddNew();
		UpdateData(true);	
		m_revise.m_C_ID = C_ID;
		m_revise.m_C_name = C_name;
		m_revise.m_C_sex = C_sex;
		m_revise.m_C_addr = C_addr;
		m_revise.m_C_age = C_age;
	
		//MessageBox(m_set.m_dboCustomerC_ID);
		UpdateData(false);
		m_revise.Update();

		m_revise.Close();
		m_revise_add.Close();
		MessageBox(L"Succeed");
		List_All(L"select * from Customer order by C_ID");
		return;
	}
	if(!m_revise_add.CanUpdate()){
		MessageBox(L"Update Failed");
		return;
	}
	m_revise.MoveFirst();
	m_revise_add.MoveFirst();
	while(!m_revise.IsEOF()){
		if(m_revise.m_C_ID == C_ID){
			while(!m_revise_add.IsEOF()){
				if(m_revise_add.m_C_ID == C_ID){
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
	m_revise.m_C_ID = C_ID;
	m_revise.m_C_name = C_name;
	m_revise.m_C_sex = C_sex;
	m_revise.m_C_addr = C_addr;
	m_revise.m_C_age = C_age;
	
	//MessageBox(m_set.m_dboCustomerC_ID);
	UpdateData(false);
	m_revise.Update();

	m_revise.Close();
	m_revise_add.Close();
	MessageBox(L"Succeed");
	List_All(L"select * from Customer order by C_ID");
}


void KCSJ_CUSTOMER::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	List_All(L"select * from Customer order by C_ID");
}
