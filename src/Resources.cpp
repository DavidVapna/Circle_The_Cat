//=============================================================================
#include "Resources.h"
//=============================================================================
//using a namespace for the pair of the enum class and the texutres
//for easier readability.
using TexturePair = std::pair<int, sf::Texture>;
//=============================================================================
//when the game starts we initiate a random number generator
//loading all of the game textures and fonts since this is a singleton class.
Resources::Resources()
	:m_textures((int)Textures::MaxTextures), m_fonts((int)Fonts::MaxFonts),
	m_sounds((int)Sounds::MaxSounds), m_music()
{
	srand((unsigned int)time(NULL));

	loadTextures();
	setAnimationInfo();
	loadFonts();
	loadSounds();

	m_music.setVolume(MUSIC_VOLUME);
	m_sound.setVolume(EFFECTS_VOLUME);
}
//=============================================================================
//load all game textures
void Resources::loadTextures()
{
	m_textures[(int)Textures::Grass] = loadSfObj<sf::Texture>("grass.png");
	m_textures[(int)Textures::Lava] = loadSfObj<sf::Texture>("lava.png");
	m_textures[(int)Textures::BackG] = loadSfObj<sf::Texture>("gameBG.png");
	m_textures[(int)Textures::IdleCat] = loadSfObj<sf::Texture>("idleDino.png");
	m_textures[(int)Textures::JumpCat] = loadSfObj<sf::Texture>("jumpDino.png");
}
//=============================================================================
//load all game fonts
void Resources::loadFonts()
{
	m_fonts[(int)Fonts::Classic] = loadSfObj<sf::Font>("font.ttf");
}
//=============================================================================
//
void Resources::loadSounds()
{
	//m_sounds[(int)Sounds::Jump] = loadSfObj<sf::SoundBuffer>("jump.wav");
}
//=============================================================================
//returning a reference to the texture.
const sf::Texture& Resources::getTexture(int wantedTexture) const
{
	auto it = m_textures.find(wantedTexture);
	if (it != m_textures.end())
		return it->second;
	throw std::out_of_range("Texture not found.");
}
//=============================================================================
//D-tor
Resources::~Resources()
{
    m_textures.clear();
	m_fonts.clear();
    m_soundsBuffer.clear();
    m_sounds.clear();
}
//=============================================================================
//
Resources& Resources::instance()
{
    static Resources inst;
    return inst;
}
//=============================================================================
//
int Resources::randomNumber(const sf::Vector2u& difficulty) const
{
    return difficulty.x + (rand() % static_cast<int>(difficulty.y - difficulty.x + 1));
}
//=============================================================================
// 
void Resources::playMusic(Sounds sound)
{
	switch (sound)
	{
	case Sounds::Theme:
		m_music.openFromFile("theme.wav");
		break;
	}
	m_music.play();
	m_music.setLoop(true);
}
//=============================================================================
//
void Resources::stopMusic()
{
	m_music.stop();
}
//=============================================================================
// 
void Resources::playSound(Sounds sound)
{
	m_sound.setBuffer(m_sounds.find((int)sound)->second);
	m_sound.play();
}
//=============================================================================
//const AnimationInfo& Resources::getAnimInfo(int wantedInfo) const
//{
//	auto it = m_animInfo.find(wantedInfo);
//	if (it != m_animInfo.end())
//		return it->second;
//	throw std::out_of_range("Animation Info not found");
//}

//=============================================================================
//
void Resources::setAnimationInfo()
{
	//m_animInfo[(int)Animations::DOROTHY_WALK_R] = AnimationInfo(sf::Vector2i(0, 0), sf::Vector2i(7, 0), sf::Vector2f(37.5f, 60));
	//m_animInfo[(int)Animations::BLOCK] = AnimationInfo(sf::Vector2i(0, 0), sf::Vector2i(0, 0), sf::Vector2f(1280.f, 668.f));
	//m_animInfo[(int)Animations::Glinda] = AnimationInfo(sf::Vector2i(0, 10), sf::Vector2i(8, 10), sf::Vector2f(64.f, 64.f));
	//m_animInfo[(int)Animations::RANDOM_L] = AnimationInfo(sf::Vector2i(0, 0), sf::Vector2i(3, 0), sf::Vector2f(46.75f, 33.f));
	//m_animInfo[(int)Animations::RANDOM_R] = AnimationInfo(sf::Vector2i(0, 1), sf::Vector2i(3, 1), sf::Vector2f(46.75f, 33.f));
	//m_animInfo[(int)Animations::REDHEELS] = AnimationInfo(sf::Vector2i(0, 0), sf::Vector2i(0, 0), sf::Vector2f(360.f, 360.f));
	//m_animInfo[(int)Animations::Portal] = AnimationInfo(sf::Vector2i(0, 0), sf::Vector2i(0, 0), sf::Vector2f(306, 165.f));
}
//=============================================================================
//returning a reference to the font requrired.
const sf::Font& Resources::getFont(int index) const
{
	auto it = m_fonts.find(index);
	if (it != m_fonts.end())
		return it->second;
	throw std::out_of_range("Font not found.");
}
