#include "VAnimation.h"

Vengine::VAnimation::VAnimation(const std::shared_ptr<raylib::Texture>& texture, const float timePerFrame) : Vengine::VAtlas(texture),
CurrentFrame(0), timePerFrame(timePerFrame), currentFrameTime(0), totalFrames(0)
{
}


void Vengine::VAnimation::CalculatePositions(int columns, int rows)
{
	totalFrames = columns * rows;
	VAtlas::CalculatePositions(columns, rows);
}

void Vengine::VAnimation::Update(float deltaTime)
{

	currentFrameTime += deltaTime;

	if (currentFrameTime >= timePerFrame)
	{
		currentFrameTime = 0;

		if (CurrentFrame + 1 == totalFrames)
		{
			CurrentFrame = 0;
		}
		else
		{
			CurrentFrame++;
		}
	}
	//CurrentFrame =  static_cast<unsigned int>(deltaTime * 1000) / static_cast<unsigned int>(timePerFrame);
	//CurrentFrame = CurrentFrame % totalFrames;
}

void Vengine::VAnimation::Draw(const raylib::Rectangle destRectangle)
{
	texture->Draw(atlasPositions[CurrentFrame], destRectangle);
}
