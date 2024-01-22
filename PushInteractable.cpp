#include "PushInteractable.h"

#include "Constants.h"
#include "nlohmann/json.hpp"
#include <fstream>

using namespace sf;
using namespace std;
using json = nlohmann::json;

void PushInteractable::SaveNewLocationToFile()
{
	ifstream file(m_OriginFile);
	nlohmann::json data = json::parse(file);
	file.close();

	json jsonData;

	for (json& tempData : data.at(Keywords::PUSHABLE_OBJECT_KEYWORD))
	{
		if (tempData.at(Keywords::ID_KEYWORD) == m_Id)
		{
			tempData[Keywords::X_KEYWORD] = m_Position.x;
			tempData[Keywords::Y_KEYWORD] = m_Position.y;
		}
		jsonData.push_back(tempData);
	}

	data.at(Keywords::PUSHABLE_OBJECT_KEYWORD) = jsonData;

	ofstream fileOut(m_OriginFile);
	fileOut << data;
	fileOut.flush();
}

void PushInteractable::Update(float dtAsSeconds, Player& player)
{
	//Compare which direction the player is to the box
	const FloatRect playerPosition = player.GetPosition();

	const Vector2f topLeftToPlayer = CheckForLeastDistance(playerPosition,
		Vector2f(m_Position.x, m_Position.y - m_Sprite.getGlobalBounds().getSize().y));
	const Vector2f bottomLeftToPlayer = CheckForLeastDistance(playerPosition,
		Vector2f(m_Position.x, m_Position.y));
	const Vector2f topRightToPlayer = CheckForLeastDistance(playerPosition,
		Vector2f(m_Position.x - m_Sprite.getGlobalBounds().getSize().x, m_Position.y - m_Sprite.getGlobalBounds().getSize().y));
	const Vector2f bottomRightToPlayer = CheckForLeastDistance(playerPosition,
		Vector2f(m_Position.x - m_Sprite.getGlobalBounds().getSize().x, m_Position.y));

	m_SidePlayerIsOn = CheckSideWithPositions(topLeftToPlayer, bottomLeftToPlayer, topRightToPlayer, bottomRightToPlayer);

}

Vector2f PushInteractable::CheckForLeastDistance(FloatRect playerLocation, const Vector2f& comparisonPosition)
{
	float difference = FLT_MAX;
	Vector2f differenceVector;

	Vector2f playerMaxPoints[] = { {playerLocation.left, playerLocation.top},
	{playerLocation.left, playerLocation.top + playerLocation.height},
	{playerLocation.left + playerLocation.width, playerLocation.top},
	{playerLocation.left + playerLocation.width, playerLocation.top + playerLocation.height} };

	for (const Vector2f& location : playerMaxPoints)
	{
		const float xDifference = abs(location.x - comparisonPosition.x);
		const float yDifference = abs(location.y - comparisonPosition.y);
		difference = min(difference, xDifference + yDifference);
		if (difference == (xDifference + yDifference))
		{
			differenceVector = Vector2f(xDifference, yDifference);
		}
	}
	return differenceVector;
}

Side PushInteractable::CheckSideWithPositions(const Vector2f& topLeft, const Vector2f& bottomLeft, const Vector2f& topRight, const Vector2f& bottomRight)
{
	bool bottomLeftClose = false;
	bool topLeftClose = false;
	bool topRightClose = false;
	bool bottomRightClose = false;

	vector<Vector2f> distances = { topLeft, bottomLeft, topRight, bottomRight };
	const Vector2f bestDistance = CheckForLeastDistanceWithSideInMind(distances);
	distances.erase(std::remove(distances.begin(), distances.end(), bestDistance), distances.end());
	const Vector2f secondBestDistance = CheckForLeastDistanceWithSideInMind(distances);

	if (bestDistance == bottomLeft || secondBestDistance == bottomLeft)
	{
		bottomLeftClose = true;
	}
	if (bestDistance == topLeft || secondBestDistance == topLeft)
	{
		topLeftClose = true;
	}
	if (bestDistance == bottomRight || secondBestDistance == bottomRight)
	{
		bottomRightClose = true;
	}
	if (bestDistance == topRight || secondBestDistance == topRight)
	{
		topRightClose = true;
	}

	if (bottomLeftClose && topLeftClose) {
		return LEFT;
	}
	if (bottomRightClose && topRightClose) {
		return RIGHT;
	}
	if (bottomLeftClose && bottomRightClose)
	{
		return DOWN;
	}
	if (topRightClose && topLeftClose) {
		return UP;
	}
	return LEFT;
}

Vector2f PushInteractable::CheckForLeastDistanceWithSideInMind(std::vector<sf::Vector2f> distances)
{
	for (int i = 0; i < static_cast<int>(distances.size()); i++)
	{
		bool wasSmaller = false;
		float xAndYCombined = distances[i].x + distances[i].y;
		for (Vector2f& checkDistance : distances)
		{
			if (distances[i] == checkDistance)
			{
				continue;
			}
			const float smallerNumber = min(xAndYCombined, (checkDistance.x + checkDistance.y));
			wasSmaller = smallerNumber == xAndYCombined;
		}
		if (wasSmaller)
		{
			return distances[i];
		}
	}
}

//If true change player to pushing type into the direction of the box
bool PushInteractable::CanInteract(Player& player)
{
	if (!b_Movable)
	{
		return false;
	}
	if (!b_Active)
	{
		return false;
	}
	if (m_CollisionBox.intersects(player.GetPushInteractableBox()))
	{
		player.SetPushing(m_SidePlayerIsOn);
		return true;
	}
	player.StopPushing();
	return false;
}

PushType PushInteractable::GetPushType() const
{
	return m_PushType;
}

void PushInteractable::Unload()
{
	SaveNewLocationToFile();
}

PushType PushInteractable::GetPushTypeFromString(const string& pushType)
{
	unordered_map<string, PushType> const table =
	{ {Constant::LOCATION_UPPERCASE, LOCATION_PUSH}, {Constant::RANDOM_UPPERCASE, RANDOM_PUSH} };
	const auto it = table.find(pushType);
	if (it != table.end()) {
		return it->second;
	}
	return RANDOM_PUSH;
}
