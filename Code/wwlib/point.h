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

/*********************************************************************************************** 
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               *** 
 *********************************************************************************************** 
 *                                                                                             * 
 *                 Project Name : Command & Conquer                                            * 
 *                                                                                             * 
 *                     $Archive:: /G/wwlib/Point.h                                            $* 
 *                                                                                             * 
 *                      $Author:: Eric_c                                                      $*
 *                                                                                             * 
 *                     $Modtime:: 4/07/99 5:24p                                               $*
 *                                                                                             * 
 *                    $Revision:: 5                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------* 
 * Functions:                                                                                  * 
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef POINT_H
#define POINT_H

template<class T> class TRect;

/*
**	This class describes a point in 2 dimensional space using arbitrary
**	components. The interpretation of which is outside the scope
**	of this class. This class is the successor to the old style COORDINATE 
**	and CELL types but also serves anywhere an X and Y value are treated
**	as a logical object (e.g., pixel location).
*/
template<class T>
class TPoint2D {
	public:
		TPoint2D(void) {}		// Default constructor does nothing by design.
		TPoint2D(T x, T y) : X(x), Y(y) {}

		// Equality comparison operators.
		bool operator == (TPoint2D<T> const & rvalue) const {return(X==rvalue.X && Y==rvalue.Y);}
		bool operator != (TPoint2D<T> const & rvalue) const {return(X!=rvalue.X || Y!=rvalue.Y);}

		// Addition and subtraction operators.
		TPoint2D<T> const & operator += (TPoint2D<T> const & rvalue) {X += rvalue.X;Y += rvalue.Y;return(*this);}
		TPoint2D<T> const & operator -= (TPoint2D<T> const & rvalue) {X -= rvalue.X;Y -= rvalue.Y;return(*this);}
		TPoint2D<T> const operator - (TPoint2D<T> const & rvalue) const {return(TPoint2D<T>(X - rvalue.X, Y - rvalue.Y));}
		TPoint2D<T> const operator + (TPoint2D<T> const & rvalue) const {return(TPoint2D<T>(X + rvalue.X, Y + rvalue.Y));}

		// Scalar multiplication and division.
		TPoint2D<T> const operator * (T rvalue) const {return(TPoint2D<T>(X * rvalue, Y * rvalue));}
		TPoint2D<T> const & operator *= (T rvalue) {X *= rvalue; Y *= rvalue;return(*this);}
		TPoint2D<T> const operator / (T rvalue) const {if (rvalue == T(0)) return(TPoint2D<T>(0,0));return(TPoint2D<T>(X / rvalue, Y / rvalue));}
		TPoint2D<T> const & operator /= (T rvalue) {if (rvalue != T(0)) {X /= rvalue;Y /= rvalue;}return(*this);}

		// Dot and cross product.
		TPoint2D<T> const operator * (TPoint2D<T> const & rvalue) const {return(TPoint2D<T>(X * rvalue.X, Y * rvalue.Y));}
		TPoint2D<T> const Dot_Product(TPoint2D<T> const & rvalue) const {return(TPoint2D<T>(X * rvalue.X, Y * rvalue.Y));}
		TPoint2D<T> const Cross_Product(TPoint2D<T> const & rvalue) const {return(TPoint2D<T>(Y - rvalue.Y, rvalue.X - X));}

		// Negation operator -- simple and effective
		TPoint2D<T> const operator - (void) const {return(TPoint2D<T>(-X, -Y));}

		// Vector support functions.
		T Length(void) const {return(T(sqrt(X*X + Y*Y)));}
		TPoint2D<T> const Normalize(void) const {
			double len = sqrt(X*X + Y*Y);
			if (len != 0.0) {
				return(TPoint2D<T>((T)((double)X / len), (T)((double)Y / len)));
			} else {
				return(*this);
			}
		}

		//	Bias a point into a clipping rectangle.
		TPoint2D<T> const Bias_To(TRect<T> const & rect) const;

		// Find distance between points.
		T Distance_To(TPoint2D<T> const & point) const {return((*this - point).Length());}

	public:
		T X;
		T Y;
};

template<class T>
TPoint2D<T> const operator * (T lvalue, TPoint2D<T> const & rvalue) 
{
	return(rvalue * lvalue);
}


/*
**	This typedef provides an uncluttered type name for use by simple integer points.
*/
typedef TPoint2D<int> Point2D;



/*
**	This describes a point in 3 dimensional space using arbitrary
**	components. This is the successor to the COORDINATE type for those
**	times when height needs to be tracked.
**
**	Notice that it is not implemented as a virtually derived class. This
**	is for efficiency reasons. This class chooses to be smaller and faster at the
**	expense of polymorphism. However, since it is publicly derived, inheritance is
**	the next best thing.
*/
template<class T>
class TPoint3D : public TPoint2D<T> {
		typedef TPoint2D<T> BASECLASS;

	public:
		TPoint3D(void) {}		// Default constructor does nothing by design.
		TPoint3D(T x, T y, T z) : TPoint2D<T>(x, y), Z(z) {}
		TPoint3D(BASECLASS const & rvalue) : TPoint2D<T>(rvalue), Z(0) {}
		
		// Equality comparison operators.
		bool operator == (TPoint3D<T> const & rvalue) const {return(this->X==rvalue.X && this->Y==rvalue.Y && this->Z==rvalue.Z);}
		bool operator != (TPoint3D<T> const & rvalue) const {return(this->X!=rvalue.X || this->Y!=rvalue.Y || this->Z!=rvalue.Z);}

		// Addition and subtraction operators.
		TPoint3D<T> const & operator += (TPoint3D<T> const & rvalue) {this->X += rvalue.X;this->Y += rvalue.Y;this->Z += rvalue.Z;return(*this);}
		TPoint2D<T> const & operator += (TPoint2D<T> const & rvalue) {BASECLASS::operator += (rvalue);return(*this);}
		TPoint3D<T> const & operator -= (TPoint3D<T> const & rvalue) {this->X -= rvalue.X;this->Y -= rvalue.Y;this->Z -= rvalue.Z;return(*this);}
		TPoint2D<T> const & operator -= (TPoint2D<T> const & rvalue) {BASECLASS::operator -= (rvalue);return(*this);}
		TPoint3D<T> const operator - (TPoint3D<T> const & rvalue) const {return(TPoint3D<T>(this->X - rvalue.X, this->Y - rvalue.Y, this->Z - rvalue.Z));}
		TPoint3D<T> const operator - (TPoint2D<T> const & rvalue) const {return(TPoint3D<T>(this->X - rvalue.X, this->Y - rvalue.Y, this->Z));}
		TPoint3D<T> const operator + (TPoint3D<T> const & rvalue) const {return(TPoint3D<T>(this->X + rvalue.X, this->Y + rvalue.Y, this->Z + rvalue.Z));}
		TPoint3D<T> const operator + (TPoint2D<T> const & rvalue) const {return(TPoint3D<T>(this->X + rvalue.X, this->Y + rvalue.Y, this->Z));}

		// Scalar multiplication and division.
		TPoint3D<T> const operator * (T rvalue) const {return(TPoint3D<T>(this->X * rvalue, this->Y * rvalue, this->Z * rvalue));}
		TPoint3D<T> const & operator *= (T rvalue) {this->X *= rvalue;this->Y *= rvalue;this->Z *= rvalue;return(*this);}
		TPoint3D<T> const operator / (T rvalue) const {if (rvalue == T(0)) return(TPoint3D<T>(0,0,0));return(TPoint3D<T>(this->X / rvalue, this->Y / rvalue, this->Z / rvalue));}
		TPoint3D<T> const & operator /= (T rvalue) {if (rvalue != T(0)) {this->X /= rvalue;this->Y /= rvalue;this->Z /= rvalue;}return(*this);}

		// Dot and cross product.
		TPoint3D<T> const operator * (TPoint3D<T> const & rvalue) const {return(TPoint3D<T>(this->X * rvalue.X, this->Y * rvalue.Y, this->Z * rvalue.Z));}
		TPoint3D<T> const Dot_Product(TPoint3D<T> const & rvalue) const {return(TPoint3D<T>(this->X * rvalue.X, this->Y * rvalue.Y, this->Z * rvalue.Z));}
		TPoint3D<T> const Cross_Product(TPoint3D<T> const & rvalue) const {return TPoint3D<T>(this->Y * rvalue.Z - this->Z * rvalue.Y, this->Z * rvalue.X - this->X * rvalue.Z, this->X * rvalue.Y - this->Y * rvalue.X);}

		// Negation operator -- simple and effective
		TPoint3D<T> const operator - (void) const {return(TPoint3D<T>(-this->X, -this->Y, -this->Z));}

		// Vector support functions.
		T Length(void) const {return(T(sqrt(this->X*this->X + this->Y*this->Y + this->Z*this->Z)));}
		TPoint3D<T> const Normalize(void) const {
			double len = sqrt(this->X*this->X + this->Y*this->Y + this->Z*this->Z);
			if (len != 0.0) {
				return(TPoint3D<T>(this->X / len, this->Y / len, this->Z / len));
			} else {
				return(*this);
			}
		}

		// Find distance between points.
		T Distance_To(TPoint3D<T> const & point) const {return((*this - point).Length());}
		T Distance_To(TPoint2D<T> const & point) const {return(BASECLASS::Distance_To(point));}

	public:

		/*
		**	The Z component of this point.
		*/
		T Z;
};

template<class T>
TPoint3D<T> const operator * (T lvalue, TPoint3D<T> const & rvalue) 
{
	return(rvalue * lvalue);
}


/*
**	This typedef provides a simple uncluttered type name for use by
**	integer 3D points.
*/
typedef TPoint3D<int> Point3D;


#endif
