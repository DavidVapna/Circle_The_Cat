//=============================================================================
#include "Board.h"
//=============================================================================
//Board C-Tor, initializing the game board by loading the tile objects according
//to the defined game board size.
Board::Board()
{
    for (unsigned row = 0; row < TILES_IN_COL; row++)
    {
        std::vector<Tile> tempRow;
        sf::Vector2f tilePos(BOARD_START.x + ((row % 2) * TILE_SIZE.x / 2), (float)(row * TILE_SIZE.y) + BOARD_START.y);
        for (unsigned col = 0; col < TILES_IN_ROW; col++)
        {
            bool lossingTile = (col == 0 || row == 0 || col == TILES_IN_ROW - 1 || row == TILES_IN_COL - 1);
            tempRow.emplace_back(Tile(Positions(sf::Vector2u{ row,col }, tilePos), lossingTile));
            tilePos.x += TILE_SIZE.x;
        }
        m_board.push_back(tempRow);
    }
    setAdjacents();
    m_board[CAT_START.x][CAT_START.y].catHere();
}
//=============================================================================
//this function helps us keep track on the adjacent tiles of each tile, that 
//way we the cat can use the this information to use as a tree and use BFS on it.
void Board::setAdjacents()
{
    for (int row = 0; row < TILES_IN_ROW; row++)
        for (int col = 0; col < TILES_IN_COL; col++)
        {
            std::list<sf::Vector2u> currAdj;
            if (row % 2 == 0 && col > 0 && row > 0)
            {
                currAdj.push_back(sf::Vector2u(row - 1, col - 1));
                if (row < TILES_IN_ROW - 1)
                    currAdj.push_back(sf::Vector2u(row + 1, col - 1));
            }
            else if (col < TILES_IN_COL - 1 && row < TILES_IN_ROW - 1)
            {
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
//
void Board::clearBoard()
{
    for(auto& row : m_board)
        for (auto& tile : row)
        {
            tile.catLeft();
            tile.setPassable();
        }
}
//=============================================================================
//
void Board::randomLava(const sf::Vector2u& difficulty)
{
    auto numOfLava = Resources::instance().randomNumber(difficulty);
    srand((unsigned int)time(NULL));

    for (int counter = 0; counter < numOfLava; counter++)
    {

        sf::Vector2u tile(rand() % TILES_IN_COL, rand() % TILES_IN_ROW);
        if (!m_board[tile.x][tile.y].isCatHere() && m_board[tile.x][tile.y].setLava());
    }
}
//=============================================================================
//
bool Board::mouseClicked(const sf::Vector2f& mousePos)
{
    for (int i = 0; i < m_board.size(); i++)
        for (int j = 0; j < m_board[i].size(); j++)
            if (m_board[i][j].setLava(mousePos))
            {
                m_clickRoute.push_front(sf::Vector2i(i, j));
                return true;
            }
    return false;
}
//=============================================================================
//
void Board::draw(sf::RenderWindow& window) const
{
    for (auto& row : m_board)
        for (auto& tile : row)
            tile.draw(window);
}
//=============================================================================
//
bool Board::undo()
{
    if (m_clickRoute.empty())
        return false;
    else {
        m_board[m_clickRoute.front().x][m_clickRoute.front().y].setPassable();
        m_clickRoute.pop_front();
    }
        return true;
}
//=============================================================================
//
bool Board::findExit(const sf::Vector2u& theCat)
{
    m_board[theCat.x][theCat.y].setVisit();
    std::vector<std::pair<sf::Vector2u, sf::Vector2u>> queue;
    queue.push_back(std::make_pair(theCat, sf::Vector2u{}));
    bool found = false;
    std::list<sf::Vector2u> escapeRoute;

    searchRoute(queue, found);
    if (found)
        setEscapeRoute(queue, escapeRoute);
    else
        senselessRoute(theCat, found);
    
    return found;
}
//=============================================================================
//
void Board::searchRoute(std::vector<std::pair<sf::Vector2u, sf::Vector2u>>& queue, bool &found)
{
    for (int i = 0; i < queue.size() && !found; ++i)
    {
        for (auto adjecent : m_board[queue[i].first.x][queue[i].first.y].getAdjacents())
        {
            if (m_board[adjecent.x][adjecent.y].isPassable() && !m_board[adjecent.x][adjecent.y].visited())
            {
                queue.push_back(std::make_pair(adjecent, queue[i].first));
                if (m_board[adjecent.x][adjecent.y].isLossing())
                {found = true; break;}
                m_board[adjecent.x][adjecent.y].setVisit();
            }
        }
    }
    for (auto& row : m_board)
        for (auto& tile : row)
            tile.resetVisit();
}
//=============================================================================
//
bool Board::validateRoute() const
{
    if (m_escapeRoute.empty())
        return false;

    for (auto& tile : m_escapeRoute)
    {
        if (!m_board[tile.x][tile.y].isPassable())
            return false;
    }
    return true;
}
//=============================================================================
//
void Board::setEscapeRoute(std::vector<std::pair<sf::Vector2u, sf::Vector2u>>& queue, std::list<sf::Vector2u>& route)
{
    route.push_back(queue.back().first);
    for (auto i = --queue.end(); i != queue.begin(); --i)
    {
        if (i->first == route.back())
            route.push_back(i->second);
    }
    route.pop_back();
    m_escapeRoute = route;
}
//=============================================================================
//
void Board::senselessRoute(const sf::Vector2u& theCat, bool &found)
{
    for (auto adjecent : m_board[theCat.x][theCat.y].getAdjacents())
        if (m_board[adjecent.x][adjecent.y].isPassable())
        {
            m_escapeRoute.push_back(adjecent);
            found = true;
            break;
        }
}
//=============================================================================
//
Tile& Board::getTile(sf::Vector2u wantedTile) 
{
    return m_board[wantedTile.x][wantedTile.y];
}
//=============================================================================
//
Tile& Board::escapeTile()
{
    auto nextTile = m_escapeRoute.back();
    m_escapeRoute.pop_back();
    return m_board[nextTile.x][nextTile.y];
}
//=============================================================================