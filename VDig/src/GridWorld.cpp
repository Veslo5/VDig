#include "GridWorld.h"
#include <algorithm>

Vgameplay::GridWorld::GridWorld(const int width, const int height, const int size, const int spacing) :
	TileWorld()
{
	for (int gridX = 0; gridX < width; gridX++)
	{
		for (int gridY = 0; gridY < height; gridY++)
		{
			auto posX = (gridX * size) + spacing;
			auto posY = (gridY * size) + spacing;

			TileWorld.push_back(std::make_shared<Vgameplay::Tile>(gridX, gridY, posX, posY, size));
		}
	}
}

std::weak_ptr<Vgameplay::Tile> Vgameplay::GridWorld::GetTileAtPos(int x, int y)
{
	const auto enumerator = std::find_if(TileWorld.begin(), TileWorld.end(),
		[&](const std::shared_ptr<Vgameplay::Tile>& tile) -> bool
		{
			return static_cast<int>(tile->GridPosition.x) == x && static_cast<int>(tile
				->GridPosition.y) == y;
		});
	if (enumerator != TileWorld.end())
	{
		return *enumerator;
	}

	return {};
}