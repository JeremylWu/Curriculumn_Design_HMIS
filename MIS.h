// MIS.h : MIS 的声明

#pragma once

// 代码生成在 2015年1月14日, 15:41

class MIS : public CRecordset
{
public:
	MIS(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(MIS)

// 字段/参数数据

// 以下字符串类型(如果存在)反映数据库字段(ANSI 数据类型的 CStringA 和 Unicode
// 数据类型的 CStringW)的实际数据类型。
//  这是为防止 ODBC 驱动程序执行可能
// 不必要的转换。如果希望，可以将这些成员更改为
// CString 类型，ODBC 驱动程序将执行所有必要的转换。
// (注意: 必须使用 3.5 版或更高版本的 ODBC 驱动程序
// 以同时支持 Unicode 和这些转换)。

	CStringW	m_dboBookB_date;
	CStringW	m_dboBookB_day;
	CStringW	m_dboBookB_bookday;
	CStringW	m_dboBookB_ID;
	CStringW	m_dboBookC_ID;
	CStringW	m_dboBookR_ID;
	CStringW	m_dboCustomerC_ID;
	CStringW	m_dboCustomerC_name;
	CStringW	m_dboCustomerC_sex;
	CStringW	m_dboCustomerC_addr;
	long	m_dboCustomerC_age;
	CStringW	m_dboEmployeeE_ID;
	CStringW	m_dboEmployeeE_name;
	CStringW	m_dboEmployeeE_sex;
	long	m_dboEmployeeE_age;
	CStringW	m_dboEmployeeE_pos;
	CStringW	m_dboRoomR_ID;
	CStringW	m_dboRoomR_type;
	CStringW	m_dboRoomR_status;
	long	m_dboRoomR_price;
	CStringW	m_dboServeS_ID;
	CStringW	m_dboServeS_ser;
	CStringW	m_dboServeR_ID;
	CStringW	m_dboServeE_ID;

// 重写
	// 向导生成的虚函数重写
	public:
	virtual CString GetDefaultConnect();	// 默认连接字符串

	virtual CString GetDefaultSQL(); 	// 记录集的默认 SQL
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX 支持
// 实现
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


