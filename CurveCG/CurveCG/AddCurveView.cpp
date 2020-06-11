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
	ON_EN_CHANGE(IDC_EDIT1, &AddCurveView::OnEnChangeEdit1)
	//	ON_EN_UPDATE(IDC_EDIT1, &AddCurveView::OnUpdateEdit1)
	ON_EN_SETFOCUS(IDC_EDIT1, &AddCurveView::OnSetfocusEdit1)
	ON_EN_KILLFOCUS(IDC_EDIT1, &AddCurveView::OnKillfocusEdit1)
	//ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_OPENCURVE, &AddCurveView::OnClickedOpencurve)
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
Description:	view 自适应splitter大小
Author:			刘崇鹏
Calls:			GetClientRect
Input:
		- cx: int, x 坐标
		- cy: int, y 坐标
Return:
*************************************************/
void AddCurveView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	//CRect shape;
	//GetClientRect(shape);

	//// 将内部内容自适应大小
	//MoveWindow(shape);
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
	// 消除滚动条
	m_nMapMode = -1;
	// 初始化 次数 下拉框
	CString degrees[] = { TEXT("1"), TEXT("2"), TEXT("3") };
	m_nMapMode = -1;

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
	int precision = _wtoi(data);

	// 获取 DrawView 指针
	CRuntimeClass* pClass = RUNTIME_CLASS(DrawView);
	DrawView* pDraw = (DrawView*)GetView(pClass);

	// DrawView 中新增一条曲线
	pDraw->addCurve(this->selectedType, curDegree, precision);
	// 获得 控制点数
	int ctrlCount = pDraw->getCtrlPointsNumOfCurve();

	// CurveInfoView 中 更新信息
	// 获取 DrawView 指针
	pClass = RUNTIME_CLASS(CurveInfoView);
	CurveInfoView* pInfo = (CurveInfoView*)GetView(pClass);

	// 在curveInfo中加入新曲线信息
	pInfo->addCurveInfo(this->selectedType, curDegree, precision);

	// 清空 CurvePoint 框
	pClass = RUNTIME_CLASS(CurvePointView);
	CurvePointView* pPointView = (CurvePointView*)GetView(pClass);
	pPointView->resetList();
}


/*************************************************
Function:		OnHScroll
Description:	处理滚动条滑动
Author:			刘崇鹏
Calls:
Input:
Return:
*************************************************/
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

			if (GetDlgItem(IDC_EDIT1) == GetFocus())
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


void AddCurveView::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CFormView::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//CString data, newData;
	//m_edit_precision.GetWindowTextW(data);
	//m_edit_precision.UpdateData(TRUE);
	//m_edit_precision.GetWindowTextW(newData);
	//data = data + _T(" ") + newData;
	//MessageBox(data);
}


//void AddCurveView::OnUpdateEdit1()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，它将不
//	// 发送此通知，除非重写 CFormView::OnInitDialog()
//	// 函数，以将 EM_SETEVENTMASK 消息发送到该控件，
//	// 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。
//
//	// TODO:  在此添加控件通知处理程序代码
//}

/*************************************************
Function:		OnSetfocusEdit1
Description:	在EditCtrl获得focus之后，进行初始化
Author:			刘崇鹏
Calls:			GetWindowTextW
Input:
Return:
*************************************************/
void AddCurveView::OnSetfocusEdit1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!isFocus) {
		isFocus = true;
		CString data;
		m_edit_precision.GetWindowTextW(data);
		nowPrecision = _wtoi(data);
	}
}

/*************************************************
Function:		OnKillfocusEdit1
Description:	在blur之后，进行框内的判断
Author:			刘崇鹏
Calls:
Input:
Return:
*************************************************/
void AddCurveView::OnKillfocusEdit1()
{
	isFocus = false;
	// TODO: 在此添加控件通知处理程序代码
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
		return;
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
}


//void AddCurveView::OnLButtonDblClk(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	CFormView::OnLButtonDblClk(nFlags, point);
//	
//}


void AddCurveView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CFormView::OnLButtonDown(nFlags, point);
	GetDlgItem(IDC_BUTTON_ADDCURVE)->SetFocus();
}



/*************************************************
Function:
Description:	打开线条
Author:			刘俊
Calls:          无					// 被本函数调用的函数清单
Input:
		-
Return:         void				// 函数返回值的说明
Others:         // 其它说明
*************************************************/
void AddCurveView::OnClickedOpencurve()
{
	// TODO: 在此添加控件通知处理程序代码

	// TODO: Add your control notification handler code here   
	// 设置过滤器   
	TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||");
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	CString strFilePath;

	// 显示打开文件对话框   
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
		strFilePath = fileDlg.GetPathName();
		CFile myCurve;
		if (!myCurve.Open(strFilePath, CFile::modeRead))
		{
			MessageBox(_T("打开失败!"));
		}

		std::string type, degree, pre;
		Curve newCurve;
		
		//读取文件内容
		DWORD len = myCurve.GetLength();
		char buffer[10000];
		myCurve.Read(buffer, 10000);
		std::string s;
		for(int i = 0; i < len; i++)
		{
			if (buffer[i] == '\0' ||i==0||i==1) continue;
			s += buffer[i];
		}
		
		std::string::size_type pos;
		std::vector<std::string> vec;
		std::string ch = "\n";
		std::string ch1 = ", ";
		//读取加载曲线信息并初始化曲线
		for (int i = 0; i < s.size(); i++)
		{
			pos = s.find(ch, i);
			if (pos < s.size())
			{
				std::string str = s.substr(i, pos - i);
				if (i == 0)
				{
					//正则匹配
					std::regex reg("type:(B|S),degree:(1|2|3),pre:(.*)");
					std::smatch res;
					if (!std::regex_match(str, res, reg))
					{
						MessageBox(_T("不支持的文件内容!"));
						return;
					}
					//设置曲线信息
					type = str[5];
					if (type == "B") newCurve.setType((CurveType)'B');
					else newCurve.setType((CurveType)'S');
					degree = str[14];
					newCurve.setDegree(atoi(degree.c_str()));
					std::string pre1 = str.substr(20,str.size()-1);
					newCurve.setPrecision(atoi(pre1.c_str()));
					i = pos + ch.size() - 1;
					continue;
				}
				vec.push_back(str);
				i = pos + ch.size() - 1;
			}
			else
			{
				MessageBox(_T("不支持的文件内容!"));
				return;
			}
		}
		//往加载的线条中写入控制点
		for (std::string it : vec)
		{
			std::string p = it.substr(1, it.size() - 2);
			pos = p.find(ch1, 0);
			std::string x = p.substr(0, pos);
			std::string y = p.substr(pos + 2, p.size() - 1);
			CP2 cPoint;
			cPoint.x = atof(x.c_str());
			cPoint.y = atof(y.c_str());
			newCurve.addCtrlPoint(cPoint);
		}

		// 获取 DrawView 指针
		CRuntimeClass* pClass = RUNTIME_CLASS(DrawView);
		DrawView* pDraw = (DrawView*)GetView(pClass);

		// DrawView 中新增一条曲线
		pDraw->addCurve(newCurve);
		// 获得 控制点数
		int ctrlCount = pDraw->getCtrlPointsNumOfCurve();

		pDraw->RedrawWindow();

		// CurveInfoView 中 更新信息
		// 获取 DrawView 指针
		pClass = RUNTIME_CLASS(CurveInfoView);
		CurveInfoView* pInfo = (CurveInfoView*)GetView(pClass);

		// 在curveInfo中加入新曲线信息
		pInfo->openCurveInfo(newCurve);

		pClass = RUNTIME_CLASS(CurvePointView);
		CurvePointView* pPoint = (CurvePointView*)GetView(pClass);
		pPoint->showCurvePoints();
		
	}

}
