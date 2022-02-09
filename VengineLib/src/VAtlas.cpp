#include "../include/VAtlas.h"

Vengine::VAtlas::VAtlas(const std::shared_ptr<raylib::Texture>& texture) : texture(texture)
{
}

void Vengine::VAtlas::CalculatePositions(int columns, int rows)
{
	this->Columns = columns;
	this->Rows = rows;

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

int Vengine::VAtlas::GetIndexFromPosition(int column, int row) const
{
	return (row * this->Columns) + column;
}

void Vengine::VAtlas::Draw(const unsigned int atlasPosition, const raylib::Vector2& pos) const
{
	texture->Draw(this->atlasPositions[atlasPosition], pos);
}

void Vengine::VAtlas::Draw(const unsigned int atlasPosition, const raylib::Vector2& pos, raylib::Color color) const
{
	texture->Draw(this->atlasPositions[atlasPosition], pos, color);
}