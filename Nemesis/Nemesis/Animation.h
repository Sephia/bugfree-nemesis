// Animation.h

#pragma once

#include "stdafx.h"

class Animation {
public:
	struct Frame{
		float duration;
		sf::IntRect iRect;
	};

public:
	Animation();
	~Animation();

	void Update(sf::Vector2f iRect);
	void Update();
	void AddFrame(Frame _frame);
	bool Init(const std::string& _path);	// Returns false if the sprite could not be loaded or there is no frames in m_animation

	sf::Sprite* GetSprite();

private:
	sf::Sprite* m_sprite;
	std::vector<Frame> m_animation;

	int m_currentFrame;
	float m_time;

	Frame* m_frame;
};
