//=============================================================================
#pragma once
//=============================================================================
#include "State.h"
//=============================================================================
class MenuState : public State{
public:
	MenuState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states);
	virtual ~MenuState();
	virtual void setWindow() override;
	virtual void draw() override;
	virtual void update(const float& deltaTime) override;
	virtual void updateInput(const float& deltaTime) override;
	virtual void setButtons() override;
	void setTitle();

protected:
	virtual void mouseEvent(const sf::Event& evnt) override;
	virtual void keyBoardEvent(const sf::Event& evnt) override;

private:
	sf::Text m_title;
};
//=============================================================================