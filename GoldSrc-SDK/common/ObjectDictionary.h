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

#include "IObjectContainer.h"

template <class T>
class ObjectDictionary: public IObjectContainer<T>
{
public:
	ObjectDictionary();
	virtual ~ObjectDictionary();

	void Init();
	void Init(int baseSize);

	bool Add(T *object);
	bool Contains(T *object);
	bool IsEmpty();
	int CountElements();

	void Clear(bool freeObjectssMemory = false);

	bool Add(T *object, float key);
	bool ChangeKey(T *object, float newKey);
	bool UnsafeChangeKey(T *object, float newKey);

	bool Remove(T *object);
	bool RemoveSingle(T *object);
	bool RemoveKey(float key);
	bool RemoveRange(float startKey, float endKey);

	T *FindClosestKey(float key);
	T *FindExactKey(float key);

	T *GetFirst();
	T *GetLast();
	T *GetNext();

	int FindKeyInCache(float key);
	int FindObjectInCache(T *object);

	void ClearCache();
	bool CheckSize();

	typedef struct entry_s {
		void *object;
		float key;
	} entry_t;

	void AddToCache(entry_t *entry);
	void AddToCache(entry_t *entry, float key);

	bool RemoveIndex(int index, bool freeObjectMemory = false);
	bool RemoveIndexRange(int minIndex, int maxIndex);
	int FindClosestAsIndex(float key);

protected:
	int m_currentEntry;
	float m_findKey;

	enum { MAX_OBJECT_CACHE = 32 };

	entry_t *m_entries;
	entry_t m_cache[MAX_OBJECT_CACHE];

	int m_cacheIndex;
	int m_size;
	int m_maxSize;
};

template <class T>
ObjectDictionary<T>::ObjectDictionary()
{
	m_currentEntry = 0;
	m_findKey = 0;
	m_entries = nullptr;

	Q_memset(m_cache, 0, sizeof(m_cache));

	m_cacheIndex = 0;
	m_size = 0;
	m_maxSize = 0;
}

template <class T>
ObjectDictionary<T>::~ObjectDictionary()
{
	if (m_entries) {
		free(m_entries);
	}
}

template <class T>
void ObjectDictionary<T>::Clear(bool freeObjectssMemory)
{
	if (freeObjectssMemory)
	{
		for (int i = 0; i < m_size; i++)
		{
			auto obj = m_entries[i].object;
			if (obj) {
				free(obj);
			}
		}
	}

	m_size = 0;
	CheckSize();
	ClearCache();
}

template <class T>
bool ObjectDictionary<T>::Add(T *object, float key)
{
	if (m_size == m_maxSize && !CheckSize())
		return false;

	entry_t *p;
	if (m_size && key < m_entries[m_size - 1].key)
	{
		p = &m_entries[FindClosestAsIndex(key)];

		auto e1 = &m_entries[m_size];
		auto e2 = &m_entries[m_size - 1];

		while (p->key <= key) { p++; }
		while (p != e1)
		{
			e1->object = e2->object;
			e1->key = e2->key;

			e1--;
			e2--;
		}
	}
	else
	{
		p = &m_entries[m_size];
	}

	p->key = key;
	p->object = object;
	m_size++;

	ClearCache();
	AddToCache(p);

	return true;
}

template <class T>
int ObjectDictionary<T>::FindClosestAsIndex(float key)
{
	if (m_size <= 0)
		return -1;

	if (key <= m_entries->key)
		return 0;

	int index = FindKeyInCache(key);
	if (index >= 0)
		return index;

	int middle;
	int first = 0;
	int last = m_size - 1;
	float keyMiddle, keyNext;

	if (key < m_entries[last].key)
	{
		while (true)
		{
			middle = (last + first) >> 1;
			keyMiddle = m_entries[middle].key;

			if (keyMiddle == key)
				break;

			if (keyMiddle < key)
			{
				if (m_entries[middle + 1].key >= key)
				{
					if (m_entries[middle + 1].key - key < key - keyMiddle)
						middle++;
					break;
				}

				first = (last + first) >> 1;
			}
			else
			{
				last = (last + first) >> 1;
			}
		}
	}
	else
	{
		middle = last;
	}

	keyNext = m_entries[middle - 1].key;
	while (keyNext == key) {
		keyNext = m_entries[middle--].key;
	}

	AddToCache(&m_entries[middle], key);
	return middle;
}

template <class T>
void ObjectDictionary<T>::ClearCache()
{
	Q_memset(m_cache, 0, sizeof(m_cache));
	m_cacheIndex = 0;
}

template <class T>
bool ObjectDictionary<T>::RemoveIndex(int index, bool freeObjectMemory)
{
	if (index < 0 || index >= m_size)
		return false;

	auto p  = &m_entries[m_size - 1];
	auto e1 = &m_entries[index];
	auto e2 = &m_entries[index + 1];

	if (freeObjectMemory && e1->object)
		free(e1->object);

	while (p != e1)
	{
		e1->object = e2->object;
		e1->key = e2->key;

		e1++;
		e2++;
	}

	p->object = nullptr;
	p->key = 0;
	m_size--;

	CheckSize();
	ClearCache();

	return false;
}

template <class T>
bool ObjectDictionary<T>::RemoveIndexRange(int minIndex, int maxIndex)
{
	if (minIndex > maxIndex)
	{
		if (maxIndex < 0)
			maxIndex = 0;

		if (minIndex >= m_size)
			minIndex = m_size - 1;
	}
	else
	{
		if (minIndex < 0)
			minIndex = 0;

		if (maxIndex >= m_size)
			maxIndex = m_size - 1;
	}

	int offset = minIndex + maxIndex - 1;
	m_size -= offset;
	CheckSize();
	return true;
}

template <class T>
bool ObjectDictionary<T>::Remove(T *object)
{
	bool found = false;
	for (int i = 0; i < m_size; i++)
	{
		if (m_entries[i].object == object) {
			RemoveIndex(i);
			found = true;
		}
	}

	return found ? true : false;
}

template <class T>
bool ObjectDictionary<T>::RemoveSingle(T *object)
{
	for (int i = 0; i < m_size; i++)
	{
		if (m_entries[i].object == object) {
			RemoveIndex(i);
			return true;
		}
	}

	return false;
}

template <class T>
bool ObjectDictionary<T>::RemoveKey(float key)
{
	int i = FindClosestAsIndex(key);
	if (m_entries[i].key == key)
	{
		int j = i;
		do {
			++j;
		}
		while (key == m_entries[j + 1].key);

		return RemoveIndexRange(i, j);
	}

	return false;
}

template <class T>
bool ObjectDictionary<T>::CheckSize()
{
	int newSize = m_maxSize;
	if (m_size == m_maxSize)
	{
		newSize = 1 - (int)(m_maxSize * -1.25f);
	}
	else if (m_maxSize * 0.5f > m_size)
	{
		newSize = (int)(m_maxSize * 0.75f);
	}

	if (newSize != m_maxSize)
	{
		auto newEntries = (entry_t *)malloc(sizeof(entry_t) * newSize);
		if (!newEntries)
			return false;

		Q_memset(&newEntries[m_size], 0, sizeof(entry_t) * (newSize - m_size));

		if (m_entries && m_size)
		{
			Q_memcpy(newEntries, m_entries, sizeof(entry_t) * m_size);
			free(m_entries);
		}

		m_entries = newEntries;
		m_maxSize = newSize;
	}

	return true;
}

template <class T>
void ObjectDictionary<T>::Init()
{
	m_size = 0;
	m_maxSize = 0;
	m_entries = nullptr;

	CheckSize();
	ClearCache();
}

template <class T>
void ObjectDictionary<T>::Init(int baseSize)
{
	m_size = 0;
	m_maxSize = 0;
	m_entries = (entry_t *)malloc(sizeof(entry_t) * baseSize);
	Q_memset(m_entries, 0, sizeof(entry_t) * baseSize);

	if (m_entries) {
		m_maxSize = baseSize;
	}
}

template <class T>
bool ObjectDictionary<T>::Add(T *object)
{
	return Add(object, 0);
}

template <class T>
int ObjectDictionary<T>::CountElements()
{
	return m_size;
}

template <class T>
bool ObjectDictionary<T>::IsEmpty()
{
	return (m_size == 0) ? true : false;
}

template <class T>
bool ObjectDictionary<T>::Contains(T *object)
{
	if (FindObjectInCache(object) >= 0)
		return true;

	for (int i = 0; i < m_size; i++)
	{
		auto e = &m_entries[i];
		if (e->object == object) {
			AddToCache(e);
			return true;
		}
	}

	return false;
}

template <class T>
T *ObjectDictionary<T>::GetFirst()
{
	m_currentEntry = 0;
	return GetNext();
}

template <class T>
T *ObjectDictionary<T>::GetLast()
{
	return (m_size > 0) ? m_entries[m_size - 1].object : nullptr;
}

template <class T>
bool ObjectDictionary<T>::ChangeKey(T *object, float newKey)
{
	int pos = FindObjectInCache(object);
	if (pos < 0)
	{
		for (pos = 0; pos < m_size; pos++)
		{
			if (m_entries[pos].object == object) {
				AddToCache(&m_entries[pos]);
				break;
			}
		}

		if (pos == m_size) {
			return false;
		}
	}

	entry_t *p, *e;

	p = &m_entries[pos];
	if (p->key == newKey)
		return false;

	int newpos = FindClosestAsIndex(newKey);
	e = &m_entries[newpos];
	if (pos < newpos)
	{
		if (e->key > newKey)
			e--;

		auto e2 = &m_entries[pos + 1];
		while (p < e)
		{
			p->object = e2->object;
			p->key = e2->key;

			p++;
			e2++;
		}
	}
	else if (pos > newpos)
	{
		if (e->key > newKey)
			e++;

		auto e2 = &m_entries[pos - 1];
		while (p > e)
		{
			p->object = e2->object;
			p->key = e2->key;

			p--;
			e2--;
		}
	}

	p->object = object;
	p->key = newKey;
	ClearCache();

	return true;
}

template <class T>
bool ObjectDictionary<T>::UnsafeChangeKey(T *object, float newKey)
{
	int pos = FindObjectInCache(object);
	if (pos < 0)
	{
		for (pos = 0; pos < m_size; pos++)
		{
			if (m_entries[pos].object == object) {
				break;
			}
		}

		if (pos == m_size) {
			return false;
		}
	}

	m_entries[pos].key = newKey;
	ClearCache();
	return true;
}

template <class T>
void ObjectDictionary<T>::AddToCache(entry_t *entry)
{
	int i = (m_cacheIndex % MAX_OBJECT_CACHE);

	m_cache[i].object = entry;
	m_cache[i].key = entry->key;
	m_cacheIndex++;
}

template <class T>
void ObjectDictionary<T>::AddToCache(entry_t *entry, float key)
{
	int i = (m_cacheIndex % MAX_OBJECT_CACHE);

	m_cache[i].object = entry;
	m_cache[i].key = key;
	m_cacheIndex++;
}

template <class T>
int ObjectDictionary<T>::FindKeyInCache(float key)
{
	for (auto& ch : m_cache)
	{
		if (ch.object && ch.key == key) {
			return (entry_t *)ch.object - m_entries;
		}
	}

	return -1;
}

template <class T>
int ObjectDictionary<T>::FindObjectInCache(T *object)
{
	for (auto& ch : m_cache)
	{
		if (ch.object && ch.object == object) {
			return (entry_t *)ch.object - m_entries;
		}
	}

	return -1;
}

template <class T>
T *ObjectDictionary<T>::FindClosestKey(float key)
{
	m_currentEntry = FindClosestAsIndex(key);
	return GetNext();
}

template <class T>
T *ObjectDictionary<T>::GetNext()
{
	if (m_currentEntry < 0 || m_currentEntry >= m_size)
		return nullptr;

	return static_cast<T *>(m_entries[m_currentEntry++].object);
}

template <class T>
T *ObjectDictionary<T>::FindExactKey(float key)
{
	if ((m_currentEntry = FindClosestAsIndex(key)) < 0)
		return nullptr;

	return (m_entries[m_currentEntry].key == key) ? GetNext() : nullptr;
}
