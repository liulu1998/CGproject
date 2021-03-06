﻿#pragma once
#include <vector>
#include "Curve.h"
#include "viewList.h"

// DrawView 视图

class DrawView : public CView
{
	DECLARE_DYNCREATE(DrawView)

protected:
	DrawView();           // 动态创建所使用的受保护的构造函数
	virtual ~DrawView();

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

private:
	std::vector<Curve> curves;		// 多条曲线
	int focus = -1;					// 当前焦点, 即当前操作哪一条曲线

	CDC bufferdc;					// 用于双缓冲的DC
	CBitmap bufferbmp;				// 承载临时对象的位图

	bool map[1800][1500];			// 对应坐标是否有控制点

public:
	int getCurvesNum() const;				// 获取曲线条数

	int getFocus() const;					// 获取当前焦点
	void setFocus(int index);		// 更改当前焦点

	void addCtrlPoint2Curve(CP2);						// 向焦点的曲线 增加控制点
	bool deleteCtrlPointFromCurve(int index);		    // 从焦点的曲线 删除控制点

	int getCtrlPointsNumOfCurve() const;						// 获得焦点曲线的 控制点数
	CP2 getCtrlPointFromCurve(int index) const;				// 从焦点的曲线 获得控制点

	int addCurve();
	int addCurve(CurveType type, int degree, int precision);
	int addCurve(Curve);

	void deleteCurve(int index);			// 删除一条曲线
	CView* GetView(CRuntimeClass* pClass);	// 获取指定类型的View

	void BufferDraw(CDC* pDC);				// 双缓冲绘图
	void drawGrid(CDC* pDC, const CRect&);						// 绘制网格

	int getCurveDegree(int index) const;
	int getCurveDegree();
	CurveType getCurveType(int index) const;
	CurveType getCurveType();
	int getCurvePrecision(int index) const;
	int getCurvePrecision();
	std::vector<EquationInfo> getCurveEquationInfo(int index) const;

	bool setCurveInfo(int index, CurveType type, int degree, int precision);	// 改变curve信息
	bool setCurveType(int index, CurveType type);
	bool setDegree(int index, int degree);
	bool setPrecision(int index, int precision);


	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
