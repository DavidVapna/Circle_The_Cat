//=============================================================================
#include "Cat.h"
#include "Tile.h"
#include "Animation.h"
//=============================================================================
//
Cat::Cat(Tile& startingTile)
    :m_faceRight(true){
    m_visitedTiles.push_back(&startingTile);
    auto& idle = Resources::instance().getTexture((int)Textures::IdleCat);
    auto& jump = Resources::instance().getTexture((int)Textures::JumpCat);
    m_idle.setTexture(idle);
    m_jump.setTexture(jump);
    m_animation.push_back(new Animation(idle, IDLE_COUNT, IDLE_SWITCH));
    m_animation.push_back(new Animation(jump, JUMP_COUNT, JUMP_SWITCH));

    sf::Vector2f idleScale, jumpScale, deadScale;
    idleScale.x = (TILE_SIZE.x / (idle.getSize().x / IDLE_COUNT.x) * 1.4);
    idleScale.y = (TILE_SIZE.y / (idle.getSize().y / IDLE_COUNT.y) * 1.4);
    m_idle.setScale(idleScale);                                        
    jumpScale.x = (TILE_SIZE.x / (jump.getSize().x / JUMP_COUNT.x) * 1.4);
    jumpScale.y = (TILE_SIZE.y / (jump.getSize().y / JUMP_COUNT.y) * 1.4);
    m_jump.setScale(jumpScale);


    sf::Vector2f idleOrg(m_idle.getGlobalBounds().height / 2, m_idle.getGlobalBounds().width / 2);
    m_idle.setOrigin(idleOrg);
    sf::Vector2f jumpOrg(m_jump.getGlobalBounds().height / 2, m_jump.getGlobalBounds().width / 2);
    m_jump.setOrigin(idleOrg);
  
    m_pos = startingTile.getPos().second + LOOKING_RIGHT;

    m_idle.setPosition(m_pos);
}
//=============================================================================
Cat::~Cat(){
    for (auto& pointer : m_animation)
        delete pointer;
}
//=============================================================================
void Cat::update(float deltaTime){
    m_animation[(int)State::idle]->update(deltaTime, m_faceRight);
    m_idle.setTextureRect(m_animation[(int)State::idle]->uvRect);
}
//=============================================================================
//
void Cat::draw(sf::RenderWindow& window) const{
    window.draw(m_idle);
}
//=============================================================================
//
void Cat::drawJump(sf::RenderWindow& window) const{
    window.draw(m_jump);
}
//=============================================================================
//
sf::Vector2u Cat::getPosition() const{
    return m_visitedTiles.back()->getPos().first;
}
//=============================================================================
//
void Cat::tryToRun(Tile& destination){
    m_visitedTiles.back()->catLeft();
    m_visitedTiles.push_back(&destination);
    auto currPos = m_pos;

    if(!destination.isLossing())
        m_faceRight = destination.getPos().second.x > m_pos.x;
    m_faceRight ?
        m_pos = destination.getPos().second + LOOKING_RIGHT :
        m_pos = destination.getPos().second + LOOKING_LEFT;

    m_jump.setPosition(currPos);
    m_idle.setPosition(m_pos);
    
    m_frame = sf::Vector2f((m_pos - currPos).x / JUMP_FRAMES, (m_pos - currPos).y / JUMP_FRAMES);

    m_visitedTiles.back()->catHere();
}
//=============================================================================
//
void Cat::jump(float deltaTime){
    m_animation[(int)State::Jump]->update(deltaTime, m_faceRight);
    m_jump.setTextureRect(m_animation[(int)State::Jump]->uvRect);
    m_jump.move(m_frame);
}
//=============================================================================
//
bool Cat::didCatWin() const{
    return m_visitedTiles.back()->isLossing();
}
//=============================================================================
//
void Cat::undo(){
    if (m_visitedTiles.size() == 1)
        return;

    m_visitedTiles.back()->catLeft();
    m_visitedTiles.pop_back();
    m_visitedTiles.back()->catHere();
    m_faceRight ?
        m_pos = m_visitedTiles.back()->getPos().second + LOOKING_RIGHT :
        m_pos = m_visitedTiles.back()->getPos().second + LOOKING_LEFT;
    m_idle.setPosition(m_pos);
}
//=============================================================================
void Cat::newLevel(Tile& startingTile){
    m_faceRight = true;
    startingTile.catHere();
    m_visitedTiles.clear();
    m_visitedTiles.push_back(&startingTile);
    m_pos = startingTile.getPos().second + LOOKING_RIGHT;
    m_idle.setPosition(m_pos);
}
//=============================================================================
bool Cat::findExit(std::vector<std::vector<Tile>> &gameBoard) {
    getTile(theCat).setVisit();
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