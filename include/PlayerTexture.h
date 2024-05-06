#pragma once
#include <map>
#include <string>
#include <SFML/Graphics/Texture.hpp>

class PlayerTexture
{
	//The collection of all textures of a player type, containing the texture and the filename
	std::map<std::string, sf::Texture> m_BaseTextures;
	std::map<std::string, sf::Texture> m_LowerTextures;
	std::map<std::string, sf::Texture> m_CloakTextures;
	std::map<std::string, sf::Texture> m_FaceTextures;
	std::map<std::string, sf::Texture> m_HairTextures;
	std::map<std::string, sf::Texture> m_HatTextures;

	//Load all textures within a folder to the correct collection (map)
	bool LoadAllBaseTextures();
	bool LoadAllLowerTextures();
	bool LoadAllCloakTextures();
	bool LoadAllFaceTextures();
	bool LoadAllHairTextures();
	bool LoadAllHatTextures();
public:
	//A call to call all load all subtypes
	bool LoadAllFiles();
	//Clear the maps, can be seen as a destructor
	void CleanAllFiles();

	//Functions to get all collections of the textures as a reference
	const std::map<std::string, sf::Texture>& GetBaseTextureMap() const;
	const std::map<std::string, sf::Texture>& GetLowerTextureMap() const;
	const std::map<std::string, sf::Texture>& GetCloakTextureMap() const;
	const std::map<std::string, sf::Texture>& GetFaceTextureMap() const;
	const std::map<std::string, sf::Texture>& GetHairTextureMap() const;
	const std::map<std::string, sf::Texture>& GetHatTextureMap() const;

	//Get the next texture in line, if last texture give first.
	static std::pair<std::string, sf::Texture> GetNextTexture(const std::map<std::string, sf::Texture>& textureMap, const std::string& filePath);

	//Get the next texture in line, if last texture give none. If none get first texture
	static std::pair<std::string, sf::Texture> GetNextTextureWithNone(const std::map<std::string, sf::Texture>& textureMap, const std::string& filePath);
};
