#include "Player.h"
#include "PlayerTexture.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <filesystem>
#include <future> 

#include "Constants.h"
#include "TextureHolder.h"

using json = nlohmann::json;
using namespace std;
using namespace sf;

void Player::SetInitialTextures()
{
	ifstream file(Files::GAME_DATA_FILE);
	json data = json::parse(file);
	file.close();

	string playerBaseTextureLocation = data.at(Keywords::PLAYER_KEYWORD).at(Keywords::PLAYER_BASE_KEYWORD);
	string playerLowerTextureLocation = data.at(Keywords::PLAYER_KEYWORD).at(Keywords::PLAYER_LOWER_LAYER_KEYWORD);
	string playerCloakTextureLocation = data.at(Keywords::PLAYER_KEYWORD).at(Keywords::PLAYER_CLOAK_KEYWORD);
	string playerFaceTextureLocation = data.at(Keywords::PLAYER_KEYWORD).at(Keywords::PLAYER_FACE_ITEM_KEYWORD);
	string playerHairTextureLocation = data.at(Keywords::PLAYER_KEYWORD).at(Keywords::PLAYER_HAIR_KEYWORD);
	string playerHatTextureLocation = data.at(Keywords::PLAYER_KEYWORD).at(Keywords::PLAYER_HAT_KEYWORD);

	if (!playerBaseTextureLocation.empty())
	{
		m_TextureBaseLocation = Files::BASE_PLAYER_GRAPHICS_FOLDER + playerBaseTextureLocation;
	}

	if (!playerLowerTextureLocation.empty())
	{
		m_TextureLowerLayerLocation = Files::LOWER_LAYER_PLAYER_GRAPHICS_FOLDER + playerLowerTextureLocation;
	}

	if (!playerCloakTextureLocation.empty())
	{
		m_TextureCloakLocation = Files::CLOAK_PLAYER_GRAPHICS_FOLDER + playerCloakTextureLocation;
	}

	if (!playerFaceTextureLocation.empty())
	{
		m_TextureFaceItemLocation = Files::FACE_ITEM_PLAYER_GRAPHICS_FOLDER + playerFaceTextureLocation;
	}

	if (!playerHairTextureLocation.empty())
	{
		m_TextureHairLocation = Files::HAIR_PLAYER_GRAPHICS_FOLDER + playerHairTextureLocation;
	}

	if (!playerHatTextureLocation.empty())
	{
		m_TextureHatLocation = Files::HAT_ITEM_PLAYER_GRAPHICS_FOLDER + playerHatTextureLocation;
	}
}

bool PlayerTexture::LoadAllBaseTextures()
{
	const string PATH = Files::BASE_PLAYER_GRAPHICS_SEARCH_FOLDER;
	for (const auto& entry : filesystem::directory_iterator(PATH))
	{
		Texture tempTexture;
		tempTexture.loadFromFile(Files::BASE_PLAYER_GRAPHICS_FOLDER + entry.path().filename().string());
		m_BaseTextures.insert(pair<string, Texture>(Player::GetFileName(entry.path().filename().filename().generic_string()), tempTexture));
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
				return pair<string, Texture>(newFileName, textureMap.at(newFileName));
			}
			const string newFileName = keys[index + 1];

			return pair<string, Texture>(newFileName, textureMap.at(newFileName));
		}
	}
	const string fileName = Player::GetFileName(filePath);
	return pair<string, Texture>(fileName, TextureHolder::GetTexture(filePath));
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
				return pair<string, Texture>(Constant::EMPTY_STRING, textureMap.at(fileName));
			}
			const string newFileName = keys[index + 1];

			return pair<string, Texture>(newFileName, textureMap.at(newFileName));
		}
		const string newFileName = keys[0];
		return pair<string, Texture>(newFileName, textureMap.at(newFileName));
	}
	const string fileName = Player::GetFileName(filePath);
	return pair<string, Texture>(fileName, TextureHolder::GetTexture(filePath));
}

void Player::UpdatePlayerTexture(const Layer layer)
{
	switch (layer)
	{
	case BASE:
		m_TextureBaseLocation = Files::BASE_PLAYER_GRAPHICS_FOLDER + m_PlayerTexture.GetNextTexture(m_PlayerTexture.GetBaseTextureMap(), m_TextureBaseLocation).first;
		if (!GetFileName(m_TextureBaseLocation).empty())
		{
			m_SpriteBase = Sprite(TextureHolder::GetTexture(m_TextureBaseLocation));
		}
		break;
	case LOWER:
		m_TextureLowerLayerLocation = Files::LOWER_LAYER_PLAYER_GRAPHICS_FOLDER + m_PlayerTexture.GetNextTexture(m_PlayerTexture.GetLowerTextureMap(), m_TextureLowerLayerLocation).first;
		if (!GetFileName(m_TextureLowerLayerLocation).empty())
		{
			m_SpriteLowerLayer = Sprite(TextureHolder::GetTexture(m_TextureLowerLayerLocation));
		}
		break;
	case CLOAK:
		m_TextureCloakLocation = Files::CLOAK_PLAYER_GRAPHICS_FOLDER + m_PlayerTexture.GetNextTextureWithNone(m_PlayerTexture.GetCloakTextureMap(), m_TextureCloakLocation).first;
		if (!GetFileName(m_TextureCloakLocation).empty())
		{
			m_SpriteCloak = Sprite(TextureHolder::GetTexture(m_TextureCloakLocation));
		}
		else
		{
			m_SpriteCloak = Sprite();
		}
		break;
	case FACE_ITEM:
		m_TextureFaceItemLocation = Files::FACE_ITEM_PLAYER_GRAPHICS_FOLDER + m_PlayerTexture.GetNextTextureWithNone(m_PlayerTexture.GetFaceTextureMap(), m_TextureFaceItemLocation).first;
		if (!GetFileName(m_TextureFaceItemLocation).empty())
		{
			m_SpriteFaceItem = Sprite(TextureHolder::GetTexture(m_TextureFaceItemLocation));
		}
		else
		{
			m_SpriteFaceItem = Sprite();
		}
		break;
	case HAIR:
		m_TextureHairLocation = Files::HAIR_PLAYER_GRAPHICS_FOLDER + m_PlayerTexture.GetNextTextureWithNone(m_PlayerTexture.GetHairTextureMap(), m_TextureHairLocation).first;
		if (!GetFileName(m_TextureHairLocation).empty())
		{
			m_SpriteHair = Sprite(TextureHolder::GetTexture(m_TextureHairLocation));
		}
		else
		{
			m_SpriteHair = Sprite();
		}
		break;
	case HAT:
		m_TextureHatLocation = Files::HAT_ITEM_PLAYER_GRAPHICS_FOLDER + m_PlayerTexture.GetNextTextureWithNone(m_PlayerTexture.GetHatTextureMap(), m_TextureHatLocation).first;
		if (!GetFileName(m_TextureHatLocation).empty())
		{
			m_SpriteHat = Sprite(TextureHolder::GetTexture(m_TextureHatLocation));
		}
		else
		{
			m_SpriteHat = Sprite();
		}
		break;
	}

	SetPositionAllSprites();
}

void Player::SaveLayers()
{
	ifstream oldFile(Files::GAME_DATA_FILE);
	nlohmann::json data = json::parse(oldFile);
	oldFile.close();
	json playerValues;

	data[Keywords::PLAYER_KEYWORD][Keywords::PLAYER_BASE_KEYWORD] = GetFileName(m_TextureBaseLocation);
	data[Keywords::PLAYER_KEYWORD][Keywords::PLAYER_LOWER_LAYER_KEYWORD] = GetFileName(m_TextureLowerLayerLocation);
	data[Keywords::PLAYER_KEYWORD][Keywords::PLAYER_CLOAK_KEYWORD] = GetFileName(m_TextureCloakLocation);
	data[Keywords::PLAYER_KEYWORD][Keywords::PLAYER_FACE_ITEM_KEYWORD] = GetFileName(m_TextureFaceItemLocation);
	data[Keywords::PLAYER_KEYWORD][Keywords::PLAYER_HAIR_KEYWORD] = GetFileName(m_TextureHairLocation);
	data[Keywords::PLAYER_KEYWORD][Keywords::PLAYER_HAT_KEYWORD] = GetFileName(m_TextureHatLocation);

	std::ofstream newFile(Files::GAME_DATA_FILE);
	newFile << data;
	newFile.flush();
}

string Player::GetFileName(const string& fileLocation)
{
	if (!fileLocation.empty())
	{
		const size_t found = fileLocation.find_last_of(Files::CHAR_SLASH);
		return fileLocation.substr(found + 1);
	}
	return Constant::EMPTY_STRING;
}

