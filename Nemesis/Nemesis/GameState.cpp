// GameState.cpp

#include "stdafx.h"
#include "GameState.h"
#include "WindowManager.h"
#include "Input.h"

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

	if (Input::IsDown(sf::Keyboard::Escape))
		return false;

	if (Input::Close())
		return false;

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
