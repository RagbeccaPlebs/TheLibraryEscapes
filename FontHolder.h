#pragma once

#ifndef FONT_HOLDER_H
#define FONT_HOLDER_H

#include <SFML/Graphics.hpp>
#include <map>

class FontHolder {
private:
	std::map<std::string, sf::Texture> m_Textures;

	//A pointer of the same type as the class itself
	static FontHolder* m_s_Instance;

public:
	FontHolder();
	static sf::Font& GetFOnt(std::string const& filename);
};

#endif