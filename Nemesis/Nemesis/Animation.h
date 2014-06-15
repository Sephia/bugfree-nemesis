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
	Animation(sf::Sprite* p_sprite);
	~Animation();

	void Update(sf::Vector2f iRect);
	void Update();
	void AddFrame(Frame &r_frame);
	bool Init();

	sf::Sprite* getSprite();

private:
	sf::Sprite* mp_sprite;
	std::vector<Frame> m_animation;

	int m_currentFrame;
	float m_time;

	Frame* mp_frame;
};
