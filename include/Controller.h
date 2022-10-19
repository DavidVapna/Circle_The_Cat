//=============================================================================
#pragma once
//=============================================================================
#include "Board.h"
#include "State.h"
#include <stack>
//=============================================================================
class Controller
{
public:
	Controller();
	void run();


private:
	std::unique_ptr<State> initMenu();
	void update();
	void display();
	void handleEvents();
	void keyBoardEvent(const sf::Event& evnt);

private:
	States m_currMod;
	std::stack<std::unique_ptr<State>> m_states;
	std::unique_ptr<sf::RenderWindow> m_window;
};
//=============================================================================