#pragma once

#include <SFML/Graphics.hpp>
#include "BookInteractable.h"

class SimpleBookInteractable : public BookInteractable
{
public:
	SimpleBookInteractable(int id, const std::string& textureFileLocation, sf::Vector2f position, EmotionType emotion);

	void Update(float dtAsSeconds);
};
