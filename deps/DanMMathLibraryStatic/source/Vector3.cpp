#include "../include/Vector3.h"
#include "math.h"
#include "../include/MathUtil.h"


Vector3::Vector3()
{
	dX = 0.f;
	dY = 0.f;
	dZ = 0.f;
}

Vector3::Vector3(Vector2 a_v2)
{
	dX = a_v2.GetdX();
	dY = a_v2.GetdY();
	dZ = 0.f;
}

Vector3::Vector3(double a_dX, double a_dY, double a_dZ)
{
	dX = a_dX;
	dY = a_dY;
	dZ = a_dZ;
}

bool Vector3::operator==(const Vector3 &a_v1)
{
	return (a_v1.dX == dX && a_v1.dY == dY && a_v1.dZ == dZ);
}
bool Vector3::operator!=(const Vector3 &a_v1)
{
	return (a_v1.dX != dX && a_v1.dY != dY && a_v1.dZ != dZ);
}

Vector3 Vector3::operator-(const Vector3 &a_v1)
{
	return Vector3(dX - a_v1.dX, dY - a_v1.dY, dZ - a_v1.dZ);
}
Vector3 Vector3::operator-(double a_dScalar)
{
	return Vector3(dX - a_dScalar, dY - a_dScalar, dZ - a_dScalar);
}
Vector3 Vector3::operator+(const Vector3 &a_v1)
{
	return Vector3(dX + a_v1.dX, dY + a_v1.dY, dZ + a_v1.dZ);
}
Vector3 Vector3::operator+(double a_dScalar)
{
	return Vector3(dX + a_dScalar, dY + a_dScalar, dZ + a_dScalar);
}

Vector3 Vector3::operator*(const Vector3 &a_v1)
{
	return Vector3(dX * a_v1.dX, dY * a_v1.dY, dZ * a_v1.dZ);
}
Vector3 Vector3::operator*(double a_dScalar)
{
	return Vector3(dX * a_dScalar, dY * a_dScalar, dZ * a_dScalar);
}
void Vector3::operator+=(const Vector3 &a_v1)
{
	dX += a_v1.dX;
	dY += a_v1.dY;
	dZ += a_v1.dZ;
}
void Vector3::operator+=(double a_dScalar)
{
	dX += a_dScalar;
	dY += a_dScalar;
	dZ += a_dScalar;
}
void Vector3::operator-=(const Vector3 &a_v1)
{
	dX -= a_v1.dX;
	dY -= a_v1.dY;
	dZ -= a_v1.dZ;
}
void Vector3::operator-=(double a_dScalar)
{
	dX -= a_dScalar;
	dY -= a_dScalar;
	dZ -= a_dScalar;
}

Vector3 Vector3::DotProduct(Vector3 &a_v1)
{
	return Vector3(dX * a_v1.dX, dY * a_v1.dY, dZ * a_v1.dZ);
}
Vector3 Vector3::CrossProduct(Vector3 &a_v1)
{
	return Vector3((dY*a_v1.dZ - dZ * a_v1.dY), (dZ * a_v1.dX - dX * a_v1.dZ), (dX * a_v1.dY - dY * a_v1.dX));
}
Vector3 Vector3::Perpendicular(Vector3 &a_v1)
{
	return Vector3(-(a_v1.dY), a_v1.dX, a_v1.dY);
}
Vector3 Vector3::RotateX(float &a_fDeg)
{
	float x = cos(DegreesToRadians(a_fDeg));
	float y = sin(DegreesToRadians(a_fDeg));
	return Vector3(double(x), double(y), double(y));
}
double Vector3::Magnitude()
{
	return sqrt((dX * dX) + (dY * dY) + (dZ * dZ));
}
Vector3 Vector3::Normalisation()
{
	return Vector3(double(dX / Magnitude()), double((dY / Magnitude())), double((dZ / Magnitude())));
}

double const &Vector3::GetdX()
{
	return dX;
}
double const &Vector3::GetdY()
{
	return dY;
}
double const &Vector3::GetdZ()
{
	return dZ;
}
void Vector3::SetdX(double a_dX)
{
	dX = a_dX;
}
void Vector3::SetdY(double a_dY)
{
	dY = a_dY;
}
void Vector3::SetdZ(double a_dZ)
{
	dZ = a_dZ;
}