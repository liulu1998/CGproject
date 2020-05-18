#pragma once

#include "Curve.h"

// MoreCurveInfo 对话框

class MoreCurveInfo : public CDialogEx
{
	DECLARE_DYNAMIC(MoreCurveInfo)

public:
	MoreCurveInfo(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MoreCurveInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_MORECURVEINFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持


	DECLARE_MESSAGE_MAP()

private:
	CButton m_addCurveDlg;
	CComboBox m_degree_cbx;					// 次数 下拉框
	CSliderCtrl m_slider_precision;
	CEdit m_edit_precision;

public:
	Curve m_curve;
	CString curveName;
	CEdit m_edit_curveName;
	//方法
public:
	CView* GetView(CRuntimeClass* pClass);	// 获取指定类型的View
	int curveSetting(int index);
	

	afx_msg void OnEnChangeEdit01();
	
	virtual BOOL OnInitDialog();
};
