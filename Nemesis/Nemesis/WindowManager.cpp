// WindowManager.cpp

#include "stdafx.h"
#include "WindowManager.h"

sf::RenderWindow *WindowManager::ms_window = nullptr;

void WindowManager::Init() {
	ms_window = new sf::RenderWindow(sf::VideoMode(1600, 900), "Nemesis");
}

bool WindowManager::PollEvents(sf::Event* event) {
	return ms_window->pollEvent(*event);
}

void WindowManager::Draw(sf::Sprite* sprite) {
	ms_window->draw(*sprite);
}

void WindowManager::Display() {
	
	ms_window->display();

	ms_window->clear();
}

void WindowManager::CleanUp() {
	if (ms_window != nullptr) {
		ms_window->close();
		delete ms_window;
		ms_window = nullptr;
	}
}