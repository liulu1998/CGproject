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
	DDX_Control(pDX, IDC_BUTTON1, m_addCurveDlg);
	DDX_Control(pDX, IDC_COMBO_DEGREE, m_degree_cbx);
	DDX_Control(pDX, IDC_SLIDER1, m_slider_precision);
	DDX_Control(pDX, IDC_EDIT1, m_edit_precision);
}

BEGIN_MESSAGE_MAP(AddCurveView, CFormView)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_RADIO_BEZIER, &AddCurveView::OnBnClickedRadioBezier)
	ON_BN_CLICKED(IDC_RADIO_BSPLINE, &AddCurveView::OnBnClickedRadioBspline)
	ON_BN_CLICKED(IDC_BUTTON_ADDCURVE, &AddCurveView::OnBnClickedButtonAddcurve)
	ON_WM_HSCROLL()
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

/*************************************************
Function:		OnSize
Description:	view自适应splitter大小
Author:			刘崇鹏
Calls:			GetClientRect
Input:
		- cx: int, x坐标
		- cy: int, y坐标
Return:
*************************************************/
void AddCurveView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	CRect shape;
	GetClientRect(shape);

	// 将内部内容自适应大小
	MoveWindow(shape);
}


/*************************************************
Function:		GetView
Description:	获取其它视图的指针，以获得其指针
Author:			刘崇鹏
Calls:			GetDocument
Input:
		- pClass: CRuntimeClass, 运行时类
Return:
		- pView: CView*, 要求类的指针
*************************************************/
CView* AddCurveView::GetView(CRuntimeClass* pClass) {
	CDocument* pDoc = (CDocument*)GetDocument();
	CView* pView;
	POSITION pos = pDoc->GetFirstViewPosition();
	while (pos != NULL)
	{
		pView = pDoc->GetNextView(pos);
		if (pView->IsKindOf(pClass))
		{
			return pView;
		}
	}
	return NULL;
}



/*************************************************
Function:		OnInitialUpdate
Description:	初始化 增加曲线 Dialog
Author:			刘陆，刘崇鹏
Calls:
Input:
Return:
*************************************************/
void AddCurveView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// 初始化 次数 下拉框
	CString degrees[] = { TEXT("1"), TEXT("2"), TEXT("3") };

	for (int i = 0; i < 3; i++)
		m_degree_cbx.AddString(degrees[i]);

	m_degree_cbx.SetCurSel(2);		// 默认三次

	// 处理 单选框, 默认选中 "B-样条曲线"
	CButton* radio = (CButton*)GetDlgItem(IDC_RADIO_BSPLINE);
	radio->SetCheck(1);

	// 初始化曲线精度滑动条
	m_slider_precision.SetRange(precisionMin, precisionMax);
	m_slider_precision.SetTicFreq(precisionInterval);
	m_slider_precision.SetPos(precisionDefault);

	// 初始化精度editCtrl
	CString precStr;
	precStr.Format(_T("%d"), precisionDefault);
	m_edit_precision.SetWindowTextW(precStr);

}


/*************************************************
Function:		OnBnClickedRadioBezier
Description:	处理 单选框Bezier 选中事件
Author:			刘陆
Calls:
Input:
Return:
*************************************************/
void AddCurveView::OnBnClickedRadioBezier()
{
	this->selectedType = Bezier;
}


/*************************************************
Function:		OnBnClickedRadioBezier
Description:	处理 单选框B-样条 选中事件
Author:			刘陆
Calls:
Input:
Return:
*************************************************/
void AddCurveView::OnBnClickedRadioBspline()
{
	this->selectedType = Spline;
}


/*************************************************
Function:		OnBnClickedButtonAddcurve
Description:	处理 "添加曲线" 按钮点击事件
Author:			刘陆, 刘崇鹏
Calls:
Input:
Return:
*************************************************/
void AddCurveView::OnBnClickedButtonAddcurve()
{
	// 次数下拉框
	int idx = m_degree_cbx.GetCurSel();
	CString str;
	m_degree_cbx.GetLBText(idx, str);

	int curDegree = _ttoi(str);		// 曲线次数 转为 整型

	// 获取精度
	CString data;
	m_edit_precision.GetWindowTextW(data);
	double precision;
	precision = 1.0 / _wtoi(data);

	// 获取 DrawView 指针
	CRuntimeClass* pClass = RUNTIME_CLASS(DrawView);
	DrawView* pDraw = (DrawView*)GetView(pClass);

	// DrawView 中新增一条曲线
	pDraw->addCurve(this->selectedType, curDegree, precision);

	// TODO: CurveInfoView 中 更新信息

	// 调试信息
	//int curvesNum = pDraw->getCurvesNum();

	//CString text;
	//text.Format(TEXT("%d,  %c,  %d"), curDegree, this->selectedType, curvesNum);
	//MessageBox(text);
}


void AddCurveView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CFormView::OnHScroll(nSBCode, nPos, pScrollBar);
	int scrollLimit, curPos;
	curPos = m_slider_precision.GetPos();

	// 当前滑动点，更新edit控件
	CString curPosStr;
	curPosStr.Format(_T("%.d"), curPos);
	m_edit_precision.SetWindowTextW(curPosStr);
	m_edit_precision.UpdateData(FALSE);

	double presicion = 1.0 / curPos;

}


//void AddCurveView::OnEnChangeEdit1()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，它将不
//	// 发送此通知，除非重写 CFormView::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//
//	// TODO:  在此添加控件通知处理程序代码
//
//
//}


BOOL AddCurveView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	if (WM_KEYFIRST <= pMsg->message && pMsg->message <= WM_KEYLAST)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			// 判断是不是来自编辑框的回车,是则

			if(GetDlgItem(IDC_EDIT1) == GetFocus())
			{
				GetDlgItem(IDC_SLIDER1)->SetFocus();
				CString rawData;
				m_edit_precision.GetWindowTextW(rawData);
				m_edit_precision.UpdateData(TRUE);
				CString newData, newDataBak;
				m_edit_precision.GetWindowTextW(newData);
				newDataBak = newData;
				// 判断是不是全数字
				if (newDataBak.TrimLeft(_T("0123456789")) != "") {
					// 非全是数字，弹框并回复数据
					MessageBox(_T("请输入数字"));
					m_edit_precision.SetWindowTextW(rawData);
					return CFormView::PreTranslateMessage(pMsg);
				} 
				else
				{
					// 全数字，判断是否超界，并赋值sliderBar
					int precision = _wtoi(newData);
					if (precision < precisionMin) {
						// 若小于100（最小值），EditCtrl回复100，scrollBar调至最小
						newData.Format(_T("%d"), precisionMin);
						m_edit_precision.SetWindowTextW(newData);
						m_slider_precision.SetPos(precisionMin);
					}
					else if (precision > precisionMax) {
						// 大于1000，类似于上
						newData.Format(_T("%d"), precisionMax);
						m_edit_precision.SetWindowTextW(newData);
						m_slider_precision.SetPos(precisionMax);
					}
					else {
						m_slider_precision.SetPos(_wtoi(newData));
						// 焦点到添加曲线上，回车就可添加曲线
						GetDlgItem(IDC_BUTTON_ADDCURVE)->SetFocus();
					}
				}

				return CFormView::PreTranslateMessage(pMsg);

			}


		}
	}

	return CFormView::PreTranslateMessage(pMsg);
}
