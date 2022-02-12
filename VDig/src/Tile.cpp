#include "Tile.h"

#include <utility>

Vgameplay::Tile::Tile(raylib::Vector2 gridPosition, raylib::Vector2 worldPosition, int size, int atlasPosition) :
	GridPosition(gridPosition),
	WorldPosition(worldPosition),
	Size(size), AtlasPosition(atlasPosition), Direction(Vgameplay::TileDirection::none)
{

}
