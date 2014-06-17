// AnimationManager.h

#pragma once

class Animation;

class AnimationManager {
public:
	void Init(const std::string& _pathAnimationSet);

	void Update();
	bool PlayAnimation(const std::string& _animationName);	// Returns false if that animation does not exist
	void DrawAnimation();

	void CleanUp();

private:
	Animation* m_currentAnimation;
	std::map<std::string, Animation*> m_animations;
};

