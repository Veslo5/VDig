#pragma once

#include "VAtlas.h"

namespace Vengine
{
	class VAnimation : public Vengine::VAtlas
	{
	public:
		VAnimation(const std::string& fileName, int columns, int rows, float timePerFrame);
		~VAnimation();

		unsigned int CurrentFrame;

		void Update(float deltaTime);

	private:
		float timePerFrame;
		float currentFrameTime;
		unsigned int totalFrames;
	};
}
