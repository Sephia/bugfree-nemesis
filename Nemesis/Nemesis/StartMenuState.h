// StartMenuState.h

#pragma once

#include "State.h"

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

	std::string GetNextState();
	bool IsState(std::string name);

	void CleanUp();

private:

};