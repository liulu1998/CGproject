// CurvePointView.cpp: 实现文件
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
	// 获取 CurvePointView
	CRuntimeClass* pClass = RUNTIME_CLASS(CurvePointView);
	// 获取view中的列表
	CListCtrl* list = &((CurvePointView*)GetView(pClass))->m_pointList;

	pClass = RUNTIME_CLASS(DrawView);
	DrawView* pDraw = (DrawView*)GetView(pClass);
	// 清空listbox
	int listLength = list->GetItemCount();
	for (int i = 0; i <= listLength; i++)
	{
		list->DeleteItem(i);
	}

	// 输出选定的curve的点
	CString data;
	int num = pDraw->getCtrlPointsNumOfCurve();

	for (int j = 0; j < num; ++j) {
		list->SetItemState(listLength, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);   //选中行
		list->SetSelectionMark(listLength);

		CP2 curPoint = pDraw->getCtrlPointFromCurve(j);

		CString x, y, id;

		id.Format(_T("%d"), j);
		x.Format(_T("%d"), curPoint.x);
		y.Format(_T("%d"), curPoint.y);

		list->SetItemText(j, 0, id);
		list->SetItemText(j, 1, x);
		list->SetItemText(j, 2, y);

	}
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
	// FIXME: 点击删除按钮后, 本 dialog 崩溃

	CRuntimeClass* pClass = RUNTIME_CLASS(CurvePointView);
	// 获取 CurvePointView
	CurvePointView* pCPV = (CurvePointView*)GetView(pClass);
	// 获取view中的列表
	CListCtrl* list = &pCPV->m_pointList;
	// 获取 DrawView
	pClass = RUNTIME_CLASS(DrawView);
	DrawView* pDraw = (DrawView*)GetView(pClass);

	int point_index = list->GetSelectedCount();

	// 删除控制点
	pDraw->deleteCtrlPointFromCurve(point_index);

	pCPV->showCurvePoints();

	// 绘制
	CDC* pDC = GetDC();
	pDraw->OnDraw(pDC);
	ReleaseDC(pDC);
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
}
