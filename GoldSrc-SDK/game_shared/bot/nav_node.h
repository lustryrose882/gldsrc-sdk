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

class CNavNode
{
public:
	// get navigation node connected in given direction, or NULL if cant go that way
	CNavNode *GetConnectedNode(NavDirType dir) const;
	const Vector *GetPosition() const;
	const Vector *GetNormal() const { return &m_normal; }
	unsigned int GetID() const { return m_id; }

	CNavNode *GetNext() { return m_next; }

	// create a connection FROM this node TO the given node, in the given direction
	CNavNode *GetParent() const;

	void MarkAsVisited(NavDirType dir);				// mark the given direction as having been visited
	BOOL HasVisited(NavDirType dir);				// return TRUE if the given direction has already been searched

	void Cover() { m_isCovered = true; }			// TODO: Should pass in area that is covering
	BOOL IsCovered() const { return m_isCovered; }	// return true if this node has been covered by an area

	void AssignArea(CNavArea *area);		// assign the given area to this node
	CNavArea *GetArea() const;				// return associated area

	void SetAttributes(unsigned char bits) { m_attributeFlags = bits; }
	unsigned char GetAttributes() const { return m_attributeFlags; }

public:
	friend void DestroyNavigationMap();

	Vector m_pos;						// position of this node in the world
	Vector m_normal;					// surface normal at this location
	CNavNode *m_to[NUM_DIRECTIONS];		// links to north, south, east, and west. NULL if no link
	unsigned int m_id;					// unique ID of this node
	unsigned char m_attributeFlags;		// set of attribute bit flags (see NavAttributeType)

	CNavNode *m_next;					// next link in master list

	// below are only needed when generating
	// flags for automatic node generation. If direction bit is clear, that direction hasn't been explored yet.
	unsigned char m_visited;
	CNavNode *m_parent;			// the node prior to this in the search, which we pop back to when this node's search is done (a stack)
	BOOL m_isCovered;			// true when this node is "covered" by a CNavArea
	CNavArea *m_area;			// the area this node is contained within
};

inline CNavNode *CNavNode::GetConnectedNode(NavDirType dir) const
{
	return m_to[dir];
}

inline const Vector *CNavNode::GetPosition() const
{
	return &m_pos;
}

inline CNavNode *CNavNode::GetParent() const
{
	return m_parent;
}

inline void CNavNode::MarkAsVisited(NavDirType dir)
{
	m_visited |= (1 << dir);
}

inline BOOL CNavNode::HasVisited(NavDirType dir)
{
	if (m_visited & (1 << dir))
		return true;

	return false;
}

inline void CNavNode::AssignArea(CNavArea *area)
{
	m_area = area;
}

inline CNavArea *CNavNode::GetArea() const
{
	return m_area;
}
