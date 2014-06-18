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

	SpawnStartingRoom();
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

void TileGrid::SpawnRectangleRoom(Position midPos, int sizeX, int sizeY) {
	int midX = midPos.m_x;
	int midY = midPos.m_y;

	int y = midY - sizeY / 2;
	int x;

	for (x = midX - sizeX / 2; x < midX + sizeX / 2; x++) {
		if (m_tiles.at(y).at(x) != nullptr) {
			delete m_tiles.at(y).at(x);
			m_tiles.at(y).at(x) = new TileWall(Position(x * TILESIZE, y * TILESIZE));
		}
	}

	int random = rand() % ((sizeY - 2) * 2);
	int counter = 0;

	for (y++; y < midY + sizeY / 2 - 1; y++) {
		for (x = midX - sizeX / 2; x < midX + sizeX / 2; x += sizeX - 1)
		if (m_tiles.at(y).at(x) != nullptr) {
			delete m_tiles.at(y).at(x);
			if (counter == random)
				m_tiles.at(y).at(x) = new TileFloor(Position(x * TILESIZE, y * TILESIZE));
			else
				m_tiles.at(y).at(x) = new TileWall(Position(x * TILESIZE, y * TILESIZE));
			counter++;
		}
	}

	for (x = midX - sizeX / 2; x < midX + sizeX / 2; x++) {
		if (m_tiles.at(y).at(x) != nullptr) {
			delete m_tiles.at(y).at(x);
			m_tiles.at(y).at(x) = new TileWall(Position(x * TILESIZE, y * TILESIZE));
		}
	}

}

void TileGrid::SpawnStartingRoom() {
	int midX = WORLDSIZE / 2;
	int midY = WORLDSIZE / 2;
	SpawnRectangleRoom(Position(midX, midY), 6, 6);
}

