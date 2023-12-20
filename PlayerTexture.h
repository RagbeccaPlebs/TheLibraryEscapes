#pragma once
#include <SFML/Graphics.hpp>
#include <map>

class PlayerTexture
{
	std::map<std::string, sf::Texture> m_BaseTextures;
	std::map<std::string, sf::Texture> m_LowerTextures;
	std::map<std::string, sf::Texture> m_CloakTextures;
	std::map<std::string, sf::Texture> m_FaceTextures;
	std::map<std::string, sf::Texture> m_HairTextures;
	std::map<std::string, sf::Texture> m_HatTextures;

	void LoadAllBaseTextures();
	void LoadAllLowerTextures();
	void LoadAllCloakTextures();
	void LoadAllFaceTextures();
	void LoadAllHairTextures();
	void LoadAllHatTextures();
public:
	void LoadAllFiles();
	void CleanAllFiles();

	std::pair<std::string, sf::Texture> GetBaseTexture(const std::string& fileName);
	std::pair<std::string, sf::Texture> GetLowerTexture(const std::string& fileName);
	std::pair<std::string, sf::Texture> GetCloakTexture(const std::string& fileName);
	std::pair<std::string, sf::Texture> GetFaceTexture(const std::string& fileName);
	std::pair<std::string, sf::Texture> GetHairTexture(const std::string& fileName);
	std::pair<std::string, sf::Texture> GetHatTexture(const std::string& fileName);
};