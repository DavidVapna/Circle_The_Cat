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
	void setAdjacents();
	bool validateEscape();
	Tile& escapeTile();
	Tile& getTile(sf::Vector2u wantedTile);
	void clearBoard();
	void nextLevel(int difficulty);
	void catsTurn();
	bool didPlayerWin();
	bool didCatWin();

private:
	void searchRoute(std::vector<std::pair<sf::Vector2u, sf::Vector2u>>& queue, bool& found);
	void setEscapeRoute(std::vector<std::pair<sf::Vector2u, sf::Vector2u>>& queue, std::list<sf::Vector2u>& route);

private:
	std::vector<std::vector<Tile>> m_board;
	std::list<sf::Vector2u> m_clickRoute;
	Cat* m_cat;
	bool m_catTurn;
	bool m_won;
	bool m_lost;
	sf::RenderWindow *m_window;
	std::list<sf::Vector2u> m_escapeRoute;
	float m_clickCD;
	float m_maxClickCD;
};
//=============================================================================