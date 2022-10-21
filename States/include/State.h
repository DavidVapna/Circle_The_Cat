//=============================================================================
#pragma once
//=============================================================================
#include <unordered_map>
#include <stack>
#include "Button.h"
//=============================================================================
class State
{
public:
	State(sf::RenderWindow* window,	std::stack<std::unique_ptr<State>>* m_states);
	virtual ~State();
	virtual void draw() = 0;
	virtual void update(const float& deltaTime) = 0;
	virtual bool isEnd() const;



protected:
	virtual void updateMouse();
	virtual void setBackground(const sf::Texture& texture);
	virtual void setButtons() = 0;
	virtual void keyBoardEvent(const sf::Event& evnt) = 0;


protected:
	sf::RenderWindow* m_window;
	sf::Sprite m_backGround;
	bool m_end;
	sf::Vector2i m_mouseScreen;
	sf::Vector2i m_mouseWindow;
	sf::Vector2f m_mouseView;
	std::unordered_map<int, std::unique_ptr<Button>> m_buttons;
	std::stack<std::unique_ptr<State>> *m_states;
	float m_timer;

private:
};
//=============================================================================


