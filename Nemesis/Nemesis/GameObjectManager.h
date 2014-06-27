// GameObjectManager.h

#pragma once

#include "TileGrid.h"
#include "stdafx.h"

class GameObject;

class GameObjectManager {
public:
	GameObjectManager();

	void Init();
	void AddObject(GameObject* _obj);

	GameObject* GetObjectAtTile(TileGrid::Tile _tile);

	void Update();
	void Draw();

	void CleanUp();

private:
	std::vector<GameObject*> m_objects;
};
