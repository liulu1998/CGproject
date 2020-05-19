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
	int precisionMin = 20;
	int precisionMax = 200;
	int precisionInterval = 10;
private:

	CEdit m_edit_curveName;
	Curve m_curve;
	//CString curveName;
	CSliderCtrl m_SLIDER;
	CEdit m_PRESICION_EDIT;
	CComboBox m_DEGREE_COMBOX;
	CString curveName;
	bool isFocus = false;
	int nowPrecision;
	//方法
public:
	
	CView* GetView(CRuntimeClass* pClass);	// 获取指定类型的View

	/*SET方法*/
	int setCurveName(CString str);
	int setCurve(CurveType type, int degree, int percision);//设置m_curve

	/*GET方法*/
	CString getCurveName();
	CurveType getCurveType();
	int getCurveDegree();
	int getCurvePrec();

	afx_msg void OnEnChangeEdit01();

	virtual BOOL OnInitDialog();
private:
	CButton m_BEZIER_BUTTON;
public:
	CButton M_BSPLINE_BUTTON;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedRadioBezier01();
	afx_msg void OnBnClickedRadioBspline01();
};
