// TileBase.h

#pragma once

#include "Position.h"

namespace sf {
	class Sprite;
}
class SpriteManager;
class WindowManager;

class TileBase {
public:
	TileBase() {}
	TileBase(Position pos) {};
	virtual ~TileBase() {};

	virtual bool IsWalkable() = 0;
	virtual std::string IsType() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void CleanUp() = 0;

protected:
	bool m_walkable;
	std::string m_type;

	sf::Sprite* m_sprite;
	SpriteManager* m_spriteManager;
	WindowManager* m_windowManager;
};