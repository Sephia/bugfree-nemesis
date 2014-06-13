// State.h

#pragma once

#include "stdafx.h"
#include "WindowManager.h"

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

	virtual std::string GetNextState() = 0;
	virtual bool IsState(std::string name) = 0;

	virtual void CleanUp() = 0;

protected:
	std::string m_nextState;
};

