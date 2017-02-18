#include "Vector2.h"


Vector2::Vector2()
{
	dX = 0.f;
	dY = 0.f;
}

Vector2::Vector2(double a_dX, double a_dY)
{
	dX = a_dX;
	dY = a_dY;
}

bool Vector2::operator==(const Vector2 &a_v1)
{
	return (a_v1.dX == dX && a_v1.dY == dY);
}
bool Vector2::operator!=(const Vector2 &a_v1)
{
	return (a_v1.dX != dX && a_v1.dY != dY);
}

double Vector2::operator-(const Vector2 &a_v1)
{
	return (dX - a_v1.dX && dY - a_v1.dY);
}
double Vector2::operator+(const Vector2 &a_v1)
{
	return (dX + a_v1.dX && dY + a_v1.dY);
}
void Vector2::operator+=(const Vector2 &a_v1)
{
	dX += a_v1.dX;
	dY += a_v1.dY;
}
void Vector2::operator-=(const Vector2 &a_v1)
{
	dX -= a_v1.dX;
	dY -= a_v1.dY;
}
double Vector2::operator*=(float a_fScalar)
{
	return (dX * a_fScalar && dY * a_fScalar);
}