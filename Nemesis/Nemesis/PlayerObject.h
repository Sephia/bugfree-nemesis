// PlayerObject.h

#pragma once

#include "GameObject.h"

class Input;

class PlayerObject : public GameObject {
public:
	PlayerObject(Position _pos);

	void Init();

	bool Update();
	void Draw();

	void SetTargetPosition(Position _pos);
	bool IsMoving();

	bool IsAt(TileGrid::Tile _tile);
	const std::string GetType();
	bool IsType(const std::string& _type);

	void CleanUp();

private:
	void UpdateViewPosition();
	void Move();
	void CheckInput();

private:
	Input* m_input;

	Position m_targetPosition;
	bool m_moving;
	float m_movementSpeed;
};
