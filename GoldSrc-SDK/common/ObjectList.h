/*
*
*    This program is free software; you can redistribute it and/or modify it
*    under the terms of the GNU General Public License as published by the
*    Free Software Foundation; either version 2 of the License, or (at
*    your option) any later version.
*
*    This program is distributed in the hope that it will be useful, but
*    WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*    General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program; if not, write to the Free Software Foundation,
*    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*/

#pragma once

#include "IObjectContainer.h"

template <typename T = void>
class ObjectList: public IObjectContainer<T>
{
public:
	void Init();

	ObjectList();
	virtual ~ObjectList();
	bool Add(T *newObject);

	T *GetFirst();
	T *GetNext();

	bool AddTail(T *newObject);
	bool AddHead(T *newObject);
	bool Remove(T *object);
	bool Contains(T *object);

	T *RemoveTail();
	T *RemoveHead();

	void Clear(bool freeElementsMemory = false);
	int CountElements();
	bool IsEmpty();

	typedef struct element_s {
		struct element_s *prev;	// pointer to the last element or NULL
		struct element_s *next;	// pointer to the next elemnet or NULL
		T *object;				// the element's object
	} element_t;

protected:
	element_t *m_head;    // first element in list
	element_t *m_tail;    // last element in list
	element_t *m_current; // current element in list
	int m_number;
};

template <typename T>
ObjectList<T>::ObjectList()
{
	m_head = m_tail = m_current = nullptr;
	m_number = 0;
}

template <typename T>
ObjectList<T>::~ObjectList()
{
	Clear(false);
}

template <typename T>
inline bool ObjectList<T>::AddHead(T *newObject)
{
	// create new element
	element_t *newElement = (element_t *)malloc(sizeof(element_t));
	Q_memset(newElement, 0, sizeof(element_t));

	// out of memory
	if (!newElement)
		return false;

	// insert element
	newElement->object = newObject;

	if (m_head)
	{
		newElement->next = m_head;
		m_head->prev = newElement;
	}

	m_head = newElement;

	// if list was empty set new m_tail
	if (!m_tail)
		m_tail = m_head;

	m_number++;
	return true;
}

template <typename T>
inline T *ObjectList<T>::RemoveHead()
{
	T *retObj;

	// check m_head is present
	if (m_head)
	{
		retObj = m_head->object;
		element_t *newHead = m_head->next;
		if (newHead)
			newHead->prev = nullptr;

		// if only one element is in list also update m_tail
		// if we remove this prev element
		if (m_tail == m_head)
			m_tail = nullptr;

		free(m_head);
		m_head = newHead;

		m_number--;
	}
	else
		retObj = nullptr;

	return retObj;
}

template <typename T>
inline bool ObjectList<T>::AddTail(T *newObject)
{
	// create new element
	element_t *newElement = (element_t *)malloc(sizeof(element_t));
	Q_memset(newElement, 0, sizeof(element_t));

	// out of memory
	if (!newElement)
		return false;

	// insert element
	newElement->object = newObject;

	if (m_tail)
	{
		newElement->prev = m_tail;
		m_tail->next = newElement;
	}

	m_tail = newElement;

	// if list was empty set new m_tail
	if (!m_head)
		m_head = m_tail;

	m_number++;
	return true;
}

template <typename T>
inline T *ObjectList<T>::RemoveTail()
{
	T *retObj;

	// check m_tail is present
	if (m_tail)
	{
		retObj = m_tail->object;
		element_t *newTail = m_tail->prev;
		if (newTail)
			newTail->next = nullptr;

		// if only one element is in list also update m_tail
		// if we remove this prev element
		if (m_head == m_tail)
			m_head = nullptr;

		free(m_tail);
		m_tail = newTail;

		m_number--;

	}
	else
		retObj = nullptr;

	return retObj;
}

template <typename T>
inline bool ObjectList<T>::IsEmpty()
{
	return (m_head == nullptr);
}

template <typename T>
int ObjectList<T>::CountElements()
{
	return m_number;
}

template <typename T>
inline bool ObjectList<T>::Contains(T *object)
{
	element_t *e = m_head;
	while (e)
	{
		if (e->object == object)
		{
			m_current = e;
			return true;
		}

		e = e->next;
	}

	return false;
}

template <typename T>
inline void ObjectList<T>::Clear(bool freeElementsMemory)
{
	element_t *ne;
	element_t *e = m_head;

	while (e)
	{
		ne = e->next;

		if (freeElementsMemory && e->object)
			free((void *)e->object);

		free(e);
		e = ne;
	}

	m_head = m_tail = m_current = nullptr;
	m_number = 0;
}

template <typename T>
inline bool ObjectList<T>::Remove(T *object)
{
	element_t *e = m_head;
	while (e)
	{
		if (e->object == object)
			break;

		e = e->next;
	}

	if (!e)
	{
		return false;
	}

	if (e->prev)
		e->prev->next = e->next;

	if (e->next)
		e->next->prev = e->prev;

	if (m_head == e)
		m_head = e->next;

	if (m_tail == e)
		m_tail = e->prev;

	if (m_current == e)
		m_current= e->next;

	free(e);
	m_number--;

	return true;
}

template <typename T>
inline void ObjectList<T>::Init()
{
	m_head = m_tail = m_current = nullptr;
	m_number = 0;
}

template <typename T>
T *ObjectList<T>::GetFirst()
{
	if (m_head)
	{
		m_current = m_head->next;
		return m_head->object;
	}
	else
	{
		m_current = nullptr;
		return nullptr;
	}
}

template <typename T>
inline T *ObjectList<T>::GetNext()
{
	if (m_current)
	{
		T *retObj = m_current->object;
		m_current = m_current->next;
		return retObj;
	}

	return nullptr;
}

template <typename T>
bool ObjectList<T>::Add(T *newObject)
{
	return AddTail(newObject);
}
