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

#define VEHICLE_SPEED0_ACCELERATION  0.005000000000000000
#define VEHICLE_SPEED1_ACCELERATION  0.002142857142857143
#define VEHICLE_SPEED2_ACCELERATION  0.003333333333333334
#define VEHICLE_SPEED3_ACCELERATION  0.004166666666666667
#define VEHICLE_SPEED4_ACCELERATION  0.004000000000000000
#define VEHICLE_SPEED5_ACCELERATION  0.003800000000000000
#define VEHICLE_SPEED6_ACCELERATION  0.004500000000000000
#define VEHICLE_SPEED7_ACCELERATION  0.004250000000000000
#define VEHICLE_SPEED8_ACCELERATION  0.002666666666666667
#define VEHICLE_SPEED9_ACCELERATION  0.002285714285714286
#define VEHICLE_SPEED10_ACCELERATION 0.001875000000000000
#define VEHICLE_SPEED11_ACCELERATION 0.001444444444444444
#define VEHICLE_SPEED12_ACCELERATION 0.001200000000000000
#define VEHICLE_SPEED13_ACCELERATION 0.000916666666666666

#define VEHICLE_STARTPITCH 60
#define VEHICLE_MAXPITCH   200
#define VEHICLE_MAXSPEED   1500

class CFuncVehicleControls: public CBaseEntity
{
public:
	virtual void Spawn() = 0;
	virtual int ObjectCaps() = 0;
};
