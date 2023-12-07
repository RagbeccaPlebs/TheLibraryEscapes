#include "Player.h"
#include <array>

using namespace sf;
using namespace std;

void Player::setPositionAllSprites() {
	m_SpriteBase.setPosition(m_Position);
	m_SpriteLowerLayer.setPosition(m_Position);
	m_SpriteCloak.setPosition(m_Position);
	m_SpriteFaceItem.setPosition(m_Position);
	m_SpriteHair.setPosition(m_Position);
}

array<Sprite, 5> Player::getSprites()
{
	array<Sprite, 5> a;
	a[0] = getSpriteBase();
	a[1] = getSpriteLowerLayer();
	a[2] = getSpriteCloak();
	a[3] = getSpriteFaceItem();
	a[4] = getSpriteHair();
	return a;
}

Sprite Player::setSpriteTextureLocation(Sprite& sprite) {
	if (sprite.getTexture() != nullptr) {
		sprite.setTextureRect(IntRect(m_TextureLocationX, m_TextureLocationY, 32, 40));
		return sprite;
	}
	else {
		return Sprite();
	}
}

void Player::setTextureLocation(const Vector2i location)
{

	m_TextureLocationX = location.x == 0 ? 16 : (getSequenceWithFour(location.x) * 16 - 2);
	m_TextureLocationY = location.y == 0 ? 8 : (getSequenceWithEight(location.y) * 8 - 2);
}

int Player::getSequenceWithFour(const int index) {
	int sequenceNumber = 1;
	for (int i = 0; i < index; i++) {
		sequenceNumber += 4;
	}
	return sequenceNumber;
}

int Player::getSequenceWithEight(const int index) {
	int sequenceNumber = 1;
	for (int i = 0; i < index; i++) {
		sequenceNumber += 8;
	}
	return sequenceNumber;
}

Sprite Player::getSpriteBase() {
	return setSpriteTextureLocation(m_SpriteBase);
}

Sprite Player::getSpriteLowerLayer()
{
	return setSpriteTextureLocation(m_SpriteLowerLayer);
}

Sprite Player::getSpriteCloak()
{
	return setSpriteTextureLocation(m_SpriteCloak);
}

Sprite Player::getSpriteFaceItem()
{
	return setSpriteTextureLocation(m_SpriteFaceItem);
}

Sprite Player::getSpriteHair()
{
	return setSpriteTextureLocation(m_SpriteHair);
}