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

// Safe way to point to CBaseEntities who may die between frames.
template <typename T = CBaseEntity>
class EntityHandle
{
public:
	EntityHandle() : m_edict(nullptr), m_serialnumber(0) {}
	EntityHandle(const EntityHandle<T> &other);
	EntityHandle(const T *pEntity);
	EntityHandle(const edict_t *pEdict);

	// cast to base class
	// NOTE: this is a unsafe method
	template <typename R>
	R *Get() const;

	edict_t *Get() const;
	edict_t *Set(edict_t *pEdict);

	void Remove();
	bool IsValid() const;
	int GetSerialNumber() const;

	bool operator==(T *pEntity) const;
	operator bool() const;
	operator T *() const;

	T *operator=(T *pEntity);
	T *operator->();

	// Copy the ehandle.
	EntityHandle<T>& operator=(const EntityHandle<T> &other);

private:
	edict_t *m_edict;
	int m_serialnumber;
};

// Short alias
using EHandle = EntityHandle<>;
using EHANDLE = EHandle;

// Inlines
template <typename T>
inline bool FNullEnt(EntityHandle<T> &hent)
{
	return (!hent || FNullEnt(OFFSET(hent.Get())));
}

// Copy constructor
template <typename T>
EntityHandle<T>::EntityHandle(const EntityHandle<T> &other)
{
	m_edict = other.m_edict;
	m_serialnumber = other.m_serialnumber;

	return (*this)
}

template <typename T>
EntityHandle<T>::EntityHandle(const T *pEntity)
{
	if (pEntity)
	{
		Set(ENT(pEntity->pev));
	}
	else
	{
		m_edict = nullptr;
		m_serialnumber = 0;
	}
}

template <typename T>
EntityHandle<T>::EntityHandle(const edict_t *pEdict)
{
	Set(const_cast<edict_t *>(pEdict));
}

template <typename T>
template <typename R>
inline R *EntityHandle<T>::Get() const
{
	return GET_PRIVATE<R>(Get());
}

template <typename T>
inline edict_t *EntityHandle<T>::Get() const
{
	if (!m_edict || m_edict->serialnumber != m_serialnumber || m_edict->free)
	{
		return nullptr;
	}

	return m_edict;
}

template <typename T>
inline edict_t *EntityHandle<T>::Set(edict_t *pEdict)
{
	m_edict = pEdict;
	if (pEdict)
	{
		m_serialnumber = pEdict->serialnumber;
	}

	return pEdict;
}

template <typename T>
void EntityHandle<T>::Remove()
{
	if (IsValid())
	{
		UTIL_Remove(*this);
	}

	m_edict = nullptr;
	m_serialnumber = 0;
}

// Returns whether this handle is valid.
template <typename T>
inline bool EntityHandle<T>::IsValid() const
{
	edict_t *pEdict = Get();
	if (!pEdict)
	{
		return false;
	}

	CBaseEntity *pEntity = GET_PRIVATE<CBaseEntity>(pEdict);
	if (!pEntity)
	{
		return false;
	}

	return true;
}

// CBaseEntity serial number.
// Used to determine if the entity is still valid.
template <typename T>
inline int EntityHandle<T>::GetSerialNumber() const
{
	return m_serialnumber;
}

template <typename T>
inline bool EntityHandle<T>::operator==(T *pEntity) const
{
	assert(("EntityHandle<T>::operator==:  got a nullptr pointer!", pEntity != nullptr));

	if (m_serialnumber != pEntity->edict()->serialnumber)
	{
		return false;
	}

	return m_edict == pEntity->edict();
}

template <typename T>
inline EntityHandle<T>::operator bool() const
{
	return IsValid();
}

// Gets the Entity this handle refers to.
// Returns null if invalid.
template <typename T>
inline EntityHandle<T>::operator T *() const
{
	return GET_PRIVATE<T>(Get());
}

// Assigns the given entity to this handle.
template <typename T>
inline T *EntityHandle<T>::operator=(T *pEntity)
{
	if (pEntity)
	{
		Set(ENT(pEntity->pev));
	}
	else
	{
		m_edict = nullptr;
		m_serialnumber = 0;
	}

	return static_cast<T *>(pEntity);
}

template <typename T>
inline T *EntityHandle<T>::operator->()
{
	edict_t *pEdict = Get();
	assert(("EntityHandle<T>::operator->:  pointer is nullptr!", pEdict != nullptr));

	T *pEntity = GET_PRIVATE<T>(pEdict);
	assert(("EntityHandle<T>::operator->:  pvPrivateData is nullptr!", pEntity != nullptr));
	return pEntity;
}

// Makes this handle refer to the same entity as the given handle.
template <typename T>
inline EntityHandle<T>& EntityHandle<T>::operator=(const EntityHandle<T> &other)
{
	m_edict = other.m_edict;
	m_serialnumber = other.m_serialnumber;

	return (*this);
}
