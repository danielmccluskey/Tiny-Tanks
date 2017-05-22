#include "../include/Matrix4x4.h"
#include "../include/Vector4.h"
#include <cmath>

Matrix4x4::Matrix4x4()
{
	m_11 = 1.f, m_12 = 0.f, m_13 = 0.f, m_14 = 0.f;
	m_21 = 0.f, m_22 = 1.f, m_23 = 0.f; m_14 = 0.f;
	m_31 = 0.f, m_32 = 0.f, m_33 = 1.f; m_14 = 0.f;
	m_31 = 0.f, m_32 = 0.f, m_33 = 0.f; m_14 = 1.f;
}
Matrix4x4::Matrix4x4(const float a_fMatrix[4][4])
{
	m_11 = a_fMatrix[0][0], m_12 = a_fMatrix[0][1], m_13 = a_fMatrix[0][2], m_14 = a_fMatrix[0][3];
	m_21 = a_fMatrix[1][0], m_22 = a_fMatrix[1][1], m_23 = a_fMatrix[1][2]; m_14 = a_fMatrix[1][3];
	m_31 = a_fMatrix[2][0], m_32 = a_fMatrix[2][1], m_33 = a_fMatrix[2][2]; m_14 = a_fMatrix[2][3];
	m_31 = a_fMatrix[3][0], m_32 = a_fMatrix[3][1], m_33 = a_fMatrix[3][2]; m_14 = a_fMatrix[3][3];
}
Matrix4x4::Matrix4x4(const float a_fMatrix[16])
{
	m_11 = a_fMatrix[0], m_12 = a_fMatrix[1], m_13 = a_fMatrix[2], m_14 = a_fMatrix[3];
	m_21 = a_fMatrix[4], m_22 = a_fMatrix[5], m_23 = a_fMatrix[6], m_24 = a_fMatrix[7];
	m_31 = a_fMatrix[8], m_32 = a_fMatrix[9], m_33 = a_fMatrix[10], m_24 = a_fMatrix[11];
	m_41 = a_fMatrix[12], m_42 = a_fMatrix[13], m_43 = a_fMatrix[14], m_44 = a_fMatrix[15];
}
Matrix4x4::Matrix4x4(const Matrix4x4 &a_mMatrix)
{
	m_11 = a_mMatrix.m_11, m_12 = a_mMatrix.m_12, m_13 = a_mMatrix.m_13, m_14 = a_mMatrix.m_14;
	m_21 = a_mMatrix.m_21, m_22 = a_mMatrix.m_22, m_23 = a_mMatrix.m_23, m_24 = a_mMatrix.m_24;
	m_31 = a_mMatrix.m_31, m_32 = a_mMatrix.m_32, m_33 = a_mMatrix.m_33, m_34 = a_mMatrix.m_34;
	m_41 = a_mMatrix.m_41, m_42 = a_mMatrix.m_32, m_43 = a_mMatrix.m_43, m_44 = a_mMatrix.m_44;
}

void Matrix4x4::RotateX(float a_fRad)
{
	const float fCos = cosf(a_fRad);
	const float fSin = sinf(a_fRad);
	m_11 = 1.f,		m_12 = 0.f,		m_13 = 0.f,		m_14 = 0.f;
	m_21 = 0.f,		m_22 = fCos,	m_23 = fSin,	m_24 = 0.f;
	m_31 = 0.f,		m_32 = -fSin,	m_33 = fCos,	m_34 = 0.f;
	m_41 = 0.f,		m_42 = 0.f,		m_43 = 0.f,		m_44 = 1.f;

}

void Matrix4x4::RotateY(float a_fRad)
{
	const float fCos = cosf(a_fRad);
	const float fSin = sinf(a_fRad);
	m_11 = fCos,	m_12 = 0.f,		m_13 = -fSin,	m_14 = 0.f;
	m_21 = 0.f,		m_22 = 1.f,		m_23 = 0.f,		m_24 = 0.f;
	m_31 = fSin,	m_32 = 0.f,		m_33 = fCos,	m_34 = 0.f;
	m_41 = 0.f,		m_42 = 0.f,		m_43 = 0.f,		m_44 = 1.f;

}
void Matrix4x4::RotateZ(float a_fRad)
{
	const float fCos = cos(a_fRad);
	const float fSin = sin(a_fRad);
	m_11 = fCos,	m_12 = fSin,	m_13 = 0.f,		m_14 = 0.f;
	m_21 = -fSin,	m_22 = fCos,	m_23 = 0.f,		m_24 = 0.f;
	m_31 = 0.f,		m_32 = 0.f,		m_33 = 1.f,		m_34 = 0.f;
	m_41 = 0.f,		m_42 = 0.f,		m_43 = 0.f,		m_44 = 1.f;
}

Matrix4x4 Matrix4x4::operator*=(Matrix4x4 &a_mMatrix)
{
	m_11 = a_mMatrix.m_11, m_12 = a_mMatrix.m_12, m_13 *= a_mMatrix.m_13, m_14 *= a_mMatrix.m_14;
	m_21 = a_mMatrix.m_21, m_22 = a_mMatrix.m_22, m_23 *= a_mMatrix.m_23, m_24 *= a_mMatrix.m_24;
	m_31 *= a_mMatrix.m_31, m_32 *= a_mMatrix.m_32, m_33 *= a_mMatrix.m_33, m_34 *= a_mMatrix.m_34;
	m_41 *= a_mMatrix.m_41, m_42 *= a_mMatrix.m_32, m_43 *= a_mMatrix.m_43, m_44 *= a_mMatrix.m_44;
	Matrix4x4 mReturnMatrix(GetMatrix());
	return mReturnMatrix;
}

void Matrix4x4::SetIdentity()
{
	m_11 = 1.f, m_12 = 0.f, m_13 = 0.f, m_14 = 0.f;
	m_21 = 0.f, m_22 = 1.f, m_23 = 0.f; m_14 = 0.f;
	m_31 = 0.f, m_32 = 0.f, m_33 = 1.f; m_14 = 0.f;
	m_31 = 0.f, m_32 = 0.f, m_33 = 0.f; m_14 = 1.f;
}
float Matrix4x4::Determinant()
{
	return (m_11 * (m_22 * m_33 - m_23 * m_32) +
		m_12 * (m_23 * m_31 - m_21 * m_33) +
		m_13 * (m_21 * m_32 - m_22 * m_31));
}

bool Matrix4x4::Inverse()
{
	float fDet = Determinant();
	if (fDet != 0.f)
	{
		float fInvDet = 1 / fDet;
		Matrix4x4 m3Temp = *this;
		m_11 = (m3Temp.m_22 * m3Temp.m_33 - m3Temp.m_23 * m3Temp.m_32) * fInvDet;
		m_12 = (m3Temp.m_13 * m3Temp.m_32 - m3Temp.m_12 * m3Temp.m_33) * fInvDet;
		m_13 = (m3Temp.m_12 * m3Temp.m_23 - m3Temp.m_13 * m3Temp.m_22) * fInvDet;
		m_14 = 0.0f;

		m_21 = (m3Temp.m_23 * m3Temp.m_31 - m3Temp.m_21 * m3Temp.m_33) * fInvDet;
		m_22 = (m3Temp.m_11 * m3Temp.m_33 - m3Temp.m_13 * m3Temp.m_31) * fInvDet;
		m_23 = (m3Temp.m_13 * m3Temp.m_21 - m3Temp.m_11 * m3Temp.m_23) * fInvDet;
		m_24 = 0.0f;

		m_31 = (m3Temp.m_21 * m3Temp.m_32 - m3Temp.m_22 * m3Temp.m_31) * fInvDet;
		m_32 = (m3Temp.m_12 * m3Temp.m_31 - m3Temp.m_11 * m3Temp.m_32) * fInvDet;
		m_33 = (m3Temp.m_11 * m3Temp.m_22 - m3Temp.m_12 * m3Temp.m_21) * fInvDet;
		m_34 = 0.0f;

		m_41 = (m3Temp.m_21 * (m3Temp.m_33 * m3Temp.m_42 - m3Temp.m_32 * m3Temp.m_43) +
				m3Temp.m_22 * (m3Temp.m_31 * m3Temp.m_43 - m3Temp.m_33 * m3Temp.m_41) +
				m3Temp.m_23 * (m3Temp.m_32 * m3Temp.m_41 - m3Temp.m_31 * m3Temp.m_42) * fInvDet);


		m_42 = (m3Temp.m_11 * (m3Temp.m_32 * m3Temp.m_43 - m3Temp.m_33 * m3Temp.m_42) +
				m3Temp.m_12 * (m3Temp.m_33 * m3Temp.m_41 - m3Temp.m_31 * m3Temp.m_43) +
				m3Temp.m_13 * (m3Temp.m_31 * m3Temp.m_42 - m3Temp.m_32 * m3Temp.m_41) * fInvDet);


		m_43 = (m3Temp.m_21 * (m3Temp.m_23 * m3Temp.m_42 - m3Temp.m_22 * m3Temp.m_43) +
				m3Temp.m_12 * (m3Temp.m_21 * m3Temp.m_43 - m3Temp.m_23 * m3Temp.m_41) +
				m3Temp.m_13 * (m3Temp.m_22 * m3Temp.m_41 - m3Temp.m_21 * m3Temp.m_42) * fInvDet);
		m_41 = 1.f;

		return true;
	}
	else
	{
		return false;
	}
}
Matrix4x4 Matrix4x4::Transpose()
{
	Matrix4x4 mTemp3x3;
	mTemp3x3.m_11 = m_11, mTemp3x3.m_12 = m_21, mTemp3x3.m_13 = m_31, mTemp3x3.m_14 = m_41;
	mTemp3x3.m_21 = m_12, mTemp3x3.m_22 = m_22, mTemp3x3.m_23 = m_32, mTemp3x3.m_24 = m_42;
	mTemp3x3.m_31 = m_13, mTemp3x3.m_32 = m_23, mTemp3x3.m_33 = m_33, mTemp3x3.m_34 = m_43;
	mTemp3x3.m_41 = m_14, mTemp3x3.m_42 = m_24, mTemp3x3.m_43 = m_34, mTemp3x3.m_44 = m_44;
	return mTemp3x3;
}
void  Matrix4x4::Zero()
{
	m_11 = 0.f, m_12 = 0.f, m_13 = 0.f, m_14 = 0.f;
	m_21 = 0.f, m_22 = 0.f, m_23 = 0.f; m_14 = 0.f;
	m_31 = 0.f, m_32 = 0.f, m_33 = 0.f; m_14 = 0.f;
	m_31 = 0.f, m_32 = 0.f, m_33 = 0.f; m_14 = 0.f;
}





Vector4 Matrix4x4::operator[](int a_iRow)
{
	switch (a_iRow)
	{
	case 0:
		return Vector4(m_11, m_12, m_13, m_14);
		break;

	case 1:
		return Vector4(m_21, m_22, m_23, m_24);
		break;

	case 2:
		return Vector4(m_31, m_32, m_33, m_34);
		break;

	default:
		return Vector4(m_41, m_42, m_43, m_44);
		break;
	}
}
Vector4 Matrix4x4::GetRow(int a_iRow)
{
	switch (a_iRow)
	{
	case 0:
		return Vector4(m_11, m_12, m_13, m_14);
		break;

	case 1:
		return Vector4(m_21, m_22, m_23, m_24);
		break;

	case 2:
		return Vector4(m_31, m_32, m_33, m_34);
		break;

	default:
		return Vector4(m_41, m_42, m_43, m_44);
		break;
	}
}
Vector4 Matrix4x4::GetCol(int a_iCol)
{
	switch (a_iCol)
	{
	case 0:
		return Vector4(m_11, m_21, m_31, m_41);
		break;

	case 1:
		return Vector4(m_12, m_22, m_32, m_42);
		break;

	case 2:
		return Vector4(m_13, m_33, m_33, m_43);
		break;

	default:
		return Vector4(m_14, m_34, m_34, m_44);
		break;
	}
}

float* Matrix4x4::GetMatrix()
{
	float fArray[16]= { m_11, m_12, m_13, m_14,m_21, m_22, m_23, m_24,m_31, m_32, m_33, m_34, m_41, m_42, m_43, m_44 };
	return fArray;
}
double Matrix4x4::GetMatrixValue(int a_fMatrixValue)
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
		return m_14;
		break;
	case 4:
		return m_21;
		break;
	case 5:
		return m_22;
		break;
	case 6:
		return m_23;
		break;
	case 7:
		return m_24;
		break;
	case 8:
		return m_31;
		break;
	case 9:
		return m_32;
		break;
	case 10:
		return m_33;
		break;
	case 11:
		return m_34;
		break;
	case 12:
		return m_41;
		break;
	case 13:
		return m_42;
		break;
	case 14:
		return m_43;
		break;
	case 15:
		return m_44;
		break;
	}


}