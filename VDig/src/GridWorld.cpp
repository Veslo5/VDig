#include "GridWorld.h"
#include <algorithm>
#include <cmath>

Vgameplay::GridWorld::GridWorld(const int width, const int height, const int size, const int spacing) : TilesSize(size),
	Width(width), Height(height)
{
	for (int gridX = 0; gridX < width; gridX++)
	{
		for (int gridY = 0; gridY < height; gridY++)
		{
			const int posX = (gridX * size) + spacing;
			const int posY = (gridY * size) + spacing;

			TileWorld.push_back(std::make_unique<Vgameplay::Tile>(Vengine::VPoint(gridX, gridY), raylib::Vector2(static_cast<float>(posX), static_cast<float>(posY)), size));
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

bool Vgameplay::GridWorld::SetTileDataGridPos(Vengine::VPoint gridPosition, int newAtlasPosition) const
{
	if (Tile* tile = GetTileAtGridPos(gridPosition))
	{
		tile->AtlasPosition = newAtlasPosition;
		return true;
	}
	return false;
}

bool Vgameplay::GridWorld::SetTileDataWorldPos(raylib::Vector2 worldPosition, int newAtlasPosition) const
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

raylib::Vector2 Vgameplay::GridWorld::GetWorldPositionFromGridPosition(Vengine::VPoint gridPosition) const
{
	return { static_cast<float>(gridPosition.x * TilesSize), static_cast<float>(gridPosition.y * TilesSize) };
}

Vengine::VPoint Vgameplay::GridWorld::GetGridPositionFromWorldPosition(raylib::Vector2 worldPosition) const
{
	return { (static_cast<int>(worldPosition.x) / TilesSize), (static_cast<int>(worldPosition.y) / TilesSize) };
}

Vgameplay::SelectedTiles Vgameplay::GridWorld::GetSurroundingTilesFromGridPosition(Vengine::VPoint gridPosition) const
{
	SelectedTiles toReturn{};


	if (Tile* centerTile = GetTileAtGridPos(gridPosition))
	{
		toReturn.CenterTile = centerTile;

		if (Tile* eastTile = GetTileAtGridPos({ gridPosition.x + 1, gridPosition.y }))
		{
			toReturn.EastTile = eastTile;
		}

		if (Tile* westTile = GetTileAtGridPos({ gridPosition.x - 1, gridPosition.y }))
		{
			toReturn.WestTile = westTile;
		}

		if (Tile* northTile = GetTileAtGridPos({ gridPosition.x, gridPosition.y - 1 }))
		{
			toReturn.NorthTile = northTile;
		}

		if (Tile* southTile = GetTileAtGridPos({ gridPosition.x, gridPosition.y + 1 }))
		{
			toReturn.SouthTile = southTile;
		}

	}

	return toReturn;
}

Vgameplay::Tile* Vgameplay::GridWorld::GetNeighborhoodTileFromGridPosition(Vengine::VPoint gridPosition, Direction direction) const
{
	switch (direction)
	{
	case Direction::north:
		return  GetTileAtGridPos({ gridPosition.x, gridPosition.y - 1 });
	case Direction::south:
		return GetTileAtGridPos({ gridPosition.x, gridPosition.y + 1 });
	case Direction::east:
		return GetTileAtGridPos({ gridPosition.x + 1, gridPosition.y });
	case Direction::west:
		return GetTileAtGridPos({ gridPosition.x - 1, gridPosition.y });
	}

	return nullptr;
}


Vgameplay::Tile* Vgameplay::GridWorld::GetTileAtGridPos(Vengine::VPoint gridPosition) const
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
	return this->GetTileAtGridPos(GetGridPositionFromWorldPosition(worldPosition));
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
