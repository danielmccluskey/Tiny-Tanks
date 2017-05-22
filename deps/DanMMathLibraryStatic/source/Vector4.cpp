#include "../include/Vector4.h"
#include "../include/MathUtil.h"
#include <cmath>


Vector4::Vector4()
{
	dX = 0.f;
	dY = 0.f;
	dZ = 0.f;
	dW = 0.f;
}
Vector4::Vector4(Vector2 a_v2)
{
	dX = a_v2.GetdX();
	dY = a_v2.GetdY();
	dZ = 0.f;
	dW = 0.f;
}
Vector4::Vector4(Vector3 a_v2)
{
	dX = a_v2.GetdX();
	dY = a_v2.GetdY();
	dZ = a_v2.GetdZ();
	dW = 0.f;
}

Vector4::Vector4(double a_dX, double a_dY, double a_dZ, double a_dW)
{
	dX = a_dX;
	dY = a_dY;
	dZ = a_dZ;
	dW = a_dW;
}


bool Vector4::operator==(const Vector4 &a_v1)
{
	return (a_v1.dX == dX && a_v1.dY == dY && a_v1.dZ == dZ && a_v1.dW == dW);
}
bool Vector4::operator!=(const Vector4 &a_v1)
{
	return (a_v1.dX != dX && a_v1.dY != dY && a_v1.dZ != dZ && a_v1.dW != dW);
}


Vector4 Vector4::operator-(const Vector4 &a_v1)
{
	return Vector4(dX - a_v1.dX, dY - a_v1.dY, dZ - a_v1.dZ, dW - a_v1.dW);
}
Vector4 Vector4::operator-(double a_dScalar)
{
	return Vector4(dX - a_dScalar, dY - a_dScalar, dZ - a_dScalar, dW - a_dScalar);
}
Vector4 Vector4::operator+(const Vector4 &a_v1)
{
	return Vector4(dX + a_v1.dX, dY + a_v1.dY, dZ + a_v1.dZ, dW + a_v1.dW);
}
Vector4 Vector4::operator+(double a_dScalar)
{
	return Vector4(dX + a_dScalar, dY + a_dScalar, dZ + a_dScalar, dW + a_dScalar);
}
Vector4 Vector4::operator*(const Vector4 &a_v1)
{
	return Vector4(dX * a_v1.dX, dY * a_v1.dY, dZ * a_v1.dZ, dW * a_v1.dW);
}
Vector4 Vector4::operator*(double a_dScalar)
{
	return Vector4(dX * a_dScalar, dY * a_dScalar, dZ * a_dScalar, dW * a_dScalar);
}
void Vector4::operator+=(const Vector4 &a_v1)
{
	dX += a_v1.dX;
	dY += a_v1.dY;
	dZ += a_v1.dZ;
	dW += a_v1.dW;
}
void Vector4::operator+=(double a_dScalar)
{
	dX += a_dScalar;
	dY += a_dScalar;
	dZ += a_dScalar;
	dW += a_dScalar;
}
void Vector4::operator-=(const Vector4 &a_v1)
{
	dX -= a_v1.dX;
	dY -= a_v1.dY;
	dZ -= a_v1.dZ;
	dW -= a_v1.dW;
}
void Vector4::operator-=(double a_dScalar)
{
	dX -= a_dScalar;
	dY -= a_dScalar;
	dZ -= a_dScalar;
	dW -= a_dScalar;
}

Vector4 Vector4::DotProduct(const Vector4 &a_v1)
{
	return Vector4(dX * a_v1.dX, dY * a_v1.dY, dZ * a_v1.dZ, dW * a_v1.dW);
}
Vector4 Vector4::Perpendicular(const Vector4 &a_v1)
{
	return Vector4(-(a_v1.dY), a_v1.dX, a_v1.dY, a_v1.dW);
}
Vector4 Vector4::RotateX(float &a_fDeg)
{
	float x = cos(DegreesToRadians(a_fDeg));
	float y = sin(DegreesToRadians(a_fDeg));
	return Vector4(double(x), double(y), double(y), double(y));
}
double Vector4::Magnitude()
{
	return sqrt((dX * dX) + (dY * dY) + (dZ * dZ) + (dW * dW));
}
Vector4 Vector4::Normalisation()
{
	float fInv = 1.0f / Magnitude();

	dX *= fInv;
	dY *= fInv;
	dZ *= fInv;
	dW *= fInv;

	return *this;
}

double const &Vector4::GetdX()
{
	return dX;
}
double const &Vector4::GetdY()
{
	return dY;
}
double const &Vector4::GetdZ()
{
	return dZ;
}
double const &Vector4::GetdW()
{
	return dW;
}
void Vector4::SetdX(double a_dX)
{
	dX = a_dX;
}
void Vector4::SetdY(double a_dY)
{
	dY = a_dY;
}
void Vector4::SetdZ(double a_dZ)
{
	dZ = a_dZ;
}
void Vector4::SetdW(double a_dW)
{
	dW = a_dW;
}