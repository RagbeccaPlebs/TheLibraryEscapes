#include "RandomPushInteractable.h"

#include "Constants.h"
#include "PickupInventoryInteractable.h"
#include "TextureHolder.h"

using namespace std;
using namespace sf;

RandomPushInteractable::RandomPushInteractable(const int id, const string& textureFileLocation,
	const Vector2f position, const string& fileOfOrigin, const float speed,
	const Vector2f minBounds, const Vector2f maxBounds, const string& soundLocation, const string& pushSoundLocation, const bool isActive)
{
	m_Id = id;
	b_Active = isActive;
	m_InteractableType = PUSH_OBJECT;
	m_PushType = RANDOM_PUSH;
	m_OriginFile = fileOfOrigin;
	const Texture& texture = TextureHolder::GetTexture(textureFileLocation);
	m_Texture = texture;
	m_Sprite = Sprite(texture);
	m_Position = position;
	m_Speed = speed;
	m_Sprite.setPosition(m_Position);
	const float textureWidth = static_cast<float>(texture.getSize().x);
	const float textureHeight = static_cast<float>(texture.getSize().y);
	m_BoundsBox = FloatRect(minBounds, Vector2f(maxBounds.x - minBounds.x, maxBounds.y - minBounds.y));
	m_InteractionBox = FloatRect(position.x - 1.f, position.y - 1.f,
		textureWidth + 2.f, textureHeight + 2.f);
	m_CollisionBox = FloatRect(position.x, position.y, textureWidth, textureHeight);

	//Sounds
	m_SoundBuffer.loadFromFile(soundLocation);
	m_Sound.setBuffer(m_SoundBuffer);
	m_PushSoundBuffer.loadFromFile(pushSoundLocation);
	m_PushSound.setBuffer(m_PushSoundBuffer);
	m_PushSound.setLoop(true);
}

pair<string, Vector2f> RandomPushInteractable::Interact()
{
	b_Interacting = true;
	return pair{ Keywords::PUSHABLE_OBJECT_KEYWORD, Vector2f(0,0) };
}

string RandomPushInteractable::Message()
{
	return Keywords::PUSHABLE_OBJECT_KEYWORD;
}

void RandomPushInteractable::Draw(RenderWindow& mainWindow)
{
	mainWindow.draw(m_Sprite);
}
