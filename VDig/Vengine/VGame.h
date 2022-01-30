#pragma once

#include "SceneManager.h"
#include "raylib-cpp.hpp"

namespace Vengine {
	class VGame
	{
	public:
		VGame(int width, int height, std::string caption, raylib::Color clearColor);
		~VGame();

		int WindowWidth, WindowHeight;
		std::string Caption;
		raylib::Color ClearColor;
		raylib::Window Window;

		SceneManager SceneManager;
		
		raylib::Camera2D Camera;

		void Run();

	private:

	};
}
