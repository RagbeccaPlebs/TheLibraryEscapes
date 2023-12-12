#pragma once

#ifndef TEXTURE_HOLDER_H
#define TEXTURE_HOLDER_H

#include <SFML/Graphics.hpp>
#include <map>

class TextureHolder {
private:
	std::map<std::string, sf::Texture> m_Textures;

	//A pointer of the same type as the class itself
	static TextureHolder* m_SingleInstance;

public:
	TextureHolder();
	static sf::Texture& GetTexture(std::string const& filename);
};

#endif