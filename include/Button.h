//=============================================================================
#pragma once
//=============================================================================
#include "Macros.h"
//=============================================================================
enum ButtonState{Idle, Hover, clicked};
//=============================================================================
class Button{
public:
	Button(sf::Vector2f pos, sf::Vector2f size, std::string text,
		    sf::Color idle, sf::Color hover, sf::Color clicked);
	~Button() = default;
	void draw(sf::RenderWindow& window);
	void update(sf::Vector2f mousePos);
	bool isClicked() const;

private:
	sf::RectangleShape m_button;
	sf::Text m_text;
	int m_state;
	sf::Color m_idle;
	sf::Color m_hover;
	sf::Color m_clicked;
};
//=============================================================================