// Animation.h

#pragma once

#include "stdafx.h"
#include "Position.h"

class SpriteManager;

class Animation {
public:
	struct Frame{
		float duration;
		sf::IntRect iRect;
	};

public:
	Animation();
	~Animation();

	void Update(Position _position);
	void Update();
	void AddFrame(Frame _frame);
	bool Init(const std::string& _path);	// Returns false if the sprite could not be loaded or there is no frames in m_animation

	sf::Sprite* GetSprite();

private:
	SpriteManager* m_spriteManager;
	sf::Sprite* m_sprite;
	std::vector<Frame> m_animation;

	int m_currentFrame;
	float m_time;

	Frame* m_frame;
};
