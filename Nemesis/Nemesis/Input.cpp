// Input.cpp

#include "stdafx.h"
#include "Input.h"
#include "WindowManager.h"

Input* Input::m_single = nullptr;
bool Input::m_instanceFlag = false;

Input::~Input() {
	m_instanceFlag = false;
}

Input* Input::GetInstance() {
	if (!m_instanceFlag) {
		m_single = new Input();
		m_instanceFlag = true;
	}

	return m_single;
}

void Input::RemoveInstance() {
	delete m_single;
	m_single = nullptr;
}

void Input::Init() {
	m_windowManager = WindowManager::GetInstance();

	m_keyboard.resize(sf::Keyboard::KeyCount, false);
	m_keyboardOld.resize(sf::Keyboard::KeyCount, false);
	
	m_mouse.resize(sf::Mouse::ButtonCount, false);
	m_mouseOld.resize(sf::Mouse::ButtonCount, false);

	m_closeEvent = false;
}

void Input::Update() {
	PostUpdate();

	sf::Event event;
	while (m_windowManager->PollEvents(&event)) {
		if (event.type == sf::Event::KeyPressed) {
			m_keyboard.at(event.key.code) = true;
		}
		else if (event.type == sf::Event::KeyReleased) {
			m_keyboard.at(event.key.code) = false;
		}
		else if (event.type == sf::Event::MouseButtonPressed) {
			m_mouse.at(event.mouseButton.button) = true;
		}
		else if (event.type == sf::Event::MouseButtonReleased) {
			m_mouse.at(event.mouseButton.button) = false;
		}
		else if (event.type == sf::Event::Closed) {
			m_closeEvent = true;
		}
	}
}

void Input::PostUpdate() {
	for (unsigned int i = 0; i < m_keyboard.size(); i++) {
		m_keyboardOld.at(i) = m_keyboard.at(i);
	}

	for (unsigned int i = 0; i < m_mouse.size(); i++) {
		m_mouseOld.at(i) = m_mouse.at(i);
	}
}

bool Input::IsDownOnce(sf::Keyboard::Key code) {
	return m_keyboard.at(code) && !m_keyboardOld.at(code);
}

bool Input::IsDownOnce(sf::Mouse::Button code) {
	return m_mouse.at(code) && !m_keyboardOld.at(code);
}

bool Input::IsDown(sf::Keyboard::Key code) {
	return m_keyboard.at(code);
}

bool Input::IsDown(sf::Mouse::Button code) {
	return m_mouse.at(code);
}

bool Input::Close() {
	return m_closeEvent;
}