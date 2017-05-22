#ifndef _Matrix3x3_H_
#define _Matrix3x3_H_

class Matrix3x3
{
public:

	Matrix3x3();
	Matrix3x3(const float a_fMatrix[3][3]);
	Matrix3x3(const float a_fMatrix[9]);
	Matrix3x3(const Matrix3x3 &a_mMatrix);
	~Matrix3x3() {}

	
	friend class Vector3;

	void RotateX(float fRad);
	void RotateY(float fRad);
	void RotateZ(float fRad);
	void SetIdentity();
	void Inverse();
	Matrix3x3 Transpose();
	float Determinant();
	void Zero();

	Vector3 operator[](int a_iRow);

	void operator+=(const Matrix3x3 &a_mMatrix);
	void operator+=(double a_dScalar);
	void operator-=(const Matrix3x3 &a_mMatrix);
	void operator-=(double a_dScalar);
	Matrix3x3 operator+(const Matrix3x3 &a_mMatrix);
	Matrix3x3 operator+(double a_dScalar);
	Matrix3x3 operator-(const Matrix3x3 &a_mMatrix);
	Matrix3x3 operator-(double a_dScalar);
	Matrix3x3 operator*(const Matrix3x3 &a_mMatrix);
	Matrix3x3 operator*(double a_dScalar);



	Vector3 GetRow(int iRow);
	Vector3 GetCol(int a_iCol);
	float* GetMatrix();
	double GetMatrixValue(int a_fMatrixValue);
	void Setter();


private:
	struct
	{
		float m_11, m_12, m_13;
		float m_21, m_22, m_23;
		float m_31, m_32, m_33;
	};
};
#endif //_Matrix3x3_H_