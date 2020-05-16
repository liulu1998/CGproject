
// CurveCGView.cpp: CCurveCGView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CurveCG.h"
#endif

#include "CurveCGDoc.h"
#include "CurveCGView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCurveCGView

IMPLEMENT_DYNCREATE(CCurveCGView, CView)

BEGIN_MESSAGE_MAP(CCurveCGView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CCurveCGView 构造/析构

CCurveCGView::CCurveCGView() noexcept
{
	// TODO: 在此处添加构造代码

}

CCurveCGView::~CCurveCGView()
{
}

BOOL CCurveCGView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CCurveCGView 绘图

void CCurveCGView::OnDraw(CDC* /*pDC*/)
{
	CCurveCGDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CCurveCGView 打印

BOOL CCurveCGView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CCurveCGView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CCurveCGView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CCurveCGView 诊断

#ifdef _DEBUG
void CCurveCGView::AssertValid() const
{
	CView::AssertValid();
}

void CCurveCGView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCurveCGDoc* CCurveCGView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCurveCGDoc)));
	return (CCurveCGDoc*)m_pDocument;
}
#endif //_DEBUG


// CCurveCGView 消息处理程序
