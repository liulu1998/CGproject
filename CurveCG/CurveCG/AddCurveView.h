#pragma once

#include "viewList.h"
#include "Curve.h"

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
	CComboBox m_degree_cbx;					// 次数 下拉框
	CurveType selectedType = Spline;		// 选中的次数

// 我们的方法
private:
	CView* GetView(CRuntimeClass* pClass);	// 获取指定类型的View
// 我们的属性
	// 精度 滑动条和编辑框的设定值
	int precisionMin = 20;
	int precisionMax = 200;
	int precisionInterval = 10;
	int precisionDefault = 100;
	int nowPrecision = precisionDefault;
	bool isFocus = false;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedRadioBezier();
	afx_msg void OnBnClickedRadioBspline();
	afx_msg void OnBnClickedButtonAddcurve();
private:
	CSliderCtrl m_slider_precision;
	CEdit m_edit_precision;
public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
//	afx_msg void OnEnChangeEdit1();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEnChangeEdit1();
//	afx_msg void OnUpdateEdit1();
	afx_msg void OnSetfocusEdit1();
	afx_msg void OnKillfocusEdit1();
//	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
