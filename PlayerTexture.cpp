#include "Player.h"
#include "PlayerTexture.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <filesystem>
#include <future> 

#include "TextureHolder.h"

using json = nlohmann::json;
using namespace std;
using namespace sf;

void Player::SetInitialTextures()
{
	const string FILE_LOCATION = "assets/save/player.json";
	ifstream file(FILE_LOCATION);
	if (!file || file.peek() == ifstream::traits_type::eof())
	{
		json jsonFile;

		jsonFile["playerBase"] = "char_a_p1_0bas_humn_v00.png";
		jsonFile["playerLower"] = "char_a_p1_1out_pfpn_v01.png";
		jsonFile["playerCloak"] = "char_a_p1_2clo_lnpl_v07.png";
		jsonFile["playerFace"] = "";
		jsonFile["playerHair"] = "";
		jsonFile["playerHat"] = "char_a_p1_5hat_pnty_v03.png";

		std::ofstream newFile(FILE_LOCATION);
		newFile << jsonFile;
		m_TextureBaseLocation = "assets/graphics/player/base/char_a_p1_0bas_humn_v00.png";
		m_TextureLowerLayerLocation = "assets/graphics/player/lower/char_a_p1_1out_pfpn_v01.png";
		m_TextureCloakLocation = "assets/graphics/player/cloak/char_a_p1_2clo_lnpl_v07.png";
		m_TextureHatLocation = "assets/graphics/player/hat/char_a_p1_5hat_pnty_v03.png";
		return;
	}

	json data = json::parse(file);
	file.close();

	string playerBaseTextureLocation = data.at("playerBase");
	string playerLowerTextureLocation = data.at("playerLower");
	string playerCloakTextureLocation = data.at("playerCloak");
	string playerFaceTextureLocation = data.at("playerFace");
	string playerHairTextureLocation = data.at("playerHair");
	string playerHatTextureLocation = data.at("playerHat");

	if (!playerBaseTextureLocation.empty())
	{
		m_TextureBaseLocation = "assets/graphics/player/base/" + playerBaseTextureLocation;
	}

	if (!playerLowerTextureLocation.empty())
	{
		m_TextureLowerLayerLocation = "assets/graphics/player/lower/" + playerLowerTextureLocation;
	}

	if (!playerCloakTextureLocation.empty())
	{
		m_TextureCloakLocation = "assets/graphics/player/cloak/" + playerCloakTextureLocation;
	}

	if (!playerFaceTextureLocation.empty())
	{
		m_TextureFaceItemLocation = "assets/graphics/player/face/" + playerFaceTextureLocation;
	}

	if (!playerHairTextureLocation.empty())
	{
		m_TextureHairLocation = "assets/graphics/player/hair/" + playerHairTextureLocation;
	}

	if (!playerHatTextureLocation.empty())
	{
		m_TextureHatLocation = "assets/graphics/player/hat/" + playerHatTextureLocation;
	}
}

bool PlayerTexture::LoadAllBaseTextures()
{
	const string PATH = "assets/graphics/player/base";
	for (const auto& entry : filesystem::directory_iterator(PATH))
	{
		Texture tempTexture;
		tempTexture.loadFromFile(PATH + "/" + entry.path().filename().string());
		m_BaseTextures.insert(pair<string, Texture>(Player::GetFileName(entry.path().filename().filename().generic_string()), tempTexture));
	}
	return true;
}


bool PlayerTexture::LoadAllLowerTextures()
{
	const string PATH = "assets/graphics/player/lower";
	for (const auto& entry : filesystem::directory_iterator(PATH))
	{
		Texture tempTexture;
		tempTexture.loadFromFile(PATH + "/" + entry.path().filename().string());
		m_LowerTextures.insert(pair<string, Texture>(entry.path().filename().filename().generic_string(), tempTexture));
	}
	return true;
}

bool PlayerTexture::LoadAllCloakTextures()
{
	const string PATH = "assets/graphics/player/cloak";
	for (const auto& entry : filesystem::directory_iterator(PATH))
	{
		Texture tempTexture;
		tempTexture.loadFromFile(PATH + "/" + entry.path().filename().string());
		m_CloakTextures.insert(pair<string, Texture>(entry.path().filename().filename().generic_string(), tempTexture));
	}
	return true;
}

bool PlayerTexture::LoadAllFaceTextures()
{
	const string PATH = "assets/graphics/player/face";
	for (const auto& entry : filesystem::directory_iterator(PATH))
	{
		Texture tempTexture;
		tempTexture.loadFromFile(PATH + "/" + entry.path().filename().string());
		m_FaceTextures.insert(pair<string, Texture>(entry.path().filename().filename().generic_string(), tempTexture));
	}
	return true;
}

bool PlayerTexture::LoadAllHairTextures()
{
	const string PATH = "assets/graphics/player/hair";
	for (const auto& entry : filesystem::directory_iterator(PATH))
	{
		Texture tempTexture;
		tempTexture.loadFromFile(PATH + "/" + entry.path().filename().string());
		m_HairTextures.insert(pair<string, Texture>(entry.path().filename().filename().generic_string(), tempTexture));
	}
	return true;
}

bool PlayerTexture::LoadAllHatTextures()
{
	const string PATH = "assets/graphics/player/hat";
	for (const auto& entry : filesystem::directory_iterator(PATH))
	{
		Texture tempTexture;
		tempTexture.loadFromFile(PATH + "/" + entry.path().filename().string());
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
				return pair<string, Texture>("", textureMap.at(fileName));
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
		m_TextureBaseLocation = "assets/graphics/player/base/" + m_PlayerTexture.GetNextTexture(m_PlayerTexture.GetBaseTextureMap(), m_TextureBaseLocation).first;
		if (!GetFileName(m_TextureBaseLocation).empty())
		{
			m_SpriteBase = Sprite(TextureHolder::GetTexture(m_TextureBaseLocation));
		}
		break;
	case LOWER:
		m_TextureLowerLayerLocation = "assets/graphics/player/lower/" + m_PlayerTexture.GetNextTexture(m_PlayerTexture.GetLowerTextureMap(), m_TextureLowerLayerLocation).first;
		if (!GetFileName(m_TextureLowerLayerLocation).empty())
		{
			m_SpriteLowerLayer = Sprite(TextureHolder::GetTexture(m_TextureLowerLayerLocation));
		}
		break;
	case CLOAK:
		m_TextureCloakLocation = "assets/graphics/player/cloak/" + m_PlayerTexture.GetNextTextureWithNone(m_PlayerTexture.GetCloakTextureMap(), m_TextureCloakLocation).first;
		if (!GetFileName(m_TextureCloakLocation).empty())
		{
			m_SpriteCloak = Sprite(TextureHolder::GetTexture(m_TextureCloakLocation));
		} else
		{
			m_SpriteCloak = Sprite();
		}
		break;
	case FACE_ITEM:
		m_TextureFaceItemLocation = "assets/graphics/player/face/" + m_PlayerTexture.GetNextTextureWithNone(m_PlayerTexture.GetFaceTextureMap(), m_TextureFaceItemLocation).first;
		if (!GetFileName(m_TextureFaceItemLocation).empty())
		{
			m_SpriteFaceItem = Sprite(TextureHolder::GetTexture(m_TextureFaceItemLocation));
		} else
		{
			m_SpriteFaceItem = Sprite();
		}
		break;
	case HAIR:
		m_TextureHairLocation = "assets/graphics/player/hair/" + m_PlayerTexture.GetNextTextureWithNone(m_PlayerTexture.GetHairTextureMap(), m_TextureHairLocation).first;
		if (!GetFileName(m_TextureHairLocation).empty())
		{
			m_SpriteHair = Sprite(TextureHolder::GetTexture(m_TextureHairLocation));
		} else
		{
			m_SpriteHair = Sprite();
		}
		break;
	case HAT:
		m_TextureHatLocation = "assets/graphics/player/hat/" + m_PlayerTexture.GetNextTextureWithNone(m_PlayerTexture.GetHatTextureMap(), m_TextureHatLocation).first;
		if (!GetFileName(m_TextureHatLocation).empty())
		{
			m_SpriteHat = Sprite(TextureHolder::GetTexture(m_TextureHatLocation));
		} else
		{
			m_SpriteHat = Sprite();
		}
		break;
	}

	SetPositionAllSprites();
}

void Player::SaveLayers()
{
	const string FILE_LOCATION = "assets/save/player.json";
	json jsonFile;

	jsonFile["playerBase"] = GetFileName(m_TextureBaseLocation);
	jsonFile["playerLower"] = GetFileName(m_TextureLowerLayerLocation);
	jsonFile["playerCloak"] = GetFileName(m_TextureCloakLocation);
	jsonFile["playerFace"] = GetFileName(m_TextureFaceItemLocation);
	jsonFile["playerHair"] = GetFileName(m_TextureHairLocation);
	jsonFile["playerHat"] = GetFileName(m_TextureHatLocation);

	std::ofstream newFile(FILE_LOCATION);
	newFile << jsonFile;
}

string Player::GetFileName(const string& fileLocation)
{
	if (!fileLocation.empty())
	{
		const size_t found = fileLocation.find_last_of('/');
		return fileLocation.substr(found + 1);
	}
	return "";
}

