#pragma once

#include "VAtlas.h"

namespace Vengine
{
	class VAnimation : public Vengine::VAtlas
	{
	public:
		VAnimation(const std::shared_ptr<raylib::Texture>& texture, float timePerFrame = 0.100f);
		~VAnimation() override = default;

		unsigned int CurrentFrame;

		void CalculatePositions(int columns, int rows) override;

		void Update(float deltaTime);
		void Draw(raylib::Rectangle destRectangle);

	private:
		float timePerFrame;
		float currentFrameTime;
		unsigned int totalFrames;
	};
}
