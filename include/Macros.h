#pragma once

#include <SFML/Graphics.hpp>


using V2U = sf::Vector2u;
using V2F = sf::Vector2f;
using Positions = std::pair<V2U, V2F>;

//*** SCREEN SIZE STUFF ***
constexpr auto GAME_WIDTH = 850;
constexpr auto GAME_HEIGHT = 850;

constexpr auto TILES_IN_ROW = 11;
constexpr auto TILES_IN_COL = 11;

const V2F BOARD_START((float)GAME_HEIGHT * 0.1, (float)GAME_WIDTH * 0.1);
const V2F BOARD_END((float)GAME_HEIGHT * 0.9, (float)GAME_WIDTH * 0.9);
const V2F BOARD_SIZE(BOARD_END - BOARD_START);
const V2F TILE_SIZE(BOARD_SIZE.x / (float)TILES_IN_ROW, BOARD_SIZE.y / (float)TILES_IN_COL);


// *** TEXTS AND STUFF ABOUT THEM ***
constexpr auto TITLE_TEXT = "CIRCLE THE CAT-OUSAUR";
constexpr auto UNDO_TEXT = "UNDO";
constexpr auto CLICKS_TEXT = "CURRENT CLICKS: ";
constexpr auto LOSSING_TEXT = "THE CAT RAN AWAY!\n   TRY AGAIN? (Y/N)";
constexpr auto WIN_TEXT = "					YOU WIN! \nPRESS ANY KEY TO CONTINUE";


const V2F TITLE_POSITION(GAME_WIDTH * 0.2, GAME_HEIGHT * 0.035);
const V2F CLICKS_POSITION(30, GAME_HEIGHT - 35);
const V2F UNDO_POSITION(GAME_WIDTH * 0.8, GAME_HEIGHT * 0.94);
const V2F LOSSING_POSITION(GAME_WIDTH * 0.20, GAME_HEIGHT * 0.45);
const V2F WIN_POSITION(GAME_WIDTH * 0.1, GAME_HEIGHT * 0.45);



//*** FOR THE GAME IN GENERAL ***
const V2U EASY(11, 14);
const V2U MEDIUM(8, 10);
const V2U HARD(4, 7);
const V2U DIFFICULTIES[3] = { EASY, MEDIUM, HARD };



//*** FOR THE CAT ***
const V2F LOOKING_RIGHT(TILE_SIZE.x * 0.25, TILE_SIZE.y * 0.85);
const V2F LOOKING_LEFT( -(TILE_SIZE.x * 0.5) , TILE_SIZE.y * 0.85);


constexpr auto JUMP_FRAMES = 170;
constexpr auto DEATH_FRAMES= 200;

const V2U CAT_START( 5,5 );

const V2U IDLE_COUNT( 10,1 );
constexpr auto IDLE_SWITCH( .1f );

const V2U JUMP_COUNT( 12,1 );
constexpr auto JUMP_SWITCH( .1f );



constexpr auto GENERAL = 0;


enum class ResourceName { Grass, Lava, BackG, IdleCat, JumpCat };
enum class Texts{Title, Counter, Undo, Lossing, WIN};

