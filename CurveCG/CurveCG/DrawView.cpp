// DrawView.cpp: 实现文件
//

#include "pch.h"
#include "CurveCG.h"
#include "DrawView.h"
#include "CP2.h"
#include "Curve.h"

#include <vector>

typedef std::vector<Curve>::iterator PCurves;


// DrawView

IMPLEMENT_DYNCREATE(DrawView, CView)

DrawView::DrawView()
{

}

DrawView::~DrawView()
{
}

BEGIN_MESSAGE_MAP(DrawView, CView)
	//	ON_WM_LBUTTONDBLCLK()
	//ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// DrawView 绘图

void DrawView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO:  在此添加绘制代码

	// 双缓冲绘图
	BufferDraw(pDC);
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
int DrawView::getCurvesNum() const {
	return (int)this->curves.size();
}


/*************************************************
Function:		getCurvesNum
Description:	获得当前曲线焦点, 即操作的曲线在 curves 中的索引
Author:			刘陆
Return:			int
*************************************************/
int DrawView::getFocus() const {
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
Function:		addCtrlPoint
Description:	向焦点的曲线 增加控制点
Author:			刘陆
Input:
			- point: CP2&, 要删除的点
Return:
*************************************************/
void DrawView::addCtrlPoint2Curve(CP2 point) {
	int idx = this->getFocus();
	if (idx != -1)
		this->curves[idx].addCtrlPoint(point);
}


/*************************************************
Function:		deleteCtrlPointFromCurve
Description:	从焦点的曲线 删除控制点
Author:			刘陆
Input:
			- index: int, 删除的控制点 在 焦点曲线中的索引
Return:
*************************************************/
bool DrawView::deleteCtrlPointFromCurve(int index) {
	int f = this->getFocus();
	if (index >= this->curves[f].getCtrlPointsNum())
		return false;

	this->curves[f].deleteCtrlPoint(index);
	return true;
}


/*************************************************
Function:		addCurve
Description:	新增一条曲线, 默认在尾部追加
Author:			刘陆
Calls:
Input:
	- type: CurveType, 曲线类型, Bezier 或 Spline
	- degree: int, 曲线次数
	- precision: int, 采样精度
Return:			int, 新创建的曲线在 curves 中的索引
Other:			添加曲线后, 默认的焦点 切换为 新增曲线
*************************************************/
int DrawView::addCurve(CurveType type, int degree, int precision) {
	Curve c = Curve(type, degree, precision);
	this->curves.push_back(c);
	this->setFocus(this->getCurvesNum() - 1);		// 切换焦点
	return this->getCurvesNum() - 1;
}


/*************************************************
Function:		getCtrlPointsNumOfCurve
Description:	获得焦点曲线的 控制点数
Author:			刘陆
Calls:
Input:
Return:			int
*************************************************/
int DrawView::getCtrlPointsNumOfCurve() const {
	int f = this->getFocus();
	return this->curves[f].getCtrlPointsNum();
}


/*************************************************
Function:		getCtrlPointFromCurve
Description:	焦点的曲线 获得控制点
Author:			刘陆
Calls:
Input:
			- index: int, 控制点在 焦点曲线 中的索引
Return:			CP2
*************************************************/
CP2 DrawView::getCtrlPointFromCurve(int index) const {
	int f = this->getFocus();
	if (index >= this->curves[f].getCtrlPointsNum())
		throw "索引越界";
	return this->curves[f].getCtrlPoint(index);
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


/*************************************************
Function:		GetView
Description:	获取其它视图的指针，以获得其指针
Author:			刘崇鹏
Calls:			GetDocument
Input:
		- pClass: CRuntimeClass, 运行时类
Return:
		- pView: CView*, 要求类的指针
*************************************************/
CView* DrawView::GetView(CRuntimeClass* pClass) {
	CDocument* pDoc = (CDocument*)GetDocument();
	CView* pView;
	POSITION pos = pDoc->GetFirstViewPosition();
	while (pos != NULL)
	{
		pView = pDoc->GetNextView(pos);
		if (pView->IsKindOf(pClass))
		{
			return pView;
		}
	}
	return NULL;
}


/*************************************************
Function:		getCurveDegree
Description:	获取曲线次数
Input:
		- index: int, 曲线在 curves 中的索引
Return:			int
*************************************************/
int DrawView::getCurveDegree(int index) const {
	if (index >= this->getCurvesNum())
		throw "索引越界";

	return this->curves[index].getCurveDegree();
}


/*************************************************
Function:		getCurveType
Description:	获取曲线类型
Input:
		- index: int, 曲线在 curves 中的索引
Return:			CurveType
*************************************************/
CurveType DrawView::getCurveType(int index) const {
	if (index >= this->getCurvesNum())
		throw "索引越界";
	return this->curves[index].getCurveType();
}


/*************************************************
Function:		getCurvePrecision
Description:	获取曲线精度
Input:
		- index: int, 曲线在 curves 中的索引
Return:			double
*************************************************/
int DrawView::getCurvePrecision(int index) const {
	if (index >= this->getCurvesNum())
		throw "索引越界";
	return this->curves[index].getCurvePrecision();
}


/*************************************************
Function:
Description:	更改一条线条的信息
Author:			刘俊
Calls:          无					// 被本函数调用的函数清单
Input:
		-index						//索引
		-type						//线条类型
		-degree						//阶数
		-precision					//精度
Return:         void				// 函数返回值的说明
Others:         // 其它说明
*************************************************/


int DrawView::changeCurveInfo(int index, CurveType type, int degree, int prec)
{
	if (index<0)
		return 0;

	this->curves[index].changeCurveInfo(type,degree,prec);

	return 1;
}


// DrawView 消息处理程序


/*************************************************
Function:		OnLButtonDown
Description:	在白板处点击时，在点列表中增加新的点信息,并更新选中状态
Author:			刘崇鹏, 刘陆
Calls:			GetView
Input:
		- nFlags: nFlags, 标志位
		- point: CPoint, 点击的点位置
Return:
		- pView: CView*, 要求类的指针
*************************************************/
void DrawView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CView::OnLButtonDown(nFlags, point);

	// 未创建曲线
	if (this->getCurvesNum() == 0) {
		MessageBox(TEXT("请先创建曲线"));
		return;
	}

	// 获取 PointView 指针
	CRuntimeClass* pClass = RUNTIME_CLASS(CurvePointView);
	CurvePointView* pPointView = (CurvePointView*)GetView(pClass);

	// 构造数据
	//CString data;

	// 转为 CP2
	CP2 curPoint = CP2((double)point.x, (double)point.y);

	// CurveView 框中新增 控制点信息
	pPointView->addPoint(curPoint);

	// 继续和Curve类联动, 如在ctrlPoint中加入点
	// 当前焦点
	int curFocus = this->getFocus();
	// 加入控制点
	this->addCtrlPoint2Curve(curPoint);

	// 绘制
	//CDC* pDC = GetDC();
	this->RedrawWindow();
	//ReleaseDC(pDC);
}


BOOL DrawView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}


/*************************************************
Function:		BufferDraw
Description:	双缓冲绘图
Author:			刘陆
Calls:			drawCurve,
Input:
		- pDC: CDC*
Return:
*************************************************/
void DrawView::BufferDraw(CDC* pDC) {
	BITMAP bmp;					// 储存位图信息的结构体
	CRect rect;
	GetClientRect(rect);		// 获取客户区域的矩形

	bufferdc.CreateCompatibleDC(NULL);		//创建兼容DC
	bufferbmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());		//创建兼容位图
	//bufferdc.SelectObject(&bufferbmp);		// 将位图选入内存区域
	CBitmap* pOldBit = bufferdc.SelectObject(&bufferbmp);
	bufferbmp.GetBitmap(&bmp);				// 获取内存位图的信息

	// >>> 在此处添加绘制代码

	// 白色背景
	bufferdc.FillSolidRect(&rect, RGB(255, 255, 255));

	// 绘制网格
	drawGrid(&bufferdc, rect);

	// 逐条绘制曲线
	for (Curve c : this->curves)
		c.drawCurve(&bufferdc);

	// <<< 添加绘制代码

	SetStretchBltMode(pDC->m_hDC, STRETCH_HALFTONE);
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &bufferdc, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);//将内存中的内容复制到设备
	bufferdc.DeleteDC();                                       //删除DC
	bufferbmp.DeleteObject();                                  //删除位图
}


/*************************************************
Function:		drawGrid
Description:	绘制网格线
Author:			刘陆
Calls:
Input:
		- pDC: CDC*
Return:
*************************************************/
void DrawView::drawGrid(CDC* pDC, const CRect& rect) {
	CPen pen, * pOldPen;
	pen.CreatePen(PS_DASHDOT, 1, RGB(191, 191, 191));		// 灰色 点划线画笔
	pOldPen = pDC->SelectObject(&pen);

	// 竖线
	for (int i = 0; i < rect.Width(); i += 30) {
		pDC->MoveTo(i, 0);
		pDC->LineTo(i, rect.Height());
	}

	// 横线
	for (int j = 0; j < rect.Height(); j += 30) {
		pDC->MoveTo(0, j);
		pDC->LineTo(rect.Width(), j);
	}

	pDC->SelectObject(pOldPen);
}
