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
}

BEGIN_MESSAGE_MAP(CurveInfoView, CFormView)
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
