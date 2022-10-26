//=============================================================================
#pragma once
//=============================================================================
#include "Tile.h"
#include "Cat.h"
//=============================================================================
class Board{
public:
	Board(sf::RenderWindow &window);
	~Board();
	void update(const float& deltaTime);
	void draw() const;
	void randomLava(const sf::Vector2u& difficulty);
	bool mouseClicked(const sf::Vector2f& mousePos);
	bool undo();
	void nextLevel (int difficulty);
	bool didPlayerWin();
	bool didCatWin();
	void resetLevel();



private:
	Tile& getTile(sf::Vector2u wantedTile);
	void setAdjacents();
	void clearLava();
	bool validateEscape();
	void searchRoute(std::vector<std::pair<sf::Vector2u, sf::Vector2u>>& queue, bool& found);
	void setEscapeRoute(std::vector<std::pair<sf::Vector2u, sf::Vector2u>>& queue, std::list<sf::Vector2u>& route);
	void resetVisit();

private:
	std::vector<std::vector<Tile>> m_board;
	std::list<sf::Vector2u> m_clickRoute;
	Cat* m_cat;
	bool m_catTurn;
	bool m_won;
	bool m_lost;
	sf::RenderWindow *m_window;
	std::list<sf::Vector2u> m_escapeRoute;
};
//=============================================================================