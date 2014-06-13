// GameState.h

#pragma once

#include "State.h"

class GameState : public State {
public:
	GameState();
	~GameState();

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

