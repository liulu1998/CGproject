#pragma once
#include "CP2.h"

class CTransform//二维几何变换  
{
public:
	CTransform();
	virtual ~CTransform();
	void SetMat(CP2*, int);
	void Identity();
	void Translate(double, double);//平移变换矩阵
	void Scale(double, double);//比例变换矩阵
	void Scale(double, double, CP2);//相对于任意点的比例变换矩阵
	void Rotate(double);//旋转变换矩阵
	void Rotate(double, CP2);//相对于任意点的旋转变换矩阵
	void ReflectOrg();//原点反射变换矩阵
	void ReflectX();//X轴反射变换矩阵
	void ReflectY();//Y轴反射变换矩阵
	void Shear(double, double);//错切变换矩阵
	void MultiMatrix();//矩阵相乘
public:
	double T[3][3];
	CP2* POld;
	int num;
};
