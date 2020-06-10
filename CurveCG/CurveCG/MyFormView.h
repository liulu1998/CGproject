#pragma once
#include <afxext.h>
#include "resource.h" 

// MyFormView 窗体视图

class MyFormView : public CFormView
{
	DECLARE_DYNCREATE(MyFormView)

protected:
	MyFormView();           // 动态创建所使用的受保护的构造函数
	virtual ~MyFormView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MyFormView };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};


