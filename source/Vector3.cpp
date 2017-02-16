#include "Vector3.h"


Vector3::Vector3()
{
	dX = 0.f;
	dY = 0.f;
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

double Vector3::operator-(const Vector3 &a_v1)
{
	return (dX - a_v1.dX && dY - a_v1.dY && dZ - a_v1.dZ);
}
double Vector3::operator+(const Vector3 &a_v1)
{
	return (dX + a_v1.dX && dY + a_v1.dY && dZ + a_v1.dZ);
}
void Vector3::operator+=(const Vector3 &a_v1)
{
	dX += a_v1.dX;
	dY += a_v1.dY;
	dZ += a_v1.dZ;
}
void Vector3::operator-=(const Vector3 &a_v1)
{
	dX -= a_v1.dX;
	dY -= a_v1.dY;
	dZ -= a_v1.dZ;
}