// AnimationManager.h

#pragma once

class Animation;

class AnimationManager {
public:
	void Init(std::string animationSet);

	void Update();
	void PlayAnimation(std::string name);

	void CleanUp();

private:
	std::map<std::string, Animation*> m_animations;
};

