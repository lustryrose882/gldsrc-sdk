/*
*
*    Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*
*    This product contains software technology licensed from Id
*    Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
*    All Rights Reserved.
*
*    Use, distribution, and modification of this source code and/or resulting
*    object code is restricted to non-commercial enhancements to products from
*    Valve LLC.  All other use, distribution, or modification is prohibited
*    without written permission from Valve LLC.
*
*/

#pragma once

// Used for many pathfinding and many other operations that are treated as planar rather than 3D.
class Vector2D
{
public:
	// Construction/destruction
	inline Vector2D() : x(), y() {}
	inline Vector2D(float X, float Y) : x(X), y(Y) {}
	inline Vector2D(const Vector2D &v) { *(int *)&x = *(int *)&v.x; *(int *)&y = *(int *)&v.y; }

	// Operators
	inline decltype(auto) operator-()         const { return Vector2D(-x, -y); }
	inline bool operator==(const Vector2D &v) const { return x == v.x && y == v.y; }
	inline bool operator!=(const Vector2D &v) const { return !(*this == v); }

	inline decltype(auto) operator+(const Vector2D &v)  const { return Vector2D(x + v.x, y + v.y); }
	inline decltype(auto) operator-(const Vector2D &v)  const { return Vector2D(x - v.x, y - v.y); }
	inline decltype(auto) operator*(const Vector2D &v)  const { return Vector2D(x * v.x, y * v.y); }
	inline decltype(auto) operator/(const Vector2D &v)  const { return Vector2D(x / v.x, y / v.y); }

	inline decltype(auto) operator+=(const Vector2D &v) { return (*this = *this + v); }
	inline decltype(auto) operator-=(const Vector2D &v) { return (*this = *this - v); }
	inline decltype(auto) operator*=(const Vector2D &v) { return (*this = *this * v); }
	inline decltype(auto) operator/=(const Vector2D &v) { return (*this = *this / v); }

	inline decltype(auto) operator+(float fl) const { return Vector2D(x + fl, y + fl); }
	inline decltype(auto) operator-(float fl) const { return Vector2D(x - fl, y - fl); }
	inline decltype(auto) operator*(float fl) const { return Vector2D(x * fl, y * fl); }
	inline decltype(auto) operator/(float fl) const { return Vector2D(x / fl, y / fl); }

	inline decltype(auto) operator+=(float fl) { return (*this = *this + fl); }
	inline decltype(auto) operator-=(float fl) { return (*this = *this - fl); }
	inline decltype(auto) operator*=(float fl) { return (*this = *this * fl); }
	inline decltype(auto) operator/=(float fl) { return (*this = *this / fl); }

	// Methods
	inline void CopyToArray(float *rgfl) const { *(int *)&rgfl[0] = *(int *)&x; *(int *)&rgfl[1] = *(int *)&y; }
	inline float Length() const { return sqrt(x * x + y * y); }			// Get the vector's magnitude
	inline float LengthSquared() const { return (x * x + y * y); }		// Get the vector's magnitude squared

	operator float*() { return &x; }
	operator const float*() const { return &x; }

	inline Vector2D Normalize() const
	{
		float flLen = Length();
		if (flLen == 0)
			return Vector2D(0, 0);

		flLen = 1 / flLen;
		return Vector2D(x * flLen, y * flLen);
	}

	inline bool IsLengthLessThan   (float length) const { return (LengthSquared() < length * length); }
	inline bool IsLengthGreaterThan(float length) const { return (LengthSquared() > length * length); }
	inline float NormalizeInPlace()
	{
		float flLen = Length();
		if (flLen == 0)
		{
			x = 1; y = 0;
		}
		else
		{
			flLen = 1 / flLen;
			x *= flLen; y *= flLen;
		}

		return flLen;
	}
	inline bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance &&
			y > -tolerance && y < tolerance);
	}

	// Members
	vec_t x, y;
};

inline float DotProduct(const Vector2D &a, const Vector2D &b) { return (a.x * b.x + a.y * b.y); }
inline Vector2D operator*(float fl, const Vector2D &v) { return v * fl; }

// 3D Vector
// Same data-layout as engine's vec3_t, which is a vec_t[3]
class Vector
{
public:
	// Construction/destruction
	inline Vector() : x(), y(), z() {}
	inline Vector(float X, float Y, float Z) : x(X), y(Y), z(Z) {}
	inline Vector(const Vector &v) { *(int *)&x = *(int *)&v.x; *(int *)&y = *(int *)&v.y; *(int *)&z = *(int *)&v.z; }
	inline Vector(const float rgfl[3]) { *(int *)&x = *(int *)&rgfl[0]; *(int *)&y = *(int *)&rgfl[1]; *(int *)&z = *(int *)&rgfl[2]; }

	// Operators
	inline decltype(auto) operator-()       const { return Vector(-x, -y, -z); }
	inline bool operator==(const Vector &v) const { return x == v.x && y == v.y && z == v.z; }
	inline bool operator!=(const Vector &v) const { return !(*this == v); }

	inline decltype(auto) operator+(const Vector &v) const { return Vector(x + v.x, y + v.y, z + v.z); }
	inline decltype(auto) operator-(const Vector &v) const { return Vector(x - v.x, y - v.y, z - v.z); }
	inline decltype(auto) operator*(const Vector &v) const { return Vector(x * v.x, y * v.y, z * v.z); }
	inline decltype(auto) operator/(const Vector &v) const { return Vector(x / v.x, y / v.y, z / v.z); }

	inline decltype(auto) operator+=(const Vector &v) { return (*this = *this + v); }
	inline decltype(auto) operator-=(const Vector &v) { return (*this = *this - v); }
	inline decltype(auto) operator*=(const Vector &v) { return (*this = *this * v); }
	inline decltype(auto) operator/=(const Vector &v) { return (*this = *this / v); }

	inline decltype(auto) operator+(float fl) const { return Vector(x + fl, y + fl, z + fl); }
	inline decltype(auto) operator-(float fl) const { return Vector(x - fl, y - fl, z - fl); }
	inline decltype(auto) operator*(float fl) const { return Vector(x * fl, y * fl, z * fl); }
	inline decltype(auto) operator/(float fl) const { return Vector(x / fl, y / fl, z / fl); }

	inline decltype(auto) operator+=(float fl) { return (*this = *this + fl); }
	inline decltype(auto) operator-=(float fl) { return (*this = *this - fl); }
	inline decltype(auto) operator*=(float fl) { return (*this = *this * fl); }
	inline decltype(auto) operator/=(float fl) { return (*this = *this / fl); }

	// Methods
	inline void CopyToArray(float *rgfl) const { *(int *)&rgfl[0] = *(int *)&x; *(int *)&rgfl[1] = *(int *)&y; *(int *)&rgfl[2] = *(int *)&z; }
	inline float Length() const { return sqrt(x * x + y * y + z * z); }				// Get the vector's magnitude
	inline float LengthSquared() const { return (x * x + y * y + z * z); }			// Get the vector's magnitude squared

	operator float*()             { return &x; } // Vectors will now automatically convert to float * when needed
	operator const float*() const { return &x; } // Vectors will now automatically convert to float * when needed

	inline Vector Normalize()
	{
		float flLen = Length();
		if (flLen == 0)
			return Vector(0, 0, 1);

		flLen = 1 / flLen;
		return Vector(x * flLen, y * flLen, z * flLen);
	}
	inline Vector2D Make2D() const
	{
		Vector2D Vec2;
		*(int *)&Vec2.x = *(int *)&x;
		*(int *)&Vec2.y = *(int *)&y;
		return Vec2;
	}

	inline float Length2D() const { return sqrt(x * x + y * y); }

	inline bool IsLengthLessThan   (float length) const { return (LengthSquared() < length * length); }
	inline bool IsLengthGreaterThan(float length) const { return (LengthSquared() > length * length); }

	inline float NormalizeInPlace()
	{
		float flLen = Length();
		if (flLen == 0)
		{
			x = 0; y = 0; z = 1;
		}
		else
		{
			flLen = 1 / flLen;
			x *= flLen; y *= flLen; z *= flLen;
		}

		return flLen;
	}
	inline bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance &&
			y > -tolerance && y < tolerance &&
			z > -tolerance && z < tolerance);
	}

	// Members
	vec_t x, y, z;
};

inline Vector operator*(float fl, const Vector &v) { return v * fl; }
inline float DotProduct(const Vector &a, const Vector &b) { return (a.x * b.x + a.y * b.y + a.z * b.z); }
inline float DotProduct2D(const Vector &a, const Vector &b) { return (a.x * b.x + a.y * b.y); }
inline Vector CrossProduct(const Vector &a, const Vector &b) { return Vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }

#define vec3_t Vector
