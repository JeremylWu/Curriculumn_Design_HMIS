// Customer.h : HCustomer 类的实现



// HCustomer 实现

// 代码生成在 2015年1月15日, 11:40

#include "stdafx.h"
#include "Customer.h"
IMPLEMENT_DYNAMIC(HCustomer, CRecordset)

HCustomer::HCustomer(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_C_ID = L"";
	m_C_name = L"";
	m_C_sex = L"";
	m_C_addr = L"";
	m_C_age = 0;
	m_nFields = 5;
	m_nDefaultType = dynaset;
}
//#error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString HCustomer::GetDefaultConnect()
{
	return _T("DSN=_SQL;UID=sa;PWD=123456;APP=Microsoft\x00ae Visual Studio\x00ae 2012;WSID=THINKPAD-PC;DATABASE=KCSJ_HMIS");
}

CString HCustomer::GetDefaultSQL()
{
	return _T("[dbo].[Customer]");
}

void HCustomer::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[C_ID]"), m_C_ID);
	RFX_Text(pFX, _T("[C_name]"), m_C_name);
	RFX_Text(pFX, _T("[C_sex]"), m_C_sex);
	RFX_Text(pFX, _T("[C_addr]"), m_C_addr);
	RFX_Long(pFX, _T("[C_age]"), m_C_age);

}
/////////////////////////////////////////////////////////////////////////////
// HCustomer 诊断

#ifdef _DEBUG
void HCustomer::AssertValid() const
{
	CRecordset::AssertValid();
}

void HCustomer::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


