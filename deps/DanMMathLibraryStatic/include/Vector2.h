#ifndef _VECTOR2_H_
#define _VECTOR2_H_

class Vector2
{
public:
	Vector2();
	Vector2(double a_dX, double a_dY);	
	~Vector2()
	{

	}
	bool operator==(const Vector2 &a_v1);	
	bool operator!=(const Vector2 &a_v1);	

	void operator+=(const Vector2 &a_v1);
	void operator+=(double a_dScalar);
	void operator-=(const Vector2 &a_v1);
	void operator-=(double a_dScalar);
	Vector2 operator+(const Vector2 &a_v1);
	Vector2 operator+(double a_dScalar);
	Vector2 operator-(const Vector2 &a_v1);
	Vector2 operator-(double a_fScalar);
	Vector2 operator*(const Vector2 &a_v2);
	Vector2 operator*(double a_fScalar);
	
	Vector2 Zero();
	Vector2 DotProduct(const Vector2 &a_v1);
	Vector2 CrossProduct(const Vector2 &a_v1);
	Vector2 Perpendicular(const Vector2 &a_v1);
	Vector2 RotateX(float a_fDeg);
	double Magnitude(const Vector2 &a_v1);
	Vector2 Normalisation(const Vector2 &a_v1);

	double const &GetdX();
	double const &GetdY();
	void SetdX(double a_dX);
	void SetdY(double a_dY);

private:
	double dX;
	double dY;
};
#endif //_VECTOR2_H_