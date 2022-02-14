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

		void CalculateTiles(raylib::Vector2 currentGridPosition, Vengine::VAtlas* atlas);
		void EndCalculation();
		int CalculateAtlasIndexForTiling(Vengine::VAtlas* atlas, Vgameplay::SelectedTiles selectedTiles);
		void CalculateTilingForNeighours(Vengine::VAtlas* atlas);

	private:
		raylib::Vector2 defaultStartingPos;
		raylib::Vector2 currentEndingPosition;
		bool isStarted;
	};

}
