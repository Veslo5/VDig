#include "VTimer.h"

Vengine::VTimer::VTimer(float seconds, std::function<void()> callback, bool repeat) : startingTime(seconds), currentTime(seconds), callback(callback), repeat(repeat), done(false)
{

}

Vengine::VTimer::~VTimer() = default;


void Vengine::VTimer::Update(float deltaTime)
{
	if (done == false)
	{

		currentTime -= deltaTime;

		if (currentTime <= 0)
		{
			callback();

			if (repeat == true)
			{
				currentTime = startingTime;
			}
			else
			{
				done = true;
			}

		}
	}
}

void Vengine::VTimer::Restart()
{
	done = false;
	currentTime = startingTime;
}


