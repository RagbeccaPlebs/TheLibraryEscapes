#include "Player.h"
#include "TextureHolder.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <filesystem>
#include <future> 

using json = nlohmann::json;
using namespace std;
using namespace sf;

//CONSTRUCTORS
Player::Player()
{
	SetInitialTextures();

	if (!m_TextureBaseLocation.empty())
	{
		m_SpriteBase = Sprite(TextureHolder::GetTexture(m_TextureBaseLocation));
	}

	if (!m_TextureLowerLayerLocation.empty())
	{
		m_SpriteLowerLayer = Sprite(TextureHolder::GetTexture(m_TextureLowerLayerLocation));
	}

	if (!m_TextureCloakLocation.empty())
	{
		m_SpriteCloak = Sprite(TextureHolder::GetTexture(m_TextureCloakLocation));
	}

	if (!m_TextureFaceItemLocation.empty())
	{
		m_SpriteFaceItem = Sprite(TextureHolder::GetTexture(m_TextureFaceItemLocation));
	}

	if (!m_TextureHairLocation.empty())
	{
		m_SpriteHair = Sprite(TextureHolder::GetTexture(m_TextureHairLocation));
	}

	if (!m_TextureHatLocation.empty())
	{
		m_SpriteHat = Sprite(TextureHolder::GetTexture(m_TextureHatLocation));
	}

	SetTextureLocation(m_PlayerMovement.GetIdleSouth().spriteLocation.at(0));

	m_CurrentSpriteSheet = m_PlayerMovement.GetIdleSouth();
}

void Player::Spawn(const Vector2f startPosition)
{
	m_Position.x = startPosition.x;
	m_Position.y = startPosition.y;

	SetPositionAllSprites();
}

//MOVEMENT
void Player::HandleInput()
{
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		m_LastButtonPressed = Side::LEFT;
		b_LeftPressed = true;
	}
	else
	{
		b_LeftPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		m_LastButtonPressed = Side::RIGHT;
		b_RightPressed = true;
	}
	else
	{
		b_RightPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		m_LastButtonPressed = Side::UP;
		b_UpPressed = true;
	}
	else
	{
		b_UpPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		m_LastButtonPressed = Side::DOWN;
		b_DownPressed = true;
	}
	else
	{
		b_DownPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::LShift))
	{
		if (b_ShiftPressed) b_ChangeRunning = true;
		b_ShiftPressed = false;

		m_Speed = Constant::PLAYER_WALK_SPEED;
	}
	else
	{
		if (!b_ShiftPressed) b_ChangeRunning = true;
		b_ShiftPressed = true;
		m_Speed = Constant::PLAYER_RUN_SPEED;
	}
}

//GETTERS
FloatRect Player::GetPosition() const
{
	return m_SpriteBase.getGlobalBounds();
}

FloatRect Player::GetFeet() const
{
	return m_Feet;
}

FloatRect Player::GetHead() const
{
	return m_Head;
}

FloatRect Player::GetLeft() const
{
	return m_Left;
}

FloatRect Player::GetRight() const
{
	return m_Right;
}

Vector2f Player::GetCenter() const
{
	const Vector2f centerLocation(
		m_Position.x + m_SpriteBase.getGlobalBounds().width / 2,
		m_Position.y + m_SpriteBase.getGlobalBounds().height / 2
	);
	return centerLocation;
}

FloatRect Player::GetInteractableBox() const
{
	return m_InteractableBox;
}

bool Player::GetDownPressed() const
{
	return b_DownPressed;
}

bool Player::GetLeftPressed() const
{
	return b_LeftPressed;
}

bool Player::GetRightPressed() const
{
	return b_RightPressed;
}

bool Player::GetUpPressed() const
{
	return b_UpPressed;
}

bool Player::IsPushing() const
{
	return m_PushingState == DOING;
}

//TEXTURE
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

void Player::SaveLayers() const
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

//SPRITE
void Player::SetPositionAllSprites() {
	m_SpriteBase.setPosition(m_Position);
	m_SpriteLowerLayer.setPosition(m_Position);
	m_SpriteCloak.setPosition(m_Position);
	m_SpriteFaceItem.setPosition(m_Position);
	m_SpriteHair.setPosition(m_Position);
	m_SpriteHat.setPosition(m_Position);
}

vector<Sprite*> Player::GetSprites()
{
	SetSpriteTextureLocationAllSprites();
	vector<Sprite*> arr(6);

	arr[0] = &m_SpriteBase;
	arr[1] = &m_SpriteLowerLayer;
	arr[2] = &m_SpriteCloak;
	arr[3] = &m_SpriteFaceItem;
	arr[4] = &m_SpriteHair;
	arr[5] = &m_SpriteHat;

	return arr;
}

void Player::SetSpriteTextureLocationAllSprites() {
	SetSpriteTextureLocation(m_SpriteBase);
	SetSpriteTextureLocation(m_SpriteLowerLayer);
	SetSpriteTextureLocation(m_SpriteCloak);
	SetSpriteTextureLocation(m_SpriteFaceItem);
	SetSpriteTextureLocation(m_SpriteHair);
	SetSpriteTextureLocation(m_SpriteHat);
}

void Player::SetSpriteTextureLocation(Sprite& sprite) const {
	if (sprite.getTexture() != nullptr) {
		sprite.setTextureRect(IntRect(m_TextureLocationX, m_TextureLocationY, 32, 40));
	}
}

void Player::SetTextureLocation(const Vector2i location)
{
	m_TextureLocationX = location.x == 0 ? 16 : (GetSequenceWithFour(location.x) * 16 - 2);
	m_TextureLocationY = location.y == 0 ? 8 : (GetSequenceWithEight(location.y) * 8 - 2);
}

int Player::GetSequenceWithFour(const int index) {
	int sequenceNumber = 1;
	for (int i = 0; i < index; i++) {
		sequenceNumber += 4;
	}
	return sequenceNumber;
}

int Player::GetSequenceWithEight(const int index) {
	int sequenceNumber = 1;
	for (int i = 0; i < index; i++) {
		sequenceNumber += 8;
	}
	return sequenceNumber;
}

//UPDATE
void Player::Update(const float elapsedTime)
{
	if (b_RightPressed) {
		m_Position.x += m_Speed * elapsedTime;
	}

	if (b_LeftPressed) {
		m_Position.x -= m_Speed * elapsedTime;
	}

	if (b_UpPressed) {
		m_Position.y -= m_Speed * elapsedTime;
	}

	if (b_DownPressed) {
		m_Position.y += m_Speed * elapsedTime;
	}

	SetPositionAllSprites();

	if (b_DownPressed || b_UpPressed || b_LeftPressed || b_RightPressed) {
		m_SecondsSinceLastAnimationUpdate += elapsedTime;
		PlayerAnimationUpdate(true);
	}
	else
	{
		m_SecondsSinceLastAnimationUpdate = 0;
		m_LastButtonPressed = NONE;
		PlayerAnimationUpdate(false);
	}

	// Update the rect for all body parts
	const FloatRect r = GetPosition();

	// Feet
	m_Feet.left = static_cast<float>(r.left + (r.width * .25));
	m_Feet.top = static_cast<float>(r.top + (r.height * .95));
	m_Feet.width = static_cast<float>(r.width - (r.width * .5));
	m_Feet.height = 1;

	// Head
	m_Head.left = static_cast<float>(r.left + (r.width * .25));
	m_Head.top = static_cast<float>(r.top + (r.height * .19));
	m_Head.width = static_cast<float>(r.width - (r.width * .5));
	m_Head.height = 1;

	// Right
	m_Right.left = static_cast<float>(r.left + (r.width * .8));
	m_Right.top = static_cast<float>(r.top + (r.height * .23));
	m_Right.width = 1;
	m_Right.height = static_cast<float>(r.height - (r.height * .29));

	// Left
	m_Left.left = static_cast<float>(r.left + (r.width * .2));
	m_Left.top = static_cast<float>(r.top + (r.height * .23));
	m_Left.width = 1;
	m_Left.height = static_cast<float>(r.height - (r.height * 0.29));

	//Update the Interactable Boxes
	m_InteractableBox.left = m_Left.left;
	m_InteractableBox.top = m_Head.top;
	m_InteractableBox.width = (m_Right.left - m_Left.left) + m_Right.width;
	m_InteractableBox.height = (m_Feet.top - m_Head.top) + m_Feet.height;
}
//Player animation
void Player::PlayerAnimationUpdate(const bool isMoving)
{
	bool changedSheet = false;
	if ((m_PushingState == STARTED || (m_PushingState == DOING && m_OldLastButtonPressed != m_LastButtonPressed)) && m_LastButtonPressed != NONE && m_LastButtonPressed == m_SidePushing) {
		m_PushingState = DOING;

		switch (m_LastButtonPressed)
		{
		case NONE:
			//Should do nothing, otherwise breaking flow
			break;
		case UP:
			m_CurrentSpriteSheet = m_PlayerMovement.GetPushingNorth();
			break;
		case RIGHT:
			m_CurrentSpriteSheet = m_PlayerMovement.GetPushingEast();
			break;
		case LEFT:
			m_CurrentSpriteSheet = m_PlayerMovement.GetPushingWest();
			break;
		case DOWN:
			m_CurrentSpriteSheet = m_PlayerMovement.GetPushingSouth();
			break;
		}
		m_OldLastButtonPressed = m_LastButtonPressed;
		changedSheet = true;
	}
	else if (b_ChangeRunning || m_PushingState == CHANGED || (m_OldLastButtonPressed != m_LastButtonPressed && m_LastButtonPressed != NONE)) {
		switch (m_LastButtonPressed)
		{
		case NONE:
			//Should do nothing, otherwise breaking flow
			break;
		case UP:
			if (isMoving)
			{
				if (b_ShiftPressed) m_CurrentSpriteSheet = m_PlayerMovement.GetRunningNorth();
				else m_CurrentSpriteSheet = m_PlayerMovement.GetWalkNorth();
			}
			else m_CurrentSpriteSheet = m_PlayerMovement.GetIdleNorth();
			break;
		case RIGHT:
			if (isMoving)
			{
				if (b_ShiftPressed) m_CurrentSpriteSheet = m_PlayerMovement.GetRunningEast();
				else m_CurrentSpriteSheet = m_PlayerMovement.GetWalkEast();
			}
			else m_CurrentSpriteSheet = m_PlayerMovement.GetIdleEast();
			break;
		case LEFT:
			if (isMoving)
			{
				if (b_ShiftPressed) m_CurrentSpriteSheet = m_PlayerMovement.GetRunningWest();
				else m_CurrentSpriteSheet = m_PlayerMovement.GetWalkWest();
			}
			else m_CurrentSpriteSheet = m_PlayerMovement.GetIdleWest();
			break;
		case DOWN:
			if (isMoving)
			{
				if (b_ShiftPressed) m_CurrentSpriteSheet = m_PlayerMovement.GetRunningSouth();
				else m_CurrentSpriteSheet = m_PlayerMovement.GetWalkSouth();
			}
			else m_CurrentSpriteSheet = m_PlayerMovement.GetIdleSouth();
			break;
		}
		if (b_ChangeRunning)
		{
			b_ChangeRunning = false;
		}
		if (m_PushingState == CHANGED)
		{
			m_PushingState = DOING;
		}
		m_OldLastButtonPressed = m_LastButtonPressed;
		changedSheet = true;
	}
	else if (m_LastButtonPressed == NONE) {
		switch (m_OldLastButtonPressed)
		{
		case NONE:
			//Should do nothing, otherwise breaking flow
			break;
		case UP:
			m_CurrentSpriteSheet = m_PlayerMovement.GetIdleNorth();
			break;
		case RIGHT:
			m_CurrentSpriteSheet = m_PlayerMovement.GetIdleEast();
			break;
		case LEFT:
			m_CurrentSpriteSheet = m_PlayerMovement.GetIdleWest();
			break;
		case DOWN:
			m_CurrentSpriteSheet = m_PlayerMovement.GetIdleSouth();
			break;
		}
		m_OldLastButtonPressed = m_LastButtonPressed;
		changedSheet = true;
	}
	PlayerMovement::SingleSprite& currentSprite = { m_CurrentSprite };

	if (changedSheet) {
		if (m_SecondsSinceLastAnimationUpdate >= m_CurrentSpriteSheet.animationSpeed[0] && m_CurrentSpriteSheet.spriteLocation.size() > 1) {
			currentSprite.animationSpeed = m_CurrentSpriteSheet.animationSpeed[1];
			currentSprite.spriteLocation = m_CurrentSpriteSheet.spriteLocation[1];
			currentSprite.index = 1;
		}
		else {
			m_SecondsSinceLastAnimationUpdate = 0;
			currentSprite.animationSpeed = m_CurrentSpriteSheet.animationSpeed[0];
			currentSprite.spriteLocation = m_CurrentSpriteSheet.spriteLocation[0];
			currentSprite.index = 0;
		}
	}
	else {
		if (m_SecondsSinceLastAnimationUpdate >= currentSprite.animationSpeed &&
			static_cast<int>(m_CurrentSpriteSheet.spriteLocation.size()) > (currentSprite.index + 1)) {
			m_SecondsSinceLastAnimationUpdate = 0;
			currentSprite.animationSpeed = m_CurrentSpriteSheet.animationSpeed[currentSprite.index + 1];
			currentSprite.spriteLocation = m_CurrentSpriteSheet.spriteLocation[currentSprite.index + 1];
			currentSprite.index = currentSprite.index + 1;
		}
		else if (m_SecondsSinceLastAnimationUpdate >= currentSprite.animationSpeed) {
			m_SecondsSinceLastAnimationUpdate = 0;
			currentSprite.animationSpeed = m_CurrentSpriteSheet.animationSpeed[0];
			currentSprite.spriteLocation = m_CurrentSpriteSheet.spriteLocation[0];
			currentSprite.index = 0;
		}
	}
	SetTextureLocation(currentSprite.spriteLocation);
}

//Stop versions
void Player::StopDown(const float position)
{
	m_Position.y = position;
	SetPositionAllSprites();
}

void Player::StopRight(const float position)
{
	m_Position.x = position;
	SetPositionAllSprites();
}

void Player::StopLeft(const float position)
{
	m_Position.x = position;
	SetPositionAllSprites();
}

void Player::StopUp(const float position)
{
	m_Position.y = position;
	SetPositionAllSprites();
}

void Player::SetPushing(const Side& side)
{
	m_SidePushing = side;
	if (m_PushingState != DOING)
	{
		m_PushingState = STARTED;
	}
}

void Player::StopPushing()
{
	if (m_PushingState != STOPPED)
	{
		m_PushingState = STOPPED;
	}
}
