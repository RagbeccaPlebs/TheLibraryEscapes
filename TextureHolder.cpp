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

	map<string, Texture>::iterator keyValuePair = m.find(filename);

	if (keyValuePair != m.end()) {
		//Found! So return
		return keyValuePair->second;
	}
	else {
		//Load file
		Texture& texture = m[filename];
		texture.loadFromFile(filename);

		return texture;
	}
}
