// TileGrid.h

#pragma once

#include "Position.h"

class TileBase;

class TileGrid {
public:
	TileGrid();
	~TileGrid();

	void Init();

	bool IsWalkable(Position pos);
	std::string IsType(Position pos);

	void Update();
	void Draw();

	void SpawnRectangleRoom(Position midPos, int sizeX, int sizeY);
	void SpawnStartingRoom();



private:
	std::vector<std::vector<TileBase*>> m_tiles;

};
