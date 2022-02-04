#include "../include/VAtlas.h"

Vengine::VAtlas::VAtlas(const std::shared_ptr<raylib::Texture>& texture) : texture(texture)
{
}

void Vengine::VAtlas::CalculatePositions(int columns, int rows)
{

	int tileWidth = texture->width / columns;
	int tileHeight = texture->height / rows;

	for (int y = 0; y < rows; ++y)
	{
		for (int x = 0; x < columns; ++x)
		{
			atlasPositions.emplace_back(x * tileWidth, y * tileHeight, tileWidth, tileHeight);
		}
	}
}

void Vengine::VAtlas::Draw(const unsigned int atlasPosition, const raylib::Vector2& pos) const
{
	texture->Draw(this->atlasPositions[atlasPosition], pos);
}
