// State.h

#pragma once

#include "stdafx.h"

class SpriteManager;
class WindowManager;
class Input;

class State {
public:

	State() {};
	virtual ~State() {};

	virtual void Init() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;

	virtual void Draw() = 0;
	virtual int Update() = 0;
	virtual int UpdateEvents() = 0;

	virtual StateName GetNextState() = 0;
	virtual bool IsState(StateName name) = 0;

	virtual void CleanUp() = 0;

protected:
	Input* m_input;
	WindowManager* m_windowManager;
	SpriteManager* m_spriteManager;

	StateName m_nextState;
};

