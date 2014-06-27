// WindowManager.h

#pragma once

#include "Position.h"

namespace sf {
	class RenderWindow;
	class Event;
	class Sprite;
}

class WindowManager {
public:
	~WindowManager();
	static WindowManager* GetInstance();
	static void RemoveInstance();
	
	void Init();
	void CleanUp();

	bool PollEvents(sf::Event* event);
	void Draw(sf::Sprite* sprite);
	void UpdateViewPosition(Position pos);

	void Display();

private:
	WindowManager(){};

private:
	static bool m_instanceFlag;
	static WindowManager* m_single;

	sf::RenderWindow *m_window;
	sf::View *m_view;
};
