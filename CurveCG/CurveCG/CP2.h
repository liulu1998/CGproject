#pragma once
class CP2
{
public:
	CP2();
	virtual ~CP2();
	CP2(double, double);
	friend CP2 operator +(const CP2&, const CP2&);
	friend CP2 operator -(const CP2&, const CP2&);
	friend CP2 operator *(const CP2&, double);
	friend CP2 operator *(double, const CP2&);
	friend CP2 operator /(const CP2&, double);
	friend CP2 operator+=(const CP2&, const CP2&);
	friend CP2 operator-=(const CP2&, const CP2&);
	friend CP2 operator*=(const CP2&, double);
	friend CP2 operator/=(const CP2&, double);
	friend bool operator==(const CP2& p1, const CP2& p2);
	friend bool operator!=(const CP2& p1, const CP2& p2);

public:
	double x;
	double y;
	double w;
};
