// CurveInfoView.cpp: 实现文件
//

#include <cstring>

#include "pch.h"
#include "CurveCG.h"
#include "CurveInfoView.h"
#include "MoreCurveInfo.h"


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
	ON_LBN_SELCHANGE(IDC_LIST_CURVES, &CurveInfoView::OnLbnSelchangeListCurves)
	//ON_LBN_DBLCLK(IDC_LIST_CURVES, &CurveInfoView::OnLbnDblclkListCurves)
//	ON_NOTIFY(HDN_ITEMDBLCLICK, 0, &CurveInfoView::OnHdnItemdblclickListCurves)
ON_NOTIFY(NM_DBLCLK, IDC_LIST_CURVES, &CurveInfoView::OnNMDblclkListCurves)
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
		m_curveList.InsertColumn(i, header[i], LVCFMT_LEFT, listRect.Width() * colWidth[i]);
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
Function:		addCurveInfo
Description:	新增一条曲线信息
Author:			刘崇鹏
Calls:			GetDocument
Input:
Return:
*************************************************/
void CurveInfoView::addCurveInfo(CurveType type, int degree, int count, int prec)
{
	CString idStr;
	int listLength = m_curveList.GetItemCount();
	int id;
	// 如果列表长度为0, id为0
	if (listLength == 0)id = 0;
	else {
		// 如果不为0, 则为最后一个元素id+1
		id = _wtoi(m_curveList.GetItemText(listLength - 1, 0)) + 1;
	}

	// 数据格式 { _T("id"), _T("type"), _T("degree"), _T("count"), _T("prec") };

	// 依次设置类型等
	CString type_, degree_, count_, prec_;

	// 格式化
	type_.Format(_T("%c"), type);
	degree_.Format(_T("%d"), degree);
	count_.Format(_T("%d"), count);
	prec_.Format(_T("%d"), prec);

	// 插入表格
	// 插入 第一列 id
	idStr.Format(_T("%d"), id);
	m_curveList.InsertItem(listLength, idStr);
	// 插入其他列
	m_curveList.SetItemText(listLength, 1, type_);
	m_curveList.SetItemText(listLength, 2, degree_);
	m_curveList.SetItemText(listLength, 3, count_);
	m_curveList.SetItemText(listLength, 4, prec_);

	// 选中新插入行
	m_curveList.SetItemState(listLength, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);   //选中行
	m_curveList.SetSelectionMark(listLength);
	m_curveList.SetFocus();
}



/*************************************************
Function:
Description:	关闭模态窗口后对线条记录进行修改
Author:			刘俊
Calls:          					// 被本函数调用的函数清单
Input:
		-CurveType type				//线条类型
		-int degree					//阶数
		-int count					//控制点数
		-int prec					//精度
Return:         void				// 函数返回值的说明
Others:         // 其它说明
*************************************************/


void CurveInfoView::changeCurveInfo(CurveType type, int degree, int prec)
{
	///TODO:关闭模态窗口后对线条记录进行修改
	int index = this->m_curveList.GetSelectionMark();
	// 依次设置类型等
	CString type_, degree_, count_, prec_;

	// 格式化
	type_.Format(_T("%c"), type);
	degree_.Format(_T("%d"), degree);
	prec_.Format(_T("%d"), prec);

	//设置文本
	m_curveList.SetItemText(index, 1, type_);
	m_curveList.SetItemText(index, 2, degree_);
	//m_curveList.SetItemText(index, 3, count_);
	m_curveList.SetItemText(index, 4, prec_);
	
}

void CurveInfoView::OnLbnSelchangeListCurves()
{
	// TODO: 在此添加控件通知处理程序代码
}


/*************************************************
Function:
Description:	双击线条记录弹出信息窗口并在窗口确认后更新线条信息
Author:			刘俊
Calls:          无					// 被本函数调用的函数清单
Input:
		-
Return:         void				// 函数返回值的说明
Others:         // 其它说明
*************************************************/
void CurveInfoView::OnNMDblclkListCurves(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	//得到当前项索引及文本
	int index = this->m_curveList.GetSelectionMark();
	CString str;
	str = m_curveList.GetItemText(index, 0);
	//模态窗口
	MoreCurveInfo pClass;
	pClass.setCurveName(str);
	
	//获取DrawView指针
	CRuntimeClass* pClass1 = RUNTIME_CLASS(DrawView);
	DrawView* pDraw = (DrawView*)GetView(pClass1);

	pClass.setCurve(pDraw->getCurveType(index), pDraw->getCurveDegree(index), pDraw->getCurvePrecision(index));
	//打开窗口
	pClass.DoModal();

	this->changeCurveInfo(pClass.getCurveType(), pClass.getCurveDegree(), pClass.getCurvePrec());
}


