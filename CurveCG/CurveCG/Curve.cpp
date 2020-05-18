#include "pch.h"
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

#include "CP2.h"
#include "Curve.h"

const double PI = 3.14159;

// 初始化 组合数表
const int Curve::combs[7][7] = {
	{1},
	{1, 1},
	{1, 2, 1},
	{1, 3, 3, 1},
	{1, 4, 6, 4, 1},
	{1, 5, 10, 10, 5, 1},
	{1, 6, 15, 20, 15, 6, 1}
};

// 初始化 阶乘表
const int Curve::factorials[6] = { 1, 1, 2, 6, 24, 120 };


Curve::Curve()
{
	// 默认 3次 样条曲线 精度0.01
	this->type = Spline;
	this->degree = 3;
	this->precision = 100;
	// 给crtlPoints预分配一条曲线，即4个点所需空间
	this->ctrlPoints.reserve(4);
	// 给curvePoints预分配一条曲线，4个点所需空间,1/precision 个
	this->curvePoints.reserve(1 / this->precision);
}


Curve::Curve(CurveType type, int degree, int precision)
{
	this->type = type;
	this->degree = degree;
	this->precision = precision;
	// 给crtlPoints预分配一条曲线，即4个点所需空间
	this->ctrlPoints.reserve(7);
	// 给curvePoints预分配一条曲线，4个点所需空间,1/precision 个
	this->curvePoints.reserve(1 / this->precision);
}


/********************************
 Function:		getCurveType
 Description:	获取曲线类型
 Input:
 Return:		CurveType
********************************/
CurveType Curve::getCurveType() const {
	return this->type;
}


/********************************
 Function:		getCurveDegree
 Description:	获取曲线次数
 Input:
 Return:		int
********************************/
int Curve::getCurveDegree() const {
	return this->degree;
}


/**********************************
 Function:		getCtrlPointsNum
 Description:	获取曲线中 控制点个数
 Input:
 Return:		int
**********************************/
int Curve::getCtrlPointsNum() const {
	return (int)this->ctrlPoints.size();
}


/**********************************
 Function:		getCtrlPointsNum
 Description:	获取曲线中 控制点个数
 Input:
 Return:		int
**********************************/
int Curve::getCurvePrecision() const {
	return this->precision;
}


/**********************************
 Function:		getCtrlPoint
 Description:	获取曲线中 某个控制点
 Input:
			- index: int, 索引
 Return:		CP2
**********************************/
CP2 Curve::getCtrlPoint(int index) const {
	if (index >= this->getCtrlPointsNum())
		throw "索引越界!";
	return this->ctrlPoints[index];
}


/*************************************************
Function:       Combination
Description:	组合数, 暴力解法
Author:			刘陆
Input:
		- n: int, 总元素数
		- m: int, 选出的元素数
Return : int
**************************************************/
int Curve::Combination(int n, int m) throw(std::string) {
	if (m > n)
		throw "组合数m>n不合法";

	int ans = 1;
	for (int i = n; i >= (n - m + 1); --i)
		ans *= i;
	while (m)
		ans /= m--;
	return ans;
}


/*************************************************
Function:       Bernstein
Description:	Bezier 曲线的 Bernstein 基函数
Author:			刘陆
Calls:			Combination
Input:
		- i: int, 第 i 个控制点
		- degree: int, 曲线阶数
		- t: double, 参量
Return: double
*************************************************/
double Curve::Bernstein(int i, int degree, double t) {
	//if (t == 0) {
	//	if (i == 0)
	//		return 1.0;
	//	return 0.0;
	//}
	//else if (t == 1) {
	//	if (i == degree)
	//		return 1.0;
	//	return 0.0;
	//}
	if (i > degree)
		throw "Bernstein 组合数错误";
	return this->combs[degree][i] * pow(t, i) * pow(1 - t, degree - i);
}



/*************************************************
Function:       F
Description:	B - 样条曲线 基函数
Author:			刘陆
Calls:			Combination
Input:
		- i: int, 第 i 个控制点
		- degree: int, 曲线阶数
		- t: double, 参量
Return: double
*************************************************/
double Curve::F(int i, int degree, double t) {
	double res = 0.0;

	for (int j = 0; j <= degree - i; j++) {

		if (j & 1)		// 奇数
			res -= (this->combs[degree + 1][j] * pow(t + degree - i - j, degree));
		else			// 偶数
			res += (this->combs[degree + 1][j] * pow(t + degree - i - j, degree));
	}
	return res / factorials[degree];
}


/*************************************************
Function:       generateCurvePoints
Description:	采样生成样条曲线上的点
Author:			刘陆
Calls:			Bernstein, F
Input:
		- start: int, 曲线起始控制点 在 ctrlPoints 中的索引
		- end: int, 曲线结束控制点 在 ctrlPoints 中的索引
Return:
		- points: vector<CP2>, 生成的点
*************************************************/
std::vector<CP2> Curve::generateCurvePoints(int start, int end)
{
	std::vector<CP2> points;

	// 调试信息
	// CString data;
	// data.Format(_T("%d"), this->precision);

	if (end - start + 1 <= this->degree)		// 控制点个数 不足以计算 degree 阶曲线
		return points;

	int offset;
	if (type == Bezier)		// Bezier 曲线
		offset = this->degree;
	else					// B - 样条曲线
		offset = 1;

	double eps = 1.0 / this->precision;		// 参量 t 精度

	for (int i = start; i + this->degree <= end; i += offset) {		// 起始控制点索引 i

		for (double t = 0; t <= 1; t += eps) {		// 参数方程 参量 t
			CP2 cur;
			for (int k = 0; k <= this->degree; k++) {			// 遍历控制点
				switch (type) {
				case Bezier:		// Bazier 曲线
					cur += ctrlPoints[i + k] * this->Bernstein(k, degree, t);
					break;
				case Spline:		// B - 样条曲线
					cur += ctrlPoints[i + k] * this->F(k, degree, t);
					break;
				}
			}
			points.push_back(cur);
		}
	}

	// 防止 Bezier 曲线 精度过低曲线不连续
	if (type == Bezier)
		points.push_back(ctrlPoints[end]);

	return points;
}


/*************************************************
Function:       addCtrlPoint
Description:	追加一个控制点, 加入 Curve.ctrlPoints 末尾
Author:			刘陆
Calls:			generateCurvePoints
Input:
		- ctrlPoint: CP2, 控制点
Return:
*************************************************/
void Curve::addCtrlPoint(CP2& ctrlPoint)
{
	ctrlPoints.push_back(ctrlPoint);		// 末尾加入控制点

	if (this->getCtrlPointsNum() - this->degree - 1 < 0)		// 控制点数量少, 无法生成曲线
		return;

	std::vector<CP2> newPoints;

	//if (this->getCurveType() == Bezier && this->getCtrlPointsNum() != this->degree + 1 && ((this->getCtrlPointsNum() + 1) % (this->degree + 1) != 0))
	if (this->getCurveType() == Bezier && ((this->getCtrlPointsNum() - 1) % (this->degree) != 0))
		return;

	newPoints = this->generateCurvePoints(this->getCtrlPointsNum() - degree - 1, this->getCtrlPointsNum() - 1);

	curvePoints.insert(curvePoints.end(), newPoints.begin(), newPoints.end());
}


/*************************************************
Function:       deleteCtrlPoint
Description:	删除一个控制点
Author:			韩继锋
Calls:			resetCurvePoints, generateCurvePoints
Input:			- index: int, 控制点在 ctrlPoints 中的索引
Return:
*************************************************/
void Curve::deleteCtrlPoint(int index) {
	if (index >= ctrlPoints.size())
		return;

	std::vector<CP2>::iterator it = this->ctrlPoints.begin();
	ctrlPoints.erase(it + index);		// 删除指定的控制点

	this->resetCurvePoints();			// 清空 curvePoints

	std::vector<CP2> points = this->generateCurvePoints(0, ctrlPoints.size() - 1);		// 重新生成所有点
	curvePoints.insert(curvePoints.end(), points.begin(), points.end());
}


/*************************************************
Function:       deleteCtrlPoint
Description:	删除一个控制点
Author:			韩继锋
Calls:			deleteCtrlPoint
Input:			- CP2 ctrlPoint: CP2, 将要删除的控制点
Return:
*************************************************/
void Curve::deleteCtrlPoint(CP2 ctrlPoint) {
	std::vector<CP2>::iterator it = find(ctrlPoints.begin(), ctrlPoints.end(), ctrlPoint);		// 在 ctrlPoints 中查找 ctrlPoint

	if (it != ctrlPoints.end()) {
		ctrlPoints.erase(it);
		this->resetCurvePoints();
		this->curvePoints = generateCurvePoints(0, ctrlPoints.size() - 1);
	}
}


/*************************************************
Function:		moveCtrlPoints
Description:	移动控制点, 即改变控制点的位置
Author:			刘陆
Calls:			resetCurvePoints, generateCurvePoints
Input:
			- index: int, 控制点在 ctrlPoints 中的索引
			- newPos: CP2, 该控制点的新位置
Return:
other:		newPos 是 CP2 实例
*************************************************/
void Curve::moveCtrlPoint(int index, CP2 newPos) throw(std::string) {
	if (index >= ctrlPoints.size())
		throw "索引越界";

	ctrlPoints[index] = newPos;
	this->resetCurvePoints();			// 清空 curvePoints

	std::vector<CP2> points = this->generateCurvePoints(0, ctrlPoints.size() - 1);		// 重新生成所有点
	curvePoints.insert(curvePoints.end(), points.begin(), points.end());
}


/*************************************************
Function:		resetCurvePoints
Description:	清空实例的 curvePoints
Author:			刘陆
*************************************************/
void Curve::resetCurvePoints() {
	curvePoints.clear();
}


/*************************************************
Function:			drawCurve
Description:		绘制曲线
Author:				刘俊
Calls:
Input:				- pDC
Return:				void
*************************************************/
void Curve::drawCurve(CDC* pDC) {
	if (this->ctrlPoints.empty())
		return;

	CPen curvePen, curvePen1, * pOldPen;		//画笔
	// TODO: 设置画笔 属性 (颜色, 粗细...)
	curvePen.CreatePen(PS_SOLID, 1, RGB(0, 123, 231));

	CBrush brush(RGB(0, 123, 231));		// 蓝色画刷, 绘制蓝色

	pOldPen = pDC->SelectObject(&curvePen);
	CBrush* pOldBrush = pDC->SelectObject(&brush);

	const int blockWidth = 4;		// 控制点矩形宽度 的一半

	pDC->MoveTo(ctrlPoints[0].x, ctrlPoints[0].y);
	for (CP2 cP : ctrlPoints) {
		//连接控制点
		pDC->LineTo(cP.x, cP.y);
		pDC->FillRect(CRect(cP.x - blockWidth, cP.y - blockWidth, cP.x + blockWidth, cP.y + blockWidth), &brush);
	}
	pDC->SelectObject(pOldBrush);

	// curvePoints 空, 不绘制曲线
	if (this->curvePoints.empty()) {
		pDC->SelectObject(pOldPen);
		return;
	}

	curvePen1.CreatePen(PS_SOLID, 2, RGB(220, 0, 0));
	pOldPen = pDC->SelectObject(&curvePen1);

	pDC->MoveTo(curvePoints[0].x, curvePoints[0].y);
	for (CP2 cP : curvePoints) {
		//样条曲线
		pDC->LineTo(cP.x, cP.y);
	}
	pDC->SelectObject(pOldPen);
}


/*************************************************
Function:		changeCurveInfo(char, int, int)
Description:	修改曲线信息，注意：若有参数为NULL，则视为未修改
Author:			刘崇鹏
Calls:			changeCurveInfo, generateCurvePoints
Input:
				- type: CurveType, 曲线的类型，Bezier 或 Spline
				- degree: int, 曲线的新阶数，NULL代表该值未修改
				- precision: int, 曲线的新画线精度
Return:
*************************************************/
void Curve::changeCurveInfo(CurveType type, int degree, int precision)
{
	// 修改曲线的类型与阶次信息
	// 如果有参数为空(值未进行修改)，直接返回
	if (type == NULL || degree == NULL || precision == NULL)return;

	/*
	// 若只有type为空，则调用degree多态函数
	if (type == NULL)
	{
		changeCurveInfo(degree);
		return;
	}
	// 若只有degree为空，则调用type多态函数
	if (degree == NULL)
	{
		changeCurveInfo(type);
		return;
	}
	// 剩下为两参数都不为空
	*/

	// 未进行修改
	if (this->type == type && this->degree == degree && this->precision == precision)return;

	// 正常绘制，生成新的curvePoints
	this->type = type;
	this->degree = degree;
	this->precision = precision;
	this->curvePoints.clear();
	this->curvePoints = generateCurvePoints(0, ctrlPoints.size() - 1);
}


/*************************************************
Function:		changeCurveInfo(char)
Description:	修改曲线信息，注意：参数为NULL代表该值未修改
Author:			刘崇鹏
Calls:			generateCurvePoints
Input:
				- type: char, 曲线的类型，即贝塞尔'B'或样条'S'曲线，NULL代表该值未修改
Return:
*************************************************/
void Curve::changeCurveInfo(CurveType type)
{
	// 为空直接返回
	if (type == NULL)return;
	// 如果和原先一致，不进行修改
	if (this->type == type)return;
	// 进行修改，重新生成curvePoints
	this->type = type;
	this->curvePoints = generateCurvePoints(0, ctrlPoints.size() - 1);
}


/*************************************************
Function:		changeCurveInfo(char)
Description:	修改曲线信息，注意：参数为NULL代表该值未修改
Author:			刘崇鹏
Calls:			generateCurvePoints
Input:
				- degree: int, 曲线的新阶数，NULL代表该值未修改
Return:
*************************************************/
void Curve::changeCurveInfo(int degree)
{
	// 为空直接返回
	if (degree == NULL)return;
	// 如果和原先一致，不进行修改
	if (this->degree == degree)return;
	// 进行修改，重新生成curvePoints
	this->degree = degree;
	this->curvePoints = generateCurvePoints(0, ctrlPoints.size() - 1);
}


/*************************************************
Function:		changeCurveInfo(double)
Description:	修改曲线信息，注意：参数为NULL代表该值未修改
Author:			刘崇鹏
Calls:			generateCurvePoints
Input:
				- precision: double, 曲线的新画线精度
Return:
*************************************************/
//void Curve::changeCurveInfo(int precision)
//{
//	// 为空直接返回
//	if (precision == NULL)return;
//	// 如果和原先一致，不进行修改
//	if (this->precision == precision)return;
//	// 进行修改，重新生成curvePoints
//	this->precision = precision;
//	this->curvePoints = generateCurvePoints(0, ctrlPoints.size() - 1);
//}
