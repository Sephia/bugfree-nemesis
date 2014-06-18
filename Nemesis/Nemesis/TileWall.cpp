// TileWall.cpp

#include "stdafx.h"
#include "TileWall.h"
#include "WindowManager.h"
#include "SpriteManager.h"

TileWall::TileWall() {
	m_walkable = false;
	m_type = "wall";

	m_sprite = SpriteManager::GetSprite("Tiles.png", 64, 0, 64, 64);
}

TileWall::TileWall(Position pos) {
	m_walkable = false;
	m_type = "wall";
	m_sprite = SpriteManager::GetSprite("Tiles.png", 64, 0, 64, 64);
	m_sprite->setPosition(sf::Vector2f((float)pos.m_x, (float)pos.m_y));
}

TileWall::~TileWall() {
	
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
	WindowManager::Draw(m_sprite);
}
