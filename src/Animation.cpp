//=============================================================================
#include "Animation.h"
//=============================================================================
//
Animation::Animation(const sf::Texture& image, const sf::Vector2u& imageCount, const float& switchTime)
{
	m_imageCount = imageCount;
	m_switchTime = switchTime;
	m_totalTime = 0.0f;
	m_currImage.x = 0;
	m_currImage.y = 0;

	uvRect.width = image.getSize().x / float(m_imageCount.x);
	uvRect.height = image.getSize().y / float(m_imageCount.y);
}
//=============================================================================
//
Animation::~Animation()
{
}
//=============================================================================
//
void Animation::update(float deltaTime, bool faceRight)
{
	m_totalTime += deltaTime;

	if (m_totalTime >= m_switchTime)
	{
		m_totalTime -= m_switchTime;
		m_currImage.x++;

		if (m_currImage.x >= m_imageCount.x)
		{
			m_currImage.x = 0;
			m_currImage.y++;
			if (m_imageCount.y > 0 && m_currImage.y >= m_imageCount.y )
				m_currImage.y = 0;
		}
	}

	uvRect.top = m_currImage.y * uvRect.height;
	
	if (faceRight)
	{
		uvRect.left = m_currImage.x * uvRect.width;
		uvRect.width = abs(uvRect.width);
	}
	else
	{
		uvRect.left = (m_currImage.x + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}
}