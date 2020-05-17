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


void CurveInfoView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect shape;
	GetClientRect(shape);

	// 将内部内容自适应大小
	MoveWindow(shape);
}


void CurveInfoView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	m_curveList.AddString(_T("赛高！！"));
	m_curveList.AddString(_T("赛高！！"));
	m_curveList.AddString(_T("赛高！！"));
	m_curveList.AddString(_T("赛高！！"));
}
