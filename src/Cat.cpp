#include "Cat.h"
//-----------------------------------------------------------------------------
//
Cat::Cat(Tile& startingTile)
{
    m_faceRight = true;
    m_jorney.push_back(&startingTile);
    auto& idle = Resources::instance().getTexture(ResourceName::IdleCat);
    auto& jump = Resources::instance().getTexture(ResourceName::JumpCat);
    m_idle.setTexture(idle);
    m_jump.setTexture(jump);

    m_animation.push_back(new Animation(idle, IDLE_COUNT, IDLE_SWITCH));
    m_animation.push_back(new Animation(jump, JUMP_COUNT, JUMP_SWITCH));
 

    V2F idleScale, jumpScale, deadScale;
    idleScale.x = (TILE_SIZE.x / (idle.getSize().x / IDLE_COUNT.x) * 1.4);
    idleScale.y = (TILE_SIZE.y / (idle.getSize().y / IDLE_COUNT.y) * 1.4);
    m_idle.setScale(idleScale);                                        
    jumpScale.x = (TILE_SIZE.x / (jump.getSize().x / JUMP_COUNT.x) * 1.4);
    jumpScale.y = (TILE_SIZE.y / (jump.getSize().y / JUMP_COUNT.y) * 1.4);
    m_jump.setScale(jumpScale);


    V2F idleOrg(m_idle.getGlobalBounds().height / 2, m_idle.getGlobalBounds().width / 2);
    m_idle.setOrigin(idleOrg);
    V2F jumpOrg(m_jump.getGlobalBounds().height / 2, m_jump.getGlobalBounds().width / 2);
    m_jump.setOrigin(idleOrg);
  
    m_pos = startingTile.getPos().second + LOOKING_RIGHT;

    m_idle.setPosition(m_pos);
}
//-----------------------------------------------------------------------------
Cat::~Cat()
{
    for (auto& pointer : m_animation)
        delete pointer;
}
//-----------------------------------------------------------------------------
void Cat::update(float deltaTime)
{
    m_animation[(int)State::idle]->update(deltaTime, m_faceRight);
    m_idle.setTextureRect(m_animation[(int)State::idle]->uvRect);
}
//-----------------------------------------------------------------------------
//
void Cat::draw(sf::RenderWindow& window) const
{
    window.draw(m_idle);
}
//-----------------------------------------------------------------------------
//
void Cat::drawJump(sf::RenderWindow& window) const
{
    window.draw(m_jump);
}
//-----------------------------------------------------------------------------
//
V2U Cat::getPosition() const
{
    return m_jorney.back()->getPos().first;
}
//-----------------------------------------------------------------------------
//
void Cat::tryToRun(Tile& destination)
{
    m_jorney.back()->catLeft();
    m_jorney.push_back(&destination);
    auto currPos = m_pos;

    if(!destination.isLossing())
        m_faceRight = destination.getPos().second.x > m_pos.x;
    m_faceRight ?
        m_pos = destination.getPos().second + LOOKING_RIGHT :
        m_pos = destination.getPos().second + LOOKING_LEFT;

    m_jump.setPosition(currPos);
    m_idle.setPosition(m_pos);
    
    m_frame = V2F((m_pos - currPos).x / JUMP_FRAMES, (m_pos - currPos).y / JUMP_FRAMES);

    m_jorney.back()->catHere();
}
//-----------------------------------------------------------------------------
//
void Cat::jump(float deltaTime)
{
    m_animation[(int)State::Jump]->update(deltaTime, m_faceRight);
    m_jump.setTextureRect(m_animation[(int)State::Jump]->uvRect);
    m_jump.move(m_frame);
}
//-----------------------------------------------------------------------------
//
bool Cat::didCatWin() const
{
    return m_jorney.back()->isLossing();
}
//-----------------------------------------------------------------------------
//
void Cat::undo()
{
    if (m_jorney.size() == 1)
        return;

    m_jorney.back()->catLeft();
    m_jorney.pop_back();
    m_jorney.back()->catHere();
    m_faceRight ?
        m_pos = m_jorney.back()->getPos().second + LOOKING_RIGHT :
        m_pos = m_jorney.back()->getPos().second + LOOKING_LEFT;
    m_idle.setPosition(m_pos);
}
//-----------------------------------------------------------------------------
void Cat::newLevel(Tile& startingTile)
{
    m_faceRight = true;
    startingTile.catHere();
    m_jorney.clear();
    m_jorney.push_back(&startingTile);
    m_pos = startingTile.getPos().second + LOOKING_RIGHT;
    m_idle.setPosition(m_pos);
}
//-----------------------------------------------------------------------------