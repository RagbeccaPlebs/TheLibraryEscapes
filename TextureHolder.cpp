//This is copied from Beginning C++ Game Programming by John Horton (2nd edition).

#include "TextureHolder.h"
#include <cassert>

using namespace sf;
using namespace std;

TextureHolder* TextureHolder::m_SingleInstance = nullptr;

TextureHolder::TextureHolder()
{
	assert(m_SingleInstance == nullptr);
	m_SingleInstance = this;
}

Texture& TextureHolder::GetTexture(string const& filename) {
	map<string, Texture>& m = m_SingleInstance->m_Textures;

	const auto keyValuePair = m.find(filename);

	if (keyValuePair != m.end()) {
		return keyValuePair->second;
	}
	//Load file since not found yet
	Texture& texture = m[filename];
	texture.loadFromFile(filename);

	return texture;
}
