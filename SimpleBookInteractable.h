#pragma once

#include <SFML/Graphics.hpp>
#include "BookInteractable.h"

class SimpleBookInteractable : public BookInteractable
{
public:
	SimpleBookInteractable(int id);

	void Update(float dtAsSeconds);
};
