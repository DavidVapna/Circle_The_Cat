//=============================================================================
#include "Board.h"
//=============================================================================
//Board C-Tor, initializing the game board by loading the tile objects according
//to the defined game board size.
Board::Board(sf::RenderWindow& window)
    :m_catTurn(false), m_won(false), m_lost(false), m_window(&window){
    for (unsigned row = 0; row < TILES_IN_COL; row++){
        std::vector<Tile> tempRow;
        sf::Vector2f tilePos(BOARD_START.x + ((row % 2) * TILE_SIZE.x / 2), (float)(row * TILE_SIZE.y) + BOARD_START.y);
        for (unsigned col = 0; col < TILES_IN_ROW; col++){
            bool lossingTile = (col == 0 || row == 0 || col == TILES_IN_ROW - 1 || row == TILES_IN_COL - 1);
            tempRow.emplace_back(Tile(Positions(sf::Vector2u{ row,col }, tilePos), lossingTile));
            tilePos.x += TILE_SIZE.x;
        }
        m_board.push_back(tempRow);
    }
    setAdjacents();
    m_cat = new Cat(getTile(CAT_START));
}
//=============================================================================
//Basic d-tor
Board::~Board(){
    m_board.clear();
    delete m_cat;
}
//=============================================================================
//this function helps us keep track on the adjacent tiles of each tile, that 
//way we the cat can use the this information to use as a tree and use BFS on it.
void Board::setAdjacents(){
    for (int row = 0; row < TILES_IN_ROW; row++)
        for (int col = 0; col < TILES_IN_COL; col++){
            std::list<sf::Vector2u> currAdj;
            if (row % 2 == 0 && col > 0 && row > 0){
                currAdj.push_back(sf::Vector2u(row - 1, col - 1));
                if (row < TILES_IN_ROW - 1)
                    currAdj.push_back(sf::Vector2u(row + 1, col - 1));
            }
            else if (col < TILES_IN_COL - 1 && row < TILES_IN_ROW - 1){
                currAdj.push_back(sf::Vector2u(row + 1, col + 1));
                if (row > 0) currAdj.push_back(sf::Vector2u(row - 1, col + 1));
            }

            if (col > 0) currAdj.push_back(sf::Vector2u(row, col - 1));
            if (row > 0) currAdj.push_back(sf::Vector2u(row - 1, col));
            if (col < TILES_IN_COL - 1) currAdj.push_back(sf::Vector2u(row, col + 1));
            if (row < TILES_IN_ROW - 1) currAdj.push_back(sf::Vector2u(row + 1, col));

            m_board[row][col].addAdjacents(currAdj);
        }
}
//=============================================================================
//this function resets all the game tiles of the board.
void Board::clearLava(){
    for(auto& row : m_board)
        for (auto& tile : row){
            tile.setPassable();
        }
}
//=============================================================================
//this function generates random lava tiles based on the level difficulty,
//the harder the level the less tiles.
void Board::randomLava(const sf::Vector2u& difficulty){
    auto numOfLava = Resources::instance().randomNumber(difficulty);
    srand((unsigned int)time(NULL));

    for (int counter = 0; counter < numOfLava; counter++){
        sf::Vector2u tile(rand() % TILES_IN_COL, rand() % TILES_IN_ROW);
        if (getTile(tile).isCatHere() || !getTile(tile).setLava()) {
            counter--;
        }
    }
    m_cat->findExit(m_board, m_escapeRoute);
}
//=============================================================================
//general board update function to update all objects that are on it.
//mostly for the buttons and the cat.
void Board::update(const float& deltaTime) {
    if (m_catTurn && !m_cat->isJumping()) {
        if (!validateEscape())
            m_won = true;
        else {
            m_cat->catMove(getTile(m_escapeRoute.back()));
            m_escapeRoute.pop_back();
            m_lost = m_cat->didCatWin();
            m_catTurn = false;
        }
    }
    m_cat->update(deltaTime);
}
//=============================================================================
//this function is called every time theres a mouse click to verify whether
//the player has pressed on a tile, and if so work accordingly (if unclicked
//tile then change to clicked, otherwise do nothing).
bool Board::mouseClicked(const sf::Vector2f& mousePos) {

    if (!m_catTurn) {
        for (int i = 0; i < m_board.size(); i++) {
            for (int j = 0; j < m_board[i].size(); j++) {
                if (m_board[i][j].setLava(mousePos)) {
                    m_clickRoute.push_front(sf::Vector2u(i, j));
                    m_catTurn = true;
                    return true;
                }
            }
        }
    }
    return false;
}
//=============================================================================
//the function draws the cat based on his state, if its his turn and he is jumping
//or if its the players turn then the cat is idel, and just general tiles drawing.
void Board::draw() const{
    for (auto& row : m_board)
        for (auto& tile : row)
            tile.draw(*m_window);

    m_cat->draw(*m_window);
}
//=============================================================================
//
bool Board::undo() {
    if (m_clickRoute.empty())
        return false;

    m_cat->undo();
    getTile(m_clickRoute.front()).setPassable();
    m_clickRoute.pop_front();
    m_cat->findExit(m_board, m_escapeRoute);
    return true;
}
//=============================================================================
//fastest way to reset the level is to undo all steps that way we wont get
//have to go over ALL the tiles.
void Board::resetLevel() {
    while (undo()) {};
}
//=============================================================================
//quick access function
Tile& Board::getTile(sf::Vector2u wantedTile){
    return m_board[wantedTile.x][wantedTile.y];
}
//=============================================================================
//reloading next level with higher difficulty (capped at 3).
void Board::nextLevel(int difficulty) {
    clearLava();
    m_cat->newLevel(getTile(CAT_START));
    randomLava(DIFFICULTIES[difficulty]);
}
//=============================================================================
//this function makes sures that the current escape route of the cat is still
//available for it, if not it'll try to find a new one.
//if there isnt one, then it means the player has won.
bool Board::validateEscape() {

    if (m_escapeRoute.empty()) {
        if (!m_cat->findExit(m_board, m_escapeRoute)) {
            return false;
        }
    }
    else {
        for (auto& tile : m_escapeRoute) {
            if (!m_board[tile.x][tile.y].isPassable()) {
                if (!m_cat->findExit(m_board, m_escapeRoute)) {
                    return false;
                }
            }
        }
    }
    resetVisit();

    return true;
}
//=============================================================================
// function to reset all visits made for whatever reason throughout the game.
void Board::resetVisit() {
    for (auto& row : m_board)
        for (auto& tile : row)
            tile.resetVisit();
}
//=============================================================================
//this function chekcs whether the cat has reached the edges of the board.
//if it did it returns true but resets the boolean
bool Board::didCatWin() {
    if (m_lost) {
        m_lost = false;
        return true;
    }
    return false;
}
//=============================================================================
//this function chekcs whether the player has circled the cat succefully.
//if they did it returns true but resets the boolean.
bool Board::didPlayerWin() {
    if (m_won) {
        m_won = false;
        return true;
    }
    return false;
}
//=============================================================================