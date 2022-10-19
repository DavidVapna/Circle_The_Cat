//=============================================================================
#pragma once
//=============================================================================
#include "Tile.h"
#include "Cat.h"
//=============================================================================
class Board{
public:
	Board();
	~Board();
	void update(const float& deltaTime);
	void draw(sf::RenderWindow& window) const;
	void randomLava(const sf::Vector2u& difficulty);
	bool mouseClicked(const sf::Vector2f& mousePos);
	bool undo();
	void setAdjacents();
	bool validateRoute() const;
	Tile& escapeTile();
	Tile& getTile(sf::Vector2u wantedTile);
	void clearBoard();

private:
	void searchRoute(std::vector<std::pair<sf::Vector2u, sf::Vector2u>>& queue, bool& found);
	void setEscapeRoute(std::vector<std::pair<sf::Vector2u, sf::Vector2u>>& queue, std::list<sf::Vector2u>& route);
	void senselessRoute(const sf::Vector2u& theCat, bool& found);

private:
	std::vector<std::vector<Tile>> m_board;
	std::list<sf::Vector2u> m_clickRoute;
	std::list<sf::Vector2u> m_escapeRoute;
	Cat* m_cat;
	bool m_catTurn;

};
//=============================================================================