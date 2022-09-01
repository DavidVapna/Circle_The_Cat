#include "Resources.h"
//-----------------------------------------------------------------------------
//
using TexturePair = std::pair<ResourceName, sf::Texture>;
//-----------------------------------------------------------------------------
//
Resources::Resources()
{
    srand((unsigned int)time(NULL));
    loadTextures();
    m_gameFont.loadFromFile("font.ttf");

}
//-----------------------------------------------------------------------------
//
void Resources::loadTextures()
{
    m_textures.insert(TexturePair(ResourceName::Grass, loadSfObj<sf::Texture>("grass.png")));
    m_textures.insert(TexturePair(ResourceName::Lava, loadSfObj<sf::Texture>("lava.png")));
    m_textures.insert(TexturePair(ResourceName::BackG, loadSfObj<sf::Texture>("gameBG.png")));
    m_textures.insert(TexturePair(ResourceName::IdleCat, loadSfObj<sf::Texture>("idleDino.png")));
    m_textures.insert(TexturePair(ResourceName::JumpCat, loadSfObj<sf::Texture>("jumpDino.png")));
}
//-----------------------------------------------------------------------------
//
const sf::Texture& Resources::getTexture(const ResourceName& wantedTexture) const
{
    auto tex = m_textures.find(wantedTexture);
    if (tex != m_textures.end()) return tex->second;
    throw std::out_of_range("Texture not found.");
}
//-----------------------------------------------------------------------------
//
const sf::Font& Resources::getFont() const
{
    return m_gameFont;
}
//-----------------------------------------------------------------------------
//
Resources::~Resources()
{
    m_textures.clear();
    m_soundsBuffer.clear();
    m_soundEffects.clear();
}
//-----------------------------------------------------------------------------
//
Resources& Resources::instance()
{
    static Resources inst;
    return inst;
}
//-----------------------------------------------------------------------------
//
int Resources::randomNumber(const V2U& difficulty)
{
    return difficulty.x + (rand() % static_cast<int>(difficulty.y - difficulty.x + 1));
}
//-----------------------------------------------------------------------------
//
void Resources::triggerSound(int theSound)
{
    m_soundEffects[theSound].setVolume(100.f);
    m_soundEffects[theSound].setLoop(false);
    m_soundEffects[theSound].play();
}
//-----------------------------------------------------------------------------
//