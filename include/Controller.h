#pragma once
//-----------------------------------------------------------------------------
#include <SFML/Graphics.hpp>
#include "Macros.h"
#include "Resources.h"
#include "Board.h"
//-----------------------------------------------------------------------------
class Controller
{
public:
	Controller();
	void run();

private:
	void handleEvents();
	void update();
	void draw();
	void setTexts();
	void setText(int size, const std::string& str, const sf::Color& color,
		const V2F& pos);
	void keyBoardEvent(const sf::Event& evnt);
	void mouseEvent(const sf::Event& evnt);
	void setSprites();
	void lostToCat();
	void levelWin();
	void catJump();
	void loadNextLevel(int difficulty);
	void undo();
	void catsTurn();


private:
	bool m_catTurn = false;
	sf::RenderWindow m_window;
	Board m_board;
	unsigned m_clicks = 0;
	sf::Vector2i m_mousePos;
	V2F m_mouseView;
	std::vector<sf::Text> m_texts;
	std::vector<sf::Sprite> m_sprites;
	Cat* m_cat;
	int m_difficulty = -1;
	float m_deltaTime;
	sf::Clock m_clock;
	
};