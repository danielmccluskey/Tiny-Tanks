#ifndef _MATHLIBARY_H_
#define _MATHLIBARY_H_
//#include <cmath>




class Vector2
{
public:
	double x;
	double y;

	Vector2(double x, double y);
};

const float fPI = 3.14159265359; //Defining PI
const float RadiansToDegrees(float a_Deg) { return ((a_Deg * 180.0f) / fPI); };
const float DegreesToRadians(float a_Deg) { return ((a_Deg * fPI) / 180.0f); };



#endif // _MATHLIBARY_H_