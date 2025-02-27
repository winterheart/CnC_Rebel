/*
**	Command & Conquer Renegade(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CVEC_H
#define CVEC_H


typedef float Vector[3];

#define FABS(f) (float(fabs(f)))

//---------------------------------------------------------------------------
inline void Add (const Vector u, const Vector v, Vector sum)
{
	sum[0] = u[0] + v[0];
	sum[1] = u[1] + v[1];
	sum[2] = u[2] + v[2];
}
//---------------------------------------------------------------------------
inline void Sub (const Vector u, const Vector v, Vector diff)
{
	diff[0] = u[0] - v[0];
	diff[1] = u[1] - v[1];
	diff[2] = u[2] - v[2];
}
//---------------------------------------------------------------------------
inline float Dot (const Vector u, const Vector v)
{
	return u[0]*v[0] + u[1]*v[1] + u[2]*v[2];
}
//---------------------------------------------------------------------------
inline void ScalarMult (const float scalar, const Vector u, Vector product)
{
	product[0] = scalar*u[0];
	product[1] = scalar*u[1];
	product[2] = scalar*u[2];
}
//---------------------------------------------------------------------------
inline int Invert3x3 (const float a[3][3], float ainv[3][3])
{
	// Invert a 3x3 using cofactors.  This is about 8 times faster than
	// the Numerical Recipes code which uses Gaussian elimination.

	ainv[0][0] = a[1][1]*a[2][2]-a[1][2]*a[2][1];
	ainv[0][1] = a[0][2]*a[2][1]-a[0][1]*a[2][2];
	ainv[0][2] = a[0][1]*a[1][2]-a[0][2]*a[1][1];
	ainv[1][0] = a[1][2]*a[2][0]-a[1][0]*a[2][2];
	ainv[1][1] = a[0][0]*a[2][2]-a[0][2]*a[2][0];
	ainv[1][2] = a[0][2]*a[1][0]-a[0][0]*a[1][2];
	ainv[2][0] = a[1][0]*a[2][1]-a[1][1]*a[2][0];
	ainv[2][1] = a[0][1]*a[2][0]-a[0][0]*a[2][1];
	ainv[2][2] = a[0][0]*a[1][1]-a[0][1]*a[1][0];

	float det = a[0][0]*ainv[0][0]+a[0][1]*ainv[1][0]+a[0][2]*ainv[2][0];
	if (FABS(det) <= 1e-06f )
		return 0;

	float invdet = 1.0f/det;
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			ainv[row][col] *= invdet;

	return 1;
}
//---------------------------------------------------------------------------
inline void MultiplyVM (Vector input, float m[3][3], Vector output)
{
	output[0] = input[0]*m[0][0] + input[1]*m[1][0] + input[2]*m[2][0];
	output[1] = input[0]*m[0][1] + input[1]*m[1][1] + input[2]*m[2][1];
	output[2] = input[0]*m[0][2] + input[1]*m[1][2] + input[2]*m[2][2];
}
//---------------------------------------------------------------------------
inline void MultiplyMM (const float A[3][3], const float B[3][3], float AB[3][3])
{
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			AB[row][col] = 0.0f;
			for (int mid = 0; mid < 3; mid++)
				AB[row][col] += A[row][mid]*B[mid][col];
		}
	}
}


#endif
