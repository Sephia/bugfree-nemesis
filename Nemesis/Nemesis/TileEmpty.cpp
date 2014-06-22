// TileEmpty.cpp

#include "stdafx.h"
#include "TileEmpty.h"
#include "SpriteManager.h"
#include "WindowManager.h"

TileEmpty::TileEmpty() {
	m_walkable = true;
	m_type = "empty";

	m_sprite = SpriteManager::GetSprite("Tiles.png", 128, 0, 64, 64);
}

TileEmpty::TileEmpty(Position pos) {
	m_walkable = false;
	m_type = "empty";
	m_sprite = SpriteManager::GetSprite("Tiles.png", 128, 0, 64, 64);
	m_sprite->setPosition(sf::Vector2f((float)pos.m_x, (float)pos.m_y));
}

TileEmpty::~TileEmpty() {
	if (m_sprite != nullptr) {
		delete m_sprite;
		m_sprite = nullptr;
	}
}

bool TileEmpty::IsWalkable() {
	return m_walkable;
}

std::string TileEmpty::IsType() {
	return m_type;
}

void TileEmpty::Update() {

}

void TileEmpty::Draw() {
	WindowManager::Draw(m_sprite);
}
