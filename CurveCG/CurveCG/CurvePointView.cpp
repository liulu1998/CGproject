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
}

BEGIN_MESSAGE_MAP(CurvePointView, CFormView)
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
