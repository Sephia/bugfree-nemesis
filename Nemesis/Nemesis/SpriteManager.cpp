// SpriteManager.cpp

#include "stdafx.h"
#include "SpriteManager.h"

bool SpriteManager::m_instanceFlag = false;
SpriteManager* SpriteManager::m_single = nullptr;

SpriteManager::~SpriteManager() {
	m_instanceFlag = false;
}

SpriteManager* SpriteManager::GetInstance() {
	if (!m_instanceFlag) {
		m_single = new SpriteManager();
		m_instanceFlag = true;
	}

	return m_single;
}

void SpriteManager::RemoveInstance() {
	delete m_single;
	m_single = nullptr;
}

void SpriteManager::Init(std::string _path) {
	m_directory = _path;
}

sf::Sprite* SpriteManager::GetSprite(const std::string& _fileName, int _locX, int _locY, int _sizeX, int _sizeY) {
	auto it = m_sprites.find(_fileName);

	if (it != m_sprites.end()) {
		sf::Sprite* sprite = new sf::Sprite(*it->second, sf::IntRect(_locX, _locY, _sizeX, _sizeY));
		sprite->setOrigin(sf::Vector2f(_sizeX / 2.0f, _sizeY / 2.0f));
		return sprite;
	}

	LoadImage(_fileName);

	it = m_sprites.find(_fileName);

	if (it != m_sprites.end()) {
		sf::Sprite* sprite = new sf::Sprite(*it->second, sf::IntRect(_locX, _locY, _sizeX, _sizeY));
		sprite->setOrigin(sf::Vector2f(_sizeX / 2.0f, _sizeY / 2.0f));
		return sprite;
	}

	sf::Sprite* sprite = nullptr;
	std::cout << "Could not load sprite " + _fileName + ". Path is: " + m_directory + _fileName << std::endl;
	return sprite;
}

void SpriteManager::LoadImage(const std::string& _fileName) {
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(m_directory + _fileName);
	m_sprites[_fileName] = texture;
}

void SpriteManager::CleanUp() {
	for (auto it = m_sprites.begin(); it != m_sprites.end(); it++) {
		if (it->second != nullptr) {
			delete it->second;
			it->second = nullptr;
		}
	}
	m_sprites.clear();
}