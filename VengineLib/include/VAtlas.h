#pragma once
#include "raylib-cpp.hpp"
#include <vector>
#include <memory>

namespace Vengine
{
	class VAtlas
	{
	public:
		VAtlas(const std::shared_ptr<raylib::Texture>& texture);
		virtual ~VAtlas() = default;

		virtual void CalculatePositions(int columns, int rows);
		void Draw(unsigned int atlasPosition, const raylib::Vector2& pos) const;

	private:
	protected:
		std::vector<raylib::Rectangle> atlasPositions;
		std::shared_ptr<raylib::Texture> texture;

	};
}