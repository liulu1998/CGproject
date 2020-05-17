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


void CurvePointView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect shape;
	GetClientRect(shape);

	// 将内部内容自适应大小
	MoveWindow(shape);
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