#include "../include/Matrix3x3.h"
#include "../include/Vector3.h"
#include <cmath>

/*Overloaded operator functions for add, subtract, and multiply by both a scalar value
Vector3 and by a Matrix3x3.

Functions to rotate around euler axis,
inversion, scale, transpose a point,
set to identity, set to zero, override access operators to retrieve matrix value at row / column.*/

Matrix3x3::Matrix3x3()
{
	m_11 = 0.f, m_12 = 0.f, m_13 = 0.f;
	m_21 = 0.f, m_22 = 0.f, m_23 = 0.f;
	m_31 = 0.f, m_32 = 0.f, m_33 = 0.f;
}

Matrix3x3::Matrix3x3(const float a_fMatrix[3][3])
{
	m_11 = a_fMatrix[0][0], m_12 = a_fMatrix[0][1], m_13 = a_fMatrix[0][2];
	m_21 = a_fMatrix[1][0], m_22 = a_fMatrix[1][1], m_23 = a_fMatrix[1][2];
	m_31 = a_fMatrix[2][0], m_32 = a_fMatrix[2][1], m_33 = a_fMatrix[2][2];
}
Matrix3x3::Matrix3x3(const float a_fMatrix[9])
{
	m_11 = a_fMatrix[0], m_12 = a_fMatrix[1], m_13 = a_fMatrix[2];
	m_21 = a_fMatrix[3], m_22 = a_fMatrix[4], m_23 = a_fMatrix[5];
	m_31 = a_fMatrix[6], m_32 = a_fMatrix[7], m_33 = a_fMatrix[8];
}
Matrix3x3::Matrix3x3(const Matrix3x3 &a_mMatrix)
{
	m_11 = a_mMatrix.m_11, m_12 = a_mMatrix.m_12, m_13 = a_mMatrix.m_13;
	m_21 = a_mMatrix.m_21, m_22 = a_mMatrix.m_22, m_23 = a_mMatrix.m_23;
	m_31 = a_mMatrix.m_31, m_32 = a_mMatrix.m_32, m_33 = a_mMatrix.m_33;
}


Vector3 Matrix3x3::operator[](int a_iRow)
{
	switch (a_iRow)
	{
	case 0:
		return Vector3(m_11, m_12, m_13);
		break;

	case 1:
		return Vector3(m_21, m_22, m_23);
		break;

	default:
		return Vector3(m_31, m_32, m_33);
		break;
	}
}

void Matrix3x3::operator+=(const Matrix3x3 &a_mMatrix)
{
	m_11 += a_mMatrix.m_11, m_12 += a_mMatrix.m_12, m_13 += a_mMatrix.m_13;
	m_21 += a_mMatrix.m_21, m_22 += a_mMatrix.m_22, m_23 += a_mMatrix.m_23;
	m_31 += a_mMatrix.m_31, m_32 += a_mMatrix.m_32, m_33 += a_mMatrix.m_33;
}
void Matrix3x3::operator+=(double a_dScalar)
{
	m_11 += a_dScalar, m_12 += a_dScalar, m_13 += a_dScalar;
	m_21 += a_dScalar, m_22 += a_dScalar, m_23 += a_dScalar;
	m_31 += a_dScalar, m_32 += a_dScalar, m_33 += a_dScalar;
}
void Matrix3x3::operator-=(const Matrix3x3 &a_mMatrix)
{
	m_11 -= a_mMatrix.m_11, m_12 -= a_mMatrix.m_12, m_13 -= a_mMatrix.m_13;
	m_21 -= a_mMatrix.m_21, m_22 -= a_mMatrix.m_22, m_23 -= a_mMatrix.m_23;
	m_31 -= a_mMatrix.m_31, m_32 -= a_mMatrix.m_32, m_33 -= a_mMatrix.m_33;
}
void Matrix3x3::operator-=(double a_dScalar)
{
	m_11 -= a_dScalar, m_12 -= a_dScalar, m_13 -= a_dScalar;
	m_21 -= a_dScalar, m_22 -= a_dScalar, m_23 -= a_dScalar;
	m_31 -= a_dScalar, m_32 -= a_dScalar, m_33 -= a_dScalar;
}
Matrix3x3 Matrix3x3::operator+(const Matrix3x3 &a_mMatrix)
{
	m_11 + a_mMatrix.m_11, m_12 + a_mMatrix.m_12, m_13 + a_mMatrix.m_13;
	m_21 + a_mMatrix.m_21, m_22 + a_mMatrix.m_22, m_23 + a_mMatrix.m_23;
	m_31 + a_mMatrix.m_31, m_32 + a_mMatrix.m_32, m_33 + a_mMatrix.m_33;
	return *this;
}
Matrix3x3 Matrix3x3::operator+(double a_dScalar)
{
	m_11 + a_dScalar, m_12 + a_dScalar, m_13 + a_dScalar;
	m_21 + a_dScalar, m_22 + a_dScalar, m_23 + a_dScalar;
	m_31 + a_dScalar, m_32 + a_dScalar, m_33 + a_dScalar;
	return *this;
}
Matrix3x3 Matrix3x3::operator-(const Matrix3x3 &a_mMatrix)
{
	m_11 + a_mMatrix.m_11, m_12 + a_mMatrix.m_12, m_13 + a_mMatrix.m_13;
	m_21 + a_mMatrix.m_21, m_22 + a_mMatrix.m_22, m_23 + a_mMatrix.m_23;
	m_31 + a_mMatrix.m_31, m_32 + a_mMatrix.m_32, m_33 + a_mMatrix.m_33;
	return *this;
}
Matrix3x3 Matrix3x3::operator-(double a_dScalar)
{
	m_11 - a_dScalar, m_12 - a_dScalar, m_13 - a_dScalar;
	m_21 - a_dScalar, m_22 - a_dScalar, m_23 - a_dScalar;
	m_31 - a_dScalar, m_32 - a_dScalar, m_33 - a_dScalar;
	return *this;

}
Matrix3x3 Matrix3x3::operator*(const Matrix3x3 &a_mMatrix)
{
	m_11 * a_mMatrix.m_11, m_12 * a_mMatrix.m_12, m_13 * a_mMatrix.m_13;
	m_21 * a_mMatrix.m_21, m_22 * a_mMatrix.m_22, m_23 * a_mMatrix.m_23;
	m_31 * a_mMatrix.m_31, m_32 * a_mMatrix.m_32, m_33 * a_mMatrix.m_33;
	return *this;
}
Matrix3x3 Matrix3x3::operator*(double a_dScalar)
{
	m_11 * a_dScalar, m_12 * a_dScalar, m_13 * a_dScalar;
	m_21 * a_dScalar, m_22 * a_dScalar, m_23 * a_dScalar;
	m_31 * a_dScalar, m_32 * a_dScalar, m_33 * a_dScalar;
	return *this;
}


void Matrix3x3::RotateX(float a_fRad)
{
	const float fCos = cosf(a_fRad);
	const float fSin = sinf(a_fRad);
	m_11 = 1.f, m_12 = 0.f, m_13 = 0.f;
	m_21 = 0.f, m_22 = fCos, m_23 = -fSin;
	m_31 = 0.f, m_32 = fSin, m_33 = fCos;
}

void Matrix3x3::RotateY(float a_fRad)
{
	const float fCos = cosf(a_fRad);
	const float fSin = sinf(a_fRad);
	m_11 = fCos, m_12 = 0.f, m_13 = fSin;
	m_21 = 0.f, m_22 = 1.f, m_23 = 0.f;
	m_31 = -fSin, m_32 = 0.f, m_33 = fCos;

}
void Matrix3x3::RotateZ(float a_fRad)
{
	const float fCos = cosf(a_fRad);
	const float fSin = sinf(a_fRad);
	m_11 = fCos, m_12 = -fSin, m_13 = 0.f;
	m_21 = fSin, m_22 = fCos, m_23 = 0.f;
	m_31 = 0.f, m_32 = 0.f, m_33 = 1.f;

}

void Matrix3x3::SetIdentity()
{
	m_11 = 1.f, m_12 = 0.f, m_13 = 0.f;
	m_21 = 0.f, m_22 = 1.f, m_23 = 0.f;
	m_31 = 0.f, m_32 = 0.f, m_33 = 1.f;
}
float Matrix3x3::Determinant()
{
	return (m_11 * (m_22 * m_33 - m_23 * m_32) +
		m_12 * (m_23 * m_31 - m_21 * m_33) +
		m_13 * (m_21 * m_32 - m_22 * m_31));
}

void Matrix3x3::Inverse()
{
	float fDet = Determinant();
	if (fDet != 0.f)
	{
		float fInvDet = 1 / fDet;
		Matrix3x3 m3Temp = *this;
		m_11 = (m3Temp.m_22 * m3Temp.m_33 - m3Temp.m_23 * m3Temp.m_32) * fInvDet;
		m_12 = (m3Temp.m_13 * m3Temp.m_32 - m3Temp.m_12 * m3Temp.m_33) * fInvDet;
		m_13 = (m3Temp.m_12 * m3Temp.m_23 - m3Temp.m_13 * m3Temp.m_22) * fInvDet;

		m_21 = (m3Temp.m_23 * m3Temp.m_31 - m3Temp.m_21 * m3Temp.m_33) * fInvDet;
		m_22 = (m3Temp.m_11 * m3Temp.m_33 - m3Temp.m_13 * m3Temp.m_31) * fInvDet;
		m_23 = (m3Temp.m_13 * m3Temp.m_21 - m3Temp.m_11 * m3Temp.m_23) * fInvDet;

		m_31 = (m3Temp.m_21 * m3Temp.m_32 - m3Temp.m_22 * m3Temp.m_31) * fInvDet;
		m_32 = (m3Temp.m_12 * m3Temp.m_31 - m3Temp.m_11 * m3Temp.m_32) * fInvDet;
		m_33 = (m3Temp.m_11 * m3Temp.m_22 - m3Temp.m_12 * m3Temp.m_21) * fInvDet;	

	}
}
Matrix3x3 Matrix3x3::Transpose()
{
	Matrix3x3 mTemp3x3;
	mTemp3x3.m_11 = m_11, mTemp3x3.m_21 = m_12, mTemp3x3.m_13 = m_31;
	mTemp3x3.m_21 = m_12, mTemp3x3.m_22 = m_22, mTemp3x3.m_23 = m_32;
	mTemp3x3.m_31 = m_13, mTemp3x3.m_23 = m_32, mTemp3x3.m_33 = m_33;
	return mTemp3x3;
}
void  Matrix3x3::Zero()
{
	m_11 = 0.f, m_12 = 0.f, m_13 = 0.f;
	m_21 = 0.f, m_22 = 0.f, m_23 = 0.f;
	m_31 = 0.f, m_32 = 0.f, m_33 = 0.f;
}









Vector3 Matrix3x3::GetRow(int a_iRow)
{
	switch (a_iRow)
	{
	case 0:
		return Vector3(m_11, m_12, m_13);
		break;

	case 1:
		return Vector3(m_21, m_22, m_23);
		break;

	default:
		return Vector3(m_31, m_32, m_33);
		break;
	}
}
Vector3 Matrix3x3::GetCol(int a_iCol)
{
	switch (a_iCol)
	{
	case 0:
		return Vector3(m_11, m_21, m_31);
		break;

	case 1:
		return Vector3(m_12, m_22, m_32);
		break;

	default:
		return Vector3(m_13, m_33, m_33);
		break;
	}
}
float* Matrix3x3::GetMatrix()
{
	float fArray[9] = { m_11, m_12, m_13, m_21, m_22, m_23, m_31, m_32, m_33 };
	return fArray;
}
double Matrix3x3::GetMatrixValue(int a_fMatrixValue)
{
	switch (a_fMatrixValue)
	{
	case 0:
		return m_11;
		break;
	case 1:
		return m_12;
		break;
	case 2:
		return m_13;
		break;
	case 3:
		return m_21;
		break;
	case 4:
		return m_22;
		break;
	case 5:
		return m_23;
		break;
	case 6:
		return m_31;
		break;
	case 7:
		return m_32;
		break;
	case 8:
		return m_33;
		break;
	}


}