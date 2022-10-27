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

const sf::Vector2i MENU_SIZE(850, 850);
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
constexpr auto WIN_TEXT = "YOU WIN! \nPRESS ENTER TO CONTINUE";

constexpr auto TIME_TEXT = "TIME: ";
//=============================================================================
const sf::Vector2f GAME_TITLE_POS(GAME_WIDTH * 0.17, GAME_HEIGHT * 0.035);
const sf::Vector2f MENU_TITLE_POS(GAME_WIDTH * 0.5, GAME_HEIGHT * 0.035);
const sf::Vector2f CLICKS_POS(30, GAME_HEIGHT - 35);
const sf::Vector2f UNDO_POS(GAME_WIDTH * 0.8, GAME_HEIGHT * 0.96);
const sf::Vector2f LOSSING_POS(GAME_WIDTH * 0.20, GAME_HEIGHT * 0.45);
const sf::Vector2f WIN_POS(GAME_WIDTH * 0.1, GAME_HEIGHT * 0.45);

const sf::Vector2f TIME_POS(GAME_WIDTH * 0.05, GAME_HEIGHT * 0.01);

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
constexpr auto JUMP_FRAMES = 85;
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
enum class Textures { Grass, Lava, GameBG, MenuBG, IdleCat, JumpCat, MaxTextures};
enum class Texts{Title, Counter, Time, Lost, WIN, MaxTexts};
enum class Sounds{Jump, MaxSounds, MenuMusic, GameMusic};
enum class Fonts{Classic, MaxFonts};

const int DEEFAULT_TEXTS = 3;
//=============================================================================
const int MUSIC_VOLUME = 25;
const int EFFECTS_VOLUME = 10;
//=============================================================================
enum class States{Menu, Game};
//=============================================================================

//=============================================================================
const sf::Vector2f MENU_BUTTON_SIZE(200, 100);
const sf::Vector2f GAME_BUTTON_SIZE(85, 60);
const sf::Vector2f PLAY_POS(MENU_SIZE.x / 2.f, MENU_SIZE.y* (2.f / 7.f));
const sf::Vector2f HELP_POS(MENU_SIZE.x / 2.f, MENU_SIZE.y* (4.f / 7.f));
const sf::Vector2f QUIT_POS(MENU_SIZE.x / 2.f, MENU_SIZE.y* (6.f / 7.f));
const sf::Vector2f CONTINUE_BUTTON(400.f, 400.f);
constexpr auto PLAY_TEXT("Play");
constexpr auto QUIT_TEXT("Exit");
constexpr auto HELP_TEXT("Help");
constexpr auto CONTINUE_TEXT("Conitune");
//=============================================================================
