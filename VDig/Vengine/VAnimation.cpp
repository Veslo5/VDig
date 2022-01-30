#include "VAnimation.h"

Vengine::VAnimation::VAnimation(const std::string& fileName, int columns, int rows, float timePerFrame) :
	Vengine::VAtlas(fileName, columns, rows),
	CurrentFrame(0), timePerFrame(timePerFrame), currentFrameTime(0), totalFrames(columns* rows)
{
}

Vengine::VAnimation::~VAnimation() = default;

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
