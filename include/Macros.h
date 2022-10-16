//=============================================================================
#pragma once
//=============================================================================
#include <SFML/Graphics.hpp>
//=============================================================================
using Positions = std::pair<sf::Vector2u, sf::Vector2f>;
//=============================================================================
//*** SCREEN SIZE STUFF ***
constexpr auto GAME_WIDTH = 850;
constexpr auto GAME_HEIGHT = 850;
//=============================================================================
//if we want to make the game wides/shorter we will update the size here
//should always be N X N.
constexpr auto TILES_IN_ROW = 11;
constexpr auto TILES_IN_COL = 11;
//=============================================================================
//calculations made for the tiles' sizes to fit alongside the cat and everything else.
const sf::Vector2f BOARD_START((float)GAME_HEIGHT * 0.1, (float)GAME_WIDTH * 0.1);
const sf::Vector2f BOARD_END((float)GAME_HEIGHT * 0.9, (float)GAME_WIDTH * 0.9);
const sf::Vector2f BOARD_SIZE(BOARD_END - BOARD_START);
const sf::Vector2f TILE_SIZE(BOARD_SIZE.x / (float)TILES_IN_ROW, BOARD_SIZE.y / (float)TILES_IN_COL);
//=============================================================================
// *** TEXTS AND STUFF ABOUT THEM ***
constexpr auto TITLE_TEXT = "CIRCLE THE CAT-OUSAUR";
constexpr auto UNDO_TEXT = "UNDO";
constexpr auto CLICKS_TEXT = "CLICKS: ";
constexpr auto LOSSING_TEXT = "THE CAT RAN AWAY!\n   TRY AGAIN? (Y/N)";
constexpr auto WIN_TEXT = "YOU WIN! \nPRESS ANY KEY TO CONTINUE";
//=============================================================================
const sf::Vector2f TITLE_POSITION(GAME_WIDTH * 0.2, GAME_HEIGHT * 0.035);
const sf::Vector2f CLICKS_POSITION(30, GAME_HEIGHT - 35);
const sf::Vector2f UNDO_POSITION(GAME_WIDTH * 0.8, GAME_HEIGHT * 0.94);
const sf::Vector2f LOSSING_POSITION(GAME_WIDTH * 0.20, GAME_HEIGHT * 0.45);
const sf::Vector2f WIN_POSITION(GAME_WIDTH * 0.1, GAME_HEIGHT * 0.45);
//=============================================================================
//*** FOR THE GAME IN GENERAL ***
const sf::Vector2u EASY(11, 14);
const sf::Vector2u MEDIUM(8, 10);
const sf::Vector2u HARD(4, 7);
const sf::Vector2u DIFFICULTIES[3] = { EASY, MEDIUM, HARD };
//=============================================================================
//*** FOR THE CAT ***
const sf::Vector2f LOOKING_RIGHT(TILE_SIZE.x * 0.25, TILE_SIZE.y * 0.85);
const sf::Vector2f LOOKING_LEFT( -(TILE_SIZE.x * 0.5) , TILE_SIZE.y * 0.85);
//=============================================================================
constexpr auto JUMP_FRAMES = 170;
constexpr auto DEATH_FRAMES= 200;
//=============================================================================
const sf::Vector2u CAT_START( 5,5 );
//=============================================================================
const sf::Vector2u IDLE_COUNT( 10,1 );
constexpr auto IDLE_SWITCH( .1f );
//=============================================================================
const sf::Vector2u JUMP_COUNT( 12,1 );
constexpr auto JUMP_SWITCH( .1f );
//=============================================================================
constexpr auto GENERAL = 0;
//=============================================================================
enum class Textures { Grass, Lava, BackG, IdleCat, JumpCat, MaxTextures};
enum class Texts{Title, Counter, Undo, Lossing, WIN, MaxTexts};
enum class Sounds{Jump, MaxSounds, Theme};
enum class Fonts{Classic, MaxFonts};
//=============================================================================
const int MUSIC_VOLUME = 25;
const int EFFECTS_VOLUME = 10;
//=============================================================================