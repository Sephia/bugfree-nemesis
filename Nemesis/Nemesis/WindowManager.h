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
	
	static void Init();
	static void CleanUp();

	static bool PollEvents(sf::Event* event);
	static void Draw(sf::Sprite* sprite);
	static void UpdateViewPosition(Position pos);

	static void Display();

private:
	static sf::RenderWindow *m_window;
	static sf::View *m_view;
};
