// GameObjectManager.cpp

#include "stdafx.h"
#include "GameObjectManager.h"
#include "PlayerObject.h"

GameObjectManager::GameObjectManager() {

}

void GameObjectManager::Init() {
	for (auto it = m_objects.begin(); it != m_objects.end(); it++) {
		(*it)->Init();
	}
}

void GameObjectManager::AddObject(GameObject* _obj) {
	m_objects.push_back(_obj);
}

GameObject* GameObjectManager::GetObjectAtTile(TileGrid::Tile _tile) {
	for (auto it = m_objects.begin(); it != m_objects.end(); it++) {
		if ((*it)->IsAt(_tile))
			return *it;
	}

	return nullptr;
}

void GameObjectManager::Update() {
	for (auto it = m_objects.begin(); it != m_objects.end(); it++) {
		if ((*it)->Update()) {
			(*it)->CleanUp();
			delete *it;
			m_objects.erase(it);
		}
	}
}

void GameObjectManager::Draw() {
	for (auto it = m_objects.begin(); it != m_objects.end(); it++) {
		(*it)->Draw();
	}
}

void GameObjectManager::CleanUp() {
	for (auto it = m_objects.begin(); it != m_objects.end(); it++) {
		(*it)->CleanUp();
	}
}