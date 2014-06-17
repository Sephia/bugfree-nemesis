// AnimationManager.cpp

#include "stdafx.h"
#include "AnimationManager.h"
#include "Animation.h"
#include "WindowManager.h"

void AnimationManager::Init(const std::string& _pathAnimationSet) {
	std::ifstream fstream;
	fstream.open(_pathAnimationSet);
	if (!fstream.good()) {
		std::cout << "Can not find AnimationSet " + _pathAnimationSet << std::endl;
		return;
	}

	std::string row;
	std::string animationName;
	std::string animationPath;

	Animation* animation = new Animation();
	Animation::Frame frame;

	while (!fstream.eof()) {
		std::getline(fstream, row);
		{
			std::stringstream sstream(row);

			sstream >> animationName;
			sstream >> animationPath;
		}
		while (true) {
			std::getline(fstream, row);
			if (row.length() == 0 || fstream.eof()) {
				animation->Init(animationPath);
				m_animations[animationName] = animation;
				animation = new Animation();
				break;
			}

			std::stringstream sstream(row);

			sstream >> frame.duration;
			sstream >> frame.iRect.left;
			sstream >> frame.iRect.top;
			sstream >> frame.iRect.width;
			sstream >> frame.iRect.height;

			animation->AddFrame(frame);
		}

		
	}

	fstream.close();
}

void AnimationManager::Update() {
	m_currentAnimation->Update();
}

bool AnimationManager::PlayAnimation(const std::string& _animationName) {
	auto it = m_animations.find(_animationName);

	if (it == m_animations.end())
		return false;

	m_currentAnimation = it->second;
	return true;
}

void AnimationManager::DrawAnimation() {
	WindowManager::Draw(m_currentAnimation->GetSprite());
}

void AnimationManager::CleanUp() {
	m_currentAnimation = nullptr;

	for (auto it = m_animations.begin(); it != m_animations.end(); it++) {
		if (it->second != nullptr) {
			delete it->second;
			it->second = nullptr;
		}
	}

	m_animations.clear();
}