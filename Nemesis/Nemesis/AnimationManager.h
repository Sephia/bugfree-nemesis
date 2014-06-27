// AnimationManager.h

#pragma once

#include "Position.h"

class Animation;
class WindowManager;

class AnimationManager {
public:
	void Init(const std::string& _pathAnimationSet);

	void Update();
	void Update(Position _position);
	bool PlayAnimation(const std::string& _animationName);	// Returns false if that animation does not exist
	void DrawAnimation();

	void CleanUp();

private:
	WindowManager* m_windowManager;

	Animation* m_currentAnimation;
	std::map<std::string, Animation*> m_animations;
};

