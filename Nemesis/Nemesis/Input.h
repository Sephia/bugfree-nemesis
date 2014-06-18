// Input.h

#pragma once

#include "stdafx.h"

class Input {
public:
	static void Init();

	static void Update();

	static bool IsDownOnce(sf::Keyboard::Key code);
	static bool IsDownOnce(sf::Mouse::Button code);

	static bool IsDown(sf::Keyboard::Key code);
	static bool IsDown(sf::Mouse::Button code);

	static bool Close();

private:
	static void PostUpdate();
private:
	static std::vector<bool> m_keyboard;
	static std::vector<bool> m_keyboardOld;
	static std::vector<bool> m_mouse;
	static std::vector<bool> m_mouseOld;
	
	static bool m_closeEvent;
};

