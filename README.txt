
Title: Circle The Cat
By David Vapna

General Explanation:
The goal of the player in this game is to trap the cat by pressing the tiles around the cat (dino in our case).
If the cat reaches to any tile on the edge of the map, the cat escapes and the game is over.

Design:
Controller class that’s responsible for the communication between the game board constant state, the players input and the cats escape route on the board to find the shortest way out.


Main data structures:
Two dimensional vector used to store the tile objects that represent the game map.
	
 
Mention worthy algorithms:
The cat’s algorithm for escape a mixture of BFS mixed with other elements so it will fit the needs of the cat.

Known Bugs:




File list:
Animation.cpp + h
Board.cpp + h
Cat.cpp + h
Controller.cpp + h
Resources.cpp + h
Tile.cpp + h
Macros.h
main.cpp
