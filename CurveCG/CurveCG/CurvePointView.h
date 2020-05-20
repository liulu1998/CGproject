#pragma once

#include "viewList.h"
#include "Curve.h"

// CurvePointView 窗体视图

class CurvePointView : public CFormView
{
	DECLARE_DYNCREATE(CurvePointView)

protected:
	CurvePointView();           // 动态创建所使用的受保护的构造函数
	virtual ~CurvePointView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_CURBEPOINT };
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

	// 我们的方法
private:
	CView* GetView(CRuntimeClass* pClass);	// 获取指定类型的View
public:
	CListCtrl m_pointList;

	void showCurvePoints();
	afx_msg void OnBnClickedButtonDelcurve();
	virtual void OnInitialUpdate();

	void addPoint(const CP2&);			// 增加一个控制点信息, 一定是在焦点曲线操作

	void resetList();					// 清空控制点列表
	afx_msg void OnBnClickedButtonSavepoints();
};
