// Engine.h

#pragma once

class StateManager;
class TileGrid;

class Engine {
public:
	Engine();
	~Engine();

	void Init();

	int Run();
	
	void CleanUp();

	static float GetDeltaTime();

private:
	static void UpdateDeltaTime();

private:
	StateManager *m_stateManager;
	bool running;

	static float m_deltaTime;
	static float m_oldTime;
	static float m_newTime;

	TileGrid* tg;
};

