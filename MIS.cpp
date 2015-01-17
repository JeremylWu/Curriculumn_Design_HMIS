// MIS.h : MIS 类的实现



// MIS 实现

// 代码生成在 2015年1月14日, 15:41

#include "stdafx.h"
#include "MIS.h"
IMPLEMENT_DYNAMIC(MIS, CRecordset)

MIS::MIS(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_dboBookB_date = L"";
	m_dboBookB_day = L"";
	m_dboBookB_bookday = L"";
	m_dboBookC_ID = L"";
	m_dboBookR_ID = L"";
	m_dboCustomerC_ID = L"";
	m_dboCustomerC_name = L"";
	m_dboCustomerC_sex = L"";
	m_dboCustomerC_addr = L"";
	m_dboCustomerC_age = 0;
	m_dboEmployeeE_ID = L"";
	m_dboEmployeeE_name = L"";
	m_dboEmployeeE_sex = L"";
	m_dboEmployeeE_age = 0;
	m_dboEmployeeE_pos = L"";
	m_dboRoomR_ID = L"";
	m_dboRoomR_type = L"";
	m_dboRoomR_status = L"";
	m_dboRoomR_price = 0;
	m_dboServeS_ser = L"";
	m_dboServeR_ID = L"";
	m_dboServeE_ID = L"";
	m_nFields = 22;
	m_nDefaultType = dynaset;
}
//#error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString MIS::GetDefaultConnect()
{
	return _T("DSN=_SQL;UID=sa;PWD=123456;APP=Microsoft\x00ae Visual Studio\x00ae 2012;WSID=THINKPAD-PC;DATABASE=KCSJ_HMIS");
}

CString MIS::GetDefaultSQL()
{
	return _T("[dbo].[Book],[dbo].[Customer],[dbo].[Employee],[dbo].[Room],[dbo].[Serve]");
}

void MIS::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[dbo].[Book].[B_date]"), m_dboBookB_date);
	RFX_Text(pFX, _T("[dbo].[Book].[B_day]"), m_dboBookB_day);
	RFX_Text(pFX, _T("[dbo].[Book].[B_bookday]"), m_dboBookB_bookday);
	RFX_Text(pFX, _T("[dbo].[Book].[C_ID]"), m_dboBookC_ID);
	RFX_Text(pFX, _T("[dbo].[Book].[R_ID]"), m_dboBookR_ID);
	RFX_Text(pFX, _T("[dbo].[Customer].[C_ID]"), m_dboCustomerC_ID);
	RFX_Text(pFX, _T("[dbo].[Customer].[C_name]"), m_dboCustomerC_name);
	RFX_Text(pFX, _T("[dbo].[Customer].[C_sex]"), m_dboCustomerC_sex);
	RFX_Text(pFX, _T("[dbo].[Customer].[C_addr]"), m_dboCustomerC_addr);
	RFX_Long(pFX, _T("[dbo].[Customer].[C_age]"), m_dboCustomerC_age);
	RFX_Text(pFX, _T("[dbo].[Employee].[E_ID]"), m_dboEmployeeE_ID);
	RFX_Text(pFX, _T("[dbo].[Employee].[E_name]"), m_dboEmployeeE_name);
	RFX_Text(pFX, _T("[dbo].[Employee].[E_sex]"), m_dboEmployeeE_sex);
	RFX_Long(pFX, _T("[dbo].[Employee].[E_age]"), m_dboEmployeeE_age);
	RFX_Text(pFX, _T("[dbo].[Employee].[E_pos]"), m_dboEmployeeE_pos);
	RFX_Text(pFX, _T("[dbo].[Room].[R_ID]"), m_dboRoomR_ID);
	RFX_Text(pFX, _T("[dbo].[Room].[R_type]"), m_dboRoomR_type);
	RFX_Text(pFX, _T("[dbo].[Room].[R_status]"), m_dboRoomR_status);
	RFX_Long(pFX, _T("[dbo].[Room].[R_price]"), m_dboRoomR_price);
	RFX_Text(pFX, _T("[dbo].[Serve].[S_ser]"), m_dboServeS_ser);
	RFX_Text(pFX, _T("[dbo].[Serve].[R_ID]"), m_dboServeR_ID);
	RFX_Text(pFX, _T("[dbo].[Serve].[E_ID]"), m_dboServeE_ID);

}
/////////////////////////////////////////////////////////////////////////////
// MIS 诊断

#ifdef _DEBUG
void MIS::AssertValid() const
{
	CRecordset::AssertValid();
}

void MIS::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


