// DrawView.cpp: 实现文件
//

#include "pch.h"
#include "CurveCG.h"
#include "DrawView.h"


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


// DrawView 消息处理程序
