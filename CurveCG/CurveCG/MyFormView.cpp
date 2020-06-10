// MyFormView.cpp: 实现文件
//

#include "pch.h"
#include "CurveCG.h"
#include "MyFormView.h"


// MyFormView

IMPLEMENT_DYNCREATE(MyFormView, CFormView)

MyFormView::MyFormView()
	: CFormView(IDD_MyFormView)
{

}

MyFormView::~MyFormView()
{
}

void MyFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(MyFormView, CFormView)
END_MESSAGE_MAP()


// MyFormView 诊断

#ifdef _DEBUG
void MyFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void MyFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// MyFormView 消息处理程序
