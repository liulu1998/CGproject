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
	DDX_Control(pDX, IDC_LIST_CURVES, m_curveList);
}

BEGIN_MESSAGE_MAP(CurveInfoView, CFormView)
	ON_WM_SIZE()
	ON_LBN_SELCHANGE(IDC_LIST_CURVES, &CurveInfoView::OnLbnSelchangeListCurves)
	ON_LBN_DBLCLK(IDC_LIST_CURVES, &CurveInfoView::OnLbnDblclkListCurves)
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

	CRect shape;
	GetClientRect(shape);

	// 将内部内容自适应大小
	MoveWindow(shape);
}


void CurveInfoView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

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
Function:
Description:	在CurveInfoView中增加一条线记录
Author:			刘俊
Calls:          无					// 被本函数调用的函数清单
Input:
		-index					//线条索引
Return:         int				// 记录索引
Others:         // 其它说明
*************************************************/


int CurveInfoView::AddCurve(int index)
{
	this->m_curveList.InsertString(index, TEXT("未命名曲线"));
	this->m_curveList.SetCurSel(index);
	return index;
}

void CurveInfoView::OnLbnSelchangeListCurves()
{
	// TODO: 在此添加控件通知处理程序代码
}



/*************************************************
Function:
Description:	双击线条记录弹出信息窗口
Author:			刘俊
Calls:          无					// 被本函数调用的函数清单
Input:
		-
Return:         void				// 函数返回值的说明
Others:         // 其它说明
*************************************************/
void CurveInfoView::OnLbnDblclkListCurves()
{
	// TODO: 双击左键弹出信息窗口
	//得到当前项索引及文本
	int index = this->m_curveList.GetCurSel();
	CString str;
	int len = this->m_curveList.GetTextLen(index);
	this->m_curveList.GetText(index, str.GetBuffer(len));
	MoreCurveInfo pClass;
	pClass.curveName = str;
	pClass.DoModal();

}
