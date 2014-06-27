// StateManager.h

#pragma once

#include "stdafx.h"

class State;

class StateManager {
public:
	StateManager();
	~StateManager();

	void AddState(State* state);
	void SetState(StateName name);
	bool ChangeState(); // false if can not find next state. Quits.

	int UpdateEvents();	// quit if false
	int Update();	// quit if false
	void Draw();

	void CleanUp();

private:
	State* m_currentState;
	std::vector<State*> m_states;
};