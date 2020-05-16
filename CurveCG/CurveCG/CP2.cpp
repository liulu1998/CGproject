#include "pch.h"
#include "CP2.h"

CP2::CP2()
{
	x = 0;
	y = 0;
	w = 1;
}

CP2::~CP2()
{

}

CP2::CP2(double x, double y)
{
	this->x = x;
	this->y = y;
	this->w = 1;
}

CP2 operator +(const CP2& p1, const CP2& p2)
{
	CP2 p;
	p.x = p1.x + p2.x;
	p.y = p1.y + p2.y;
	return p;
}

CP2 operator -(const CP2& p1, const CP2& p2)
{
	CP2 p;
	p.x = p1.x - p2.x;
	p.y = p1.y - p2.y;
	return p;
}

CP2 operator *(const CP2& p1, double k)//点和常量的积
{
	CP2 p;
	p.x = p1.x * k;
	p.y = p1.y * k;
	return p;
}

CP2 operator *(double k, const CP2& p1)//点和常量的积
{
	CP2 p;
	p.x = k * p1.x;
	p.y = k * p1.y;
	return p;
}

CP2 operator /(const CP2& p1, double k)//点和常量的除
{
	if (fabs(k) < 1e-6)
		k = 1.0;
	CP2 p;
	p.x = p1.x / k;
	p.y = p1.y / k;
	return p;
}

CP2 operator+=(const CP2& p1, const CP2& p2)
{
	CP2 p;
	p.x = p1.x + p2.x;
	p.y = p1.y + p2.y;
	return p;
}

CP2 operator-=(const CP2& p1, const CP2& p2)
{
	CP2 p;
	p.x = p1.x - p2.x;
	p.y = p1.y - p2.y;
	return p;
}

CP2 operator*=(const CP2& p1, double k)
{
	CP2 p;
	p.x = p1.x * k;
	p.y = p1.y * k;
	return p;
}

CP2 operator/=(const CP2& p1, double k)
{
	if (fabs(k) < 1e-6)
		k = 1.0;
	CP2 p;
	p.x = p1.x / k;
	p.y = p1.y / k;
	return p;
}


bool operator==(const CP2& p1, const CP2& p2) {
	return p1.x == p2.x && p1.y == p2.y;
}


bool operator!=(const CP2& p1, const CP2& p2) {
	return !operator==(p1, p2);
}
