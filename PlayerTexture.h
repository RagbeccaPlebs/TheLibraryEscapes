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

	bool LoadAllBaseTextures();
	bool LoadAllLowerTextures();
	bool LoadAllCloakTextures();
	bool LoadAllFaceTextures();
	bool LoadAllHairTextures();
	bool LoadAllHatTextures();
public:
	bool LoadAllFiles();
	void CleanAllFiles();

	const std::map<std::string, sf::Texture>& GetBaseTextureMap() const;
	const std::map<std::string, sf::Texture>& GetLowerTextureMap() const;
	const std::map<std::string, sf::Texture>& GetCloakTextureMap() const;
	const std::map<std::string, sf::Texture>& GetFaceTextureMap() const;
	const std::map<std::string, sf::Texture>& GetHairTextureMap() const;
	const std::map<std::string, sf::Texture>& GetHatTextureMap() const;
	std::pair<std::string, sf::Texture> GetNextTexture(const std::map<std::string, sf::Texture>& textureMap, const std::string& filePath);
	std::pair<std::string, sf::Texture> GetNextTextureWithNone(const std::map<std::string, sf::Texture>& textureMap, const std::string& filePath);
};