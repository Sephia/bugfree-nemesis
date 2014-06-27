// GameState.h

#pragma once

#include "State.h"

class TileGrid;
class GameObjectManager;

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

	StateName GetNextState();
	bool IsState(StateName name);

	void CleanUp();

private:
	TileGrid* m_tg;
	GameObjectManager* m_gom;
};

