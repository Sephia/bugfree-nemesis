// Animation.cpp

#include "stdafx.h"
#include "Animation.h"
#include "SpriteManager.h"
#include "Engine.h"

Animation::Animation() {
	m_time = 0.0f;
	m_currentFrame = 0;
}

Animation::~Animation() {
	if (m_sprite != nullptr) {
		delete m_sprite;
		m_sprite = nullptr;
	}

	if (m_frame != nullptr) {
		m_frame = nullptr;
	}
	m_animation.clear();
}

void Animation::AddFrame(Frame _frame) {
	m_animation.push_back(_frame);
}

void Animation::Update(Position _position) {
	m_time += Engine::GetDeltaTime();

	if (m_time >= m_animation[m_currentFrame].duration) {
		m_time = 0.0f;
		m_currentFrame = ++m_currentFrame % m_animation.size();
		m_frame = &m_animation[m_currentFrame];
		m_sprite->setTextureRect(m_frame->iRect);
	}
	m_sprite->setPosition(sf::Vector2f(_position.m_x, _position.m_y));
}

void Animation::Update() {
	m_time += Engine::GetDeltaTime();

	if (m_time >= m_animation[m_currentFrame].duration) {
		m_time = 0.0f;
		m_currentFrame = ++m_currentFrame % m_animation.size();
		m_frame = &m_animation[m_currentFrame];
		m_sprite->setTextureRect(m_frame->iRect);
	}
}

bool Animation::Init(const std::string& _path) {
	m_spriteManager = SpriteManager::GetInstance();
	m_sprite = m_spriteManager->GetSprite(_path);

	std::cout << m_sprite->getOrigin().x << " " << m_sprite->getOrigin().y << std::endl;

	if (m_sprite == nullptr)
		return false;

	if (m_animation.size() > 0) {
		m_frame = &m_animation[0];
		m_sprite->setTextureRect(m_frame->iRect);
		m_sprite->setOrigin(m_frame->iRect.width / 2.0f, m_frame->iRect.height / 2.0f);
		return true;
	}

	return false;
}

sf::Sprite* Animation::GetSprite() {
	return m_sprite;
}