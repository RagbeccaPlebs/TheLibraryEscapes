#include "Engine.h"
#include "MapManager.h"

using namespace sf;

void Engine::detectCollisions(Player& player) {
	FloatRect detectionZone = player.getPosition();

	const int TILE_SIZE = MapManager::TILE_SIZE;

	// Make a FloatRect to test each block
	FloatRect block(0, 0, TILE_SIZE, TILE_SIZE);

	// Build a zone around the player to detect collisions
	int startX = (int)(detectionZone.left / TILE_SIZE);
	int startY = (int)(detectionZone.top / TILE_SIZE);
	int endX = (int)(detectionZone.left / TILE_SIZE) + 5;
	int endY = (int)(detectionZone.top / TILE_SIZE) + 5;

	// Make sure we don't test positions lower than zero
	// Or higher than the end of the array
	if (startX < 0)startX = 0;
	if (startY < 0)startY = 0;
	if (endX >= m_Map.getMapSize().x)
		endX = m_Map.getMapSize().x;
	if (endY >= m_Map.getMapSize().y)
		endY = m_Map.getMapSize().y;

	for (int x = startX; x < endX; x++)
	{
		for (int y = startY; y < endY; y++)
		{

			// Is character colliding with a regular block
			if (m_Map.getArrayCollisionLevel()[y][x] >= 1)
			{
				// Initialize the starting position of the current block
				block.left = x * TILE_SIZE;
				block.top = y * TILE_SIZE;

				if (player.getRight().intersects(block))
				{
					player.stopRight(block.left - (player.getRight().left - player.getPosition().left));
				}
				else if (player.getLeft().intersects(block))
				{
					player.stopLeft(block.left + (player.getCenter().x - player.getLeft().left));
				}

				if (player.getFeet().intersects(block))
				{
					player.stopDown(block.top - player.getFeet().top + player.getPosition().top - 1);
				}
				else if (player.getHead().intersects(block))
				{
					player.stopUp(block.top + block.height - (player.getHead().top - player.getPosition().top));
				}
			}

		}

	}
}