// TileEmpty.h

#pragma once

#include "TileBase.h"

class TileEmpty : public TileBase {
public:
	TileEmpty();
	TileEmpty(Position pos);
	~TileEmpty();

	bool IsWalkable();
	std::string IsType();
	void Update();
	void Draw();
};

