// StartMenuState.cpp

#include "stdafx.h"
#include "StartMenuState.h"
#include "WindowManager.h"
#include "Engine.h"
#include "Position.h"
#include "Input.h"
#include "SpriteManager.h"

StartMenuState::StartMenuState() {
	m_nextState = NONE;
	m_windowManager = nullptr;
	m_spriteManager = nullptr;
	m_input = nullptr;
}

StartMenuState::~StartMenuState() {

}

void StartMenuState::Init() {
	m_windowManager = WindowManager::GetInstance();
	m_spriteManager = SpriteManager::GetInstance();
	m_input = Input::GetInstance();

	m_viewPosition.m_x = 800;
	m_viewPosition.m_y = 450;
}

void StartMenuState::Enter() {
	m_nextState = NONE;

	m_windowManager->UpdateViewPosition(m_viewPosition);
}

void StartMenuState::Exit() {

}

void StartMenuState::Draw() {
	// Draw things here
}

int StartMenuState::Update() {
	m_windowManager->UpdateViewPosition(m_viewPosition);

	return true;
}

int StartMenuState::UpdateEvents() {

	if (m_input->IsDown(sf::Keyboard::Escape))
		return false;

	if (m_input->Close())
		return false;

	return true;
}

StateName StartMenuState::GetNextState() {
	return m_nextState;
}

bool StartMenuState::IsState(StateName name) {
	return name == STARTMENUSTATE;
}

void StartMenuState::CleanUp() {

}
