// StartMenuState.cpp

#include "stdafx.h"
#include "StartMenuState.h"
#include "WindowManager.h"
#include "Engine.h"
#include "Position.h"
#include "Input.h"

StartMenuState::StartMenuState() {
	m_nextState = "";
}

StartMenuState::~StartMenuState() {

}

void StartMenuState::Init() {
	m_viewPosition.m_x = 800;
	m_viewPosition.m_y = 450;
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
	WindowManager::UpdateViewPosition(m_viewPosition);
	// Update things here
	return true;
}

int StartMenuState::UpdateEvents() {

	if (Input::IsDown(sf::Keyboard::Escape))
		return false;

	if (Input::Close())
		return false;

	if (Input::IsDown(sf::Keyboard::A))
		m_viewPosition.m_x -= 1.0f * 10;
	if (Input::IsDown(sf::Keyboard::D))
		m_viewPosition.m_x += 1.0f * 10;
	if (Input::IsDown(sf::Keyboard::W))
		m_viewPosition.m_y -= 1.0f * 10;
	if (Input::IsDown(sf::Keyboard::S))
		m_viewPosition.m_y += 1.0f * 10;

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
