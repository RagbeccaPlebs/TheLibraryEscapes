
#include "PlayerTexture.h"

#include <filesystem>
#include <string>
#include <SFML/Graphics/Texture.hpp>

#include "Constants.h"
#include "Player.h"
#include <future>

#include "TextureHolder.h"

using namespace sf;
using namespace std;

bool PlayerTexture::LoadAllBaseTextures()
{
	const std::string PATH = Files::BASE_PLAYER_GRAPHICS_SEARCH_FOLDER;
	for (const auto& entry : filesystem::directory_iterator(PATH))
	{
		Texture tempTexture;
		tempTexture.loadFromFile(Files::BASE_PLAYER_GRAPHICS_FOLDER + entry.path().filename().string());
		m_BaseTextures.insert(std::pair<string, Texture>(Player::GetFileName(entry.path().filename().filename().generic_string()), tempTexture));
	}
	return true;
}


bool PlayerTexture::LoadAllLowerTextures()
{
	const string PATH = Files::LOWER_LAYER_PLAYER_GRAPHICS_SEARCH_FOLDER;
	for (const auto& entry : filesystem::directory_iterator(PATH))
	{
		Texture tempTexture;
		tempTexture.loadFromFile(Files::LOWER_LAYER_PLAYER_GRAPHICS_FOLDER + entry.path().filename().string());
		m_LowerTextures.insert(pair<string, Texture>(entry.path().filename().filename().generic_string(), tempTexture));
	}
	return true;
}

bool PlayerTexture::LoadAllCloakTextures()
{
	const string PATH = Files::CLOAK_PLAYER_GRAPHICS_SEARCH_FOLDER;
	for (const auto& entry : filesystem::directory_iterator(PATH))
	{
		Texture tempTexture;
		tempTexture.loadFromFile(Files::CLOAK_PLAYER_GRAPHICS_FOLDER + entry.path().filename().string());
		m_CloakTextures.insert(pair<string, Texture>(entry.path().filename().filename().generic_string(), tempTexture));
	}
	return true;
}

bool PlayerTexture::LoadAllFaceTextures()
{
	const string PATH = Files::FACE_ITEM_PLAYER_GRAPHICS_SEARCH_FOLDER;
	for (const auto& entry : filesystem::directory_iterator(PATH))
	{
		Texture tempTexture;
		tempTexture.loadFromFile(Files::FACE_ITEM_PLAYER_GRAPHICS_FOLDER + entry.path().filename().string());
		m_FaceTextures.insert(pair<string, Texture>(entry.path().filename().filename().generic_string(), tempTexture));
	}
	return true;
}

bool PlayerTexture::LoadAllHairTextures()
{
	const string PATH = Files::HAIR_PLAYER_GRAPHICS_SEARCH_FOLDER;
	for (const auto& entry : filesystem::directory_iterator(PATH))
	{
		Texture tempTexture;
		tempTexture.loadFromFile(Files::HAIR_PLAYER_GRAPHICS_FOLDER + entry.path().filename().string());
		m_HairTextures.insert(pair<string, Texture>(entry.path().filename().filename().generic_string(), tempTexture));
	}
	return true;
}

bool PlayerTexture::LoadAllHatTextures()
{
	const string PATH = Files::HAT_ITEM_PLAYER_GRAPHICS_SEARCH_FOLDER;
	for (const auto& entry : filesystem::directory_iterator(PATH))
	{
		Texture tempTexture;
		tempTexture.loadFromFile(Files::HAT_ITEM_PLAYER_GRAPHICS_FOLDER + entry.path().filename().string());
		m_HatTextures.insert(pair<string, Texture>(entry.path().filename().filename().generic_string(), tempTexture));
	}
	return true;
}

bool PlayerTexture::LoadAllFiles()
{
	future<bool> isBaseLoadedFuture = std::async(&PlayerTexture::LoadAllBaseTextures, this);
	future<bool> isLowerLayerLoadedFuture = std::async(&PlayerTexture::LoadAllLowerTextures, this);
	future<bool> isCloakLayerLoadedFuture = std::async(&PlayerTexture::LoadAllCloakTextures, this);
	future<bool> isFaceItemLayerLoadedFuture = std::async(&PlayerTexture::LoadAllFaceTextures, this);
	future<bool> isHairLayerLoadedFuture = std::async(&PlayerTexture::LoadAllHairTextures, this);
	future<bool> isHatLayerLoadedFuture = std::async(&PlayerTexture::LoadAllHatTextures, this);

	return isBaseLoadedFuture.get() && isLowerLayerLoadedFuture.get() && isCloakLayerLoadedFuture.get() && isFaceItemLayerLoadedFuture.get() && isHairLayerLoadedFuture.get() && isHatLayerLoadedFuture.get();
}

void PlayerTexture::CleanAllFiles()
{
	m_BaseTextures.clear();
	m_LowerTextures.clear();
	m_CloakTextures.clear();
	m_FaceTextures.clear();
	m_HairTextures.clear();
	m_HatTextures.clear();
}

const map<string, Texture>& PlayerTexture::GetBaseTextureMap() const
{
	return m_BaseTextures;
}

const map<string, Texture>& PlayerTexture::GetLowerTextureMap() const
{
	return m_LowerTextures;
}

const map<string, Texture>& PlayerTexture::GetCloakTextureMap() const
{
	return m_CloakTextures;
}

const map<string, Texture>& PlayerTexture::GetFaceTextureMap() const
{
	return m_FaceTextures;
}

const map<string, Texture>& PlayerTexture::GetHairTextureMap() const
{
	return m_HairTextures;
}

const map<string, Texture>& PlayerTexture::GetHatTextureMap() const
{
	return m_HatTextures;
}

std::pair<std::string, sf::Texture> PlayerTexture::GetNextTexture(const map<string, Texture>& textureMap, const std::string& filePath)
{
	if (!textureMap.empty())
	{
		vector<string> keys;
		for (const pair<string, Texture> entry : textureMap) {
			keys.push_back(entry.first);
		}

		const string fileName = Player::GetFileName(filePath);

		const auto it = ranges::find(keys.begin(), keys.end(), fileName);

		// If element was found 
		if (it != keys.end())
		{
			const int index = it - keys.begin();
			if (static_cast<size_t>(index) == keys.size() - 1)
			{
				const string newFileName = keys[0];
				return pair<string, Texture>{newFileName, textureMap.at(newFileName)};
			}
			const string newFileName = keys[index + 1];

			return pair<string, Texture>{newFileName, textureMap.at(newFileName)};
		}
	}
	const string fileName = Player::GetFileName(filePath);
	return pair<string, Texture>{fileName, TextureHolder::GetTexture(filePath)};
}

std::pair<std::string, sf::Texture> PlayerTexture::GetNextTextureWithNone(const map<string, Texture>& textureMap, const std::string& filePath)
{
	if (!textureMap.empty())
	{
		vector<string> keys;
		for (const pair<string, Texture> entry : textureMap) {
			keys.push_back(entry.first);
		}

		const string fileName = Player::GetFileName(filePath);

		const auto it = ranges::find(keys.begin(), keys.end(), fileName);

		// If element was found 
		if (it != keys.end())
		{
			const int index = it - keys.begin();
			if (static_cast<size_t>(index) == keys.size() - 1)
			{
				return pair<string, Texture>{Constant::EMPTY_STRING, textureMap.at(fileName)};
			}
			const string newFileName = keys[index + 1];

			return pair<string, Texture>{newFileName, textureMap.at(newFileName)};
		}
		const string newFileName = keys[0];
		return pair<string, Texture>{newFileName, textureMap.at(newFileName)};
	}
	const string fileName = Player::GetFileName(filePath);
	return pair<string, Texture>{fileName, TextureHolder::GetTexture(filePath)};
}
