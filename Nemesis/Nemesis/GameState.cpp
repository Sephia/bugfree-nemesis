// GameState.cpp

#include "stdafx.h"
#include "GameState.h"
#include "WindowManager.h"

GameState::GameState() {
	m_nextState = "";
}

GameState::~GameState() {

}

void GameState::Init() {

}

void GameState::Enter() {
	m_nextState = "";
}

void GameState::Exit() {

}

void GameState::Draw() {
	// Draw things here
}

int GameState::Update() {
	// Update things here
	return true;
}

int GameState::UpdateEvents() {
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

std::string GameState::GetNextState() {
	return m_nextState;
}

bool GameState::IsState(std::string name) {
	return name == "GameState";
}

void GameState::CleanUp() {

}
