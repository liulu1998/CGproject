#include "pch.h"
#include "MySplitter.h"
BEGIN_MESSAGE_MAP(MySplitter, CSplitterWnd)
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()


LRESULT MySplitter::OnNcHitTest(CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ


	return HTNOWHERE;
	//return CSplitterWnd::OnNcHitTest(point);

}

// ���Ʒָ�����ʹ֮��ϸ
void MySplitter::OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rect)
{
	// TODO: �ڴ����ר�ô����/����û���

	//CSplitterWnd::OnDrawSplitter(pDC, nType, rect);
	if (nType == splitBox) {
		CSplitterWnd::OnDrawSplitter(pDC, splitBorder, rect);
		return;
	}

	CSplitterWnd::OnDrawSplitter(pDC, nType, rect);

}
