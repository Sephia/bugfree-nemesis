// TileWall.h

#pragma once

#include "TileBase.h"

class TileWall : public TileBase {
public:
	TileWall();
	TileWall(Position pos);
	~TileWall();

	bool IsWalkable();
	std::string IsType();
	void Update();
	void Draw();
	void CleanUp();
};

