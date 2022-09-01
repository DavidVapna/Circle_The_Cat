#pragma once
//-----------------------------------------------------------------------------
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "Resources.h"
#include "Macros.h"
//-----------------------------------------------------------------------------
class Tile
{
public:
	Tile(const Positions& position, bool lossingTile);
	bool setNotPassable();
	bool handleClick(const V2F& mouseClick, const sf::Vector2i& last);
	void draw(sf::RenderWindow& window) const;

	const sf::Vector2i& undo();
	void setVisit();
	bool visited();
	void resetVisit();
	void addAdjacents(const std::list<V2U>& adjacents);
	std::list<V2U> getAdjacents();
	bool isPassable() const;
	bool isLossing() const;
	Positions getPos() const;
	void catHere();
	void catLeft();
	bool isCatHere() const;
	~Tile() = default;
	void setPassable();
private:
	void addTile(ResourceName tile, const V2F& position);



private:
	bool m_passable = true;
	bool m_lossingTile;
	bool m_visited = false;
	std::vector<sf::Sprite> m_states;
	Positions m_position;
	sf::Vector2i m_lastTile = { -1,-1};
	std::list<V2U> m_adjacents;
	bool m_catIsHere = false;
};