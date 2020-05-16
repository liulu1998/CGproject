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
}

BEGIN_MESSAGE_MAP(AddCurveView, CFormView)
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
