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

#include <vector>

class CCoreTriangleEffect;

#define TRIANGLE_FPS 30

typedef struct visibleparticles_s
{
	CCoreTriangleEffect *pVisibleParticle;
} visibleparticles_t;

// Memory block record
class MemoryBlock
{
private:
	char *m_pData;
	//bool m_bBlockIsInUse;
	public:
	MemoryBlock(long lBlockSize) :
		next(NULL), prev(NULL)
		//m_bBlockIsInUse(false) // Initialize block to 'free' state.
	{
		// Allocate memory here.
		m_pData = new char[lBlockSize];
	}

	virtual ~MemoryBlock()
	{
		// Free memory.
		delete[] m_pData;
	}

	inline char *Memory() { return m_pData; }

	MemoryBlock *next;
	MemoryBlock *prev;
};

class MemList
{
public:
	MemList() : m_pHead(NULL) {}

	~MemList() { Reset(); }

	void Push(MemoryBlock *newItem)
	{
		if (!m_pHead)
		{
			m_pHead = newItem;
			newItem->next = NULL;
			newItem->prev = NULL;
			return;
		}

		auto temp = m_pHead;
		m_pHead = newItem;
		m_pHead->next = temp;
		m_pHead->prev = NULL;

		temp->prev = m_pHead;
	}


	MemoryBlock *Front()
	{
		return m_pHead;
	}

	MemoryBlock *Pop()
	{
		if (!m_pHead)
			return NULL;

		auto temp = m_pHead;

		m_pHead = m_pHead->next;

		if (m_pHead)
			m_pHead->prev = NULL;

		temp->next = NULL;
		temp->prev = NULL;

		return temp;
	}

	void Delete(MemoryBlock *pItem)
	{
		if (m_pHead == pItem)
		{
			auto temp = m_pHead;

			m_pHead = m_pHead->next;
			if (m_pHead)
				m_pHead->prev = NULL;

			temp->next = NULL;
			temp->prev = NULL;
			return;
		}

		auto prev = pItem->prev;
		auto next = pItem->next;

		if (prev)
			prev->next = next;

		if (next)
			next->prev = prev;

		pItem->next = NULL;
		pItem->prev = NULL;
	}

	void Reset()
	{
		while(m_pHead)
			Delete(m_pHead);
	}

private:
	MemoryBlock *m_pHead;
};

// Some helpful typedefs.
typedef std::vector<MemoryBlock *> VectorOfMemoryBlocks;
typedef VectorOfMemoryBlocks::iterator MemoryBlockIterator;

// Mini memory manager - singleton
class CMiniMem
{
private:
	// Main memory pool.  Array is fine, but vectors are
	//  easier. :)
	static VectorOfMemoryBlocks m_vecMemoryPool;
	// Size of memory blocks in pool.
	static long m_lMemoryBlockSize;
	static long m_lMaxBlocks;
	static long m_lMemoryPoolSize;
	static CMiniMem *_instance;

	int m_iTotalParticles;
	int m_iParticlesDrawn;

protected:
	// private constructor and destructor.
	CMiniMem(long lMemoryPoolSize, long lMaxBlockSize);
	virtual ~CMiniMem();

	// ------------ Memory pool manager calls.
	// Find a free block and mark it as "in use".
	// Return NULL if no free blocks found.
	char *AllocateFreeBlock();
	public:

	// Return a pointer to usable block of memory.
	char *newBlock();

	// Mark a target memory item as no longer "in use".
	void deleteBlock(MemoryBlock *p);

	// Return the remaining capacity of the memory pool as a percent.
	long PercentUsed();

	void ProcessAll(); //Processes all

	void Reset(); // clears memory, setting all particles to not used.

	static int ApplyForce(Vector vOrigin, Vector vDirection, float flRadius, float flStrength);

	static CMiniMem *Instance();
	static long MaxBlockSize();

	bool CheckSize(int iSize);

	int GetTotalParticles() { return m_iTotalParticles; }
	int GetDrawnParticles() { return m_iParticlesDrawn; }
	void IncreaseParticlesDrawn() { m_iParticlesDrawn++; }

	void Shutdown();

	visibleparticles_t *m_pVisibleParticles;
};
