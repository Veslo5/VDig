#pragma once

#include "raylib-cpp.hpp"
#include <memory>

namespace Vgameplay {
	enum class TileDirection { none, up, down, left, right };
	enum class TileType { blank, wall, path };

	class Tile
	{
	public:
		Tile(raylib::Vector2 gridPosition, raylib::Vector2 worldPosition, int size, int atlasPosition = 0);
		~Tile() = default;

		const raylib::Vector2 GridPosition;
		const raylib::Vector2 WorldPosition;
		const int Size;
		int AtlasPosition;
		TileDirection Direction;
		TileType Type;

	private:

	};

}