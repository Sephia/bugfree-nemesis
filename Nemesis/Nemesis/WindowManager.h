// WindowManager.h

#pragma once

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

	static void Display();

private:
	static sf::RenderWindow *ms_window;
};
