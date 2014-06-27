#include "stdafx.h"
#include "Engine.h"
#include "StateManager.h"
#include "StartMenuState.h"
#include "GameState.h"
#include "WindowManager.h"
#include "SpriteManager.h"
#include "Input.h"


float Engine::m_deltaTime = 0.0f;
float Engine::m_oldTime = 0.0f;
float Engine::m_newTime = 0.0f;

Engine::Engine() {
	m_windowManager = nullptr;
	m_stateManager = nullptr;
	m_input = nullptr;
	m_spriteManager = nullptr;

	m_running = true;

	srand((unsigned)time(NULL));
}


Engine::~Engine() {

}

void Engine::Init() {
	m_oldTime = (float)clock();

	m_input = Input::GetInstance();
	m_input->Init();

	m_windowManager = WindowManager::GetInstance();
	m_windowManager->Init();

	m_spriteManager = SpriteManager::GetInstance();
	m_spriteManager->Init("../data/sprites/");

	m_stateManager = new StateManager();
	m_stateManager->AddState(new StartMenuState());
	m_stateManager->AddState(new GameState());
	m_stateManager->SetState(GAMESTATE);
}

int Engine::Run() {
	UpdateDeltaTime();
	m_input->Update();

	if (!m_stateManager->UpdateEvents()) {
		m_running = false;
	}
	else if (m_stateManager->Update()) {
		m_stateManager->Draw();
		m_windowManager->Display();
	}
	else {
		if (!m_stateManager->ChangeState()) {
			m_running = false;
		}
	}

	return m_running;
}

void Engine::CleanUp(){
	m_spriteManager->CleanUp();
	SpriteManager::RemoveInstance();
	m_spriteManager = nullptr;

	m_windowManager->CleanUp();
	WindowManager::RemoveInstance();
	m_windowManager = nullptr;

	Input::RemoveInstance();
	m_input = nullptr;

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