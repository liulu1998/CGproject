﻿
// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "CurveCG.h"

#include "MainFrm.h"
#include "AddCurveView.h"
#include "CurveInfoView.h"
#include "CurvePointView.h"
#include "DrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// 设置程序左上角logo，IDI_ICON_LOGO为图标相应的资源ID
	SetClassLong(m_hWnd, GCL_HICON, (LONG)AfxGetApp()->LoadIconW(IDI_ICON_LOGO));

	// 设置右侧标题
	SetTitle(_T("图不行学小组出品"));

	// 设置窗口大小
	MoveWindow(0, 0, 1400, 800);

	// 设置居中窗口
	CenterWindow();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	//cs.style = cs.style & ~WS_MAXIMIZEBOX;	// 不能最大化，但可以拖拽改变大小
	cs.style = WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX;		// 不能最大化，且不可拖拽改变大小
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	//return CFrameWnd::OnCreateClient(lpcs, pContext);

	// 拆成1行1列
	m_spliter.CreateStatic(this, 1, 2, WS_CHILD | WS_VISIBLE | WS_BORDER);
	// 将左边列拆成3行
	m_LeftSpliter.CreateStatic(&m_spliter, 3, 1, WS_CHILD | WS_VISIBLE, m_spliter.IdFromRowCol(0, 0));

	CRect shape;
	GetClientRect(shape);

	// 输出窗口大小
	//CString str;
	//str.Format(_T("%d %d"), shape.Width(), shape.Height());
	//MessageBox(str);

	// 左右侧具体显示内容
	m_LeftSpliter.CreateView(0, 0, RUNTIME_CLASS(AddCurveView), CSize(shape.Width() / 5, shape.Height() / 3), pContext);
	m_LeftSpliter.CreateView(1, 0, RUNTIME_CLASS(CurveInfoView), CSize(shape.Width() / 5, shape.Height() / 3), pContext);
	m_LeftSpliter.CreateView(2, 0, RUNTIME_CLASS(CurvePointView), CSize(shape.Width() / 5, shape.Height() / 3), pContext);
	m_spliter.CreateView(0, 1, RUNTIME_CLASS(DrawView), CSize(shape.Width() * 4 / 5, shape.Height()), pContext);
	//m_spliter.CreateView(0, 1, RUNTIME_CLASS(DrawView), CSize(1139, 700), pContext);
	//m_LeftSpliter.CreateView(0, 0, RUNTIME_CLASS(AddCurveView), CSize(284, 233), pContext);
	//m_LeftSpliter.CreateView(1, 0, RUNTIME_CLASS(CurveListView), CSize(284, 233), pContext);
	//m_LeftSpliter.CreateView(2, 0, RUNTIME_CLASS(CurvePointView), CSize(284, 233), pContext);

	m_spliter.SetColumnInfo(0, shape.Width() / 5, 10);
	m_spliter.SetColumnInfo(1, shape.Width()*4 / 5, 10);
	m_LeftSpliter.SetRowInfo(0, shape.Height() / 3, 10);
	m_LeftSpliter.SetRowInfo(1, shape.Height() / 3, 10);
	m_LeftSpliter.SetRowInfo(2, shape.Height() / 3, 10);
	return TRUE;	// 自己拆分
}
