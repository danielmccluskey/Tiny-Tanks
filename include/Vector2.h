#pragma once
class Vector2
{
public:
	

	Vector2(double x, double y);

	bool operator==(const Vector2 &a_v1)
	{
		return (a_v1.dX == dX && a_v1.dY == dY);
	}
	bool operator!=(const Vector2 &a_v1)
	{
		return (a_v1.dX != dX && a_v1.dY != dY);
	}
	void operator+(const Vector2 &a_v1)
	{
		dX += a_v1.dX;
		dY += a_v1.dY;
	}
	void operator-(const Vector2 &a_v1)
	{
		dX -= a_v1.dX;
		dY -= a_v1.dY;
	}
	 
private:
	double dX;
	double dY;
};