// TileFloor.h

#pragma once

#include "TileBase.h"

class TileFloor : public TileBase {
public:
	TileFloor();
	TileFloor(Position pos);
	~TileFloor();

	bool IsWalkable();
	std::string IsType();
	void Update();
	void Draw();
};

