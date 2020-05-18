#pragma once

#include "viewList.h"
#include "DrawView.h"

// CurveInfoView 窗体视图

class CurveInfoView : public CFormView
{
	DECLARE_DYNCREATE(CurveInfoView)

protected:
	CurveInfoView();           // 动态创建所使用的受保护的构造函数
	virtual ~CurveInfoView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_CURVEINFO };
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
	// 存有点信息的ListBox
	CListBox m_curveList;
	virtual void OnInitialUpdate();

// 我们的方法
private:
	CView* GetView(CRuntimeClass* pClass);	// 获取指定类型的View


public:
	afx_msg void OnLbnSelchangeListCurves();
	int AddCurve(int index);
	afx_msg void OnLbnDblclkListCurves();
};


