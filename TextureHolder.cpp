#include "TextureHolder.h"
#include <assert.h>

using namespace sf;
using namespace std;

TextureHolder* TextureHolder::m_s_Instance = nullptr;

TextureHolder::TextureHolder()
{
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

Texture& TextureHolder::GetTexture(string const& filename) {
	map<string, Texture>& m = m_s_Instance->m_Textures;

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
