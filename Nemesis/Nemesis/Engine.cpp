#include "stdafx.h"
#include "Engine.h"
#include "StateManager.h"
#include "StartMenuState.h"
#include "GameState.h"
#include "WindowManager.h"
#include "SpriteManager.h"

#include "TileGrid.h"

float Engine::m_deltaTime = 0.0f;
float Engine::m_oldTime = 0.0f;
float Engine::m_newTime = 0.0f;

Engine::Engine() {
	m_stateManager = nullptr;
	running = true;
}


Engine::~Engine() {

}

void Engine::Init() {
	m_oldTime = (float)clock();

	WindowManager::Init();
	SpriteManager::Init("../data/sprites/");

	tg = new TileGrid();
	tg->Init();

	m_stateManager = new StateManager();
	m_stateManager->AddState(new StartMenuState);
	m_stateManager->AddState(new GameState);
	m_stateManager->SetState("StartMenuState");
}

int Engine::Run() {
	UpdateDeltaTime();

	tg->Update();
	tg->Draw();

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

float Engine::GetDeltaTime() {
	return m_deltaTime;
}

void Engine::UpdateDeltaTime() {
	m_oldTime = m_newTime;
	m_newTime = (float)clock();

	m_deltaTime = float(m_newTime - m_oldTime) / CLOCKS_PER_SEC;
	if (m_deltaTime > 0.1f) {
		m_deltaTime = 0.1f;
	}
}