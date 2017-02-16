#include "Vector4.h"


Vector4::Vector4()
{
	dX = 0.f;
	dY = 0.f;
	dZ = 0.f;
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

double Vector4::operator-(const Vector4 &a_v1)
{
	return (dX - a_v1.dX && dY - a_v1.dY && dZ - a_v1.dZ && dW - a_v1.dW);
}
double Vector4::operator+(const Vector4 &a_v1)
{
	return (dX + a_v1.dX && dY + a_v1.dY && dZ + a_v1.dZ && dW + a_v1.dW);
}
void Vector4::operator+=(const Vector4 &a_v1)
{
	dX += a_v1.dX;
	dY += a_v1.dY;
	dZ += a_v1.dZ;
	dW += a_v1.dW;
}
void Vector4::operator-=(const Vector4 &a_v1)
{
	dX -= a_v1.dX;
	dY -= a_v1.dY;
	dZ -= a_v1.dZ;
	dW -= a_v1.dW;
}