#include "VAtlas.h"

Vengine::VAtlas::VAtlas(const std::string& fileName, int columns, int rows) : raylib::Texture(fileName)
{
	int tileWidth = this->width / columns;
	int tileHeight = this->height / rows;

	for (int y = 0; y < rows; ++y)
	{
		for (int x = 0; x < columns; ++x)
		{
			AtlasPositions.emplace_back(x * tileWidth, y * tileHeight, tileWidth, tileHeight);
		}
	}

}

Vengine::VAtlas::~VAtlas() = default;
