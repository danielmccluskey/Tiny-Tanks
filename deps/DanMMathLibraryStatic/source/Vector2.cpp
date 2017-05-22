#include "../include/Vector2.h"
#include "../include/MathUtil.h"


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

Vector2 Vector2::Zero()
{
	dX = 0.0f;
	dY = 0.0f;
	return *this;
}
bool Vector2::operator==(const Vector2 &a_v1)
{
	return (a_v1.dX == dX && a_v1.dY == dY);
}
bool Vector2::operator!=(const Vector2 &a_v1)
{
	return (a_v1.dX != dX && a_v1.dY != dY);
}

Vector2 Vector2::operator-(const Vector2 &a_v1)
{
	return Vector2(dX - a_v1.dX, dY - a_v1.dY);
}
Vector2 Vector2::operator-(double a_dScalar)
{
	return Vector2(dX - a_dScalar, dY - a_dScalar);
}
Vector2 Vector2::operator+(const Vector2 &a_v1)
{
	return Vector2(dX + a_v1.dX, dY + a_v1.dY);
}
Vector2 Vector2::operator+(double a_dScalar)
{
	return Vector2(dX + a_dScalar, dY + a_dScalar);
}
void Vector2::operator+=(const Vector2 &a_v1)
{
	dX += a_v1.dX;
	dY += a_v1.dY;
}
void Vector2::operator+=(double a_dScalar)
{
	dX += a_dScalar;
	dY += a_dScalar;
}
void Vector2::operator-=(const Vector2 &a_v1)
{
	dX -= a_v1.dX;
	dY -= a_v1.dY;
}
void Vector2::operator-=(double a_dScalar)
{
	dX -= a_dScalar;
	dY -= a_dScalar;
}
Vector2 Vector2::operator*(double a_fScalar)
{
	return Vector2(dX * a_fScalar, dY * a_fScalar);
}
Vector2 Vector2::operator*(const Vector2 &a_v2)
{
	return Vector2(dX * a_v2.dY, dY * a_v2.dY);
}

Vector2 Vector2::DotProduct(const Vector2 &a_v1)
{
	return Vector2((dX * a_v1.dX), (dY * a_v1.dY));
}
Vector2 Vector2::CrossProduct(const Vector2 &a_v1)
{
	return Vector2(dX * a_v1.dY, dY * a_v1.dX);
}

Vector2 Vector2::Perpendicular(const Vector2 &a_v1)
{
	return Vector2(a_v1.dY, -(a_v1.dX));
}
Vector2 Vector2::RotateX(float a_fDeg) 
{
	float x = cos(DegreesToRadians(a_fDeg));
	float y = sin(DegreesToRadians(a_fDeg));
	return Vector2(x, y);
}
double Vector2::Magnitude(const Vector2 &a_v1)
{
	return sqrt((a_v1.dX * a_v1.dX) + (a_v1.dY * a_v1.dY));
}
Vector2 Vector2::Normalisation(const Vector2 &a_v1)
{
	return Vector2(double(a_v1.dX / Magnitude(a_v1)), double((a_v1.dY / Magnitude(a_v1))));
}

double const &Vector2::GetdX()
{
	return dX;
}
double const &Vector2::GetdY()
{
	return dY;
}
void Vector2::SetdX(double a_dX)
{
	dX = a_dX;
}
void Vector2::SetdY(double a_dY)
{
	dY = a_dY;
}