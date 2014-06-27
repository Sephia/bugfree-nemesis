// PlayerObject.cpp

#include "stdafx.h"
#include "PlayerObject.h"
#include "Engine.h"
#include "AnimationManager.h"
#include "WindowManager.h"
#include "Input.h"

PlayerObject::PlayerObject(Position _pos) {
	m_position = _pos;

	m_animManager = nullptr;
	m_input = nullptr;
	m_windowManager = nullptr;
}

void PlayerObject::Init() {
	m_input = Input::GetInstance();

	m_animManager = new AnimationManager();
	m_animManager->Init("../data/animations/player.txt");
	m_animManager->PlayAnimation("Idle");

	m_windowManager = WindowManager::GetInstance();

	m_movementSpeed = 100.0f;
}

bool PlayerObject::Update() {
	
	if (m_moving)
		Move();
	else
		CheckInput();

	m_animManager->Update(m_position);
	UpdateViewPosition();
	
	return false;
}

void PlayerObject::Draw() {
	m_animManager->DrawAnimation();
}

void PlayerObject::SetTargetPosition(Position _pos) {
	m_targetPosition = _pos;
	m_moving = true;
}

bool PlayerObject::IsMoving() {
	return m_moving;
}

bool PlayerObject::IsAt(TileGrid::Tile _tile) {
	TileGrid::Tile atTile;
	atTile.m_x = m_position.m_x / TILESIZE;
	atTile.m_y = m_position.m_y / TILESIZE;
	return (atTile.m_x == _tile.m_x && atTile.m_y == _tile.m_y);
}

const std::string PlayerObject::GetType() {
	return m_type;
}

bool PlayerObject::IsType(const std::string& _type) {
	return _type == m_type;
}

void PlayerObject::CleanUp() {
	if (m_animManager != nullptr) {
		m_animManager->CleanUp();
		delete m_animManager;
		m_animManager = nullptr;
	}

	m_input = nullptr;
	m_windowManager = nullptr;
}

void PlayerObject::UpdateViewPosition() {
	m_windowManager->UpdateViewPosition(m_position);
}

void PlayerObject::Move() {
	if (abs(m_targetPosition.m_x - m_position.m_x) < 3 && abs(m_targetPosition.m_y - m_position.m_y) < 3) {
		m_position = m_targetPosition;
		m_moving = false;
	}
	else {
		Position vector = m_targetPosition - m_position;
		vector.Normalize();

		m_position.m_x = m_position.m_x + vector.m_x * Engine::GetDeltaTime() * m_movementSpeed;
		m_position.m_y = m_position.m_y + vector.m_y * Engine::GetDeltaTime() * m_movementSpeed;
	}
}

void PlayerObject::CheckInput() {
	if (m_input->IsDown(sf::Keyboard::W)) {
		m_targetPosition = m_position;
		m_targetPosition.m_y -= TILESIZE;
		m_moving = true;
	}
	else if (m_input->IsDown(sf::Keyboard::S)) {
		m_targetPosition = m_position;
		m_targetPosition.m_y += TILESIZE;
		m_moving = true;
	}
	else if (m_input->IsDown(sf::Keyboard::A)) {
		m_targetPosition = m_position;
		m_targetPosition.m_x -= TILESIZE;
		m_moving = true;
	}
	else if (m_input->IsDown(sf::Keyboard::D)) {
		m_targetPosition = m_position;
		m_targetPosition.m_x += TILESIZE;
		m_moving = true;
	}
}