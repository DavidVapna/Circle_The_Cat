//=============================================================================
#include "Tile.h"
//=============================================================================
//C-tor for the tile, recieves position that will not change until destroyed,
//also starts as either a lossing tile from the outer area of the map.
//each tile can be either grass (stepable) or lava (clicked by player).
Tile::Tile(const Positions& position, bool lossingTile)
	:m_passable(true), m_lossingTile(lossingTile), m_visited(false),
	m_catIsHere(false), m_position(position)
{
	addState((int)Textures::Grass, position.second);
	addState((int)Textures::Lava, position.second);
}
//=============================================================================
//private function to generate the tile.
void Tile::addState(int tile, const sf::Vector2f& position)
{
	sf::Sprite newTile;
	newTile.setPosition(position);
	newTile.setTexture(Resources::instance().getTexture(tile));

	sf::Vector2f scaleTo;
	scaleTo.x = TILE_SIZE.x / newTile.getTexture()->getSize().x;
	scaleTo.y = TILE_SIZE.y / newTile.getTexture()->getSize().y;
	newTile.setScale(scaleTo);

	m_states.push_back(newTile);
}
//=============================================================================
//
void Tile::setPassable()
{
	m_passable = true;
}
//=============================================================================
//
std::list<sf::Vector2u> Tile::getAdjacents()
{
	return m_adjacents;
}
//=============================================================================
//
bool Tile::isLossing() const
{
	return m_lossingTile;
}
//=============================================================================
//
bool Tile::setLava(const sf::Vector2f& mouseClick)
{
	if (mouseClick == sf::Vector2f(0, 0) ||
		m_states[GENERAL].getGlobalBounds().contains(mouseClick)) 
	{
		if (m_passable && !m_catIsHere)
		{
			m_passable = false;
			return true;
		}
	}
	return false;
}
//=============================================================================
//
void Tile::draw(sf::RenderWindow& window) const
{
	if (m_passable) 
		window.draw(m_states[(int)Textures::Grass]);
	else  
		window.draw(m_states[(int)Textures::Lava]);
}
//=============================================================================
//
bool Tile::isPassable() const
{
	return m_passable;
}
//=============================================================================
//
void Tile::setVisit()
{
	m_visited = true;
}
//=============================================================================
//
bool Tile::visited()
{
	return m_visited;
}
//=============================================================================
//
void Tile::resetVisit()
{
	m_visited = false;
}
//=============================================================================
//
void Tile::addAdjacents(const std::list<sf::Vector2u>& adjacents)
{
	m_adjacents = adjacents;
}
//=============================================================================
//
void Tile::catHere()
{
	m_catIsHere = true;
}
//=============================================================================
//
bool Tile::isCatHere() const
{
	return m_catIsHere;
}
//=============================================================================
//
Positions Tile::getPos() const
{
	return m_position;
}
//=============================================================================
//
void Tile::catLeft()
{
	m_catIsHere = false;
}