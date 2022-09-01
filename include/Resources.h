#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Macros.h"
#include <unordered_map>
#include <string>
//-----------------------------------------------------------------------------
class Resources
{
public:
	static Resources& instance();
	const sf::Texture& getTexture(const ResourceName &wantedTexture) const;
	const sf::Font& getFont() const;
	void triggerSound(int theSound);
	int randomNumber(const V2U &difficulty);
	~Resources();

private:
	void loadTextures();
	void setTexts();



	template <class SfObj>
	SfObj loadSfObj(const std::string& str);



private:
	Resources();
	Resources(const Resources&) = default;
	Resources& operator=(const Resources&) = default;



	std::unordered_map<ResourceName, sf::Texture> m_textures;
	std::vector<sf::SoundBuffer> m_soundsBuffer;
	std::vector<sf::Sound> m_soundEffects;
	sf::Font m_gameFont;

};
//-----------------------------------------------------------------------------
template <class SfmlObject>
SfmlObject Resources::loadSfObj(const std::string& str)
{
	SfmlObject obj;
	if (obj.loadFromFile(str))
		return std::move(obj);
	throw std::out_of_range("Coldn't find the file");
}
//-----------------------------------------------------------------------------