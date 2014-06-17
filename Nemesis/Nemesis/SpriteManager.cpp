// SpriteManager.cpp

#include "stdafx.h"
#include "SpriteManager.h"

std::string SpriteManager::m_directory;
std::map<std::string, sf::Texture*> SpriteManager::m_sprites;

void SpriteManager::Init(std::string _path) {
	m_directory = _path;
}

sf::Sprite* SpriteManager::GetSprite(const std::string& _fileName, int _locX, int _locY, int _sizeX, int _sizeY) {
	auto it = m_sprites.find(_fileName);

	if (it != m_sprites.end()) {
		return new sf::Sprite(*it->second, sf::IntRect(_locX, _locY, _sizeX, _sizeY));
	}

	LoadImage(_fileName);

	it = m_sprites.find(_fileName);

	if (it != m_sprites.end()) {
		return new sf::Sprite(*it->second, sf::IntRect(_locX, _locY, _sizeX, _sizeY));
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