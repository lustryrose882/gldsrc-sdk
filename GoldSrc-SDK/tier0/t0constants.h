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

// numeric constants to avoid typos with wrong number of zeros
const int64_t k_nMillion = 1000000;
const int64_t k_nThousand = 1000;
const int64_t k_nKiloByte = 1024;
const int64_t k_nMegabyte = k_nKiloByte * k_nKiloByte;
const int64_t k_nGigabyte = k_nMegabyte * k_nKiloByte;

// Timing constants

const unsigned int k_nSecondsPerHour = 60 * 60;
const unsigned int k_nSecondsPerDay = k_nSecondsPerHour * 24;

const int k_cSecondsPerMinute = 60;
const int k_cSecondsPerHour = k_cSecondsPerMinute * 60;
const int k_cSecondsPerDay = k_cSecondsPerHour * 24;
const int k_cSecondsPerWeek = k_cSecondsPerDay * 7;
const int k_cSecondsPerYear = k_cSecondsPerDay * 365;
