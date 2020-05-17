#include "pch.h"
#include "MySplitter.h"
BEGIN_MESSAGE_MAP(MySplitter, CSplitterWnd)
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()


LRESULT MySplitter::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值


	return HTNOWHERE;
	//return CSplitterWnd::OnNcHitTest(point);

}

// 绘制分割条，使之变细
void MySplitter::OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rect)
{
	// TODO: 在此添加专用代码和/或调用基类

	//CSplitterWnd::OnDrawSplitter(pDC, nType, rect);
	if (nType == splitBox) {
		CSplitterWnd::OnDrawSplitter(pDC, splitBorder, rect);
		return;
	}

	CSplitterWnd::OnDrawSplitter(pDC, nType, rect);

}
