// Employee.h : HEmployee 类的实现



// HEmployee 实现

// 代码生成在 2015年1月15日, 14:51

#include "stdafx.h"
#include "Employee.h"
IMPLEMENT_DYNAMIC(HEmployee, CRecordset)

HEmployee::HEmployee(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_E_ID = L"";
	m_E_name = L"";
	m_E_sex = L"";
	m_E_age = 0;
	m_E_pos = L"";
	m_nFields = 5;
	m_nDefaultType = dynaset;
}
//#error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString HEmployee::GetDefaultConnect()
{
	return _T("DSN=_SQL;UID=sa;PWD=123456;APP=Microsoft\x00ae Visual Studio\x00ae 2012;WSID=THINKPAD-PC;DATABASE=KCSJ_HMIS");
}

CString HEmployee::GetDefaultSQL()
{
	return _T("[dbo].[Employee]");
}

void HEmployee::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[E_ID]"), m_E_ID);
	RFX_Text(pFX, _T("[E_name]"), m_E_name);
	RFX_Text(pFX, _T("[E_sex]"), m_E_sex);
	RFX_Long(pFX, _T("[E_age]"), m_E_age);
	RFX_Text(pFX, _T("[E_pos]"), m_E_pos);

}
/////////////////////////////////////////////////////////////////////////////
// HEmployee 诊断

#ifdef _DEBUG
void HEmployee::AssertValid() const
{
	CRecordset::AssertValid();
}

void HEmployee::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


