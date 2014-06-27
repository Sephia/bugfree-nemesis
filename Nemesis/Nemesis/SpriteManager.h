// SpriteManager.h

#pragma once

class SpriteManager {
public:
	~SpriteManager();
	static SpriteManager* GetInstance();
	static void RemoveInstance();

	void Init(std::string _path);

	sf::Sprite* GetSprite(const std::string& _fileName, int _locX = 0, int _locY = 0, int _sizeX = 0, int _sizeY = 0);

	void CleanUp();

private:
	SpriteManager() {};
	void LoadImage(const std::string& _fileName);

private:
	static bool m_instanceFlag;
	static SpriteManager* m_single;

	std::string m_directory;
	std::map<std::string, sf::Texture*> m_sprites;
};
