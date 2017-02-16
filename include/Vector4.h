#ifndef _VECTOR4_H_
#define _VECTOR4_H_
class Vector4
{
public:
	double dX;
	double dY;
	double dZ;
	double dW;

	Vector4();
	Vector4(double a_dX, double a_dY, double a_dZ, double a_dW);

	~Vector4()
	{

	}
	bool operator==(const Vector4 &a_v1);
	bool operator!=(const Vector4 &a_v1);
	void operator+=(const Vector4 &a_v1);
	void operator-=(const Vector4 &a_v1);
	double operator+(const Vector4 &a_v1);
	double operator-(const Vector4 &a_v1);

private:

};
#endif //_VECTOR4_H_