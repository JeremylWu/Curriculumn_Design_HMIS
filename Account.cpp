// Account.h : CAccount 类的实现



// CAccount 实现

// 代码生成在 2015年1月16日, 11:50

#include "stdafx.h"
#include "Account.h"
IMPLEMENT_DYNAMIC(CAccount, CRecordset)

CAccount::CAccount(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_Uid = "";
	m_Handle = "";
	m_Password = "";
	m_Authority = "";
	m_nFields = 4;
	m_nDefaultType = dynaset;
}
//#error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString CAccount::GetDefaultConnect()
{
	return _T("DSN=_SQL;UID=sa;PWD=123456;APP=Microsoft\x00ae Visual Studio\x00ae 2012;WSID=THINKPAD-PC;DATABASE=KCSJ_HMIS");
}

CString CAccount::GetDefaultSQL()
{
	return _T("[dbo].[Account]");
}

void CAccount::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[Uid]"), m_Uid);
	RFX_Text(pFX, _T("[Handle]"), m_Handle);
	RFX_Text(pFX, _T("[Password]"), m_Password);
	RFX_Text(pFX, _T("[Authority]"), m_Authority);

}
/////////////////////////////////////////////////////////////////////////////
// CAccount 诊断

#ifdef _DEBUG
void CAccount::AssertValid() const
{
	CRecordset::AssertValid();
}

void CAccount::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


