#pragma once

#include "raylib-cpp.hpp"
#include <memory>

namespace Vgameplay {
	class Tile
	{
	public:
		Tile(int gridX, int gridY, int posX, int posY, int size, int atlasPosition = 0);
		~Tile() = default;

		const raylib::Vector2 GridPosition;
		const raylib::Vector2 WorldPosition;
		const int Size;
		int AtlasPosition;

	private:

	};

}