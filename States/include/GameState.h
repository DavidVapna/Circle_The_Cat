//=============================================================================
#pragma once
//=============================================================================
#include "State.h"
#include "Board.h"
//=============================================================================
class GameState : public State{
public:
	GameState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states);
	virtual ~GameState();
	virtual void draw() override;
	virtual void update(const float& deltaTime) override;
	void updateInput(const float& deltaTime)override;
	virtual void setButtons() override;


	void loadNextLevel(int difficulty);
	void lostToCat();
	void levelWin();
	void catJump();
	void catsTurn();
	void undo();

private:
	void handleEvents();
	virtual void mouseEvent(const sf::Event& evnt) override;
	virtual void keyBoardEvent(const sf::Event& evnt) override;
	void restartLevel();

	//
	void setTexts();
	void setText(int size, const std::string& str,
		const sf::Color& color, const sf::Vector2f& pos);


private:
	Board m_board;
	float m_deltaTime;
	sf::Clock m_gameClock;
	unsigned m_clicks = 0;
	std::vector<sf::Text> m_texts;
	int m_difficulty = -1;
	sf::Clock m_clock;
};
//=============================================================================





