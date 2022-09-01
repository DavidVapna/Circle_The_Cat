#pragma once



#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Macros.h"
#include "Tile.h"
#include "Animation.h"
#include <list>




class Cat
{
public:
	Cat(Tile& startingTile);
	~Cat();
	void tryToRun(Tile& destination);
	void update(float deltaTime);
	void draw(sf::RenderWindow& window) const;
	void drawJump(sf::RenderWindow& window) const;
	V2U getPosition() const;
	void undo();
	void jump(float deltaTime);
	bool didCatWin() const;
	void newLevel(Tile& startingTile);


private:
	enum class State{idle, Jump};

private:
	std::list<Tile*> m_jorney;
	std::vector<Animation*> m_animation;
	bool m_faceRight;
	
	sf::Sprite m_idle;
	sf::Sprite m_jump;

	sf::Vector2f m_frame;
	V2F m_pos;

};