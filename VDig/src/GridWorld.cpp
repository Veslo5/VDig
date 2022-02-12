#include "GridWorld.h"
#include <algorithm>
#include <cmath>

Vgameplay::GridWorld::GridWorld(const int width, const int height, const int size, const int spacing) : TilesSize(size), Height(height), Width(width)
{
	for (int gridX = 0; gridX < width; gridX++)
	{
		for (int gridY = 0; gridY < height; gridY++)
		{
			const auto posX = (gridX * size) + spacing;
			const auto posY = (gridY * size) + spacing;

			TileWorld.push_back(std::make_unique<Vgameplay::Tile>(raylib::Vector2(gridX, gridY), raylib::Vector2(posX, posY), size));
		}
	}
}

int Vgameplay::GridWorld::GetPixelSizeX() const
{
	return Width * TilesSize;
}

int Vgameplay::GridWorld::GetPixelSizeY() const
{
	return Height * TilesSize;
}

bool Vgameplay::GridWorld::SetTileDataGridPos(raylib::Vector2 gridPosition, int newAtlasPosition)
{
	if (Tile* tile = GetTileAtGridPos(gridPosition))
	{
		tile->AtlasPosition = newAtlasPosition;
		return true;
	}
	return false;
}

bool Vgameplay::GridWorld::SetTileDataWorldPos(raylib::Vector2 worldPosition, int newAtlasPosition)
{
	if (Tile* tile = GetTileAtWorldPos(worldPosition))
	{
		tile->AtlasPosition = newAtlasPosition;
		return true;
	}
	return false;
}

bool Vgameplay::GridWorld::IsTileExistOnGridPos(raylib::Vector2 gridPosition) const
{
	if (Tile* tile = GetTileAtGridPos(gridPosition))
	{
		return true;
	}
	return false;
}

raylib::Vector2 Vgameplay::GridWorld::GetWorldPositionFromGridPosition(raylib::Vector2 gridPosition) const
{
	return { floor(gridPosition.x * TilesSize), floor(gridPosition.y * TilesSize) };
}

raylib::Vector2 Vgameplay::GridWorld::GetGridPositionFromWorldPosition(raylib::Vector2 worldPosition) const
{
	return { floor(worldPosition.x / TilesSize), floor(worldPosition.y / TilesSize) };
}


Vgameplay::Tile* Vgameplay::GridWorld::GetTileAtGridPos(raylib::Vector2 gridPosition) const
{
	const auto enumerator = std::find_if(TileWorld.begin(), TileWorld.end(),
		[&gridPosition](const std::unique_ptr<Vgameplay::Tile>& tile) -> bool
		{
			return gridPosition == tile->GridPosition;
		});

	if (enumerator != TileWorld.end())
	{
		return enumerator->get();
	}

	return nullptr;
}

Vgameplay::Tile* Vgameplay::GridWorld::GetTileAtWorldPos(raylib::Vector2 worldPosition) const
{
	const float column = worldPosition.x / static_cast<float>(TilesSize);
	const float row = worldPosition.y / static_cast<float>(TilesSize);

	return this->GetTileAtGridPos({ column, row });
}

Vgameplay::Tile* Vgameplay::GridWorld::GetTileAtGridPosIndex(raylib::Vector2 gridPosition) const
{
	const int pos = (static_cast<int>(gridPosition.y) * this->Width) + static_cast<int>(gridPosition.x);

	if (pos < 0 || pos > TileWorld.size())
	{
		return nullptr;
	}

	return TileWorld.at(pos).get();
}
