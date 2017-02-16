#ifndef _VECTOR3_H_
#define _VECTOR3_H_
class Vector3
{
public:
	double dX;
	double dY;
	double dZ;

	Vector3();
	Vector3(double a_dX, double a_dY, double a_dZ);

	~Vector3()
	{

	}
	bool operator==(const Vector3 &a_v1);
	bool operator!=(const Vector3 &a_v1);
	void operator+=(const Vector3 &a_v1);
	void operator-=(const Vector3 &a_v1);
	double operator+(const Vector3 &a_v1);
	double operator-(const Vector3 &a_v1);

private:

};
#endif //_VECTOR3_H_