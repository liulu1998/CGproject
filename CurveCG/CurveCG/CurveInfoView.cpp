// CurveInfoView.cpp: 实现文件
//

#include "pch.h"
#include "CurveCG.h"
#include "CurveInfoView.h"


// CurveInfoView

IMPLEMENT_DYNCREATE(CurveInfoView, CFormView)

CurveInfoView::CurveInfoView()
	: CFormView(IDD_DLG_CURVEINFO)
{

}

CurveInfoView::~CurveInfoView()
{
}

void CurveInfoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_LIST_CURVES, m_curveList);
	DDX_Control(pDX, IDC_LIST_CURVES, m_curveList);
}

BEGIN_MESSAGE_MAP(CurveInfoView, CFormView)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CurveInfoView 诊断

#ifdef _DEBUG
void CurveInfoView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CurveInfoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CurveInfoView 消息处理程序

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
void CurveInfoView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	//CRect shape;
	//GetClientRect(shape);

	//// 将内部内容自适应大小
	//MoveWindow(shape);
}


void CurveInfoView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// 曲线列表初始化, 设置整行选中
	m_curveList.SetExtendedStyle(m_curveList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	// 设置基本格式
	// 设置表头
	CRect listRect;
	m_curveList.GetWindowRect(listRect);

	CString header[] = { _T("id"), _T("type"), _T("degree"), _T("count"), _T("prec") };
	float colWidth[] = { 0.14, 0.18, 0.22, 0.2, 0.26 };
	for (int i = 0; i < 5; i++)
	{
		m_curveList.InsertColumn(i, header[i], LVCFMT_LEFT, listRect.Width()*colWidth[i]);
	}





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
CView* CurveInfoView::GetView(CRuntimeClass* pClass) {
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
Function:		GetView
Description:	获取其它视图的指针，以获得其指针
Author:			刘崇鹏
Calls:			GetDocument
Input:
		- pClass: CRuntimeClass, 运行时类
Return:
		- pView: CView*, 要求类的指针
*************************************************/
void CurveInfoView::addCurveInfo(Curve newCurve)
{
	CString idStr;
	int listLenth = m_curveList.GetItemCount();
	int id;
	// 如果列表长度为0, id为0
	if (listLenth == 0)id = 0;
	else {
		// 如果不为0, 则为最后一个元素id+1
		id = _wtoi(m_curveList.GetItemText(listLenth - 1, 0)) + 1;
	}
	// 数据格式 { _T("id"), _T("type"), _T("degree"), _T("count"), _T("prec") };

	// 插入id
	idStr.Format(_T("%d"), id);
	m_curveList.InsertItem(listLenth, idStr);
	// 依次设置类型等
	CString type, degree, count, prec;
	type.Format(_T("%c"), CurveType(newCurve.getCurveType()));
	degree.Format(_T("%d"), newCurve.getCurveDegree());
	count.Format(_T("%d"), newCurve.getCtrlPointsNum());
	prec.Format(_T("%.3f"), newCurve.getCurvePrecision());
	// 插入表格
	m_curveList.SetItemText(listLenth, 1, type);
	m_curveList.SetItemText(listLenth, 2, degree);
	m_curveList.SetItemText(listLenth, 3, count);
	m_curveList.SetItemText(listLenth, 4, prec);
	// 选中新插入行
	m_curveList.SetItemState(listLenth, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);   //选中行
	m_curveList.SetSelectionMark(listLenth);
	m_curveList.SetFocus();

}