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

#include <mathlib/vector2d.h>

namespace vgui
{


class VGuiVertex
{
public:
	VGuiVertex() : x(0), y(0), u(0), v(0) {}
	VGuiVertex(int x1, int y1, float u1, float v1) : x(x1), y(y1), u(u1), v(v1) {}

	void Init(int x1, int y1)
	{
		SetVertex(x1, y1);
	}

	void Init(int x1, int y1, float u1, float v1)
	{
		SetVertex(x1, y1, u1, v1);
	}

	void Init(const Vector2D &pos, const Vector2D &coord = Vector2D(0, 0))
	{
		SetVertex(pos[0], pos[1], coord[0], coord[1]);
	}

	void SetVertex(int x1, int y1)
	{
		x = x1; y = y1;
	}

	void SetVertex(int x1, int y1, float u1, float v1)
	{
		x = x1; y = y1;
		u = u1; v = v1;
	}

	int GetX() const { return x; };
	int GetY() const { return y; };

	float GetU() const { return u; };
	float GetV() const { return v; };

	void GetVertex(int &x1, int &y1, float &u1, float &v1) const
	{
		x1 = x; y1 = y;
		u1 = u; v1 = v;
	}

	bool operator==(const VGuiVertex &vertex) const
	{
		return (vertex.x == x &&
				vertex.y == y &&
				vertex.u == u &&
				vertex.v == v);
	}

private:
	int x, y;
	float u, v;
};

} // namespace vgui
