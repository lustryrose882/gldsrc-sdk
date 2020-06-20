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

// Encapsulation of a finite-state-machine state
template <typename T>
class SimpleState
{
public:
	SimpleState() { m_parent = NULL; }

	virtual ~SimpleState() {};
	virtual void OnEnter(T userData) {};		// when state is entered
	virtual void OnUpdate(T userData) {};		// state behavior
	virtual void OnExit(T userData) {};			// when state exited
	virtual const char *GetName() const = 0;	// return state name

	void SetParent(SimpleState<T> *parent)
	{
		m_parent = parent;
	}
	SimpleState<T> *GetParent() const
	{
		return m_parent;
	}

private:
	// the parent state that contains this state
	SimpleState<T> *m_parent;
};

// Encapsulation of a finite state machine
template <typename T, typename S>
class SimpleStateMachine
{
public:
	SimpleStateMachine()
	{
		m_state = NULL;
	}
	void Reset(T userData)
	{
		m_userData = userData;
		m_state = NULL;
	}
	// change behavior state - WARNING: not re-entrant. Do not SetState() from within OnEnter() or OnExit()
	void SetState(S *newState)
	{
		if (m_state)
			m_state->OnExit(m_userData);

		newState->OnEnter(m_userData);

		m_state = newState;
		m_stateTimer.Start();
	}
	// how long have we been in the current state
	float GetStateDuration() const
	{
		return m_stateTimer.GetElapsedTime();
	}
	// return true if given state is current state of machine
	bool IsState(const S *state) const
	{
		return (state == m_state);
	}
	// execute current state of machine
	void Update()
	{
		if (m_state)
			m_state->OnUpdate(m_userData);
	}

protected:
	S *m_state;					// current behavior state
	IntervalTimer m_stateTimer;	// how long have we been in the current state
	T m_userData;
};
