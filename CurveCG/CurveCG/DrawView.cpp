// DrawView.cpp: 实现文件
//

#include "pch.h"
#include "CurveCG.h"
#include "DrawView.h"
#include "Curve.h"


// DrawView

IMPLEMENT_DYNCREATE(DrawView, CView)

DrawView::DrawView()
{

}

DrawView::~DrawView()
{
}

BEGIN_MESSAGE_MAP(DrawView, CView)
END_MESSAGE_MAP()


// DrawView 绘图

void DrawView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO:  在此添加绘制代码
}


// DrawView 诊断

#ifdef _DEBUG
void DrawView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void DrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


/*************************************************
Function:		getCurvesNum
Description:	获得曲线条数
Author:			刘陆
Calls:
Input:
Return:			int
*************************************************/
int DrawView::getCurvesNum() {
	return (int)this->curves.size();
}


/*************************************************
Function:		getCurvesNum
Description:	获得当前曲线焦点, 即操作的曲线在 curves 中的索引
Author:			刘陆
Return:			int
*************************************************/
int DrawView::getFocus() {
	return this->focus;
}


/*************************************************
Function:		setCurvesNum
Description:	更改当前曲线焦点, 即切换当前操作的曲线
Author:			刘陆
Return:
*************************************************/
void DrawView::setFocus(int index) {
	if (index >= this->getCurvesNum())
		return;
	this->focus = index;
}


/*************************************************
Function:		addCurve
Description:	新增一条曲线, 默认在尾部追加
Author:			刘陆
Calls:
Input:
	- type: CurveType, 曲线类型, Bezier 或 Spline
	- degree: int, 曲线次数
	- precision: double, 采样精度
Return:			int, 新创建的曲线在 curves 中的索引
Other:			添加曲线后, 默认的焦点 切换为 新增曲线
*************************************************/
int DrawView::addCurve(CurveType type, int degree, double precision) {
	Curve c = Curve(type, degree, precision);
	this->curves.push_back(c);
	this->setFocus(this->getCurvesNum() - 1);		// 切换焦点
	return this->getCurvesNum() - 1;
}


/*************************************************
Function:		addCurve
Description:	新增一条曲线, 全部默认参数
Author:			刘陆
Calls:
Input:
Return:			int, 新创建的曲线在 curves 中的索引
Other:			添加曲线后, 默认的焦点 切换为 新增曲线
*************************************************/
int DrawView::addCurve() {
	Curve c = Curve();
	this->curves.push_back(c);
	this->setFocus(this->getCurvesNum() - 1);		// 切换焦点
	return this->getCurvesNum() - 1;
}


/*************************************************
Function:		deleteCurve
Description:	删除一条曲线
Author:			刘陆
Calls:
Input:
		- index: int, 曲线的索引
Return:
*************************************************/
void DrawView::deleteCurve(int index) {
	if (index >= this->getCurvesNum())
		return;
	curves.erase(curves.begin() + index);
}


// DrawView 消息处理程序
