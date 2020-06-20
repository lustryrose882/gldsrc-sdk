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

// std::pair style container; exists to work easily in our CUtlMap/CUtlHashMap classes
template <typename T1, typename T2>
class CUtlPair
{
public:
	CUtlPair() {}
	CUtlPair(T1 t1, T2 t2) : first(t1), second(t2) {}

	bool operator<(const CUtlPair<T1, T2> &rhs) const
	{
		if (first != rhs.first)
			return first < rhs.first;

		return second < rhs.second;
	}

	bool operator==(const CUtlPair<T1, T2> &rhs) const
	{
		return first == rhs.first && second == rhs.second;
	}

	T1 first;
	T2 second;
};

// utility to make a CUtlPair without having to specify template parameters
template <typename T1, typename T2>
inline CUtlPair<T1, T2> MakeUtlPair(T1 t1, T2 t2)
{
	return CUtlPair<T1, T2>(t1, t2);
}

// HashItem() overload that works automatically with our hash containers
//template <typename T1, typename T2>
//inline uint32_t HashItem(const CUtlPair<T1, T2> &item)
//{
//	return HashItem((uint64_t)HashItem(item.first) + ((uint64_t)HashItem(item.second) << 32));
//}
