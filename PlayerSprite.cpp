#include "Player.h"
#include <array>

#include "TextureHolder.h"

using namespace sf;
using namespace std;

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