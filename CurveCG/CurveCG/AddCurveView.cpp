// AddCurveView.cpp: 实现文件
//

#include "pch.h"
#include "CurveCG.h"
#include "AddCurveView.h"


// AddCurveView

IMPLEMENT_DYNCREATE(AddCurveView, CFormView)

AddCurveView::AddCurveView()
	: CFormView(IDD_DLG_ADDCURVE)
{

}

AddCurveView::~AddCurveView()
{
}

void AddCurveView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_addCurveDlg);
}

BEGIN_MESSAGE_MAP(AddCurveView, CFormView)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// AddCurveView 诊断

#ifdef _DEBUG
void AddCurveView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void AddCurveView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// AddCurveView 消息处理程序


void AddCurveView::OnSize(UINT nType, int cx, int cy)
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
CView* AddCurveView::GetView(CRuntimeClass* pClass) {
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