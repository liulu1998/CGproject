#pragma once
#include <afxext.h>
class MySplitter :
	public CSplitterWnd
{
public:
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnNcHitTest(CPoint point);
	virtual void OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rect);
};

