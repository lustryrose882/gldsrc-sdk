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

#include <stdlib.h>
#include <string.h>
#include <vgui/VGUI.h>

namespace vgui2
{


// Simple lightweight dynamic array implementation
template <class ELEMTYPE>
class Dar
{
public:
	Dar() :
		_count(0),
		_capacity(0),
		_data(NULL)
	{
	}

	~Dar()
	{
		if (_data)
		{
			delete [] _data;
			_data = NULL;
		}
	}

protected:
	enum { INVALID_DAR_IDX = -1 };

public:
	void EnsureCapacity(int wantedCapacity)
	{
		if (wantedCapacity <= _capacity)
			return;

		// double capacity until it is >= wantedCapacity
		// this could be done with math, but iterative is just so much more fun
		int newCapacity = _capacity;
		if (!newCapacity)
			newCapacity = 1;

		while (newCapacity < wantedCapacity)
		{
			newCapacity *= 2;
		}

		// allocate and zero newData
		ELEMTYPE *newData = new ELEMTYPE[newCapacity];
		if (!newData)
		{
			exit(0);
			return;
		}

		memset(newData, 0, sizeof(ELEMTYPE) * newCapacity);
		_capacity = newCapacity;

		// copy data into newData
		for (int i = 0; i < _count; i++)
		{
			newData[i] = _data[i];
		}

		delete [] _data;
		_data = newData;
	}

	int AddToTail(ELEMTYPE elem)
	{
		return AddElement(elem);
	}

	int AddToHead(ELEMTYPE elem)
	{
		return InsertElementAt(elem, 0);
	}

	// Returns the index of the element in the array, -1 if not found
	int FindElement(ELEMTYPE elem) const
	{
		for (int i = 0; i < _count; i++)
		{
			if (_data[i] == elem)
			{
				return i;
			}
		}

		return INVALID_DAR_IDX;
	}

	int InvalidIndex() const
	{
		return INVALID_DAR_IDX;
	}

	bool HasElement(ELEMTYPE elem) const
	{
		if (FindElement(elem) != InvalidIndex())
		{
			return true;
		}

		return false;
	}

	void SetCount(int count)
	{
		if (count < 0 || count > _capacity)
			return;

		_count = count;
	}

	int Count() const
	{
		return _count;
	}

	int AddElement(ELEMTYPE elem)
	{
		EnsureCapacity(_count + 1);
		_data[_count] = elem;
		_count++;
		return _count - 1;
	}

	void MoveElementToEnd(ELEMTYPE elem)
	{
		// FIXED: If there are no at least 2 elements, ignore
		if (_count < 2)
			return;

		// quick check to see if it's already at the end
		if (_data[_count - 1] == elem)
			return;

		// search backwards in the array looking for the element (since it's probably close to the end already)
		for (int i = _count - 2; i >= 0; i--)
		{
			if (_data[i] == elem)
			{
				// slide the data back
				memmove(_data + i, _data + i + 1, sizeof(ELEMTYPE) * (_count - (i + 1)));
				_data[_count - 1] = elem;
				break;
			}
		}
	}

	int PutElement(ELEMTYPE elem)
	{
		int index = FindElement(elem);
		if (index >= 0)
		{
			return index;
		}

		return AddElement(elem);
	}

	bool IsValidIndex(int i) const
	{
		return (i >= 0 && i < _count);
	}

	// insert element at index and move all the others down 1
	int InsertElementAt(ELEMTYPE elem, int index)
	{
		if (index < 0 || index > _count)
			return index;

		int idx;
		if (index == _count || _count == 0)
		{
			idx = AddElement(elem);
		}
		else
		{
			// just to make sure it is big enough
			idx = AddElement(elem);

			for (int i = idx; i > index; i--)
			{
				_data[i] = _data[i - 1];
			}

			_data[index] = elem;
		}

		return idx;
	}

	void SetElementAt(ELEMTYPE elem, int index)
	{
		if (index < 0 || index >= _capacity)
			return;

		if (index >= _count)
		{
			// null out from index to _count
			for (int i = _count; i < index; i++)
			{
				_data[i] = NULL;
			}

			SetCount(index + 1);
		}

		_data[index] = elem;
	}

	void RemoveElementAt(int index)
	{
		if (!IsValidIndex(index))
			return;

		// slide everything to the right of index, left one
		for (int i = index; i < _count - 1; i++)
		{
			_data[i] = _data[i + 1];
		}

		_count--;
	}

	void RemoveElementsBefore(int index)
	{
		if (!IsValidIndex(index))
			return;

		// Slide everything to the right of index, left to the start
		for (int i = index; i < _count; i++)
		{
			_data[i - index] = _data[i];
		}

		_count = _count - index;
	}

	void Remove(int index)
	{
		RemoveElementAt(index);
	}

	void RemoveElement(ELEMTYPE elem)
	{
		int i = FindElement(elem);
		if (i != InvalidIndex())
		{
			RemoveElementAt(i);
		}
	}

	void RemoveAll()
	{
		_count = 0;
	}

	ELEMTYPE operator[](int index)
	{
		if (!IsValidIndex(index))
			return NULL;

		return _data[index];
	}

	ELEMTYPE *GetBaseData() const
	{
		return _data;
	}

	ELEMTYPE *Base() const
	{
		return GetBaseData();
	}

	void CopyFrom(Dar<ELEMTYPE> &dar)
	{
		EnsureCapacity(dar.Count());
		memcpy(_data, dar._data, sizeof(ELEMTYPE) * dar.Count());
		_count = dar._count;
	}

private:
	int _count;
	int _capacity;
	ELEMTYPE *_data;
};


} // namespace vgui2
