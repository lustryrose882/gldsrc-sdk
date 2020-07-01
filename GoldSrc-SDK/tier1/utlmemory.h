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

#include <string.h>

#include "tier0/dbg.h"
#include "tier0/platform.h"

#ifdef _MSC_VER
	#pragma warning(push)
	#pragma warning(disable:4100) // 'identifier' : unreferenced formal parameter
#endif

class CUtlMemoryAllocator
{
protected:
	inline void *Alloc(int nInitSize)
	{
		void *block = malloc(nInitSize);
		memset(block, 0, nInitSize);
		return block;
	}

	inline void *Realloc(void *pMemory, int Size)
	{
		return realloc(pMemory, Size);
	}

	inline void Free(void *pMemory)
	{
		free(pMemory);
	}
};

// The CUtlMemory class:
// A growable memory class which doubles in size by default
template <class T, class I = int, class A = CUtlMemoryAllocator>
class CUtlMemory: public A
{
public:
	// constructor, destructor
	CUtlMemory(int nGrowSize = 0, int nInitAllocationCount = 0);
	CUtlMemory(void *pMemory, int numElements);
	CUtlMemory(const void *pMemory, int numElements);
	~CUtlMemory();

	// Copy construction and assignment are not valid
	CUtlMemory(const CUtlMemory &rhs) = delete;
	const CUtlMemory &operator=(const CUtlMemory &rhs) = delete;

#ifdef VALVE_RVALUE_REFS
	CUtlMemory(CUtlMemory &&src);
	CUtlMemory &operator=(CUtlMemory &&src);
#endif // VALVE_RVALUE_REFS

	// Set the size by which the memory grows
	void Init(int nGrowSize = 0, int nInitSize = 0);

	class Iterator_t
	{
	public:
		Iterator_t(I i) : index(i) {}
		I index;

		bool operator==(const Iterator_t it) const { return index == it.index; }
		bool operator!=(const Iterator_t it) const { return index != it.index; }
	};

	Iterator_t First() const							{ return Iterator_t(IsIdxValid(0) ? 0 : InvalidIndex()); }
	Iterator_t Next(const Iterator_t &it) const			{ return Iterator_t(IsIdxValid(it.index + 1) ? it.index + 1 : InvalidIndex()); }
	I GetIndex(const Iterator_t &it) const				{ return it.index; }
	bool IsIdxAfter(I i, const Iterator_t &it) const	{ return i > it.index; }
	bool IsValidIterator(const Iterator_t &it) const	{ return IsIdxValid(it.index); }
	Iterator_t InvalidIterator() const					{ return Iterator_t(InvalidIndex()); }

	// element access
	T		&operator[](I i);
	const T	&operator[](I i) const;
	T		&Element(I i);
	const T	&Element(I i) const;

	// Can we use this index?
	bool IsIdxValid(I i) const;

	// Specify the invalid ('null') index that we'll only return on failure
	static const I INVALID_INDEX = (I)-1; // For use with COMPILE_TIME_ASSERT
	static I InvalidIndex()
	{
		return INVALID_INDEX;
	}

	// Gets the base address (can change when adding elements!)
	T *Base();
	const T *Base() const;

	// Attaches the buffer to external memory....
	void SetExternalBuffer(void *pMemory, int numElements);
	void SetExternalBuffer(const void *pMemory, int numElements);
	void AssumeMemory(void *pMemory, int nSize);
	T *Detach();
	void *DetachMemory();

	// Fast swap
	void Swap(CUtlMemory<T, I, A> &mem);

	// Switches the buffer from an external memory buffer to a reallocatable buffer
	// Will copy the current contents of the external buffer to the reallocatable buffer
	void ConvertToGrowableMemory(int nGrowSize);

	// Size
	int NumAllocated() const;
	int CubAllocated() const;
	int Count() const;

	// Grows the memory, so that at least allocated + num elements are allocated
	void Grow(int num = 1);

	// Makes sure we've got at least this much memory
	void EnsureCapacity(int num);

	// Memory deallocation
	void Purge();

	// Purge all but the given number of elements
	void Purge(int numElements, bool bRealloc = true);

	// is the memory externally allocated?
	bool IsExternallyAllocated() const;

	// is the memory read only?
	bool IsReadOnly() const;

	// Set the size by which the memory grows
	void SetGrowSize(int size);

#ifdef DBGFLAG_VALIDATE
	void Validate(CValidator &validator, const char *pchName);		// Validate our internal structures
#endif // DBGFLAG_VALIDATE

protected:
	enum
	{
		EXTERNAL_BUFFER_MARKER = -1,
		EXTERNAL_CONST_BUFFER_MARKER = -2,
	};

	void *m_pMemory;
	int m_nAllocationCount;
	int m_nGrowSize;
};

// The CUtlMemory class:
// A growable memory class which doubles in size by default
template <class T, size_t SIZE, class I = int>
class CUtlMemoryFixedGrowable: public CUtlMemory<T, I>
{
	using BaseClass = CUtlMemory<T, I>;

public:
	CUtlMemoryFixedGrowable(int nGrowSize = 0, int nInitSize = SIZE) :
		BaseClass(m_pFixedMemory, SIZE)
	{
		Assert(nInitSize == 0 || nInitSize == SIZE);
		m_nMallocGrowSize = nGrowSize;
	}

	void Grow(int nCount = 1)
	{
		if (this->IsExternallyAllocated())
		{
			this->ConvertToGrowableMemory(m_nMallocGrowSize);
		}

		BaseClass::Grow(nCount);
	}

	void EnsureCapacity(int num)
	{
		if (CUtlMemory<T, T>::m_nAllocationCount >= num)
			return;

		if (this->IsExternallyAllocated())
		{
			// Can't grow a buffer whose memory was externally allocated
			this->ConvertToGrowableMemory(m_nMallocGrowSize);
		}

		BaseClass::EnsureCapacity(num);
	}

private:
	int m_nMallocGrowSize;
	T m_pFixedMemory[SIZE];
};

// The CUtlMemoryFixed class:
// A fixed memory class
template <typename T, size_t SIZE, int nAlignment = 0>
class CUtlMemoryFixed
{
public:
	// constructor, destructor
	CUtlMemoryFixed(int nGrowSize = 0, int nInitSize = 0)	{ Assert(nInitSize == 0 || nInitSize == SIZE); 	}
	CUtlMemoryFixed(void *pMemory, int numElements)			{ Assert(0); 									}

	// Can we use this index?
	bool IsIdxValid(int i) const							{ return (i >= 0) && (i < SIZE); }

	// Specify the invalid ('null') index that we'll only return on failure
	static const int INVALID_INDEX = -1; // For use with COMPILE_TIME_ASSERT
	static int InvalidIndex() { return INVALID_INDEX; }

	// Gets the base address
	T *Base()												{ if (nAlignment == 0) return (T *)(&m_Memory[0]); else return (T *)AlignValue(&m_Memory[0], nAlignment); }
	const T *Base() const									{ if (nAlignment == 0) return (T *)(&m_Memory[0]); else return (T *)AlignValue(&m_Memory[0], nAlignment); }

	// element access
	T		&operator[](int i)								{ Assert(IsIdxValid(i)); return Base()[i];	}
	const T	&operator[](int i) const						{ Assert(IsIdxValid(i)); return Base()[i];	}
	T		&Element(int i)									{ Assert(IsIdxValid(i)); return Base()[i];	}
	const T	&Element(int i) const							{ Assert(IsIdxValid(i)); return Base()[i];	}

	// Attaches the buffer to external memory....
	void SetExternalBuffer(void *pMemory, int numElements)	{ Assert(0); }

	// Size
	int NumAllocated() const	{ return SIZE; }
	int Count() const			{ return SIZE; }

	// Grows the memory, so that at least allocated + num elements are allocated
	void Grow(int num = 1) { Assert(0); }

	// Makes sure we've got at least this much memory
	void EnsureCapacity(int num) { Assert(num <= SIZE); }

	// Memory deallocation
	void Purge() {}

	// Purge all but the given number of elements (NOT IMPLEMENTED IN CUtlMemoryFixed)
	void Purge(int numElements, bool bRealloc = true) { Assert(0); }

	// is the memory externally allocated?
	bool IsExternallyAllocated() const { return false; }

	// Set the size by which the memory grows
	void SetGrowSize(int size) {}

	class Iterator_t
	{
	public:
		Iterator_t(int i) : index(i) {}
		int index;
		bool operator==(const Iterator_t it) const		{ return index == it.index; }
		bool operator!=(const Iterator_t it) const		{ return index != it.index; }
	};

	Iterator_t First() const							{ return Iterator_t(IsIdxValid(0) ? 0 : InvalidIndex()); }
	Iterator_t Next(const Iterator_t &it) const			{ return Iterator_t(IsIdxValid(it.index + 1) ? it.index + 1 : InvalidIndex()); }
	int GetIndex(const Iterator_t &it) const			{ return it.index; }
	bool IsIdxAfter(int i, const Iterator_t &it) const	{ return i > it.index; }
	bool IsValidIterator(const Iterator_t &it) const	{ return IsIdxValid(it.index); }
	Iterator_t InvalidIterator() const					{ return Iterator_t(InvalidIndex()); }

#ifdef DBGFLAG_VALIDATE
	void Validate(CValidator &validator, const char *pchName) {}		// Validate our internal structures
#endif // DBGFLAG_VALIDATE

private:
	uint8_t m_Memory[SIZE * sizeof(T) + nAlignment];
};

// Constructor, Destructor
template <class T, class I, class A>
CUtlMemory<T, I, A>::CUtlMemory(int nGrowSize, int nInitAllocationCount) :
	m_pMemory(NULL),
	m_nAllocationCount(nInitAllocationCount),
	m_nGrowSize(nGrowSize)
{
	Assert(nGrowSize >= 0);

	if (m_nAllocationCount)
	{
		m_pMemory = A::Alloc(m_nAllocationCount * sizeof(T));
	}
}

template <class T, class I, class A>
CUtlMemory<T, I, A>::CUtlMemory(void *pMemory, int numElements) :
	m_pMemory(pMemory),
	m_nAllocationCount(numElements)
{
	// Special marker indicating externally supplied modifyable memory
	m_nGrowSize = EXTERNAL_BUFFER_MARKER;
}

template <class T, class I, class A>
CUtlMemory<T, I, A>::CUtlMemory(const void *pMemory, int numElements) :
	m_pMemory(const_cast<void *>(pMemory)),
	m_nAllocationCount(numElements)
{
	// Special marker indicating externally supplied modifyable memory
	m_nGrowSize = EXTERNAL_CONST_BUFFER_MARKER;
}

template <class T, class I, class A>
CUtlMemory<T, I, A>::~CUtlMemory()
{
	Purge();

#ifdef _DEBUG
	m_pMemory = reinterpret_cast<void *>(0xFEFEBAAD);
	m_nAllocationCount = 0x7BADF00D;
#endif
}

#ifdef VALVE_RVALUE_REFS

template <class T, class I, class A>
CUtlMemory<T, I, A>::CUtlMemory(CUtlMemory &&src) :
	m_pMemory(src.m_pMemory),
	m_nAllocationCount(src.m_nAllocationCount),
	m_nGrowSize(src.m_nGrowSize)
{
	// Default init this so when we destruct src it doesn't do anything
	src.m_pMemory = NULL;
	src.m_nAllocationCount = 0;
	src.m_nGrowSize = 0;
}

template <class T, class I, class A>
CUtlMemory<T, I, A> &CUtlMemory<T, I, A>::operator=(CUtlMemory &&src)
{
	// Copy member variables to locals before purge to handle self-assignment
	void *pMemory = src.m_pMemory;
	int nAllocationCount = src.m_nAllocationCount;
	int nGrowSize = src.m_nGrowSize;

	src.m_pMemory = NULL;
	src.m_nAllocationCount = 0;
	src.m_nGrowSize = 0;

	// If this is a self-assignment, Purge() is a no-op here
	Purge();

	m_pMemory = pMemory;
	m_nAllocationCount = nAllocationCount;
	m_nGrowSize = nGrowSize;

	return *this;
}

#endif // VALVE_RVALUE_REFS

template <class T, class I, class A>
void CUtlMemory<T, I, A>::Init(int nGrowSize, int nInitSize)
{
	Purge();

	m_nGrowSize = nGrowSize;
	m_nAllocationCount = nInitSize;

	Assert(nGrowSize >= 0);

	if (m_nAllocationCount)
	{
		m_pMemory = A::Alloc(m_nAllocationCount * sizeof(T));
	}
}

// Fast swap
template <class T, class I, class A>
void CUtlMemory<T, I, A>::Swap(CUtlMemory<T, I, A> &mem)
{
	SWAP(m_nGrowSize, mem.m_nGrowSize);
	SWAP(m_pMemory, mem.m_pMemory);
	SWAP(m_nAllocationCount, mem.m_nAllocationCount);
}

// Switches the buffer from an external memory buffer to a reallocatable buffer
template <class T, class I, class A>
void CUtlMemory<T, I, A>::ConvertToGrowableMemory(int nGrowSize)
{
	if (!IsExternallyAllocated())
		return;

	m_nGrowSize = nGrowSize;
	if (m_nAllocationCount)
	{
		int nNumBytes = m_nAllocationCount * sizeof(T);
		void *pMemory = A::Alloc(nNumBytes);
		memcpy(pMemory, m_pMemory, nNumBytes);
		m_pMemory = pMemory;
	}
	else
	{
		m_pMemory = NULL;
	}
}

// Attaches the buffer to external memory
template <class T, class I, class A>
void CUtlMemory<T, I, A>::SetExternalBuffer(void *pMemory, int numElements)
{
	// Blow away any existing allocated memory
	Purge();

	m_pMemory = pMemory;
	m_nAllocationCount = numElements;

	// Indicate that we don't own the memory
	m_nGrowSize = EXTERNAL_BUFFER_MARKER;
}

template <class T, class I, class A>
void CUtlMemory<T, I, A>::SetExternalBuffer(const void *pMemory, int numElements)
{
	// Blow away any existing allocated memory
	Purge();

	m_pMemory = const_cast<void *>(pMemory);
	m_nAllocationCount = numElements;

	// Indicate that we don't own the memory
	m_nGrowSize = EXTERNAL_CONST_BUFFER_MARKER;
}

template <class T, class I, class A>
void CUtlMemory<T, I, A>::AssumeMemory(void *pMemory, int numElements)
{
	// Blow away any existing allocated memory
	Purge();

	// Simply take the pointer but don't mark us as external
	m_pMemory = pMemory;
	m_nAllocationCount = numElements;
}

template <class T, class I, class A>
void *CUtlMemory<T, I, A>::DetachMemory()
{
	if (IsExternallyAllocated())
		return NULL;

	void *pMemory = m_pMemory;
	m_pMemory = NULL;
	m_nAllocationCount = 0;
	return pMemory;
}

template <class T, class I, class A>
inline T *CUtlMemory<T, I, A>::Detach()
{
	return (T *)DetachMemory();
}

// Element access
template <class T, class I, class A>
inline T &CUtlMemory<T, I, A>::operator[](I i)
{
	DbgAssert(!IsReadOnly());
	DbgAssert(IsIdxValid(i));
	return ((T *)m_pMemory)[i];
}

template <class T, class I, class A>
inline const T &CUtlMemory<T, I, A>::operator[](I i) const
{
	DbgAssert(IsIdxValid(i));
	return ((T *)m_pMemory)[i];
}

template <class T, class I, class A>
inline T &CUtlMemory<T, I, A>::Element(I i)
{
	DbgAssert(!IsReadOnly());
	DbgAssert(IsIdxValid(i));
	return ((T *)m_pMemory)[i];
}

template <class T, class I, class A>
inline const T &CUtlMemory<T, I, A>::Element(I i) const
{
	DbgAssert(IsIdxValid(i));
	return ((T *)m_pMemory)[i];
}

// Is the memory externally allocated?
template <class T, class I, class A>
bool CUtlMemory<T, I, A>::IsExternallyAllocated() const
{
	return (m_nGrowSize < 0);
}

// Is the memory read only?
template <class T, class I, class A>
bool CUtlMemory<T, I, A>::IsReadOnly() const
{
	return (m_nGrowSize == EXTERNAL_CONST_BUFFER_MARKER);
}

template <class T, class I, class A>
void CUtlMemory<T, I, A>::SetGrowSize(int nSize)
{
	Assert(!IsExternallyAllocated());
	Assert(nSize >= 0);

	m_nGrowSize = nSize;
}

// Gets the base address (can change when adding elements!)
template <class T, class I, class A>
inline T *CUtlMemory<T, I, A>::Base()
{
	Assert(!IsReadOnly());
	return (T *)m_pMemory;
}

template <class T, class I, class A>
inline const T *CUtlMemory<T, I, A>::Base() const
{
	return (T *)m_pMemory;
}

// Size
template <class T, class I, class A>
inline int CUtlMemory<T, I, A>::NumAllocated() const
{
	return m_nAllocationCount;
}

template <class T, class I, class A>
inline int CUtlMemory<T, I, A>::CubAllocated() const
{
	return m_nAllocationCount * sizeof(T);
}

template <class T, class I, class A>
inline int CUtlMemory<T, I, A>::Count() const
{
	return m_nAllocationCount;
}

// Is element index valid?
template <class T, class I, class A>
inline bool CUtlMemory<T, I, A>::IsIdxValid(I i) const
{
	// GCC warns if I is an unsigned type and we do a ">= 0" against it (since the comparison is always 0).
	// We get the warning even if we cast inside the expression. It only goes away if we assign to another variable.
	long x = i;
	return (x >= 0) && (x < m_nAllocationCount);
}

// Grows the memory
inline int UtlMemory_CalcNewAllocationCount(int nAllocationCount, int nGrowSize, int nNewSize, int nBytesItem, bool &needToReallocate)
{
	if (nGrowSize)
	{
		nAllocationCount = ((1 + ((nNewSize - 1) / nGrowSize)) * nGrowSize);
		needToReallocate = true;
	}
	else
	{
		if (!nAllocationCount)
		{
			if (nBytesItem > 0)
			{
				// Compute an allocation which is at least as big as a cache line...
				nAllocationCount = (31 + nBytesItem) / nBytesItem;

				// If the requested amount is larger then compute an allocation which
				// is exactly the right size. Otherwise we can end up with wasted memory
				// when CUtlVector::EnsureCount(n) is called.
				if (nAllocationCount < nNewSize)
					nAllocationCount = nNewSize;
			}
			else
			{
				// Should be impossible, but if hit try to grow an amount that may be large
				// enough for most cases and thus avoid both divide by zero above as well as
				// likely memory corruption afterwards.
				AssertMsg1(false, "nBytesItem is %d in UtlMemory_CalcNewAllocationCount", nBytesItem);
				nAllocationCount = 256;
			}
		}

		// Cap growth to avoid high-end doubling insanity (1 GB -> 2 GB -> overflow)
		int nMaxGrowStep = max(1, 256 * 1024 * 1024 / (nBytesItem > 0 ? nBytesItem : 1));
		while (nAllocationCount < nNewSize)
		{
			// Grow by doubling, but at most 256 MB at a time
			nAllocationCount += min(nAllocationCount, nMaxGrowStep);
			needToReallocate = true;
		}
	}

	return nAllocationCount;
}

template <class T, class I, class A>
void CUtlMemory<T, I, A>::Grow(int num)
{
	Assert(num > 0);

	if (IsExternallyAllocated())
	{
		// Can't grow a buffer whose memory was externally allocated
		Assert(0);
		return;
	}

	// Make sure we have at least numallocated + num allocations.
	// Use the grow rules specified for this memory (in m_nGrowSize)
	int nAllocationRequested = m_nAllocationCount + num;

	bool needToReallocate = false;
	int nNewAllocationCount = UtlMemory_CalcNewAllocationCount(m_nAllocationCount, m_nGrowSize, nAllocationRequested, sizeof(T), needToReallocate);

	// if m_nAllocationRequested wraps index type I, recalculate
	if ((int)(I)nNewAllocationCount < nAllocationRequested)
	{
		if ((int)(I)nNewAllocationCount == 0 && (int)(I)(nNewAllocationCount - 1) >= nAllocationRequested)
		{
			nNewAllocationCount--; // deal w/ the common case of m_nAllocationCount == MAX_USHORT + 1
		}
		else
		{
			if ((int)(I)nAllocationRequested != nAllocationRequested)
			{
				// we've been asked to grow memory to a size s.t. the index type can't address the requested amount of memory
				Assert(0);
				return;
			}

			while ((int)(I)nNewAllocationCount < nAllocationRequested)
			{
				nNewAllocationCount = (nNewAllocationCount + nAllocationRequested) / 2;
			}
		}
	}

	m_nAllocationCount = nNewAllocationCount;

	if (m_pMemory && needToReallocate)
	{
		m_pMemory = A::Realloc(m_pMemory, m_nAllocationCount * sizeof(T));
		Assert(m_pMemory);
	}
	else if (!m_pMemory)
	{
		m_pMemory = A::Alloc(m_nAllocationCount * sizeof(T));
		Assert(m_pMemory);
	}
	else
	{
		Assert(!"Unexpected memory grow error!");
	}
}

// Makes sure we've got at least this much memory
template <class T, class I, class A>
inline void CUtlMemory<T, I, A>::EnsureCapacity(int num)
{
	if (m_nAllocationCount >= num)
		return;

	if (IsExternallyAllocated())
	{
		// Can't grow a buffer whose memory was externally allocated
		Assert(0);
		return;
	}

	m_nAllocationCount = num;

	if (m_pMemory)
	{
		m_pMemory = A::Realloc(m_pMemory, m_nAllocationCount * sizeof(T));
	}
	else
	{
		m_pMemory = A::Alloc(m_nAllocationCount * sizeof(T));
	}
}

// Memory deallocation
template <class T, class I, class A>
void CUtlMemory<T, I, A>::Purge()
{
	if (!IsExternallyAllocated())
	{
		if (m_pMemory)
		{
			A::Free(m_pMemory);
			m_pMemory = NULL;
		}

		m_nAllocationCount = 0;
	}
}

template <class T, class I, class A>
void CUtlMemory<T, I, A>::Purge(int numElements, bool bRealloc)
{
	Assert(numElements >= 0);

	if (numElements > m_nAllocationCount)
	{
		// Ensure this isn't a grow request in disguise.
		Assert(numElements <= m_nAllocationCount);
		return;
	}

	// If we have zero elements, simply do a purge:
	if (numElements == 0)
	{
		Purge();
		return;
	}

	if (IsExternallyAllocated())
	{
		// Can't shrink a buffer whose memory was externally allocated, fail silently like purge
		return;
	}

	// If the number of elements is the same as the allocation count, we are done
	if (numElements == m_nAllocationCount)
	{
		return;
	}

	if (!m_pMemory)
	{
		// Allocation count is non zero, but memory is null.
		Assert(m_pMemory);
		return;
	}

	if (bRealloc)
	{
		m_nAllocationCount = numElements;

		// Allocation count > 0, shrink it down
		m_pMemory = A::Realloc(m_pMemory, m_nAllocationCount * sizeof(T));
	}
	else
	{
		// Some of the tracking may be wrong as we are changing the size but are not reallocating.
		m_nAllocationCount = numElements;
	}
}

// Data and memory validation
#ifdef DBGFLAG_VALIDATE
void CUtlMemoryBase::Validate(CValidator &validator, const char *pchName)
{
#ifdef _WIN32
	validator.Push(typeid(*this).raw_name(), this, pchName);
#else
	validator.Push(typeid(*this).name(), this, pchName);
#endif

	if (m_pMemory)
	{
		validator.ClaimMemory((void *)m_pMemory);
	}

	validator.Pop();
}
#endif // DBGFLAG_VALIDATE

// The CUtlMemory class:
// A growable memory class which doubles in size by default
template <class T, int nAlignment>
class CUtlMemoryAligned: public CUtlMemory<T>
{
public:
	// constructor, destructor
	CUtlMemoryAligned(int nGrowSize = 0, int nInitSize = 0);
	CUtlMemoryAligned(void *pMemory, int numElements);
	CUtlMemoryAligned(const void *pMemory, int numElements);
	~CUtlMemoryAligned();

	// Attaches the buffer to external memory....
	void SetExternalBuffer(void *pMemory, int numElements);
	void SetExternalBuffer(const void *pMemory, int numElements);

	// Grows the memory, so that at least allocated + num elements are allocated
	void Grow(int num = 1);

	// Makes sure we've got at least this much memory
	void EnsureCapacity(int num);

	// Memory deallocation
	void Purge();

	// Purge all but the given number of elements (NOT IMPLEMENTED IN CUtlMemoryAligned)
	void Purge(int numElements)
	{
		Assert(0);
	}

private:
	void *Align(const void *pAddr);
};

// Aligns a pointer
template <class T, int nAlignment>
void *CUtlMemoryAligned<T, nAlignment>::Align(const void *pAddr)
{
	size_t nAlignmentMask = nAlignment - 1;
	return (void *)(((size_t)pAddr + nAlignmentMask) & (~nAlignmentMask));
}

// Constructor, destructor
template <class T, int nAlignment>
CUtlMemoryAligned<T, nAlignment>::CUtlMemoryAligned(int nGrowSize, int nInitAllocationCount)
{
	CUtlMemory<T>::m_pMemory = NULL;
	CUtlMemory<T>::m_nAllocationCount = nInitAllocationCount;
	CUtlMemory<T>::m_nGrowSize = nGrowSize;

	// Alignment must be a power of two
	COMPILE_TIME_ASSERT((nAlignment & (nAlignment - 1)) == 0);
	Assert((nGrowSize >= 0) && (nGrowSize != CUtlMemory<T>::EXTERNAL_BUFFER_MARKER));
	if (CUtlMemory<T>::m_nAllocationCount)
	{
		CUtlMemory<T>::m_pMemory = _aligned_malloc(nInitAllocationCount * sizeof(T), nAlignment);
	}
}

template <class T, int nAlignment>
CUtlMemoryAligned<T, nAlignment>::CUtlMemoryAligned(void *pMemory, int numElements)
{
	// Special marker indicating externally supplied memory
	CUtlMemory<T>::m_nGrowSize = CUtlMemory<T>::EXTERNAL_BUFFER_MARKER;

	CUtlMemory<T>::m_pMemory = Align(pMemory);
	CUtlMemory<T>::m_nAllocationCount = ((int)(pMemory + numElements) - (int)CUtlMemory<T>::m_pMemory) / sizeof(T);
}

template <class T, int nAlignment>
CUtlMemoryAligned<T, nAlignment>::CUtlMemoryAligned(const void *pMemory, int numElements)
{
	// Special marker indicating externally supplied memory
	CUtlMemory<T>::m_nGrowSize = CUtlMemory<T>::EXTERNAL_CONST_BUFFER_MARKER;

	CUtlMemory<T>::m_pMemory = Align(pMemory);
	CUtlMemory<T>::m_nAllocationCount = ((int)(pMemory + numElements) - (int)CUtlMemory<T>::m_pMemory) / sizeof(T);
}

template <class T, int nAlignment>
CUtlMemoryAligned<T, nAlignment>::~CUtlMemoryAligned()
{
	Purge();
}

// Attaches the buffer to external memory
template <class T, int nAlignment>
void CUtlMemoryAligned<T, nAlignment>::SetExternalBuffer(void *pMemory, int numElements)
{
	// Blow away any existing allocated memory
	Purge();

	CUtlMemory<T>::m_pMemory = Align(pMemory);
	CUtlMemory<T>::m_nAllocationCount = ((int)(pMemory + numElements) - (int)CUtlMemory<T>::m_pMemory) / sizeof(T);

	// Indicate that we don't own the memory
	CUtlMemory<T>::m_nGrowSize = CUtlMemory<T>::EXTERNAL_BUFFER_MARKER;
}

template <class T, int nAlignment>
void CUtlMemoryAligned<T, nAlignment>::SetExternalBuffer(const void *pMemory, int numElements)
{
	// Blow away any existing allocated memory
	Purge();

	CUtlMemory<T>::m_pMemory = Align(pMemory);
	CUtlMemory<T>::m_nAllocationCount = ((int)(pMemory + numElements) - (int)CUtlMemory<T>::m_pMemory) / sizeof(T);

	// Indicate that we don't own the memory
	CUtlMemory<T>::m_nGrowSize = CUtlMemory<T>::EXTERNAL_CONST_BUFFER_MARKER;
}

// Grows the memory
template <class T, int nAlignment>
void CUtlMemoryAligned<T, nAlignment>::Grow(int num)
{
	Assert(num > 0);

	if (this->IsExternallyAllocated())
	{
		// Can't grow a buffer whose memory was externally allocated
		Assert(0);
		return;
	}

	// Make sure we have at least numallocated + num allocations.
	// Use the grow rules specified for this memory (in m_nGrowSize)
	int nAllocationRequested = CUtlMemory<T>::m_nAllocationCount + num;

	CUtlMemory<T>::m_nAllocationCount = UtlMemory_CalcNewAllocationCount(CUtlMemory<T>::m_nAllocationCount, CUtlMemory<T>::m_nGrowSize, nAllocationRequested, sizeof(T));

	if (CUtlMemory<T>::m_pMemory)
	{
		CUtlMemory<T>::m_pMemory = MemAlloc_ReallocAligned(CUtlMemory<T>::m_pMemory, CUtlMemory<T>::m_nAllocationCount * sizeof(T), nAlignment);
		Assert(CUtlMemory<T>::m_pMemory);
	}
	else
	{
		CUtlMemory<T>::m_pMemory = MemAlloc_AllocAligned(CUtlMemory<T>::m_nAllocationCount * sizeof(T), nAlignment);
		Assert(CUtlMemory<T>::m_pMemory);
	}
}

// Makes sure we've got at least this much memory
template <class T, int nAlignment>
inline void CUtlMemoryAligned<T, nAlignment>::EnsureCapacity(int num)
{
	if (CUtlMemory<T>::m_nAllocationCount >= num)
		return;

	if (this->IsExternallyAllocated())
	{
		// Can't grow a buffer whose memory was externally allocated
		Assert(0);
		return;
	}

	CUtlMemory<T>::m_nAllocationCount = num;

	if (CUtlMemory<T>::m_pMemory)
	{
		CUtlMemory<T>::m_pMemory = MemAlloc_ReallocAligned(CUtlMemory<T>::m_pMemory, CUtlMemory<T>::m_nAllocationCount * sizeof(T), nAlignment);
	}
	else
	{
		CUtlMemory<T>::m_pMemory = MemAlloc_AllocAligned(CUtlMemory<T>::m_nAllocationCount * sizeof(T), nAlignment);
	}
}

// Memory deallocation
template <class T, int nAlignment>
void CUtlMemoryAligned<T, nAlignment>::Purge()
{
	if (!this->IsExternallyAllocated())
	{
		if (CUtlMemory<T>::m_pMemory)
		{
			MemAlloc_FreeAligned(CUtlMemory<T>::m_pMemory);
			CUtlMemory<T>::m_pMemory = NULL;
		}

		CUtlMemory<T>::m_nAllocationCount = 0;
	}
}

// Shared allocation
// Implements virtual methods for use external
class CUtlMemoryAllocatorShared
{
public:
	using alloc_t		= void *(*)(size_t _Size);
	using realloc_t		= void *(*)(void *_Block, size_t _Size);
	using free_t		= void  (*)(void *_Block);

	// internal leak tracking should be used in debug
	virtual void SetMemFunctions(alloc_t _pfnalloc, realloc_t _pfnrealloc, free_t _pfnfree)
	{
		if (_pfnalloc)		m_Alloc = _pfnalloc;
		if (_pfnrealloc)	m_Realloc = _pfnrealloc;
		if (_pfnfree)		m_Free = _pfnfree;
	}

protected:
	CUtlMemoryAllocatorShared()
	{
		// initialize default mem functions
		m_Alloc		= malloc;
		m_Realloc	= realloc;
		m_Free		= free;
	}

	virtual void *Alloc(int nInitSize)
	{
		return m_Alloc(nInitSize);
	}

	virtual void *Realloc(void *pMemory, int Size)
	{
		return m_Realloc(pMemory, Size);
	}

	virtual void Free(void *pMemory)
	{
		m_Free(pMemory);
	}

private:
	alloc_t		m_Alloc;
	realloc_t	m_Realloc;
	free_t		m_Free;
};

template <class T, class I = int>
class CUtlMemoryShared: public CUtlMemory<T, I, CUtlMemoryAllocatorShared>
{
public:
	using CAllocator = CUtlMemoryAllocatorShared;

	// constructors
	CUtlMemoryShared(int nGrowSize = 0, int nInitSize = 0) :
		CUtlMemory<T, I, CAllocator>(nGrowSize, nInitSize)
	{
	}

	CUtlMemoryShared(T *pMemory, int numElements) :
		CUtlMemory<T, I, CAllocator>(pMemory, numElements)
	{
	}
};
