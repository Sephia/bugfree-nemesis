// TileFloor.cpp

#include "stdafx.h"
#include "TileFloor.h"
#include "SpriteManager.h"
#include "WindowManager.h"

TileFloor::TileFloor() {
	m_walkable = true;
	m_type = "floor";

	m_spriteManager = SpriteManager::GetInstance();
	m_sprite = m_spriteManager->GetSprite("Tiles.png", 0, 0, 64, 64);
}

TileFloor::TileFloor(Position pos) {
	m_walkable = false;
	m_type = "floor";

	m_windowManager = WindowManager::GetInstance();

	m_spriteManager = SpriteManager::GetInstance();
	m_sprite = m_spriteManager->GetSprite("Tiles.png", 0, 0, 64, 64);
	m_sprite->setPosition(sf::Vector2f((float)pos.m_x, (float)pos.m_y));
}

TileFloor::~TileFloor() {
	if (m_sprite != nullptr) {
		delete m_sprite;
		m_sprite = nullptr;
	}
}

bool TileFloor::IsWalkable() {
	return m_walkable;
}

std::string TileFloor::IsType() {
	return m_type;
}

void TileFloor::Update() {

}

void TileFloor::Draw() {
	m_windowManager->Draw(m_sprite);
}

void TileFloor::CleanUp() {
	if (m_sprite != nullptr) {
		delete m_sprite;
		m_sprite = nullptr;
	}

	m_windowManager = nullptr;
	m_spriteManager = nullptr;
}