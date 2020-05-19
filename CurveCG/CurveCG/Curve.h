#pragma once
#include <vector>
#include <string>
#include "CP2.h"


struct EquationInfo {
	std::string name;       // 参数方程
	int x, y;       // 文本的输出位置
};

enum CurveType
{
	Bezier = 'B',
	Spline = 'S'
};

class Curve {
	// 构造器
public:
	Curve(); 	//无参构造器，初始化内部参数为默认值
	Curve(CurveType type, int degree, int precision);   // 有参构造器

// 属性
private:
	std::vector<CP2> ctrlPoints;				// 控制点
	std::vector<CP2> curvePoints;				// 样条曲线上的点
	std::vector<EquationInfo> equations;        // 各个子曲线的参数方程

	CurveType type;      // 曲线类型
	int degree;			 // 曲线阶数
	int precision;		 // 曲线的精度, 即一段曲线由 多少个点 组成
	const static int combs[7][7];				// 组合数表
	const static int factorials[6];			    // 阶乘表

// 方法
public:
	double Bernstein(int i, int degree, double t);	// Bernstein 基函数
	double F(int i, int degree, double t);			// B-样条 基函数

	std::vector<CP2> generateCurvePoints(int start, int end);		// 生成样条曲线上的点
	void addCtrlPoint(CP2);					// 追加一个控制点

	void deleteCtrlPoint(int index);		// 删除控制点, 及其多种重载
	void deleteCtrlPoint(CP2);

	void moveCtrlPoint(int index, CP2 newPos);		// 移动控制点

	void drawCurve(CDC* pDC);						// 绘制本条曲线
	void resetCurvePoints();					    // 清空 实例的 curvePoints

	void changeCurveInfo(CurveType type, int degree, int precision);	// 修改曲线信息, 及其重载
	void setType(CurveType type);
	void setDegree(int degree);
	void setPrecision(int precision);
	//void changeCurveInfo(CurveType type);
	//void changeCurveInfo(int degree);
	//void changeCurveInfo(int precision);

	int Combination(int n, int m);			// 组合数

	/** Getters */
	CurveType getCurveType() const;				// 获得曲线类型
	int getCtrlPointsNum() const;					// 获得曲线中 控制点个数
	int getCurveDegree() const;					// 获得曲线次数
	int getCurvePrecision() const;				// 获得曲线精度
	CP2 getCtrlPoint(int index) const;			// 获得曲线中 某个控制点
};
