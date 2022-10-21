//=============================================================================
#pragma once
//=============================================================================
#include "State.h"
//=============================================================================
class MenuState : public State{
public:
	MenuState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states);
	virtual ~MenuState();
	virtual void draw() override;
	virtual void update(const float& deltaTime) override;

private:
	void setTitle();
	virtual void setButtons() override;
	virtual void keyBoardEvent(const sf::Event& evnt) override;


private:
	sf::Text m_title;
};
//=============================================================================