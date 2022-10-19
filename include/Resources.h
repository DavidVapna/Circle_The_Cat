//=============================================================================
#pragma once
//=============================================================================
#include <iostream>
#include <SFML\Audio.hpp>
#include <unordered_map>
#include <string>
#include <cstdlib>
#include <vector>
#include "Macros.h"
//=============================================================================
class Resources{
public:
	//public functions
	static Resources& instance();
	int randomNumber(const sf::Vector2u &difficulty) const;
	const sf::Texture& getTexture(int wantedTexture) const;
	const sf::Font& getFont(int wantedFont) const;
	void playMusic(Sounds sound);
	void playSound(Sounds sound);
	void stopMusic();
	//const AnimationInfo& getAnimInfo(int wantedInfo) const;
	~Resources();

private:
	//private functions
	Resources();
	Resources(const Resources&) = default;
	Resources& operator=(const Resources&) = default;
	void loadTextures();

	//void setTexts();
	void loadSounds();
	void loadFonts();
	void setAnimationInfo();


	template <class SfObj>
	SfObj loadSfObj(const std::string& str);
	template<class Container, class Return>
	Return findInMap(Container map, int index) const;


private:
	//private members
	//std::unordered_map <int, AnimationInfo> m_animInfo;


	std::unordered_map <int, sf::Texture> m_textures;
	std::unordered_map <int, sf::Font> m_fonts;
	std::unordered_map <int, sf::SoundBuffer> m_sounds;
	std::vector<sf::SoundBuffer> m_soundsBuffer;
	sf::Font m_gameFont;
	sf::Sound m_sound;
	sf::Music m_music;
};
//=============================================================================
//
template <class SfmlObject>
SfmlObject Resources::loadSfObj(const std::string& str)
{
	SfmlObject obj;
	if (obj.loadFromFile(str))
		return std::move(obj);
	throw std::out_of_range("Coldn't find the file");
}
//==============================================================================
//
template<class Container, class Return>
Return Resources::findInMap(Container map, int index) const
{
	auto it = map.find(index);
	if (it != map.end())
		return (it->second);
	throw std::out_of_range("Texture not found.");
}
//==============================================================================