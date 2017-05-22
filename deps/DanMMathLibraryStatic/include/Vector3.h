#ifndef _VECTOR3_H_
#define _VECTOR3_H_
#include "../include/Vector2.h"
class Vector3
{
public:
	Vector3();
	Vector3(double a_dX, double a_dY, double a_dZ);
	Vector3(Vector2 a_v2);
	~Vector3()
	{

	}
	bool operator==(const Vector3 &a_v1);
	bool operator!=(const Vector3 &a_v1);

	void operator+=(const Vector3 &a_v1);
	void operator+=(double a_dScalar);
	void operator-=(const Vector3 &a_v1);
	void operator-=(double a_dScalar);
	Vector3 operator+(const Vector3 &a_v1);
	Vector3 operator+(double a_dScalar);
	Vector3 operator-(const Vector3 &a_v1);
	Vector3 operator-(double a_dScalar);
	Vector3 operator*(const Vector3 &a_v2);
	Vector3 operator*(double a_fScalar);

	Vector3 DotProduct(Vector3 &a_v1);
	Vector3 Perpendicular(Vector3 &a_v1);
	Vector3 RotateX(float &a_fDeg);
	double Magnitude();
	Vector3 Normalisation();
	Vector3 CrossProduct(Vector3 &a_v1);

	double const &GetdX();
	double const &GetdY();
	double const &GetdZ();
	void SetdX(double a_dX);
	void SetdY(double a_dY);
	void SetdZ(double a_dZ);
private:
	double dX;
	double dY;
	double dZ;
};
#endif //_VECTOR3_H_