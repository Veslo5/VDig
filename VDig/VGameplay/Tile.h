#pragma once

#include "raylib-cpp.hpp"
#include <memory>

namespace Vgameplay {
	class Tile
	{
	public:
		Tile(int gridX, int gridY, int posX, int posY, int size);
		~Tile();

		const raylib::Vector2 GridPosition;
		const raylib::Vector2 Position;
		const int Size;

	private:

	};

}