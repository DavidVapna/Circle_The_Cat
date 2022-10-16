//=============================================================================
#pragma once
//=============================================================================
#include "Resources.h"
//=============================================================================
class Tile
{
public:
	Tile(const Positions& position, bool lossingTile);
	//bool setNotPassable();
	bool setLava(const sf::Vector2f& mouseClick = sf::Vector2f(0,0));
	void draw(sf::RenderWindow& window) const;

	void setVisit();
	bool visited();
	void resetVisit();
	void addAdjacents(const std::list<sf::Vector2u>& adjacents);
	std::list<sf::Vector2u> getAdjacents();
	bool isPassable() const;
	bool isLossing() const;
	Positions getPos() const;
	void catHere();
	void catLeft();
	bool isCatHere() const;
	~Tile() = default;
	void setPassable();

private:
	//private functions
	void addState(int tile, const sf::Vector2f& position);



private:
	//private members
	bool m_passable;
	bool m_lossingTile;
	bool m_visited;
	bool m_catIsHere;
	Positions m_position;
	std::vector<sf::Sprite> m_states;
	std::list<sf::Vector2u> m_adjacents;
};
//=============================================================================