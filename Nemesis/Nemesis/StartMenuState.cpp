// StartMenuState.cpp

#include "stdafx.h"
#include "StartMenuState.h"
#include "WindowManager.h"

StartMenuState::StartMenuState() {
	m_nextState = "";
}

StartMenuState::~StartMenuState() {

}

void StartMenuState::Init() {

}

void StartMenuState::Enter() {
	m_nextState = "";
}

void StartMenuState::Exit() {
	
}

void StartMenuState::Draw() {
	// Draw things here
}

int StartMenuState::Update() {
	// Update things here
	return true;
}

int StartMenuState::UpdateEvents() {
	sf::Event event;
	while (WindowManager::PollEvents(&event)) {
		switch (event.type) {
		case sf::Event::Closed:
			return false;
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				return false;

		default:
			break;


		}
	}
	return true;
}

std::string StartMenuState::GetNextState() {
	return m_nextState;
}

bool StartMenuState::IsState(std::string name) {
	return name == "StartMenuState";
}

void StartMenuState::CleanUp() {
	
}
