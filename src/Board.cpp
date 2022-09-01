#include "Board.h"
//-----------------------------------------------------------------------------
//
Board::Board()
{
    for (unsigned row = 0; row < TILES_IN_COL; row++)
    {
        std::vector<Tile> tempRow;
        V2F tilePos(BOARD_START.x + ((row % 2) * TILE_SIZE.x / 2), (float)(row * TILE_SIZE.y) + BOARD_START.y);
        for (unsigned col = 0; col < TILES_IN_ROW; col++)
        {
            bool lossingTile = (col == 0 || row == 0 || col == TILES_IN_ROW - 1 || row == TILES_IN_COL - 1);
            tempRow.emplace_back(Tile(Positions(V2U{ row,col }, tilePos), lossingTile));
            tilePos.x += TILE_SIZE.x;
        }
        m_board.push_back(tempRow);
    }
    setAdjacents();
    m_board[CAT_START.x][CAT_START.y].catHere();
}
//-----------------------------------------------------------------------------
//
void Board::setAdjacents()
{
    for (int row = 0; row < TILES_IN_ROW; row++)
        for (int col = 0; col < TILES_IN_COL; col++)
        {
            std::list<V2U> currAdj;
            if (row % 2 == 0)
            {
                if (col > 0 && row > 0)
                {
                    currAdj.push_back(V2U(row - 1, col - 1));
                    if (row < TILES_IN_ROW - 1) currAdj.push_back(V2U(row + 1, col - 1));
                }
            }
            else
            {
                if (col < TILES_IN_COL - 1 && row < TILES_IN_ROW - 1)
                {
                    currAdj.push_back(V2U(row + 1, col + 1));
                    if (row > 0) currAdj.push_back(V2U(row - 1, col + 1));
                }
            }
            if (col > 0) currAdj.push_back(V2U(row, col - 1));
            if (row > 0) currAdj.push_back(V2U(row - 1, col));
            if (col < TILES_IN_COL - 1) currAdj.push_back(V2U(row, col + 1));
            if (row < TILES_IN_ROW - 1) currAdj.push_back(V2U(row + 1, col));

            m_board[row][col].addAdjacents(currAdj);
        }
}
//-----------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
//
void Board::randomLava(const V2U& difficulty)
{
    auto numOfLava = Resources::instance().randomNumber(difficulty);
    srand((unsigned int)time(NULL));
    int counter = 0;

    while (counter < numOfLava)
    {
        V2U tile(rand() % TILES_IN_COL, rand() % TILES_IN_ROW);
        if (!m_board[tile.x][tile.y].isCatHere() && m_board[tile.x][tile.y].setNotPassable())
            counter++;
    }
}
//-----------------------------------------------------------------------------
//
bool Board::mouseClicked(const V2F& mousePos)
{
    for (int i = 0; i < m_board.size(); i++)
        for (int j = 0; j < m_board[i].size(); j++)
            if (m_board[i][j].handleClick(mousePos, m_lastTile))
            {
                m_lastTile = sf::Vector2i(i, j);
                return true;
            }
    return false;
}
//-----------------------------------------------------------------------------
//
void Board::draw(sf::RenderWindow& window) const
{
    for (auto& row : m_board)
        for (auto& tile : row)
            tile.draw(window);
}
//-----------------------------------------------------------------------------
//
bool Board::undo()
{
    if (m_lastTile.x > TILES_IN_ROW || m_lastTile.y > TILES_IN_COL ||
        m_lastTile.x < 0|| m_lastTile.y < 0 ) return false;
    
    m_lastTile = m_board[m_lastTile.x][m_lastTile.y].undo();
    return true;
}
//-----------------------------------------------------------------------------
//
bool Board::findExit(const V2U& theCat)
{
    m_board[theCat.x][theCat.y].setVisit();
    std::vector<std::pair<V2U, V2U>> queue;
    queue.push_back(std::make_pair(theCat, V2U{}));
    bool found = false;
    std::list<V2U> escapeRoute;

    searchRoute(queue, found);
    if (found)
        setEscapeRoute(queue, escapeRoute);
    else
        senselessRoute(theCat, found);
    
    return found;
}
//-----------------------------------------------------------------------------
//
void Board::searchRoute(std::vector<std::pair<V2U, V2U>>& queue, bool &found)
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
//-----------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
//
void Board::setEscapeRoute(std::vector<std::pair<V2U, V2U>>& queue, std::list<V2U>& route)
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
//-----------------------------------------------------------------------------
//
void Board::senselessRoute(const V2U& theCat, bool &found)
{
    for (auto adjecent : m_board[theCat.x][theCat.y].getAdjacents())
        if (m_board[adjecent.x][adjecent.y].isPassable())
        {
            m_escapeRoute.push_back(adjecent);
            found = true;
            break;
        }
}
//-----------------------------------------------------------------------------
//
Tile& Board::getTile(V2U wantedTile) 
{
    return m_board[wantedTile.x][wantedTile.y];
}
//-----------------------------------------------------------------------------
//
Tile& Board::escapeTile()
{
    auto nextTile = m_escapeRoute.back();
    m_escapeRoute.pop_back();
    return m_board[nextTile.x][nextTile.y];
}
