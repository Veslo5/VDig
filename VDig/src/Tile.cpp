#include "Tile.h"

#include <utility>

Vgameplay::Tile::Tile(int gridX, int gridY, int posX, int posY, int size, int atlasPosition) :
	GridPosition(static_cast<float>(gridX), static_cast<float>(gridY)),
	WorldPosition(static_cast<float>(posX), static_cast<float>(posY)),
	Size(size), AtlasPosition(atlasPosition)
{

}
