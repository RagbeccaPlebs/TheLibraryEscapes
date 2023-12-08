#include "Player.h"
#include <array>

using namespace sf;
using namespace std;

void Player::SetPositionAllSprites() {
	m_SpriteBase.setPosition(m_Position);
	m_SpriteLowerLayer.setPosition(m_Position);
	m_SpriteCloak.setPosition(m_Position);
	m_SpriteFaceItem.setPosition(m_Position);
	m_SpriteHair.setPosition(m_Position);
}

array<Sprite, 5> Player::GetSprites()
{
	array<Sprite, 5> a;
	a[0] = GetSpriteBase();
	a[1] = GetSpriteLowerLayer();
	a[2] = GetSpriteCloak();
	a[3] = GetSpriteFaceItem();
	a[4] = GetSpriteHair();
	return a;
}

Sprite Player::SetSpriteTextureLocation(Sprite& sprite) {
	if (sprite.getTexture() != nullptr) {
		sprite.setTextureRect(IntRect(m_TextureLocationX, m_TextureLocationY, 32, 40));
		return sprite;
	}
	else {
		return Sprite();
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

Sprite Player::GetSpriteBase() {
	return SetSpriteTextureLocation(m_SpriteBase);
}

Sprite Player::GetSpriteLowerLayer()
{
	return SetSpriteTextureLocation(m_SpriteLowerLayer);
}

Sprite Player::GetSpriteCloak()
{
	return SetSpriteTextureLocation(m_SpriteCloak);
}

Sprite Player::GetSpriteFaceItem()
{
	return SetSpriteTextureLocation(m_SpriteFaceItem);
}

Sprite Player::GetSpriteHair()
{
	return SetSpriteTextureLocation(m_SpriteHair);
}