#pragma once

#include <vector>
#include "GridWorld.h"
#include "raylib-cpp.hpp"
#include "VAtlas.h"

namespace Vgameplay
{
	class TileBuilder
	{
	public:
		TileBuilder() = default;
		~TileBuilder() = default;

		std::vector<Tile> SelectedTiles;

		void CalculateTiles(Vengine::VPoint currentGridPosition, Vengine::VAtlas* atlas);
		void EndCalculation();
		int CalculateAtlasIndexForTiling(Vengine::VAtlas* atlas, Vgameplay::SelectedTiles selectedTiles);
		void CalculateTilingForNeighours(Vengine::VAtlas* atlas);

	private:
		Vengine::VPoint defaultStartingPos;
		Vengine::VPoint currentEndingPosition;
		bool isStarted;
	};

}
