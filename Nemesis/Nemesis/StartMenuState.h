// StartMenuState.h

#pragma once

#include "State.h"
#include "Position.h"

namespace sf {
	class View;
}

class StartMenuState : public State {
public:
	StartMenuState();
	~StartMenuState();

	void Init();
	void Enter();
	void Exit();

	void Draw();
	int Update();
	int UpdateEvents();

	StateName GetNextState();
	bool IsState(StateName name);

	void CleanUp();

private:
	Position m_viewPosition;

};