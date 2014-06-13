// Engine.h

#pragma once

class StateManager;

class Engine {
public:
	Engine();
	~Engine();

	void Init();

	int Run();
	
	void CleanUp();

private:
	StateManager *m_stateManager;
	bool running;
};

