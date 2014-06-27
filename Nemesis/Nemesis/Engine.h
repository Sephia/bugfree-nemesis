// Engine.h

#pragma once

class StateManager;
class TileGrid;
class GameObjectManager;
class SpriteManager;
class WindowManager;
class Input;

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
	Input* m_input;
	WindowManager* m_windowManager;
	SpriteManager* m_spriteManager;
	StateManager* m_stateManager;

	bool m_running;

	static float m_deltaTime;
	static float m_oldTime;
	static float m_newTime;
};

