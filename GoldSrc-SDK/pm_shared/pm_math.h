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

//#define PITCH 0	// up/down
//#define YAW   1 // left/right
//#define ROLL  2 // fall over

//extern Vector vec3_origin;
//extern const int nanmask;

//#define IS_NAN(x)	((*reinterpret_cast<int *>(&(x)) & nanmask) == nanmask)

float anglemod(float a);
void AngleVectors(const vec_t *angles, vec_t *forward, vec_t *right, vec_t *up);
void AngleVectorsTranspose(const vec_t *angles, vec_t *forward, vec_t *right, vec_t *up);
void AngleMatrix(const vec_t *angles, float (*matrix)[4]);
void AngleIMatrix(const vec_t *angles, float (*matrix)[4]);
void NormalizeAngles(float *angles);
void InterpolateAngles(float *start, float *end, float *output, float frac);
float AngleBetweenVectors(const vec_t *v1, const vec_t *v2);
void VectorTransform(const vec_t *in1, float *in2, vec_t *out);
int VectorCompare(const vec_t *v1, const vec_t *v2);
void VectorMA(const vec_t *veca, float scale, const vec_t *vecb, vec_t *vecc);

float _DotProduct(const vec_t *v1, const vec_t *v2);
void _VectorSubtract(vec_t *veca, vec_t *vecb, vec_t *out);
void _VectorAdd(vec_t *veca, vec_t *vecb, vec_t *out);
void _VectorCopy(vec_t *in, vec_t *out);
void CrossProduct(const vec_t *v1, const vec_t *v2, vec_t *cross);

float Length(const vec_t *v);
float Distance(const vec_t *v1, const vec_t *v2);
float VectorNormalize(vec_t *v);

void VectorInverse(vec_t *v);
void VectorScale(const vec_t *in, vec_t scale, vec_t *out);
int Q_log2(int val);
void VectorMatrix(vec_t *forward, vec_t *right, vec_t *up);
void VectorAngles(const vec_t *forward, vec_t *angles);
