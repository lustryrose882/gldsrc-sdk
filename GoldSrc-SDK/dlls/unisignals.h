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

#define SIGNAL_BUY       BIT(0)
#define SIGNAL_BOMB      BIT(1)
#define SIGNAL_RESCUE    BIT(2)
#define SIGNAL_ESCAPE    BIT(3)
#define SIGNAL_VIPSAFETY BIT(4)

class CUnifiedSignals
{
public:
	CUnifiedSignals()
	{
		m_flSignal = 0;
		m_flState = 0;
	}
public:
	void Update()
	{
		m_flState = m_flSignal;
		m_flSignal = 0;
	}
	void Signal(int flags) { m_flSignal |= flags; }
	int GetSignal() const { return m_flSignal; }
	int GetState() const { return m_flState; }

private:
	int m_flSignal;
	int m_flState;
};
