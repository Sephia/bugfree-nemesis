// Input.h

#pragma once

#include "stdafx.h"

class WindowManager;

class Input {
public:
	~Input();
	static Input* GetInstance();
	static void RemoveInstance();

	void Init();

	void Update();

	bool IsDownOnce(sf::Keyboard::Key code);
	bool IsDownOnce(sf::Mouse::Button code);

	bool IsDown(sf::Keyboard::Key code);
	bool IsDown(sf::Mouse::Button code);

	bool Close();

private:
	Input(){};
	void PostUpdate();

private:
	static Input* m_single;
	static bool m_instanceFlag;

	std::vector<bool> m_keyboard;
	std::vector<bool> m_keyboardOld;
	std::vector<bool> m_mouse;
	std::vector<bool> m_mouseOld;
	
	bool m_closeEvent;

	WindowManager* m_windowManager;
};

