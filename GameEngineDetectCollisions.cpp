#include "GameEngineLogic.h"
#include "TiledMapLoader.h"

using namespace sf;

void GameEngineLogic::DetectCollisions(Player& player) {
	const FloatRect detectionZone = player.GetPosition();

	constexpr int TILE_SIZE = TiledMapLoader::STANDARD_TILE_SIZE;

	// Make a FloatRect to test each block
	FloatRect block(0, 0, TILE_SIZE, TILE_SIZE);

	// Build a zone around the player to detect collisions
	int startX = static_cast<int>(detectionZone.left / TILE_SIZE);
	int startY = static_cast<int>(detectionZone.top / TILE_SIZE);
	int endX = static_cast<int>(detectionZone.left / TILE_SIZE) + MAX_RANGE_COLLISIONS_DETECTION;
	int endY = static_cast<int>(detectionZone.top / TILE_SIZE) + MAX_RANGE_COLLISIONS_DETECTION;

	// Make sure we don't test positions lower than zero
	// Or higher than the end of the array
	if (startX < 0) {
		startX = 0;
	}
	if (startY < 0) {
		startY = 0;
	}
	if (endX >= m_Map->GetMapSize().x) {
		endX = m_Map->GetMapSize().x;
	}
	if (endY >= m_Map->GetMapSize().y) {
		endY = m_Map->GetMapSize().y;
	}

	for (int x = startX; x < endX; x++)
	{
		for (int y = startY; y < endY; y++)
		{

			// Is character colliding with a regular block
			if (m_Map->GetArrayCollisionLevel()[y][x] >= 1)
			{
				// Initialize the starting position of the current block
				block.left = static_cast<float>(x * TILE_SIZE);
				block.top = static_cast<float>(y * TILE_SIZE);

				if (player.GetRight().intersects(block))
				{
					player.StopRight(block.left - (player.GetRight().left - player.GetPosition().left + player.GetRight().width));
				}
				else if (player.GetLeft().intersects(block))
				{
					player.StopLeft(block.left + (player.GetCenter().x - player.GetLeft().left));
				}

				if (player.GetFeet().intersects(block))
				{
					player.StopDown(block.top - player.GetFeet().top + player.GetPosition().top - 1);
				}
				else if (player.GetHead().intersects(block))
				{
					player.StopUp(block.top + block.height - (player.GetHead().top - player.GetPosition().top));
				}
			}

		}

	}
}