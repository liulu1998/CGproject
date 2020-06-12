// MoreCurveInfo.cpp: 实现文件
//

#include "pch.h"
#include "CurveCG.h"
#include "MoreCurveInfo.h"
#include "afxdialogex.h"
#include "CurveCGView.h"
#include "CP2.h"
#include "Curve.h"
#include "viewList.h"
#include<sstream>

// MoreCurveInfo 对话框

IMPLEMENT_DYNAMIC(MoreCurveInfo, CDialogEx)

MoreCurveInfo::MoreCurveInfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_MORECURVEINFO, pParent)
	, curveName(_T(""))
{

}

MoreCurveInfo::~MoreCurveInfo()
{
}

void MoreCurveInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_01, m_edit_curveName);
	DDX_Text(pDX, IDC_EDIT_01, curveName);
	DDX_Control(pDX, IDC_COMBO_DEGREE_01, m_DEGREE_COMBOX);
	DDX_Control(pDX, IDC_EDIT_02, m_PRESICION_EDIT);
	DDX_Control(pDX, IDC_RADIO_BEZIER_01, m_BEZIER_BUTTON);
	DDX_Control(pDX, IDC_RADIO_BSPLINE_01, M_BSPLINE_BUTTON);
	DDX_Control(pDX, IDC_LIST2, XEqution);
	DDX_Control(pDX, IDC_LIST1, YEquation);
}



BEGIN_MESSAGE_MAP(MoreCurveInfo, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_01, &MoreCurveInfo::OnEnChangeEdit01)
	ON_BN_CLICKED(IDOK, &MoreCurveInfo::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO_BEZIER_01, &MoreCurveInfo::OnBnClickedRadioBezier01)
	ON_BN_CLICKED(IDC_RADIO_BSPLINE_01, &MoreCurveInfo::OnBnClickedRadioBspline01)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &MoreCurveInfo::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// MoreCurveInfo 消息处理程序

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
CView* MoreCurveInfo::GetView(CRuntimeClass* pClass) {
	CDocument* pDoc = ((CFrameWndEx*)AfxGetMainWnd())->GetActiveDocument();
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
Function:
Description:	设置线条名称
Author:			刘俊
Calls:          无					// 被本函数调用的函数清单
Input:
		-str						//线条名称
Return:         int				// 失败返回0，成功返回1
Others:         // 其它说明
*************************************************/


int MoreCurveInfo::setCurveName(CString str)
{
	if (str == "")
		return 0;

	this->curveName = str;
	return 1;
}


/*************************************************
Function:
Description:	得到线条名称
Author:			刘俊
Calls:          无					// 被本函数调用的函数清单
Input:
		-
Return:         CString				// 函数返回值的说明
Others:         // 其它说明
*************************************************/


CString MoreCurveInfo::getCurveName()
{
	return this->curveName;
}

CurveType MoreCurveInfo::getCurveType()
{
	return m_curve.getCurveType();
}

int MoreCurveInfo::getCurveDegree()
{
	return m_curve.getCurveDegree();
}

int MoreCurveInfo::getCurvePrec()
{
	return m_curve.getCurvePrecision();
}


/*************************************************
Function:
Description:	设置线条信息
Author:			刘俊
Calls:          无					// 被本函数调用的函数清单
Input:
		-
Return:         int				// 失败返回0，成功返回1
Others:         // 其它说明
*************************************************/
int MoreCurveInfo::setCurve(CurveType type, int degree, int percision)
{
	// TODO: precision 已经换为 整型, 此处的判断调整 ?
	if (type == NULL || degree == 0 || percision == 0)
	{
		return 0;
	}

	this->m_curve.changeCurveInfo(type, degree, percision);

	return 1;
}

/*************************************************
Function:
Description:	设置子曲线方程
Author:			刘俊
Calls:          无					// 被本函数调用的函数清单
Input:
		-vector<Equation>
Return:         int				// 函数返回值的说明
Others:         // 其它说明
*************************************************/
int MoreCurveInfo::setCurveEquation(std::vector<EquationInfo> e) 
{

	// 曲线列表初始化, 设置整行选中
	XEqution.SetExtendedStyle(this->XEqution.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	YEquation.SetExtendedStyle(this->YEquation.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	// 设置基本格式
	// 设置表头
	CRect listRect;
	XEqution.GetWindowRect(listRect);
	YEquation.GetWindowRect(listRect);

	CString header[] = { _T("id"), _T("XEquation") };
	CString header1[] = { _T("id"), _T("YEquation") };
	float colWidth[] = { 0.15, 0.85 };
	for (int i = 0; i < 2; i++)
	{
		XEqution.InsertColumn(i, header[i], LVCFMT_LEFT, listRect.Width() * colWidth[i]);
		YEquation.InsertColumn(i, header1[i], LVCFMT_LEFT, listRect.Width() * colWidth[i]);
	}

	if (e.empty()) return 0;

	//设置数据
	for (int i = 0;i<e.size();i++)
	{
		// 插入表格
	// 插入 第一列 id
		CString idstr;
		idstr.Format(_T("%d"), i+1);
		this->XEqution.InsertItem(i, idstr);
		this->YEquation.InsertItem(i, idstr);
		// 插入其他列
		this->XEqution.SetItemText(i, 1, e[i].nameX);
		this->YEquation.SetItemText(i, 1, e[i].nameY);
	}

	return 1;
}

/*************************************************
Function:
Description:	设置线条方程
Author:			刘俊
Calls:          无					// 被本函数调用的函数清单
Input:
		-vector<Equation>
Return:         int				// 函数返回值的说明
Others:         // 其它说明
*************************************************/


int MoreCurveInfo::setEquation(std::vector<EquationInfo > e)
{
	if (e.empty())
	{
		return 0;
	}

	for (EquationInfo i : e)
	{
		this->equation.push_back(i);
	}
	return 1;
}

void MoreCurveInfo::OnEnChangeEdit01()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}



/*************************************************
Function:
Description:	初始化线条详细信息
Author:			刘俊, 刘崇鹏
Calls:          无					// 被本函数调用的函数清单
Input:
		-
Return:         BOOL				// 函数返回值的说明
Others:         // 其它说明
*************************************************/


BOOL MoreCurveInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//初始化dialog名
	this->SetWindowTextW((CString)"线条详细信息");

	//初始化名称
	this->m_edit_curveName.SetWindowTextW(curveName);
	this->m_edit_curveName.SetReadOnly(TRUE);

	//初始化类型
	if (m_curve.getCurveType() == 'B')
		m_BEZIER_BUTTON.SetCheck(1);
	else
		M_BSPLINE_BUTTON.SetCheck(1);

	// 初始化 次数 下拉框
	CString degrees[] = { TEXT("1"), TEXT("2"), TEXT("3") };
	for (int i = 0; i < 3; i++)
		m_DEGREE_COMBOX.AddString(degrees[i]);
	m_DEGREE_COMBOX.SetCurSel(m_curve.getCurveDegree() - 1);		// 默认三次

	//初始化精度编辑框
	CString ss;
	ss.Format(_T("%d"), m_curve.getCurvePrecision());
	this->m_PRESICION_EDIT.SetWindowTextW(ss);
	nowPrecision = m_curve.getCurvePrecision();

	this->setCurveEquation(this->equation);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


/*************************************************
Function:
Description:	点击确定按钮修改线条信息
Author:			刘俊, 刘崇鹏
Calls:          					// 被本函数调用的函数清单
Input:
		-
Return:         void				// 函数返回值的说明
Others:         // 其它说明
*************************************************/


void MoreCurveInfo::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();

	//TODO:获取修改信息并传递给父窗口
	//获得线条名称
	CString str,str1,str2;
	m_edit_curveName.GetWindowTextW(str);
	setCurveName(str);

	//获得线条阶数 
	m_DEGREE_COMBOX.GetWindowTextW(str1);
	//获得精度
	m_PRESICION_EDIT.GetWindowTextW(str2);
	this->m_curve.changeCurveInfo(this->m_curve.getCurveType(),_ttoi(str1),_ttoi(str2));


}


/*************************************************
Function:
Description:	点击Bezier单选框事件
Author:			刘俊
Calls:          无					// 被本函数调用的函数清单
Input:
		-
Return:         void				// 函数返回值的说明
Others:         // 其它说明
*************************************************/


void MoreCurveInfo::OnBnClickedRadioBezier01()
{
	// TODO: 在此添加控件通知处理程序代码

	this->m_curve.setType(Bezier);
}



/*************************************************
Function:
Description:	点击BSline单选框事件
Author:			刘俊
Calls:          					// 被本函数调用的函数清单
Input:
		-
Return:         void				// 函数返回值的说明
Others:         // 其它说明
*************************************************/


void MoreCurveInfo::OnBnClickedRadioBspline01()
{
	// TODO: 在此添加控件通知处理程序代码
	this->m_curve.setType(Spline);
}


void MoreCurveInfo::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
