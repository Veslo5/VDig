#pragma once

#include "Tile.h"
#include <vector>
#include <memory>


namespace Vgameplay
{
	class GridWorld
	{
	public:
		GridWorld(int width, int height, int size, int spacing);
		~GridWorld() = default;

		const int TilesSize;
		int Width;
		int Height;

		std::vector<std::shared_ptr<Tile>> TileWorld;
		std::weak_ptr<Tile> GetTileAtPos(int x, int y);
		std::weak_ptr<Tile> GetTileAtWorldPos(int x, int y);

	private:
	};


}