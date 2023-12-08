#include "FontHolder.h"
#include <cassert>

using namespace sf;
using namespace std;

FontHolder* FontHolder::m_s_Instance = nullptr;

FontHolder::FontHolder()
{
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

Font& FontHolder::GetTexture(string const& filename) {
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
