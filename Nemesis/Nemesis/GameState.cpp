// GameState.cpp

#include "stdafx.h"
#include "GameState.h"
#include "WindowManager.h"
#include "Input.h"
#include "TileGrid.h"
#include "GameObjectManager.h"
#include "PlayerObject.h"
#include "SpriteManager.h"

GameState::GameState() {
	m_nextState = NONE;
	
	m_input = nullptr;
	m_spriteManager = nullptr;
}

GameState::~GameState() {

}

void GameState::Init() {
	m_input = Input::GetInstance();

	m_spriteManager = SpriteManager::GetInstance();

	m_tg = TileGrid::GetInstance();
	m_tg->Init();

	m_gom = new GameObjectManager();
	m_gom->AddObject(new PlayerObject(m_tg->GetStartPosition()));
	m_gom->Init();
}

void GameState::Enter() {
	m_nextState = NONE;
}

void GameState::Exit() {

}

int GameState::Update() {
	m_gom->Update();	// Update the gameobjects

	m_tg->Update();		// Update the grid
	
	return true;
}

void GameState::Draw() {
	m_tg->Draw();

	m_gom->Draw();
}

int GameState::UpdateEvents() {

	if (m_input->IsDown(sf::Keyboard::Escape))
		return false;

	if (m_input->Close())
		return false;

	return true;
}

StateName GameState::GetNextState() {
	return m_nextState;
}

bool GameState::IsState(StateName name) {
	return name == GAMESTATE;
}

void GameState::CleanUp() {
	m_tg->CleanUp();
	TileGrid::RemoveInstance();
	m_tg = nullptr;
}
