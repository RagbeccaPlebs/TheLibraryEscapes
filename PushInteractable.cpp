#include "PushInteractable.h"

#include "Constants.h"
#include "nlohmann/json.hpp"
#include <fstream>

using namespace sf;
using namespace std;
using json = nlohmann::json;

void PushInteractable::SaveNewLocationToFile() const
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

void PushInteractable::Update(const float& dtAsSeconds, Player& player)
{
	if (!b_Movable)
	{
		return;
	}

	//Compare which direction the player is to the box
	const Vector2f playerCenter = player.GetCenter();

	const float topLeftToPlayer = CheckForDistance(playerCenter,
		Vector2f(m_Position.x, m_Position.y));
	const float bottomLeftToPlayer = CheckForDistance(playerCenter,
		Vector2f(m_Position.x, m_Position.y + m_Sprite.getGlobalBounds().height));
	const float topRightToPlayer = CheckForDistance(playerCenter,
		Vector2f(m_Position.x + m_Sprite.getGlobalBounds().getSize().x, m_Position.y));
	const float bottomRightToPlayer = CheckForDistance(playerCenter,
		Vector2f(m_Position.x + m_Sprite.getGlobalBounds().getSize().x, m_Position.y + m_Sprite.getGlobalBounds().getSize().y));

	m_SidePlayerIsOn = CheckSideWithPositions(topLeftToPlayer, bottomLeftToPlayer, topRightToPlayer, bottomRightToPlayer);

	if (b_Interacting)
	{
		b_Interacting = false;
		bool changed = false;
		const Vector2f oldPosition = m_Position;
		if (player.GetRightPressed() && m_SidePlayerIsOn == RIGHT) {
			m_Position.x += m_Speed * dtAsSeconds;
			changed = true;
		}

		if (player.GetLeftPressed() && m_SidePlayerIsOn == LEFT) {
			m_Position.x -= m_Speed * dtAsSeconds;
			changed = true;
		}

		if (player.GetUpPressed() && m_SidePlayerIsOn == UP) {
			m_Position.y -= m_Speed * dtAsSeconds;
			changed = true;
		}

		if (player.GetDownPressed() && m_SidePlayerIsOn == DOWN) {
			m_Position.y += m_Speed * dtAsSeconds;
			changed = true;
		}

		const auto box = FloatRect(m_Position.x, m_Position.y, m_Sprite.getGlobalBounds().width, m_Sprite.getGlobalBounds().height);

		if (m_BoundsBox.intersects(box))
		{
			m_Sprite.setPosition(m_Position);
			m_InteractionBox = FloatRect(m_Position.x - 1.f, m_Position.y - 1.f,
				m_Sprite.getGlobalBounds().width + 2.f, m_Sprite.getGlobalBounds().height + 2.f);
			m_CollisionBox = box;
			if (changed)
			{
				PlaySoundOfNotPlaying();
			}
			else
			{
				if (GetPushSoundStatus() == SoundSource::Playing)
				{
					StopPushSound();
				}
			}
		}
		else
		{
			m_Position = oldPosition;
		}
	}
}

float PushInteractable::CheckForDistance(const Vector2f& playerCenter, const Vector2f& comparisonPosition)
{
	const float xDifference = abs(playerCenter.x - comparisonPosition.x);
	const float yDifference = abs(playerCenter.y - comparisonPosition.y);

	return xDifference + yDifference;
}

Side PushInteractable::CheckSideWithPositions(const float& topLeft, const float& bottomLeft, const float& topRight, const float& bottomRight)
{
	bool bottomLeftClose = false;
	bool topLeftClose = false;
	bool topRightClose = false;
	bool bottomRightClose = false;

	vector<float> distances = { topLeft, bottomLeft, topRight, bottomRight };
	const float bestDistance = CheckForLeastDistance(distances);
	distances.erase(std::remove(distances.begin(), distances.end(), bestDistance), distances.end());
	const float secondBestDistance = CheckForLeastDistance(distances);

	if (fabs(bestDistance - bottomLeft) < numeric_limits<float>::epsilon() || fabs(secondBestDistance - bottomLeft) < numeric_limits<float>::epsilon())
	{
		bottomLeftClose = true;
	}
	if (fabs(bestDistance - topLeft) < numeric_limits<float>::epsilon() || fabs(secondBestDistance - topLeft) < numeric_limits<float>::epsilon())
	{
		topLeftClose = true;
	}
	if (fabs(bestDistance - bottomRight) < numeric_limits<float>::epsilon() || fabs(secondBestDistance - bottomRight) < numeric_limits<float>::epsilon())
	{
		bottomRightClose = true;
	}
	if (fabs(bestDistance - topRight) < numeric_limits<float>::epsilon() || fabs(secondBestDistance - topRight) < numeric_limits<float>::epsilon())
	{
		topRightClose = true;
	}

	if (bottomLeftClose && topLeftClose)
	{
		return RIGHT;
	}
	if (bottomRightClose && topRightClose)
	{
		return LEFT;
	}
	if (bottomLeftClose && bottomRightClose)
	{
		return UP;
	}
	if (topRightClose && topLeftClose)
	{
		return DOWN;
	}
	return LEFT;
}

float PushInteractable::CheckForLeastDistance(std::vector<float> distances)
{
	float smallestNumber = FLT_MAX;
	for (int i = 0; i < static_cast<int>(distances.size()); i++)
	{
		for (float& checkDistance : distances)
		{
			if (fabs(distances[i] - checkDistance) < numeric_limits<float>::epsilon())
			{
				continue;
			}
			const float smallerNumber = min(distances[i], checkDistance);
			smallestNumber = min(smallestNumber, smallerNumber);
		}
	}
	return smallestNumber;
}

//If true change player to pushing type into the direction of the box
bool PushInteractable::CanInteract(Player& player, const bool isOnlyOneActive)
{
	if (!b_Active)
	{
		if (player.IsPushing() && isOnlyOneActive)
		{
			player.StopPushing();
		}
		return false;
	}
	if (!b_Movable)
	{
		if (player.IsPushing() && isOnlyOneActive) {
			player.StopPushing();
		}
		return false;
	}
	if (m_InteractionBox.intersects(player.GetInteractableBox()))
	{
		player.SetPushing(m_SidePlayerIsOn);
		b_BeingPushed = true;
		return true;
	}
	if (b_WasBeingPushed)
	{
		player.StopPushing();
		if (GetPushSoundStatus() == SoundSource::Playing)
		{
			StopPushSound();
		}
		b_WasBeingPushed = false;
	}

	if (b_BeingPushed)
	{
		player.SetPushing(m_SidePlayerIsOn);
		b_BeingPushed = false;
		b_WasBeingPushed = true;
		return true;
	}
	return false;
}

PushType PushInteractable::GetPushType() const
{
	return m_PushType;
}

FloatRect PushInteractable::GetCollisionBox() const
{
	return m_CollisionBox;
}

void PushInteractable::Unload()
{
	SaveNewLocationToFile();
}

PushInteractable::~PushInteractable()
{
	m_Sound.resetBuffer();
	m_PushSound.resetBuffer();
}

void PushInteractable::PlayPushSound()
{
	m_PushSound.play();
}

void PushInteractable::StopPushSound()
{
	m_PushSound.stop();
}

void PushInteractable::PlaySoundOfNotPlaying()
{
	if (GetPushSoundStatus() != SoundSource::Playing)
	{
		PlayPushSound();
	}
}

SoundSource::Status PushInteractable::GetPushSoundStatus() const
{
	return m_PushSound.getStatus();
}

void PushInteractable::PlayAlternativeSound()
{
	m_Sound.play();
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
