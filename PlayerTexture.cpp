#include "Player.h"
#include "PlayerTexture.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <filesystem>

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

void PlayerTexture::LoadAllBaseTextures()
{
	const string PATH = "assets/graphics/player/base";
	for (const auto& entry : filesystem::directory_iterator(PATH))
	{
		Texture tempTexture;
		tempTexture.loadFromFile(PATH + "/" + entry.path().filename().string());
		m_BaseTextures.insert(pair<string, Texture>(entry.path().filename().filename().generic_string(), tempTexture));
	}
}


void PlayerTexture::LoadAllLowerTextures()
{
	const string PATH = "assets/graphics/player/lower";
	for (const auto& entry : filesystem::directory_iterator(PATH))
	{
		Texture tempTexture;
		tempTexture.loadFromFile(PATH + "/" + entry.path().filename().string());
		m_LowerTextures.insert(pair<string, Texture>(entry.path().filename().filename().generic_string(), tempTexture));
	}
}

void PlayerTexture::LoadAllCloakTextures()
{
	const string PATH = "assets/graphics/player/cloak";
	for (const auto& entry : filesystem::directory_iterator(PATH))
	{
		Texture tempTexture;
		tempTexture.loadFromFile(PATH + "/" + entry.path().filename().string());
		m_CloakTextures.insert(pair<string, Texture>(entry.path().filename().filename().generic_string(), tempTexture));
	}
}

void PlayerTexture::LoadAllFaceTextures()
{
	const string PATH = "assets/graphics/player/face";
	for (const auto& entry : filesystem::directory_iterator(PATH))
	{
		Texture tempTexture;
		tempTexture.loadFromFile(PATH + "/" + entry.path().filename().string());
		m_FaceTextures.insert(pair<string, Texture>(entry.path().filename().filename().generic_string(), tempTexture));
	}
}

void PlayerTexture::LoadAllHairTextures()
{
	const string PATH = "assets/graphics/player/hair";
	for (const auto& entry : filesystem::directory_iterator(PATH))
	{
		Texture tempTexture;
		tempTexture.loadFromFile(PATH + "/" + entry.path().filename().string());
		m_HairTextures.insert(pair<string, Texture>(entry.path().filename().filename().generic_string(), tempTexture));
	}
}

void PlayerTexture::LoadAllHatTextures()
{
	const string PATH = "assets/graphics/player/hat";
	for (const auto& entry : filesystem::directory_iterator(PATH))
	{
		Texture tempTexture;
		tempTexture.loadFromFile(PATH + "/" + entry.path().filename().string());
		m_HairTextures.insert(pair<string, Texture>(entry.path().filename().filename().generic_string(), tempTexture));
	}
}

void PlayerTexture::LoadAllFiles()
{
	LoadAllBaseTextures();
	LoadAllLowerTextures();
	LoadAllCloakTextures();
	LoadAllFaceTextures();
	LoadAllHairTextures();
	LoadAllHatTextures();
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

pair<string, Texture> PlayerTexture::GetBaseTexture(const string& fileName)
{
	return pair<string, Texture>(fileName, m_BaseTextures.at(fileName));
}

pair<string, Texture> PlayerTexture::GetLowerTexture(const string& fileName)
{
	return pair<string, Texture>(fileName, m_LowerTextures.at(fileName));
}

pair<string, Texture> PlayerTexture::GetCloakTexture(const string& fileName)
{
	return pair<string, Texture>(fileName, m_CloakTextures.at(fileName));
}

pair<string, Texture> PlayerTexture::GetFaceTexture(const string& fileName)
{
	return pair<string, Texture>(fileName, m_FaceTextures.at(fileName));
}

pair<string,Texture> PlayerTexture::GetHairTexture(const string& fileName)
{
	return pair<string, Texture>(fileName, m_HairTextures.at(fileName));
}

std::pair<std::string, sf::Texture> PlayerTexture::GetHatTexture(const std::string& fileName)
{
	return pair<string, Texture>(fileName, m_HatTextures.at(fileName));
}

void Player::UpdatePlayerTexture()
{
	
}

