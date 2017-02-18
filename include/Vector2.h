#ifndef _VECTOR2_H_
#define _VECTOR2_H_

class Vector2
{
public:
	double dX;
	double dY;

	Vector2();
	Vector2(double a_dX, double a_dY);	

	~Vector2()
	{

	}
	bool operator==(const Vector2 &a_v1);	
	bool operator!=(const Vector2 &a_v1);	
	void operator+=(const Vector2 &a_v1);
	void operator-=(const Vector2 &a_v1);
	double operator+(const Vector2 &a_v1);
	double operator-(const Vector2 &a_v1);
	double operator*=(float a_fScalar);
	 
private:
	
};
#endif //_VECTOR2_H_