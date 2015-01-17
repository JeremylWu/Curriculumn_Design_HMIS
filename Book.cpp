// Book.h : HBook 类的实现



// HBook 实现

// 代码生成在 2015年1月15日, 14:52

#include "stdafx.h"
#include "Book.h"
IMPLEMENT_DYNAMIC(HBook, CRecordset)

HBook::HBook(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_B_date = L"";
	m_B_day = L"";
	m_B_bookday = L"";
	m_C_ID = L"";
	m_R_ID = L"";
	m_B_ID = L"";
	m_nFields = 6;
	m_nDefaultType = dynaset;
}
//#error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString HBook::GetDefaultConnect()
{
	return _T("DSN=_SQL;UID=sa;PWD=123456;APP=Microsoft\x00ae Visual Studio\x00ae 2012;WSID=THINKPAD-PC;DATABASE=KCSJ_HMIS");
}

CString HBook::GetDefaultSQL()
{
	return _T("[dbo].[Book]");
}

void HBook::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[B_date]"), m_B_date);
	RFX_Text(pFX, _T("[B_day]"), m_B_day);
	RFX_Text(pFX, _T("[B_bookday]"), m_B_bookday);
	RFX_Text(pFX, _T("[C_ID]"), m_C_ID);
	RFX_Text(pFX, _T("[R_ID]"), m_R_ID);
	RFX_Text(pFX, _T("[B_ID]"), m_B_ID);

}
/////////////////////////////////////////////////////////////////////////////
// HBook 诊断

#ifdef _DEBUG
void HBook::AssertValid() const
{
	CRecordset::AssertValid();
}

void HBook::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


