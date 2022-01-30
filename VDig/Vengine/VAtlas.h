#pragma once
#include "raylib-cpp.hpp"
#include <vector>

namespace Vengine
{
	class VAtlas : public raylib::Texture2D
	{
	public:
		VAtlas(const std::string& fileName, int columns, int rows);
		~VAtlas();

		std::vector<raylib::Rectangle> AtlasPositions;
	};
}