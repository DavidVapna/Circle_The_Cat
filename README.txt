
Title: Circle The Cat
By David Vapna

General Explanation:
The goal of the player in this game is to trap the cat by pressing the tiles around the cat (dino in our case).
If the cat reaches to any tile on the edge of the map, the cat escapes and the game is over.

Design:
Controller class that’s responsible for running the program based on the current state(menu, game, help and pause).
The player's input(clicking on tiles) affects the cat's escape route on the board, the cat always trys to find the shortest way out.

Main data structures:
Two dimensional vector used to store the tile objects that represent the game map.
stack of State class, responsible for easy and quick change between different display states.

	
 
Mention worthy algorithms:
The cat’s algorithm for escape a mixture of BFS mixed with other elements so it will fit the needs of the cat.

Known Bugs:




File list:
Animation.cpp + h
Board.cpp + h
Button.cpp + h
Cat.cpp + h
Controller.cpp + h
Resources.cpp + h
Tile.cpp + h
Macros.h
main.cpp
States.cpp + h
GameState.cpp + h
MenuState.cpp+h

