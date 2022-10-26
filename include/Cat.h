//=============================================================================
#pragma once
//=============================================================================
#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <list>
//=============================================================================
class Tile;
class Animation;
//=============================================================================
class Cat{
public:
	Cat(Tile& startingTile);
	~Cat();
	void catMove(Tile& destination);
	void update(float deltaTime);
	void draw(sf::RenderWindow& window) const;
	sf::Vector2u getPosition() const;
	void undo();
	bool didCatWin() const;
	void newLevel(Tile& startingTile);
	bool findExit(std::vector<std::vector<Tile>>& gameBoard, std::list<sf::Vector2u>& escape);
	void ResetLevel();
	bool isJumping() const;

private:
	enum class State{idle, Jump};
	void searchRoute(std::vector<std::pair<sf::Vector2u, sf::Vector2u>>& queue, bool& found);

private:
	std::list<Tile*> m_visitedTiles;
	std::vector<Animation*> m_animation;
	bool m_faceRight;
	bool m_jumping;
	sf::Sprite m_idle;
	sf::Sprite m_jump;

	sf::Vector2f m_frame;
	sf::Vector2f m_pos;
	int m_jumpCounter;

};
//=============================================================================