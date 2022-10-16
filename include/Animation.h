//=============================================================================
#pragma once
//=============================================================================
#include "Macros.h"
//=============================================================================
class Animation
{
public:
	Animation(const sf::Texture& image, const sf::Vector2u& imageCount, const float& switchTime);
	~Animation();
	void update(float deltaTime, bool faceRight);

private:
	Animation() = default;
	Animation(const Animation&) = default;
	Animation& operator=(const Animation&) = default;

public:
	sf::IntRect uvRect;

private:
	sf::Vector2u m_imageCount;
	sf::Vector2u m_currImage;

	float m_totalTime;
	float m_switchTime;
};
//=============================================================================