#pragma once
class Vector2
{
public:
	
	Vector2::Vector2()
	{
		dX = 0.f;
		dY = 0.f;
	}

	Vector2(double a_dX, double a_dY)
	{
		dX = a_dX;
		dY = a_dY;
	}

	bool operator==(const Vector2 &a_v1)
	{
		return (a_v1.dX == dX && a_v1.dY == dY);
	}
	bool operator!=(const Vector2 &a_v1)
	{
		return (a_v1.dX != dX && a_v1.dY != dY);
	}
	void operator+=(const Vector2 &a_v1)
	{
		dX += a_v1.dX;
		dY += a_v1.dY;
	}
	void operator-(const Vector2 &a_v1)
	{
		dX -= a_v1.dX;
		dY -= a_v1.dY;
	}
	double dX;
	double dY;
	 
private:
	
};