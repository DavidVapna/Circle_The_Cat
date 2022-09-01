#pragma once

#include <SFML\Graphics.hpp>
#include "Macros.h"


class Animation
{
public:
	Animation(const sf::Texture& image, const V2U& imageCount, const float& switchTime);
	~Animation();
	void update(float deltaTime, bool faceRight);

private:
	Animation() = default;
	Animation(const Animation&) = default;
	Animation& operator=(const Animation&) = default;

public:
	sf::IntRect uvRect;

private:
	V2U m_imageCount;
	V2U m_currImage;

	float m_totalTime;
	float m_switchTime;
};