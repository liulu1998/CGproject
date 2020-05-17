#pragma once
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
	int focus;						// 当前焦点, 即当前操作哪一条曲线

public:
	int getCurvesNum();				// 获取曲线条数
	int getFocus();					// 获取当前焦点
	void setFocus(int index);		// 更改当前焦点

	int addCurve();
	int addCurve(CurveType type, int degree, double precision);

	void deleteCurve(int index);	// 删除一条曲线
	CView* GetView(CRuntimeClass* pClass);	// 获取指定类型的View

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
