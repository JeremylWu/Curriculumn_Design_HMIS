#pragma once


// Global

class Global : public CWnd
{
	DECLARE_DYNAMIC(Global)

public:
	Global();
	virtual ~Global();

protected:
	DECLARE_MESSAGE_MAP()
};
extern CString Message;
