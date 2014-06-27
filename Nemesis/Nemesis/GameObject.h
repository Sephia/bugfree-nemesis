// GameObject.h

#pragma once

#include "Position.h"
#include "stdafx.h"
#include "TileGrid.h"

class AnimationManager;
class WindowManager;

class GameObject {
public:

	virtual ~GameObject() {};

	virtual void Init() = 0;

	virtual	bool Update() = 0;
	virtual void Draw() = 0;

	virtual bool IsMoving() = 0;

	virtual bool IsAt(TileGrid::Tile _tile) = 0;
	virtual const std::string GetType() = 0;
	virtual bool IsType(const std::string& _type) = 0;

	virtual void CleanUp() = 0;

protected:
	Position m_position;
	std::string m_type;

	WindowManager* m_windowManager;
	AnimationManager* m_animManager;
};

