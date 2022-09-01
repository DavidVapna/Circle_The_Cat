#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Macros.h"
#include "Tile.h"
#include "Cat.h"
//-----------------------------------------------------------------------------
class Board
{
public:
	Board();
	void draw(sf::RenderWindow& window) const;
	void randomLava(const V2U& difficulty);
	bool mouseClicked(const V2F& mousePos);
	bool undo();
	void setAdjacents();
	bool findExit(const V2U& theCat);
	bool validateRoute() const;
	Tile& escapeTile();
	Tile& getTile(V2U wantedTile);
	void clearBoard();

private:
	void searchRoute(std::vector<std::pair<V2U, V2U>>& queue, bool& found);
	void setEscapeRoute(std::vector<std::pair<V2U, V2U>>& queue, std::list<V2U>& route);
	void senselessRoute(const V2U& theCat, bool& found);

private:
	std::vector<std::vector<Tile>> m_board;
	sf::Vector2i m_lastTile = { -1,-1 };
	std::list<V2U> m_escapeRoute;
};