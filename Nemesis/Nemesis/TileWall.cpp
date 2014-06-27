// TileWall.cpp

#include "stdafx.h"
#include "TileWall.h"
#include "WindowManager.h"
#include "SpriteManager.h"

TileWall::TileWall() {
	m_windowManager = WindowManager::GetInstance();

	m_walkable = false;
	m_type = "wall";

	m_spriteManager = SpriteManager::GetInstance();
	m_sprite = m_spriteManager->GetSprite("Tiles.png", 64, 0, 64, 64);
}

TileWall::TileWall(Position pos) {
	m_windowManager = WindowManager::GetInstance();

	m_walkable = false;
	m_type = "wall";

	m_spriteManager = SpriteManager::GetInstance();
	m_sprite = m_spriteManager->GetSprite("Tiles.png", 64, 0, 64, 64);
	m_sprite->setPosition(sf::Vector2f(pos.m_x, pos.m_y));
}

TileWall::~TileWall() {
	if (m_sprite != nullptr) {
		delete m_sprite;
		m_sprite = nullptr;
	}
}

bool TileWall::IsWalkable() {
	return m_walkable;
}

std::string TileWall::IsType() {
	return m_type;
}

void TileWall::Update() {

}

void TileWall::Draw() {
	m_windowManager->Draw(m_sprite);
}

void TileWall::CleanUp() {
	if (m_sprite != nullptr) {
		delete m_sprite;
		m_sprite = nullptr;
	}

	m_windowManager = nullptr;
	m_spriteManager = nullptr;
}