﻿// CurvePointView.cpp: 实现文件
//

#include "pch.h"
#include "CurveCG.h"
#include "CurvePointView.h"


// CurvePointView

IMPLEMENT_DYNCREATE(CurvePointView, CFormView)

CurvePointView::CurvePointView()
	: CFormView(IDD_DLG_CURBEPOINT)
{

}

CurvePointView::~CurvePointView()
{
}

void CurvePointView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_POINTS, m_pointList);
}

BEGIN_MESSAGE_MAP(CurvePointView, CFormView)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_DELCURVE, &CurvePointView::OnBnClickedButtonDelcurve)
	ON_BN_CLICKED(IDC_BUTTON_ADDPOINT, &CurvePointView::OnBnClickedButtonAddpoint)
END_MESSAGE_MAP()


// CurvePointView 诊断

#ifdef _DEBUG
void CurvePointView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CurvePointView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CurvePointView 消息处理程序

/*************************************************
Function:		OnSize
Description:	view自适应splitter大小
Author:			刘崇鹏
Calls:			GetClientRect
Input:
		- cx: int, x坐标
		- cy: int, y坐标
Return:
*************************************************/
void CurvePointView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	//CRect shape;
	//GetClientRect(shape);

	//// 将内部内容自适应大小
	//MoveWindow(shape);
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
CView* CurvePointView::GetView(CRuntimeClass* pClass) {
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
Function:		showCurvePoints
Description:	列出指定曲线的点信息
Author:			韩继锋
Calls:			GetView, getCtrlPoint
Input:
		- c: Curve, 曲线类
Return:
*************************************************/
void CurvePointView::showCurvePoints() {
	// 获取 DrawView 指针
	CRuntimeClass* pClass = RUNTIME_CLASS(DrawView);
	DrawView* pDraw = (DrawView*)GetView(pClass);

	// 清空 listbox
	this->resetList();

	// 输出 焦点曲线 的所有控制点
	CString data;
	int num = pDraw->getCtrlPointsNumOfCurve();

	for (int j = 0; j < num; j++) {
		// 当前控制点
		CP2 curPoint = pDraw->getCtrlPointFromCurve(j);

		CString x, y, id;
		// 注意: 需要强制类型转换
		id.Format(_T("%d"), j);
		x.Format(_T("%d"), (int)curPoint.x);
		y.Format(_T("%d"), (int)curPoint.y);

		this->m_pointList.InsertItem(j, id);
		this->m_pointList.SetItemText(j, 1, x);
		this->m_pointList.SetItemText(j, 2, y);
	}
	// 选中最后一行
	int listLength = this->m_pointList.GetItemCount() - 1;
	this->m_pointList.SetItemState(listLength, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
	this->m_pointList.SetSelectionMark(listLength);
}


/*************************************************
Function:		OnBnClickedButtonDelcurve
Description:	点击删除键来删除点
Author:			韩继锋
Calls:			GetView, getCurve, getFocus, showCurvePoints
Input:
Return:
*************************************************/
void CurvePointView::OnBnClickedButtonDelcurve()
{
	// 获取 选中行 索引
	int point_index = this->m_pointList.GetNextItem(-1, LVIS_SELECTED);

	// 获取 DrawView 指针
	CRuntimeClass* pClass = RUNTIME_CLASS(DrawView);
	DrawView* pDraw = (DrawView*)GetView(pClass);

	// 删除控制点
	if (!pDraw->deleteCtrlPointFromCurve(point_index))
		return;

	// 清空 listCtrl, 重新生成 listCtrl
	this->resetList();
	this->showCurvePoints();

	// 重新绘制 右部区域
	pDraw->RedrawWindow();
}


//添加按钮事件，目前似乎用不到这个按钮
void CurvePointView::OnBnClickedButtonAddpoint() {
	// TODO: 在此添加控件通知处理程序代码

}


void CurvePointView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// 初始化列表
	// 设置表头
	CRect listRect;
	m_pointList.GetWindowRect(listRect);

	CString header[] = { _T("id"), _T("x"), _T("y") };
	float colWidth[] = { 0.2, 0.4, 0.4 };
	for (int i = 0; i < 3; i++)
	{
		m_pointList.InsertColumn(i, header[i], LVCFMT_LEFT, listRect.Width() * colWidth[i]);
	}
	// 点击则选中整行, 整行高亮
	this->m_pointList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);
}


/*************************************************
Function:		addPoint
Description:	向控制点列表中增加一条控制点信息
Author:			刘陆
Calls:
Input:
Return:
Other:
*************************************************/
void CurvePointView::addPoint(const CP2& point) {
	int n = this->m_pointList.GetItemCount();

	CString index, x, y;
	index.Format(_T("%d"), n);
	x.Format(_T("%d"), (int)point.x);
	y.Format(_T("%d"), (int)point.y);

	this->m_pointList.InsertItem(n, index);
	this->m_pointList.SetItemText(n, 1, x);
	this->m_pointList.SetItemText(n, 2, y);

	int listLength = this->m_pointList.GetItemCount() - 1;
	this->m_pointList.SetItemState(listLength, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
	this->m_pointList.SetSelectionMark(listLength);
}


/*************************************************
Function:		resetList
Description:	清空 控制点列表
Author:			刘陆
Calls:
Input:
Return:
*************************************************/
void CurvePointView::resetList() {
	this->m_pointList.DeleteAllItems();
}
