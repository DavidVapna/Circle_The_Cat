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
	void lostToCat();
	virtual void mouseEvent(const sf::Event& evnt) override;
	virtual void updateButtons(const float& deltaTime) override;
	void handleEvents() override;

private:
	virtual void music() override;
	virtual void keyBoardEvent(const sf::Event& evnt) override;
	virtual void setButtons() override;
	void updateWin();
	void updateLose();
	void gameUpdate(const float& deltaTime);
	//
	void setTexts();
	void setText(int size, const std::string& str,
		const sf::Color& color, const sf::Vector2f& pos);


private:
	Board *m_board;

	unsigned m_clicks = 0;
	std::vector<sf::Text> m_texts;
	int m_difficulty = -1;
	sf::Clock m_gameClock;
	sf::Time m_time;
};
//=============================================================================





