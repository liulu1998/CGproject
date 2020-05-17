#pragma once

#include "viewList.h"

// AddCurveView 窗体视图

class AddCurveView : public CFormView
{
	DECLARE_DYNCREATE(AddCurveView)

protected:
	AddCurveView();           // 动态创建所使用的受保护的构造函数
	virtual ~AddCurveView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_ADDCURVE };
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
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
private:
	CButton m_addCurveDlg;

// 我们的方法
private:
	CView* GetView(CRuntimeClass* pClass);	// 获取指定类型的View
};


