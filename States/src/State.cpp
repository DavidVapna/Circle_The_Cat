//=============================================================================
#include "State.h"
//=============================================================================
State::State(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states)
	:m_end(false),m_window(window), m_states(states), m_timer(0)
{
}
//=============================================================================
State::~State()
{

}
//=============================================================================
bool State::isEnd() const
{
	return m_end;
}
//=============================================================================
void State::updateMouse()
{
	m_mouseScreen = sf::Mouse::getPosition();
	m_mouseWindow = sf::Mouse::getPosition(*m_window);
	m_mouseView = m_window->mapPixelToCoords(m_mouseWindow);
}
//=============================================================================
void State::setBackground(const sf::Texture& texture){
	m_backGround.setTexture(texture);
	sf::Vector2f scaleTo;
	scaleTo.x = (float)GAME_WIDTH / texture.getSize().x;
	scaleTo.y = (float)GAME_HEIGHT / texture.getSize().y;
	m_backGround.setScale(scaleTo);
}
//=============================================================================