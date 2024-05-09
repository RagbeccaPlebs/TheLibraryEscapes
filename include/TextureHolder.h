#pragma once

//This is copied from Beginning C++ Game Programming by John Horton (2nd edition).

#include <SFML/Graphics.hpp>
#include <map>

class TextureHolder
{
	std::map<std::string, sf::Texture> m_Textures;

	//A pointer of the same type as the class itself
	static TextureHolder* m_SingleInstance;

public:
	TextureHolder();
	static sf::Texture& GetTexture(std::string const& filename);
};