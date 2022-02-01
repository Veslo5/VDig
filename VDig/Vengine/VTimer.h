#pragma once
#include <functional>

namespace Vengine
{

	class VTimer
	{
	public:
		VTimer(float seconds, std::function<void()> callback, bool repeat);
		~VTimer();

		void Update(float deltaTime);

		void Restart();

	private:

		float startingTime;
		float currentTime;
		const std::function<void()> callback;
		bool repeat;
		bool done;
	};
}