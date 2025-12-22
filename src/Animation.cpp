#include "Animation.h"

Animation::Animation() {
	startTime = std::chrono::steady_clock::now();
}

void Animation::applyToSprite(sf::Sprite& s)
{
	int entitySize = 30;
	s.setTextureRect(sf::IntRect({entitySize * currentFrame, 0}, {entitySize, entitySize}));
}

bool Animation::update() {
	if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTime) >= holdTime)
	{
		if (currentFrame >= frames - 1)
			currentFrame = -1;
		++currentFrame;

		startTime = std::chrono::steady_clock::now();
		return true;
	}
	return false;
}

void Animation::startMeasureTime(int howLong_ms)
{
	startTime = std::chrono::steady_clock::now();
	std::chrono::milliseconds tmp(howLong_ms);
	holdTime = tmp;
}

bool Animation::checkIfTimePassed()
{
	if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTime) >= holdTime)
		return true;
	return false;
}