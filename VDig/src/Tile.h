#pragma once

#include "raylib-cpp.hpp"
#include "VPoint.h"
#include <memory>


namespace Vgameplay {
	enum class TileDirection { none, up, down, left, right };
	enum class TileType { blank, wall, path };

	class Tile
	{
	public:
		Tile(Vengine::VPoint gridPosition, raylib::Vector2 worldPosition, int size, int atlasPosition = 0);
		~Tile() = default;

		const Vengine::VPoint GridPosition;
		const raylib::Vector2 WorldPosition;
		const int Size;
		int AtlasPosition;
		TileDirection Direction;
		TileType Type;

	private:

	};

}
