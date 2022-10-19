//=============================================================================
#include "Board.h"
//=============================================================================
//Board C-Tor, initializing the game board by loading the tile objects according
//to the defined game board size.
Board::Board()
    :m_catTurn(false){
    m_cat = new Cat(getTile(CAT_START));
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
    getTile(CAT_START).catHere();
}
//=============================================================================
//default d-tor
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
void Board::clearBoard(){
    for(auto& row : m_board)
        for (auto& tile : row){
            tile.catLeft();
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
        if (!getTile(tile).isCatHere() && getTile(tile).setLava());
    }
}
//=============================================================================
//general board update function to update all objects that are on it.
//mostly for the buttons and the cat.
void Board::update(const float& deltaTime) {
    m_cat->update(deltaTime);
}
//=============================================================================
//this function is called every time theres a mouse click to verify whether
//the player has pressed on a tile, and if so work accordingly (if unclicked
//tile then change to clicked, otherwise do nothing).
bool Board::mouseClicked(const sf::Vector2f& mousePos){
    for (int i = 0; i < m_board.size(); i++)
        for (int j = 0; j < m_board[i].size(); j++)
            if (m_board[i][j].setLava(mousePos)){
                m_clickRoute.push_front(sf::Vector2u(i, j));
                m_catTurn = true;
                m_cat->findExit(this->m_board);
                return true;
            }
    return false;
}
//=============================================================================
//
void Board::draw(sf::RenderWindow& window) const{
    for (auto& row : m_board)
        for (auto& tile : row)
            tile.draw(window);

    m_catTurn ? m_cat->drawJump(window) : m_cat->draw(window);
}
//=============================================================================
//
bool Board::undo(){
    if (m_clickRoute.empty())
        return false;
    else {
        m_cat->undo();
        getTile(m_clickRoute.front()).setPassable();
        m_clickRoute.pop_front();
    }
        return true;
}
//=============================================================================
//
void Board::searchRoute(std::vector<std::pair<sf::Vector2u, sf::Vector2u>>& queue, bool &found){
    for (int i = 0; i < queue.size() && !found; ++i){
        for (auto adjecent : getTile(queue[i].first).getAdjacents()){
            if (getTile(adjecent).isPassable() && !getTile(adjecent).visited()){
                queue.push_back(std::make_pair(adjecent, queue[i].first));
                if (getTile(adjecent).isLossing()){
                    found = true; break;
                }
                getTile(adjecent).setVisit();
            }
        }
    }
    for (auto& row : m_board)
        for (auto& tile : row)
            tile.resetVisit();
}
//=============================================================================
//
bool Board::validateRoute(){
    if (m_escapeRoute.empty() && !m_cat->findExit(m_board))
           return false;

    for (auto& tile : m_escapeRoute){
        if (!m_board[tile.x][tile.y].isPassable() && !m_cat->findExit(m_board))            
               return false;
    }
    return true;
}
//=============================================================================
//
void Board::setEscapeRoute(std::vector<std::pair<sf::Vector2u, sf::Vector2u>>& queue, std::list<sf::Vector2u>& route){
    route.push_back(queue.back().first);
    for (auto i = --queue.end(); i != queue.begin(); --i){
        if (i->first == route.back())
            route.push_back(i->second);
    }
    route.pop_back();
    m_escapeRoute = route;
}
//=============================================================================
//
void Board::senselessRoute(const sf::Vector2u& theCat, bool &found){
    for (auto adjecent : getTile(theCat).getAdjacents())
        if (getTile(adjecent).isPassable()){
            m_escapeRoute.push_back(adjecent);
            found = true;
            break;
        }
}
//=============================================================================
//
Tile& Board::getTile(sf::Vector2u wantedTile){
    return m_board[wantedTile.x][wantedTile.y];
}
//=============================================================================
//
Tile& Board::escapeTile(){
    auto nextTile = m_escapeRoute.back();
    m_escapeRoute.pop_back();
    return getTile(nextTile);
}
//=============================================================================
//
void Board::catJump(sf::RenderWindow& window) {
    float deltaTime = 0.0f;
    sf::Clock clock;
    for (auto i = 0; i < JUMP_FRAMES; ++i) {
        window.clear();
        deltaTime = clock.restart().asSeconds();
        m_cat->jump(deltaTime);
        m_cat->drawJump(window);
        window.display();
    }
}
//=============================================================================
void Board::nextLevel(int difficulty) {
    clearBoard();
    m_cat->newLevel(getTile(CAT_START));
    randomLava(DIFFICULTIES[difficulty]);
}
//=============================================================================
