// TileGrid.cpp

#include "stdafx.h"
#include "TileGrid.h"
#include "TileWall.h"
#include "TileFloor.h" 

TileGrid::TileGrid() {

}

TileGrid::~TileGrid() {

}

void TileGrid::Init() {
	m_tiles.resize(WORLDSIZE);
	for (unsigned int y = 0; y < m_tiles.size(); y++) {
		m_tiles.at(y).resize(WORLDSIZE);
		for (unsigned int x = 0; x < m_tiles.at(y).size(); x++) {
			m_tiles.at(y).at(x) = new TileFloor(Position(x * TILESIZE, y * TILESIZE));
		}
	}
}

bool TileGrid::IsWalkable(Position pos) {
	return m_tiles.at(pos.m_y / TILESIZE).at(pos.m_x / TILESIZE)->IsWalkable();
}

std::string TileGrid::IsType(Position pos) {
	return m_tiles.at(pos.m_y / TILESIZE).at(pos.m_x / TILESIZE)->IsType();
}

void TileGrid::Update() {
	for (unsigned int y = 0; y < m_tiles.size(); y++) {
		for (unsigned int x = 0; x < m_tiles.at(y).size(); x++) {
			m_tiles.at(y).at(x)->Update();
		}
	}
}

void TileGrid::Draw() {
	for (unsigned int y = 0; y < m_tiles.size(); y++) {
		for (unsigned int x = 0; x < m_tiles.at(y).size(); x++) {
			m_tiles.at(y).at(x)->Draw();
		}
	}
}