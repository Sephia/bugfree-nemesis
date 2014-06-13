#include "stdafx.h"
#include "Engine.h"
#include "StateManager.h"
#include "StartMenuState.h"
#include "GameState.h"
#include "WindowManager.h"

Engine::Engine() {
	m_stateManager = nullptr;
	running = true;
}


Engine::~Engine() {

}

void Engine::Init() {
	WindowManager::Init();

	m_stateManager = new StateManager();
	m_stateManager->AddState(new StartMenuState);
	m_stateManager->AddState(new GameState);
	m_stateManager->SetState("StartMenuState");
}

int Engine::Run() {
	if (!m_stateManager->UpdateEvents()) {
		running = false;
	}
	else if (m_stateManager->Update()) {
		m_stateManager->Draw();
		WindowManager::Display();
	}
	else {
		if (!m_stateManager->ChangeState()) {
			running = false;
		}
	}

	return running;
}

void Engine::CleanUp(){
	WindowManager::CleanUp();

	if (m_stateManager != nullptr) {
		m_stateManager->CleanUp();
		delete m_stateManager;
		m_stateManager = nullptr;
	}
}