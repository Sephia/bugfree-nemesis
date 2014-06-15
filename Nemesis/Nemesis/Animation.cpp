// Animation.cpp

#include "stdafx.h"
#include "Animation.h"

Animation::Animation(sf::Sprite* p_sprite) {
	mp_sprite = p_sprite;
	m_time = 0.0f;
	m_currentFrame = 0;
}


Animation::~Animation() {
	if (mp_sprite != nullptr) {
		delete mp_sprite;
		mp_sprite = nullptr;
	}

	if (mp_frame != nullptr) {
		mp_frame = nullptr;
	}
	m_animation.clear();
}

void Animation::AddFrame(Frame& r_frame) {
	m_animation.push_back(r_frame);
}

void Animation::Update(sf::Vector2f position) {
	// TODO: Create global static class for deltatime
	//m_time += Settings::ms_deltatime;
	if (m_time >= m_animation[m_currentFrame].duration) {
		m_time = 0.0f;
		m_currentFrame = ++m_currentFrame % m_animation.size();
		mp_frame = &m_animation[m_currentFrame];
		mp_sprite->setTextureRect(mp_frame->iRect);
	}
	mp_sprite->setPosition(position);
}

void Animation::Update() {
	// TODO: Create global static class for deltatime
	//m_time += Settings::ms_deltatime;
	if (m_time >= m_animation[m_currentFrame].duration) {
		m_time = 0.0f;
		m_currentFrame = ++m_currentFrame % m_animation.size();
		mp_frame = &m_animation[m_currentFrame];
		mp_sprite->setTextureRect(mp_frame->iRect);
	}
}

bool Animation::Init() {
	if (m_animation.size() > 0) {
		mp_frame = &m_animation[0];
		mp_sprite->setTextureRect(mp_frame->iRect);
		return true;
	}

	return false;
}

sf::Sprite* Animation::getSprite() {
	return mp_sprite;
}