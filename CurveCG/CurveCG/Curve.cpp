#include "pch.h"
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <sstream>

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

// 一次 Bezier 系数矩阵
const int Curve::W1[2][2] = {
	{-1, 1},
	{1, 0}
};

// 二次曲线 系数矩阵
const int Curve::W2[2][3][3] = {
	{
		{1, -2, 1},
		{-2, 2, 0},
		{1, 0, 0}
	},
	{
		{1, -2, 1},
		{-2, 2, 0},
		{1, 1, 0}
	}
};

// 三次 Bezier 系数矩阵
const int Curve::W3[2][4][4] = {
	{
		{-1, 3, -3, 1},
		{3, -6, 3, 0},
		{-3, 3, 0, 0},
		{1, 0, 0, 0}
	},
	{
		{-1, 3, -3, 1},
		{3, -6, 3, 0},
		{-3, 0, 3, 0},
		{1, 4, 1, 0}
	}
};

// 样条曲线 系数矩阵 的前缀系数
const double Curve::BSplineW[4] = { 1.0, 1.0, 1.0 / 2, 1.0 / 6 };


Curve::Curve()
{
	// 默认 3次 样条曲线 精度0.01
	this->type = Spline;
	this->degree = 3;
	this->precision = 100;
	// 给crtlPoints预分配一条曲线，即4个点所需空间
	this->ctrlPoints.reserve(4);
	// 给curvePoints预分配一条曲线，4个点所需空间,1/precision 个
	this->curvePoints.reserve(this->precision);
}


Curve::Curve(CurveType type, int degree, int precision)
{
	this->type = type;
	this->degree = degree;
	this->precision = precision;
	// 给crtlPoints预分配一条曲线，即4个点所需空间
	this->ctrlPoints.reserve(7);
	// 给curvePoints预分配一条曲线，4个点所需空间,1/precision 个
	this->curvePoints.reserve(this->precision);
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
	if (t == 0) {
		if (i == 0) {
			return 1.0;
			return 0.0;
		}
	}
	else if (t == 1) {
		if (i == degree)
			return 1.0;
		return 0.0;
	}

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
Function:       buildInfo
Description:	处理曲线方程的某个维度
Author:			刘陆
Calls:
Input:
			- p: 求解完毕的矩阵指针
			- dim: int, 维度, 0 或 1
			- n: int, 循环总数
			- info: 保存的字符串指针
Return:
*************************************************/
void buildInfo(double(*p)[2], int dim, int n, CString& info) {
	CString pattern;
	for (int i = 0; i < n; i++) {
		double cur = p[i][dim];
		if (cur == 0)
			continue;

		pattern.Empty();

		if (n - 1 - i == 1) {		// t ^ 1
			if (cur < 0)
				pattern.Format(_T("%.3lf t "), cur);
			else
				pattern.Format(_T("+%.3lf t "), cur);
		}
		else if (i == n - 1) {		// 常数项
			if (cur < 0)
				pattern.Format(_T("%.3f"), cur);
			else if (p[n - 1][0] > 0)
				pattern.Format(_T("+%.3f"), cur);
		}
		else {
			if (cur < 0)
				pattern.Format(_T("%.3lf t^%d "), cur, n - 1 - i);
			else
				pattern.Format(_T("+%.3lf t^%d "), cur, n - 1 - i);
		}
		info += pattern;
	}
}


/*************************************************
Function:       calEquation
Description:	计算曲线方程
Author:			刘陆
Calls:
Input:
		- start: int, 曲线起始控制点
		- end: int, 曲线结束控制点
Return:			Equation
*************************************************/
EquationInfo Curve::calEquation(int start, int end) {
	const int* parr = NULL;		// 指向 对应系数矩阵 的指针

	if (degree == 1)
		parr = &(Curve::W1[0][0]);
	else if (degree == 2) {
		if (type == Bezier)
			parr = &(Curve::W2[0][0][0]);
		else
			parr = &(Curve::W2[1][0][0]);
	}
	else {
		if (type == Bezier)
			parr = &(Curve::W3[0][0][0]);
		else
			parr = &(Curve::W3[1][0][0]);
	}

	int n = degree + 1;

	double(*p)[2];				// 最终结果, N * 2 矩阵
	p = new double[n][2];

	// 矩阵乘
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 2; j++) {
			int tot = 0;

			for (int k = 0; k < n; k++) {
				if (!j)
					tot += (int)ctrlPoints[start + k].x * *(parr + i * n + k);
				else
					tot += (int)ctrlPoints[start + k].y * *(parr + i * n + k);
			}

			p[i][j] = tot;
		}
	}

	// B- 样条曲线 前缀系数
	if (this->type == Spline && this->degree != 1) {
		double w = this->BSplineW[this->degree];

		for (int i = 0; i < n; i++)
			p[i][0] *= w, p[i][1] *= w;
	}

	// 构造 info
	EquationInfo info;
	CString pattern;

	buildInfo(p, 0, n, info.nameX);
	buildInfo(p, 1, n, info.nameY);

	delete[] p;
	return info;
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

	if (end - start + 1 <= this->degree)		// 控制点个数 不足以计算 degree 阶曲线
		return points;

	int offset;
	if (type == Bezier)		// Bezier 曲线
		offset = this->degree;
	else					// B - 样条曲线
		offset = 1;

	double eps = 1.0 / this->precision;		// 参量 t 精度

	for (int i = start; i + this->degree <= end; i += offset) {		// 起始控制点索引 i
		EquationInfo info = calEquation(i, i + this->degree);		// 计算该段曲线方程
		this->equations.push_back(info);

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
void Curve::addCtrlPoint(CP2 ctrlPoint)
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
	this->equations.clear();

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
		this->equations.clear();
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

	this->equations.clear();

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
Author:				刘俊, 刘陆
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
Description:	修改曲线信息，注意：若有参数为NULL，则不进行修改
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

	// type不为空
	if (type != NULL)
	{
		this->type = type;
	}
	// degree不为空
	if (degree != NULL)
	{
		this->degree = degree;
	}
	// precision不为空
	if (precision != NULL)
	{
		this->precision = precision;
	}


	// 正常绘制，生成新的curvePoints
	resetCurvePoints();
	this->equations.clear();
	this->curvePoints = generateCurvePoints(0, ctrlPoints.size() - 1);
}

void Curve::setType(CurveType type)
{
	this->type = type;
}

void Curve::setDegree(int degree)
{
	this->degree = degree;
}

void Curve::setPrecision(int precision)
{
	this->precision = precision;
}
