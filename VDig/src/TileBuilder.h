#pragma once

#include <vector>
#include "raylib-cpp.hpp"

namespace Vgameplay
{
	class TileBuilder
	{
	public:
		TileBuilder() = default;
		~TileBuilder() = default;

		std::vector<raylib::Vector2> SelectedTiles;

		void CalculateTiles(raylib::Vector2 currentGridPosition);
		void EndCalculation();

	private:
		raylib::Vector2 defaultStartingPos;
		raylib::Vector2 currentEndingPosition;
		bool isStarted;
	};

}