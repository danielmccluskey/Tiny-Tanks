#ifndef _VECTOR4_H_
#define _VECTOR4_H_
#include "../include/Vector3.h"
class Vector4
{
public:
	Vector4();
	Vector4(double a_dX, double a_dY, double a_dZ, double a_dW);
	Vector4(Vector2 a_v2);
	Vector4(Vector3 a_v2);

	~Vector4()
	{

	}
	bool operator==(const Vector4 &a_v1);
	bool operator!=(const Vector4 &a_v1);
	
	void operator+=(const Vector4 &a_v1);
	void operator+=(double a_dScalar);
	void operator-=(const Vector4 &a_v1);
	void operator-=(double a_dScalar);
	Vector4 operator+(const Vector4 &a_v1);
	Vector4 operator+(double a_dScalar);
	Vector4 operator-(const Vector4 &a_v1);
	Vector4 operator-(double a_fScalar);
	Vector4 operator*(const Vector4 &a_v2);
	Vector4 operator*(double a_fScalar);

	Vector4 DotProduct(const Vector4 &a_v1);
	Vector4 Perpendicular(const Vector4 &a_v1);
	Vector4 RotateX(float &a_fDeg);
	double Magnitude();
	Vector4 Normalisation();

	double const &GetdX();
	double const &GetdY();
	double const &GetdZ();
	double const &GetdW();
	void SetdX(double a_dX);
	void SetdY(double a_dY);
	void SetdZ(double a_dZ);
	void SetdW(double a_dW);
private:
	double dX;
	double dY;
	double dZ;
	double dW;
};
#endif //_VECTOR4_H_