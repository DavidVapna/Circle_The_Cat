//=============================================================================
#pragma once
//=============================================================================
#include "State.h"
//=============================================================================
class MenuState : public State {
public:
	MenuState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states);
	virtual ~MenuState();
	virtual void draw() override;
	virtual void update(const float& deltaTime) override;
	virtual void mouseEvent(const sf::Event& evnt) override { return; }
	virtual void updateButtons(const float& deltaTime) override;
	virtual void handleEvents() override;


private:
	void setTitle();
	virtual void setButtons() override;
	virtual void keyBoardEvent(const sf::Event& evnt) override;
	virtual void music() override;

private:
	sf::Text m_title;
};
//=============================================================================