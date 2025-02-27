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

#include "col.h"


// The eight box vertices of the box at time zero are
//   center+extent[i]*basis[i]
//   center-extent[i]*basis[i]
// for i = 0,1,2,3.  The vertices after a time step of dt are
//   center+dt*velocity+extent[i]*basis[i]
//   center+dt*velocity-extent[i]*basis[i]
// for i = 0,1,2,3.


//---------------------------------------------------------------------------
IntersectType BoxesIntersect (float dt, const Box& box0, const Box& box1)
{
	// Comments indicate where additional speed is gained for orthonormal bases
	// for both boxes.  If a box is known to be flat (a[i] = 0 for some i OR
	// b[j] = 0 for some j), then more terms can be eliminated.

	const Vector* A = box0.basis;
	const Vector* B = box1.basis;
	const float* a = box0.extent;
	const float* b = box1.extent;

	// memoized values for Dot(A[i],A[j]), Dot(A[i],B[j]), Dot(B[i],B[j])
	float AA[3][3], AB[3][3], BB[3][3];

	// calculate difference of centers
	Vector C, V;
	Sub(box1.center,box0.center,C);
	Sub(box1.velocity,box0.velocity,V);

	float ra, rb, rsum, u0, u1;

	// L = A0
	AA[0][0] = Dot(A[0],A[0]);  // = 1 for orthonormal basis
	AA[0][1] = Dot(A[0],A[1]);  // = 0 for orthonormal basis
	AA[0][2] = Dot(A[0],A[2]);  // = 0 for orthonormal basis
	AB[0][0] = Dot(A[0],B[0]);
	AB[0][1] = Dot(A[0],B[1]);
	AB[0][2] = Dot(A[0],B[2]);

	ra = FABS(a[0]*AA[0][0])+FABS(a[1]*AA[0][1])+FABS(a[2]*AA[0][2]);
		// = FABS(a[0]) for orthonormal basis
	rb = FABS(b[0]*AB[0][0])+FABS(b[1]*AB[0][1])+FABS(b[2]*AB[0][2]);
	rsum = ra+rb;
	u0 = Dot(C,A[0]);
	u1 = u0+dt*Dot(V,A[0]);
	if ((u0 > rsum && u1 > rsum) || (u0 < -rsum && u1 < -rsum) )
		return itA0;

	// L = A1
	AA[1][1] = Dot(A[1],A[1]);  // = 1 for orthonormal basis
	AA[1][2] = Dot(A[1],A[2]);  // = 0 for orthonormal basis
	AB[1][0] = Dot(A[1],B[0]);
	AB[1][1] = Dot(A[1],B[1]);
	AB[1][2] = Dot(A[1],B[2]);
	ra = FABS(a[0]*AA[0][1])+FABS(a[1]*AA[1][1])+FABS(a[2]*AA[1][2]);
		// = FABS(a[1]) for orthonormal basis
	rb = FABS(b[0]*AB[1][0])+FABS(b[1]*AB[1][1])+FABS(b[2]*AB[1][2]);
	rsum = ra+rb;
	u0 = Dot(C,A[1]);
	u1 = u0+dt*Dot(V,A[1]);
	if ((u0 > rsum && u1 > rsum) || (u0 < -rsum && u1 < -rsum) )
		return itA1;

	// L = A2
	AA[2][2] = Dot(A[2],A[2]);  // = 1 for orthonormal basis
	AB[2][0] = Dot(A[2],B[0]);
	AB[2][1] = Dot(A[2],B[1]);
	AB[2][2] = Dot(A[2],B[2]);
	ra = FABS(a[0]*AA[0][2])+FABS(a[1]*AA[1][2])+FABS(a[2]*AA[2][2]);
		// = FABS(a[2]) for orthonormal basis
	rb = FABS(b[0]*AB[2][0])+FABS(b[1]*AB[2][1])+FABS(b[2]*AB[2][2]);
	rsum = ra+rb;
	u0 = Dot(C,A[2]);
	u1 = u0+dt*Dot(V,A[2]);
	if ((u0 > rsum && u1 > rsum) || (u0 < -rsum && u1 < -rsum) )
		return itA2;

	// L = B0
	BB[0][0] = Dot(B[0],B[0]);  // = 1 for orthonormal basis
	BB[0][1] = Dot(B[0],B[1]);  // = 0 for orthonormal basis
	BB[0][2] = Dot(B[0],B[2]);  // = 0 for orthonormal basis
	ra = FABS(a[0]*AB[0][0])+FABS(a[1]*AB[1][0])+FABS(a[2]*AB[2][0]);
	rb = FABS(b[0]*BB[0][0])+FABS(b[1]*BB[0][1])+FABS(b[2]*BB[0][2]);
		// = FABS(b[0]) for orthonormal basis
	rsum = ra+rb;
	u0 = Dot(C,B[0]);
	u1 = u0+dt*Dot(V,B[0]);
	if ((u0 > rsum && u1 > rsum) || (u0 < -rsum && u1 < -rsum) )
		return itB0;

	// L = B1
	BB[1][1] = Dot(B[1],B[1]);  // = 1 for orthonormal basis
	BB[1][2] = Dot(B[1],B[2]);  // = 0 for orthonormal basis
	ra = FABS(a[0]*AB[0][1])+FABS(a[1]*AB[1][1])+FABS(a[2]*AB[2][1]);
	rb = FABS(b[0]*BB[0][1])+FABS(b[1]*BB[1][1])+FABS(b[2]*BB[1][2]);
		// = FABS(b[1]) for orthonormal basis
	rsum = ra+rb;
	u0 = Dot(C,B[1]);
	u1 = u0+dt*Dot(V,B[1]);
	if ((u0 > rsum && u1 > rsum) || (u0 < -rsum && u1 < -rsum) )
		return itB1;

	// L = B2
	BB[2][2] = Dot(B[2],B[2]);  // = 1 for orthonormal basis
	ra = FABS(a[0]*AB[0][2])+FABS(a[1]*AB[1][2])+FABS(a[2]*AB[2][2]);
	rb = FABS(b[0]*BB[0][2])+FABS(b[1]*BB[1][2])+FABS(b[2]*BB[2][2]);
		// = FABS(b[2]) for orthonormal basis
	rsum = ra+rb;
	u0 = Dot(C,B[2]);
	u1 = u0+dt*Dot(V,B[2]);
	if ((u0 > rsum && u1 > rsum) || (u0 < -rsum && u1 < -rsum) )
		return itB2;

	// check separating axes which are cross products of box edges
	float Ainv[3][3], coeff[3][3];
	Invert3x3(A,Ainv);
		// Ainv = Transpose(A) for orthonormal basis, no need to invert
	MultiplyMM(B,Ainv,coeff);
		// coeff[i][j] = AB[j][i] for orthonormal basis, no need to multiply

	// memoize minors of coefficient matrix
	float minor[3][3];

	// difference of centers in A-basis
	Vector d0, d1, product;
	MultiplyVM(C,Ainv,d0);  // Ainv = Transpose(A) for orthonormal basis
	MultiplyVM(V,Ainv,d1);  // Ainv = Transpose(A) for orthonormal basis
	ScalarMult(dt,d1,product);
	Add(d0,product,d1);

	// L = A0xB0
	minor[0][1] = coeff[0][1]*coeff[2][2]-coeff[2][1]*coeff[0][2];
		// = -coeff[1][0] for orthonormal bases
	minor[0][2] = coeff[0][1]*coeff[1][2]-coeff[1][1]*coeff[0][2];
		// = +coeff[2][0] for orthonormal bases
	ra = FABS(a[1]*coeff[0][2])+FABS(a[2]*coeff[0][1]);
	rb = FABS(b[1]*minor[0][2])+FABS(b[2]*minor[0][1]);
		// = FABS(b[1]*coeff[2][0])+FABS(b[2]*coeff[1][0]) for orthonormal bases
	rsum = ra+rb;
	u0 = d0[2]*coeff[1][0]-d0[1]*coeff[2][0];
	u1 = d1[2]*coeff[1][0]-d1[1]*coeff[2][0];
	if ((u0 > rsum && u1 > rsum) || (u0 < -rsum && u1 < -rsum) )
		return itA0B0;

	// L = A0xB1
	minor[0][0] = coeff[1][1]*coeff[2][2]-coeff[2][1]*coeff[1][2];
		// = +coeff[0][0] for orthonormal bases
	ra = FABS(a[1]*coeff[1][2])+FABS(a[2]*coeff[1][1]);
	rb = FABS(b[0]*minor[0][2])+FABS(b[2]*minor[0][0]);
		// = FABS(b[0]*coeff[2][0])+FABS(b[2]*coeff[0][0]) for orthonormal bases
	rsum = ra+rb;
	u0 = d0[2]*coeff[1][1]-d0[1]*coeff[1][2];
	u1 = d1[2]*coeff[1][1]-d1[1]*coeff[1][2];
	if ((u0 > rsum && u1 > rsum) || (u0 < -rsum && u1 < -rsum) )
		return itA0B1;

	// L = A0xB2
	ra = FABS(a[1]*coeff[2][2])+FABS(a[2]*coeff[2][1]);
	rb = FABS(b[0]*minor[0][1])+FABS(b[1]*minor[0][0]);
		// = FABS(b[0]*coeff[1][0])+FABS(b[1]*coeff[0][0]) for orthonormal bases
	rsum = ra+rb;
	u0 = d0[2]*coeff[2][1]-d0[1]*coeff[2][2];
	u1 = d1[2]*coeff[2][1]-d1[1]*coeff[2][2];
	if ((u0 > rsum && u1 > rsum) || (u0 < -rsum && u1 < -rsum) )
		return itA0B2;

	// L = A1xB0
	minor[1][1] = coeff[0][0]*coeff[2][2]-coeff[2][0]*coeff[0][2];
		// = +coeff[1][1] for orthonormal bases
	minor[1][2] = coeff[0][0]*coeff[1][2]-coeff[1][0]*coeff[0][2];
		// = -coeff[2][1] for orthonormal bases
	ra = FABS(a[0]*coeff[0][2])+FABS(a[2]*coeff[0][0]);
	rb = FABS(b[1]*minor[1][2])+FABS(b[2]*minor[1][1]);
		// = FABS(b[1]*coeff[2][1])+FABS(b[2]*coeff[1][1]) for orthonormal bases
	rsum = ra+rb;
	u0 = d0[0]*coeff[0][2]-d0[2]*coeff[0][0];
	u1 = d1[0]*coeff[0][2]-d1[2]*coeff[0][0];
	if ((u0 > rsum && u1 > rsum) || (u0 < -rsum && u1 < -rsum) )
		return itA1B0;

	// L = A1xB1
	minor[1][0] = coeff[1][0]*coeff[2][2]-coeff[2][0]*coeff[1][2];
		// = -coeff[0][1] for orthonormal bases
	ra = FABS(a[0]*coeff[1][2])+FABS(a[2]*coeff[1][0]);
	rb = FABS(b[0]*minor[1][2])+FABS(b[2]*minor[1][0]);
		// = FABS(b[0]*coeff[2][1])+FABS(b[2]*coeff[0][1]) for orthonormal bases
	rsum = ra+rb;
	u0 = d0[0]*coeff[1][2]-d0[2]*coeff[1][0];
	u1 = d1[0]*coeff[1][2]-d1[2]*coeff[1][0];
	if ((u0 > rsum && u1 > rsum) || (u0 < -rsum && u1 < -rsum) )
		return itA1B1;

	// L = A1xB2
	ra = FABS(a[0]*coeff[2][2])+FABS(a[2]*coeff[2][0]);
	rb = FABS(b[0]*minor[1][1])+FABS(b[1]*minor[1][0]);
		// = FABS(b[0]*coeff[1][1])+FABS(b[1]*coeff[0][1]) for orthonormal bases
	rsum = ra+rb;
	u0 = d0[0]*coeff[2][2]-d0[2]*coeff[2][0];
	u1 = d1[0]*coeff[2][2]-d1[2]*coeff[2][0];
	if ((u0 > rsum && u1 > rsum) || (u0 < -rsum && u1 < -rsum) )
		return itA1B2;

	// L = A2xB0
	minor[2][1] = coeff[0][0]*coeff[2][1]-coeff[2][0]*coeff[0][1];
		// = -coeff[2][1] for orthonormal bases
	minor[2][2] = coeff[0][0]*coeff[1][1]-coeff[1][0]*coeff[0][1];
		// = +coeff[2][2] for orthonormal bases
	ra = FABS(a[0]*coeff[0][1])+FABS(a[1]*coeff[0][0]);
	rb = FABS(b[1]*minor[2][2])+FABS(b[2]*minor[2][1]);
		// = FABS(b[1]*coeff[2][2])+FABS(b[2]*coeff[1][2]) for orthonormal bases
	rsum = ra+rb;
	u0 = d0[1]*coeff[0][0]-d0[0]*coeff[0][1];
	u1 = d1[1]*coeff[0][0]-d1[0]*coeff[0][1];
	if ((u0 > rsum && u1 > rsum) || (u0 < -rsum && u1 < -rsum) )
		return itA2B0;

	// L = A2xB1
	minor[2][0] = coeff[1][0]*coeff[2][1]-coeff[2][0]*coeff[1][1];
		// = +coeff[0][2] for orthonormal bases
	ra = FABS(a[0]*coeff[1][1])+FABS(a[1]*coeff[1][0]);
	rb = FABS(b[0]*minor[2][2])+FABS(b[2]*minor[2][0]);
		// = FABS(b[0]*coeff[2][2])+FABS(b[2]*coeff[0][2]) for orthonormal bases
	rsum = ra+rb;
	u0 = d0[1]*coeff[1][0]-d0[0]*coeff[1][1];
	u1 = d1[1]*coeff[1][0]-d1[0]*coeff[1][1];
	if ((u0 > rsum && u1 > rsum) || (u0 < -rsum && u1 < -rsum) )
		return itA2B1;

	// L = A2xB2
	ra = FABS(a[0]*coeff[2][1])+FABS(a[1]*coeff[2][0]);
	rb = FABS(b[0]*minor[2][1])+FABS(b[1]*minor[2][0]);
		// = FABS(b[0]*coeff[1][2])+FABS(b[1]*coeff[0][2]) for orthonormal bases
	rsum = ra+rb;
	u0 = d0[1]*coeff[2][0]-d0[0]*coeff[2][1];
	u1 = d1[1]*coeff[2][0]-d1[0]*coeff[2][1];
	if ((u0 > rsum && u1 > rsum) || (u0 < -rsum && u1 < -rsum) )
		return itA2B2;

	return itIntersects;
}
