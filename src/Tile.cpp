#include "Tile.h"
//-----------------------------------------------------------------------------
//
Tile::Tile(const Positions& position, bool lossingTile)
	:m_position(position), m_lossingTile(lossingTile)
{
	addTile(ResourceName::Grass, position.second);
	addTile(ResourceName::Lava, position.second);
}
//-----------------------------------------------------------------------------
//
void Tile::addTile(ResourceName tile, const V2F& position)
{
	sf::Sprite newTile;
	newTile.setPosition(position);
	newTile.setTexture(Resources::instance().getTexture(tile));

	V2F scaleTo;
	scaleTo.x = TILE_SIZE.x / newTile.getTexture()->getSize().x;
	scaleTo.y = TILE_SIZE.y / newTile.getTexture()->getSize().y;
	newTile.setScale(scaleTo);

	m_states.push_back(newTile);
}
//-----------------------------------------------------------------------------
//
bool Tile::setNotPassable()
{
	if (!m_passable) return false;
	else { m_passable = false; return true; }
}
//-----------------------------------------------------------------------------
//
void Tile::setPassable()
{
	m_passable = true;
}
//-----------------------------------------------------------------------------
//
std::list<V2U> Tile::getAdjacents()
{
	return m_adjacents;
}
//-----------------------------------------------------------------------------
//
bool Tile::isLossing() const
{
	return m_lossingTile;
}
//-----------------------------------------------------------------------------
//
bool Tile::handleClick(const V2F& mouseClick, const sf::Vector2i& last)
{
	if (m_states[GENERAL].getGlobalBounds().contains(mouseClick))
		if (m_passable && !m_catIsHere)
		{
			m_passable = false;
			m_lastTile = last;
			return true;
		}
	return false;
}
//-----------------------------------------------------------------------------
//
void Tile::draw(sf::RenderWindow& window) const
{
	if (m_passable) { window.draw(m_states[(int)ResourceName::Grass]); }
	else { window.draw(m_states[(int)ResourceName::Lava]); }
}
//-----------------------------------------------------------------------------
//
bool Tile::isPassable() const
{
	return m_passable;
}
//-----------------------------------------------------------------------------
//
void Tile::setVisit()
{
	m_visited = true;
}
//-----------------------------------------------------------------------------
//
bool Tile::visited()
{
	return m_visited;
}
//-----------------------------------------------------------------------------
//
void Tile::resetVisit()
{
	m_visited = false;
}
//-----------------------------------------------------------------------------
//
void Tile::addAdjacents(const std::list<V2U>& adjacents)
{
	m_adjacents = adjacents;
}
//-----------------------------------------------------------------------------
//
void Tile::catHere()
{
	m_catIsHere = true;
}
//-----------------------------------------------------------------------------
//
bool Tile::isCatHere() const
{
	return m_catIsHere;
}
//-----------------------------------------------------------------------------
//
const sf::Vector2i& Tile::undo()
{
	m_passable = true;
	return m_lastTile;
}
//-----------------------------------------------------------------------------
//
Positions Tile::getPos() const
{
	return m_position;
}
//-----------------------------------------------------------------------------
//
void Tile::catLeft()
{
	m_catIsHere = false;
}