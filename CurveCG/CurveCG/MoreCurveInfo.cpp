// MoreCurveInfo.cpp: 实现文件
//

#include "pch.h"
#include "CurveCG.h"
#include "MoreCurveInfo.h"
#include "afxdialogex.h"
#include "CurveCGView.h"
#include "CP2.h"
#include "Curve.h"
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
	DDX_Control(pDX, IDC_SLIDER2, m_SLIDER);
	DDX_Control(pDX, IDC_EDIT_02, m_PRESICION_EDIT);
	DDX_Control(pDX, IDC_RADIO_BEZIER_01, m_BEZIER_BUTTON);
	DDX_Control(pDX, IDC_RADIO_BSPLINE_01, M_BSPLINE_BUTTON);
}



BEGIN_MESSAGE_MAP(MoreCurveInfo, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_01, &MoreCurveInfo::OnEnChangeEdit01)
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
Description:	设置线条信息
Author:			刘俊
Calls:          无					// 被本函数调用的函数清单
Input:
		-
Return:         int				// 失败返回0，成功返回1
Others:         // 其它说明
*************************************************/
int MoreCurveInfo::setCurve(CurveType type, int degree, double percision)
{
	if (type == NULL || degree == 0 || percision == 0)
	{
		return 0;
	}

	this->m_curve.changeCurveInfo(type, degree, percision);

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
Author:			刘俊
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
	//初始化名称
	this->m_edit_curveName.SetWindowTextW(curveName);
	
	//初始化类型
	if (m_curve.getCurveType() == 'B')
		m_BEZIER_BUTTON.SetCheck(1);
	else
		M_BSPLINE_BUTTON.SetCheck(1);

	// 初始化 次数 下拉框
	CString degrees[] = { TEXT("1"), TEXT("2"), TEXT("3") };
	for (int i = 0; i < 3; i++)
		m_DEGREE_COMBOX.AddString(degrees[i]);
	m_DEGREE_COMBOX.SetCurSel(m_curve.getCurveDegree()-1);		// 默认三次

	//初始化精度滑动条
	m_SLIDER.SetRange(precisionMin, precisionMax);
	m_SLIDER.SetTicFreq(precisionInterval);
	m_SLIDER.SetPos(m_curve.getCurvePrecision());
	//初始化精度编辑框
	CString ss ;
	ss.Format(_T("%lf"), m_curve.getCurvePrecision());
	this->m_PRESICION_EDIT.SetWindowTextW(ss);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
