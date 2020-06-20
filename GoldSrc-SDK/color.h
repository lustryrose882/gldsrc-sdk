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

// Basic handler for an rgb set of colors
// This class is fully inline
class Color
{
public:
	// constructors
	Color()
	{
		_color[0] = 0;
		_color[1] = 0;
		_color[2] = 0;
		_color[3] = 0;
	}

	constexpr Color(int r, int g, int b) :
		_color{(unsigned char)r, (unsigned char)g, (unsigned char)b, 0}
	{
	}

	constexpr Color(int r, int g, int b, int a) :
		_color{(unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a}
	{
	}

	constexpr bool IsEmpty() const
	{
		return
			_color[0] == 0 &&
			_color[1] == 0 &&
			_color[2] == 0 &&
			_color[3] == 0;
	}

	// set the color
	// r - red component (0-255)
	// g - green component (0-255)
	// b - blue component (0-255)
	// a - alpha component, controls transparency (0 - transparent, 255 - opaque);
	void SetColor(int r, int g, int b, int a = 0)
	{
		_color[0] = (unsigned char)r;
		_color[1] = (unsigned char)g;
		_color[2] = (unsigned char)b;
		_color[3] = (unsigned char)a;
	}

	void GetColor(int &r, int &g, int &b, int &a) const
	{
		r = _color[0];
		g = _color[1];
		b = _color[2];
		a = _color[3];
	}

	void Reset()
	{
		_color[0] = 0;
		_color[1] = 0;
		_color[2] = 0;
		_color[3] = 0;
	}

	void SetRawABGR32(int colorHex32)
	{
		// ABGR32
		_color[2] = (colorHex32) & 0xFF;
		_color[1] = (colorHex32 >> 8) & 0xFF;
		_color[0] = (colorHex32 >> 16) & 0xFF;
		_color[3] = (colorHex32 >> 24) & 0xFF;
	}

	void SetRawRGBA32(int color32)
	{
		// RGBA32
		_color[0] = (color32) & 0xFF;
		_color[1] = (color32 >> 8) & 0xFF;
		_color[2] = (color32 >> 16) & 0xFF;
		_color[3] = (color32 >> 24) & 0xFF;
	}

	int GetRawABGR32() const
	{
		return (_color[3] << 24) | (_color[0] << 16) | (_color[1] << 8) | _color[1];
	}

	int GetRawRGBA32() const
	{
		return (_color[3] << 24) | (_color[2] << 16) | (_color[1] << 8) | _color[0];
	}

	inline int r() const { return _color[0]; }
	inline int g() const { return _color[1]; }
	inline int b() const { return _color[2]; }
	inline int a() const { return _color[3]; }

	unsigned char &operator[](int index)
	{
		return _color[index];
	}

	const unsigned char &operator[](int index) const
	{
		return _color[index];
	}

	bool operator==(const Color &rhs) const
	{
		return (*((int *)this) == *((int *)&rhs));
	}

	bool operator!=(const Color &rhs) const
	{
		return !(operator==(rhs));
	}

	Color &operator=(const Color &rhs)
	{
		SetRawRGBA32(rhs.GetRawRGBA32());
		return *this;
	}

private:
	unsigned char _color[4];
};

extern Color col_lightcoral;
extern Color col_blue;
extern Color col_sundance;
