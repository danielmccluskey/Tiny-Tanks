#ifndef _Matrix4x4_H_
#define _Matrix4x4_H_

class Matrix4x4
{
public:

	Matrix4x4();
	Matrix4x4(const float a_fMatrix[4][4]);
	Matrix4x4(const float a_fMatrix[16]);
	Matrix4x4(const Matrix4x4 &a_mMatrix);
	~Matrix4x4() {}

	
	friend class Vector4;

	void RotateX(float fRad);
	void RotateY(float fRad);
	void RotateZ(float fRad);
	void Multiply(float a_fScalar);
	void SetIdentity();
	bool Inverse();
	Matrix4x4 Transpose();
	float Determinant();
	void Zero();

	Vector4 operator[](int a_iRow);
	float* GetMatrix();
	double GetMatrixValue(int a_fMatrixValue);
	Matrix4x4 operator*=(Matrix4x4 &a_mMatrix);

	Vector4 GetRow(int iRow);
	Vector4 GetCol(int a_iCol);




private:
	struct
	{
		float m_11, m_12, m_13, m_14;
		float m_21, m_22, m_23, m_24;
		float m_31, m_32, m_33, m_34;
		float m_41, m_42, m_43, m_44;
	};
};
#endif //_Matrix4x4_H_